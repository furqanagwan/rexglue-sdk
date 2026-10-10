/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include "thirdparty/dxbc/DXBCChecksum.h"

#include <algorithm>
#include <atomic>
#include <cinttypes>
#include <cmath>
#include <cstring>
#include <deque>
#include <mutex>
#include <set>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include <rex/assert.h>
#include <rex/chrono/clock.h>
#if REXGLUE_SHADER_DXIL
#include <rex/graphics/pipeline/shader/spirv_builtin_geometry_shader.h>
#include <rex/graphics/pipeline/shader/spirv_to_dxil_compiler.h>
#include <rex/graphics/pipeline/shader/spirv_translator.h>
#endif
#include <rex/cvar.h>
#include <rex/dbg.h>
#include <rex/perf/counter.h>
#include <rex/filesystem.h>
#include <rex/graphics/d3d12/command_processor.h>
#include <rex/graphics/d3d12/pipeline_cache.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/storage_seed.h>
#include <rex/graphics/format/dxbc.h>
#include <rex/graphics/pipeline_util.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/hash.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string.h>
#include <rex/string/buffer.h>
#include <rex/thread.h>
#include <rex/types.h>
#include <rex/ui/d3d12/d3d12_util.h>

REXCVAR_DEFINE_BOOL(d3d12_dxbc_disasm, false, "GPU/D3D12", "Dump DXBC disassembly");

REXCVAR_DEFINE_BOOL(d3d12_dxbc_disasm_dxilconv, false, "GPU/D3D12",
                    "Dump DXIL conversion disassembly");

REXCVAR_DEFINE_INT32(d3d12_pipeline_creation_threads, -1, "GPU/D3D12",
                     "Number of pipeline creation threads (-1 for auto)")
    .range(-1, 32)
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_STRING(shader_cache_shipped, "", "GPU",
                      "Folder of the shader cache shipped with the title (empty: shader_cache "
                      "beside the executable); seeds this PC's cache at startup");
REXCVAR_DEFINE_BOOL(shader_replacements, false, "GPU",
                    "Use the title's replacement shaders (shader_replacements beside the "
                    "executable) in place of the translated ones they name")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);
REXCVAR_DEFINE_BOOL(d3d12_tessellation_wireframe, false, "GPU/D3D12",
                    "Render tessellation as wireframe");

namespace rex::graphics::d3d12 {

namespace shaders {
#include "../shaders/bytecode/d3d12_5_1/adaptive_quad_hs.h"
#include "../shaders/bytecode/d3d12_5_1/adaptive_triangle_hs.h"
#include "../shaders/bytecode/d3d12_5_1/continuous_quad_1cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/continuous_quad_4cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/continuous_triangle_1cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/continuous_triangle_3cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/discrete_quad_1cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/discrete_quad_4cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/discrete_triangle_1cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/discrete_triangle_3cp_hs.h"
#include "../shaders/bytecode/d3d12_5_1/float24_round_ps.h"
#include "../shaders/bytecode/d3d12_5_1/float24_truncate_ps.h"
#include "../shaders/bytecode/d3d12_5_1/tessellation_adaptive_vs.h"
#include "../shaders/bytecode/d3d12_5_1/tessellation_indexed_vs.h"
}

PipelineCache::PipelineCache(D3D12CommandProcessor& command_processor,
                             const RegisterFile& register_file,
                             const D3D12RenderTargetCache& render_target_cache,
                             bool bindless_resources_used, bool zpd_hybrid_supported)
    : command_processor_(command_processor),
      register_file_(register_file),
      render_target_cache_(render_target_cache),
      bindless_resources_used_(bindless_resources_used),
      zpd_hybrid_supported_(zpd_hybrid_supported) {
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();

  bool edram_rov_used =
      render_target_cache.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;

  shader_translator_ = std::make_unique<DxbcShaderTranslator>(
      provider.GetAdapterVendorID(), bindless_resources_used_, edram_rov_used,
      !render_target_cache_.gamma_render_target_as_unorm16(),
      render_target_cache_.msaa_2x_supported(), render_target_cache_.draw_resolution_scale_x(),
      render_target_cache_.draw_resolution_scale_y(), provider.GetGraphicsAnalysis() != nullptr);

  depth_only_pixel_shader_ = std::move(shader_translator_->CreateDepthOnlyPixelShader());
  if (edram_rov_used) {
    using DepthStencilMode = DxbcShaderTranslator::Modification::DepthStencilMode;
    viz_survey_depth_only_pixel_shader_ = std::move(shader_translator_->CreateDepthOnlyPixelShader(
        false, DepthStencilMode::kNoModifiers, true));
  }
  if (!edram_rov_used && zpd_hybrid_supported_) {
    using DepthStencilMode = DxbcShaderTranslator::Modification::DepthStencilMode;
    zpd_total_depth_only_pixel_shader_ =
        std::move(shader_translator_->CreateDepthOnlyPixelShader(true));
    if (render_target_cache_.depth_float24_convert_in_pixel_shader()) {
      zpd_total_float24_truncate_pixel_shader_ =
          std::move(shader_translator_->CreateDepthOnlyPixelShader(
              true, DepthStencilMode::kFloat24Truncating));
      zpd_total_float24_round_pixel_shader_ = std::move(
          shader_translator_->CreateDepthOnlyPixelShader(true, DepthStencilMode::kFloat24Rounding));
    }
  }
}

PipelineCache::~PipelineCache() {
  Shutdown();
}

bool PipelineCache::Initialize() {
  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();

  if (REXCVAR_GET(shader_replacements)) {
    const std::filesystem::path folder =
        rex::filesystem::GetExecutableFolder() / "shader_replacements";
    const size_t count = shader_replacements_.Load(folder);
    REXGPU_INFO("Shader replacements: {} from {}", count, rex::path_to_utf8(folder));
  }

  dxbc_converter_ = nullptr;
  dxc_utils_ = nullptr;
  dxc_compiler_ = nullptr;
  if (REXCVAR_GET(d3d12_dxbc_disasm_dxilconv)) {
    if (FAILED(provider.DxbcConverterCreateInstance(CLSID_DxbcConverter,
                                                    IID_PPV_ARGS(&dxbc_converter_)))) {
      REXGPU_ERROR(
          "Failed to create DxbcConverter, converted DXIL disassembly for "
          "debugging will be unavailable");
    }
    if (FAILED(provider.DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxc_utils_)))) {
      REXGPU_ERROR(
          "Failed to create DxcUtils, converted DXIL disassembly for debugging "
          "will be unavailable");
    }
    if (FAILED(provider.DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxc_compiler_)))) {
      REXGPU_ERROR(
          "Failed to create DxcCompiler, converted DXIL disassembly for "
          "debugging will be unavailable");
    }
  }

  uint32_t logical_processor_count = rex::thread::logical_processor_count();
  if (!logical_processor_count) {
    logical_processor_count = 6;
  }

  creation_threads_busy_ = 0;
  creation_completion_event_ = rex::thread::Event::CreateManualResetEvent(true);
  assert_not_null(creation_completion_event_);
  creation_completion_set_event_ = false;
  creation_threads_shutdown_from_ = SIZE_MAX;
  if (REXCVAR_GET(d3d12_pipeline_creation_threads) != 0) {
    size_t creation_thread_count;
    if (REXCVAR_GET(d3d12_pipeline_creation_threads) < 0) {
      creation_thread_count = std::max(logical_processor_count * 3 / 4, uint32_t(1));
    } else {
      creation_thread_count =
          std::min(uint32_t(REXCVAR_GET(d3d12_pipeline_creation_threads)), logical_processor_count);
    }
    for (size_t i = 0; i < creation_thread_count; ++i) {
      std::unique_ptr<rex::thread::Thread> creation_thread =
          rex::thread::Thread::Create({}, [this, i]() { CreationThread(i); });
      assert_not_null(creation_thread);
      creation_thread->set_name("D3D12 Pipelines");

      creation_thread->set_priority(rex::thread::ThreadPriority::kBelowNormal);
      creation_threads_.push_back(std::move(creation_thread));
    }
  }

#if REXGLUE_SHADER_DXIL
  if (REXCVAR_GET(gpu_shader_path) == "dxil") {
    const char* unsupported = nullptr;
    if (!command_processor_.bindless_resources_used()) {
      unsupported = "it needs bindless resources";
    } else if (provider.GetHighestShaderModel() < D3D_SHADER_MODEL_6_6) {
      unsupported = "the adapter is below Shader Model 6.6";
    } else if (!command_processor_.GetDxilRootSignature()) {
      unsupported = "its root signature couldn't be created";
    } else if (!SpirvToDxilCompiler::IsSignerAvailable()) {
      unsupported = "dxil.dll can't sign DXIL";
    }
    if (unsupported) {
      REXGPU_WARN("gpu_shader_path=dxil unavailable ({}); using DXBC", unsupported);
    } else {
      dxil_shader_cache_host_ = std::make_unique<DxilShaderCacheHost>(*this);
      dxil_shader_cache_ = std::make_unique<GuestSpirvShaderCache>(
          *dxil_shader_cache_host_, register_file_, render_target_cache_);
      if (!dxil_shader_cache_->Initialize()) {
        REXGPU_WARN("gpu_shader_path=dxil: no SPIR-V translator; using DXBC");
        dxil_shader_cache_.reset();
      } else if (!InitializeDxilHelperPixelShaders()) {
        REXGPU_WARN("gpu_shader_path=dxil: no helper pixel shaders; using DXBC");
        dxil_shader_cache_.reset();
      } else {
        REXGPU_INFO("Guest shaders: SPIR-V -> DXIL (xenia-edge translator, Mesa spirv_to_dxil)");
      }
    }
  }
#endif
  return true;
}

void PipelineCache::Shutdown() {
  if (!creation_threads_.empty()) {
    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);
      creation_threads_shutdown_from_ = 0;
    }
    creation_request_cond_.notify_all();
    for (size_t i = 0; i < creation_threads_.size(); ++i) {
      rex::thread::Wait(creation_threads_[i].get(), false);
    }
    creation_threads_.clear();
  }
  creation_completion_event_.reset();

  ShutdownShaderStorage();

  current_pipeline_ = nullptr;
  for (auto it : pipelines_) {
    ID3D12PipelineState* state = it.second->state.load(std::memory_order_acquire);
    if (state) {
      state->Release();
    }
    delete it.second;
  }
  pipelines_.clear();
  COUNT_profile_set("gpu/pipeline_cache/pipelines", 0);

  if (bindless_resources_used_) {
    bindless_sampler_layout_map_.clear();
    bindless_sampler_layouts_.clear();
  }
  texture_binding_layout_map_.clear();
  texture_binding_layouts_.clear();
  for (auto it : shaders_) {
    delete it.second;
  }
  shaders_.clear();
  shader_storage_index_ = 0;

  ui::d3d12::util::ReleaseAndNull(dxc_compiler_);
  ui::d3d12::util::ReleaseAndNull(dxc_utils_);
  ui::d3d12::util::ReleaseAndNull(dxbc_converter_);
}

void PipelineCache::EndSubmission() {
  if (shader_storage_file_flush_needed_ || pipeline_storage_file_flush_needed_) {
    {
      std::lock_guard<std::mutex> lock(storage_write_request_lock_);
      if (shader_storage_file_flush_needed_) {
        storage_write_flush_shaders_ = true;
      }
      if (pipeline_storage_file_flush_needed_) {
        storage_write_flush_pipelines_ = true;
      }
    }
    storage_write_request_cond_.notify_one();
    shader_storage_file_flush_needed_ = false;
    pipeline_storage_file_flush_needed_ = false;
  }
  if (!creation_threads_.empty() && REXCVAR_GET(async_shader_compilation)) {
    creation_request_cond_.notify_one();
  } else if (!creation_threads_.empty()) {
    CreateQueuedPipelinesOnProcessorThread();

    bool await_creation_completion_event;
    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);

      await_creation_completion_event = creation_threads_busy_ != 0;
      if (await_creation_completion_event) {
        creation_completion_event_->Reset();
        creation_completion_set_event_ = true;
      }
    }
    if (await_creation_completion_event) {
      creation_request_cond_.notify_one();
      rex::thread::Wait(creation_completion_event_.get(), false);
    }
  }
}

void PipelineCache::AwaitPipeline(void* handle) {
  auto* pipeline = reinterpret_cast<Pipeline*>(handle);
  if (!pipeline->creation_pending.load(std::memory_order_acquire)) {
    return;
  }
  if (!pipeline->creation_claimed.exchange(true, std::memory_order_acq_rel)) {
    PipelineRuntimeDescription runtime_description;
    pipeline->state.store(PrepareRuntimeDescriptionForQueuedCreation(pipeline, runtime_description)
                              ? CreateD3D12Pipeline(runtime_description)
                              : nullptr,
                          std::memory_order_release);
    pipeline->creation_pending.store(false, std::memory_order_release);
    return;
  }

  while (pipeline->creation_pending.load(std::memory_order_acquire)) {
    std::this_thread::yield();
  }
}

void PipelineCache::AwaitQueuedPipelines() {
  if (creation_threads_.empty()) {
    return;
  }
  CreateQueuedPipelinesOnProcessorThread();
  AwaitPipelineCompletion();
}

bool PipelineCache::IsCreatingPipelines() {
  if (creation_threads_.empty()) {
    return false;
  }
  std::lock_guard<std::mutex> lock(creation_request_lock_);
  return !creation_queue_.empty() || creation_threads_busy_ != 0;
}

void PipelineCache::AwaitPipelineCompletion() {
  if (creation_threads_.empty()) {
    return;
  }

  bool await_creation_completion_event;
  {
    std::lock_guard<std::mutex> lock(creation_request_lock_);
    await_creation_completion_event = !creation_queue_.empty() || creation_threads_busy_ != 0;
    if (await_creation_completion_event) {
      creation_completion_event_->Reset();
      creation_completion_set_event_ = true;
    }
  }

  if (await_creation_completion_event) {
    creation_request_cond_.notify_one();
    rex::thread::Wait(creation_completion_event_.get(), false);
  }
}

D3D12Shader* PipelineCache::LoadShader(xenos::ShaderType shader_type, const uint32_t* host_address,
                                       uint32_t dword_count) {
  return LoadShader(shader_type, host_address, dword_count,
                    XXH3_64bits(host_address, dword_count * sizeof(uint32_t)));
}

D3D12Shader* PipelineCache::LoadShader(xenos::ShaderType shader_type, const uint32_t* host_address,
                                       uint32_t dword_count, uint64_t data_hash) {
  auto it = shaders_.find(data_hash);
  if (it != shaders_.end()) {
    return it->second;
  }

  D3D12Shader* shader = new D3D12Shader(shader_type, data_hash, host_address, dword_count);
  shaders_.emplace(data_hash, shader);
  return shader;
}

DxbcShaderTranslator::Modification PipelineCache::GetCurrentVertexShaderModification(
    const Shader& shader, Shader::HostVertexShaderType host_vertex_shader_type,
    uint32_t interpolator_mask) const {
  assert_true(shader.type() == xenos::ShaderType::kVertex);
  assert_true(shader.is_ucode_analyzed());
  const auto& regs = register_file_;

  DxbcShaderTranslator::Modification modification(
      shader_translator_->GetDefaultVertexShaderModification(
          shader.GetDynamicAddressableRegisterCount(regs.Get<reg::SQ_PROGRAM_CNTL>().vs_num_reg),
          host_vertex_shader_type));

  modification.vertex.interpolator_mask = interpolator_mask;

  auto pa_cl_clip_cntl = regs.Get<reg::PA_CL_CLIP_CNTL>();
  uint32_t user_clip_planes = pa_cl_clip_cntl.clip_disable ? 0 : pa_cl_clip_cntl.ucp_ena;
  modification.vertex.user_clip_plane_count = rex::bit_count(user_clip_planes);
  modification.vertex.user_clip_plane_cull =
      uint32_t(user_clip_planes && pa_cl_clip_cntl.ucp_cull_only_ena);
  modification.vertex.point_ps_ucp_mode = pa_cl_clip_cntl.ps_ucp_mode;
  modification.vertex.vertex_kill_and = uint32_t(
      (shader.writes_point_size_edge_flag_kill_vertex() & 0b100) && !pa_cl_clip_cntl.vtx_kill_or);

  modification.vertex.output_point_size =
      uint32_t((shader.writes_point_size_edge_flag_kill_vertex() & 0b001) &&
               regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type == xenos::PrimitiveType::kPointList);

  return modification;
}

DxbcShaderTranslator::Modification PipelineCache::GetCurrentPixelShaderModification(
    const Shader& shader, uint32_t interpolator_mask, uint32_t param_gen_pos,
    reg::RB_DEPTHCONTROL normalized_depth_control) const {
  assert_true(shader.type() == xenos::ShaderType::kPixel);
  assert_true(shader.is_ucode_analyzed());
  const auto& regs = register_file_;

  DxbcShaderTranslator::Modification modification(
      shader_translator_->GetDefaultPixelShaderModification(
          shader.GetDynamicAddressableRegisterCount(regs.Get<reg::SQ_PROGRAM_CNTL>().ps_num_reg)));

  modification.pixel.interpolator_mask = interpolator_mask;
  modification.pixel.interpolators_centroid =
      interpolator_mask & ~xenos::GetInterpolatorSamplingPattern(
                              regs.Get<reg::RB_SURFACE_INFO>().msaa_samples,
                              regs.Get<reg::SQ_CONTEXT_MISC>().sc_sample_cntl,
                              regs.Get<reg::SQ_INTERPOLATOR_CNTL>().sampling_pattern);

  if (param_gen_pos < xenos::kMaxInterpolators) {
    modification.pixel.param_gen_enable = 1;
    modification.pixel.param_gen_interpolator = param_gen_pos;
    modification.pixel.param_gen_point =
        uint32_t(regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type == xenos::PrimitiveType::kPointList);
  } else {
    modification.pixel.param_gen_enable = 0;
    modification.pixel.param_gen_interpolator = 0;
    modification.pixel.param_gen_point = 0;
  }

  if (render_target_cache_.GetPath() == RenderTargetCache::Path::kHostRenderTargets) {
    using DepthStencilMode = DxbcShaderTranslator::Modification::DepthStencilMode;
    if (render_target_cache_.depth_float24_convert_in_pixel_shader() &&
        normalized_depth_control.z_enable &&
        regs.Get<reg::RB_DEPTH_INFO>().depth_format == xenos::DepthRenderTargetFormat::kD24FS8) {
      modification.pixel.depth_stencil_mode = render_target_cache_.depth_float24_round()
                                                  ? DepthStencilMode::kFloat24Rounding
                                                  : DepthStencilMode::kFloat24Truncating;
    } else {
      if (shader.implicit_early_z_write_allowed() &&
          (!shader.writes_color_target(0) ||
           !draw_util::DoesCoverageDependOnAlpha(regs.Get<reg::RB_COLORCONTROL>()))) {
        modification.pixel.depth_stencil_mode = DepthStencilMode::kEarlyHint;
      } else {
        modification.pixel.depth_stencil_mode = DepthStencilMode::kNoModifiers;
      }
    }
  }

  return modification;
}

bool PipelineCache::ConfigurePipeline(
    D3D12Shader::D3D12Translation* vertex_shader, D3D12Shader::D3D12Translation* pixel_shader,
    const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
    reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask, bool zpd_total,
    bool viz_survey, uint32_t bound_depth_and_color_render_target_bits,
    const uint32_t* bound_depth_and_color_render_target_formats, void** pipeline_handle_out,
    ID3D12RootSignature** root_signature_out) {
#if XE_GPU_FINE_GRAINED_DRAW_SCOPES
  SCOPE_profile_cpu_f("gpu");
#endif

  assert_not_null(pipeline_handle_out);
  assert_not_null(root_signature_out);

  bool use_async = REXCVAR_GET(async_shader_compilation) && !creation_threads_.empty() &&
                   pixel_shader != nullptr;

  assert_true(register_file_.Get<reg::SQ_PROGRAM_CNTL>().vs_export_mode !=
                  xenos::VertexShaderExportMode::kPosition2VectorsEdge &&
              register_file_.Get<reg::SQ_PROGRAM_CNTL>().vs_export_mode !=
                  xenos::VertexShaderExportMode::kPosition2VectorsEdgeKill);
  assert_false(register_file_.Get<reg::SQ_PROGRAM_CNTL>().gen_index_vtx);

  if (!vertex_shader->shader().is_ucode_analyzed()) {
    vertex_shader->shader().AnalyzeUcode(ucode_disasm_buffer_);
  }
  if (!vertex_shader->is_translated() && !use_async) {
    std::lock_guard<std::mutex> lock(translation_request_lock_);
    if (!vertex_shader->is_translated()) {
      if (!TranslateAnalyzedShader(*shader_translator_, *vertex_shader, dxbc_converter_, dxc_utils_,
                                   dxc_compiler_)) {
        REXGPU_ERROR("Failed to translate the vertex shader!");
        return false;
      }
      if (shader_storage_file_ &&
          vertex_shader->shader().ucode_storage_index() != shader_storage_index_) {
        vertex_shader->shader().set_ucode_storage_index(shader_storage_index_);
        assert_not_null(storage_write_thread_);
        shader_storage_file_flush_needed_ = true;
        {
          std::lock_guard<std::mutex> storage_lock(storage_write_request_lock_);
          storage_write_shader_queue_.push_back(&vertex_shader->shader());
        }
        storage_write_request_cond_.notify_all();
      }
    }
  }
  if (!use_async && !vertex_shader->is_valid()) {
    return false;
  }
  if (pixel_shader != nullptr) {
    if (!pixel_shader->is_translated() && !use_async) {
      std::lock_guard<std::mutex> lock(translation_request_lock_);
      if (!pixel_shader->is_translated()) {
        pixel_shader->shader().AnalyzeUcode(ucode_disasm_buffer_);
        if (!TranslateAnalyzedShader(*shader_translator_, *pixel_shader, dxbc_converter_,
                                     dxc_utils_, dxc_compiler_)) {
          REXGPU_ERROR("Failed to translate the pixel shader!");
          return false;
        }
        if (shader_storage_file_ &&
            pixel_shader->shader().ucode_storage_index() != shader_storage_index_) {
          pixel_shader->shader().set_ucode_storage_index(shader_storage_index_);
          assert_not_null(storage_write_thread_);
          shader_storage_file_flush_needed_ = true;
          {
            std::lock_guard<std::mutex> storage_lock(storage_write_request_lock_);
            storage_write_shader_queue_.push_back(&pixel_shader->shader());
          }
          storage_write_request_cond_.notify_all();
        }
      }
    }
    if (pixel_shader->is_translated() && !pixel_shader->is_valid()) {
      return false;
    }
  }

  PipelineRuntimeDescription runtime_description;
  if (!GetCurrentStateDescription(
          vertex_shader, pixel_shader, primitive_processing_result, normalized_depth_control,
          normalized_color_mask, zpd_total, viz_survey, bound_depth_and_color_render_target_bits,
          bound_depth_and_color_render_target_formats, runtime_description, use_async)) {
    return false;
  }
  PipelineDescription& description = runtime_description.description;

  if (current_pipeline_ != nullptr && !std::memcmp(&current_pipeline_->description.description,
                                                   &description, sizeof(description))) {
    *pipeline_handle_out = current_pipeline_;
    *root_signature_out = current_pipeline_->root_signature.load(std::memory_order_acquire);
    return true;
  }

  uint64_t hash = XXH3_64bits(&description, sizeof(description));
  auto found_range = pipelines_.equal_range(hash);
  for (auto it = found_range.first; it != found_range.second; ++it) {
    Pipeline* found_pipeline = it->second;
    if (!std::memcmp(&found_pipeline->description.description, &description, sizeof(description))) {
      PROFILE_PIPELINE_CACHE_HIT();
      current_pipeline_ = found_pipeline;
      *pipeline_handle_out = found_pipeline;
      *root_signature_out = found_pipeline->root_signature.load(std::memory_order_acquire);
      return true;
    }
  }
  PROFILE_PIPELINE_CACHE_MISS();

  Pipeline* new_pipeline = new Pipeline;
  std::memcpy(&new_pipeline->description, &runtime_description, sizeof(runtime_description));
  new_pipeline->root_signature.store(runtime_description.root_signature, std::memory_order_release);
  pipelines_.emplace(hash, new_pipeline);
  COUNT_profile_set("gpu/pipeline_cache/pipelines", pipelines_.size());

  if (use_async) {
    uint32_t bound_rts =
        pipeline_util::GetBoundRTMaskFromNormalizedColorMask(normalized_color_mask);
    uint32_t shader_writes_color_targets =
        pixel_shader ? pixel_shader->shader().writes_color_targets() : 0;
    bool shader_writes_depth = pixel_shader ? pixel_shader->shader().writes_depth()
                                            : normalized_depth_control.z_write_enable != 0;
    new_pipeline->priority = pipeline_util::CalculatePipelinePriority(
        bound_rts, shader_writes_color_targets, shader_writes_depth);
    new_pipeline->pending_vertex_shader = vertex_shader;
    new_pipeline->pending_pixel_shader = pixel_shader;

    new_pipeline->creation_pending.store(true, std::memory_order_relaxed);
    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);
      creation_queue_.push(new_pipeline);
    }
    creation_request_cond_.notify_one();
  } else {
    new_pipeline->state.store(CreateD3D12Pipeline(runtime_description), std::memory_order_release);
  }

  if (pipeline_storage_file_) {
    assert_not_null(storage_write_thread_);
    pipeline_storage_file_flush_needed_ = true;
    {
      std::lock_guard<std::mutex> lock(storage_write_request_lock_);
      storage_write_pipeline_queue_.emplace_back();
      PipelineStoredDescription& stored_description = storage_write_pipeline_queue_.back();
      stored_description.description_hash = hash;
      std::memcpy(&stored_description.description, &description, sizeof(description));
    }
    storage_write_request_cond_.notify_all();
  }

  current_pipeline_ = new_pipeline;
  *pipeline_handle_out = new_pipeline;
  *root_signature_out = new_pipeline->root_signature.load(std::memory_order_acquire);
  return true;
}

bool PipelineCache::TranslateAnalyzedShader(DxbcShaderTranslator& translator,
                                            D3D12Shader::D3D12Translation& translation,
                                            IDxbcConverter* dxbc_converter, IDxcUtils* dxc_utils,
                                            IDxcCompiler* dxc_compiler) {
  D3D12Shader& shader = static_cast<D3D12Shader&>(translation.shader());

  if (!translator.TranslateAnalyzedShader(translation)) {
    REXGPU_ERROR("Shader {:016X} translation failed; marking as ignored", shader.ucode_data_hash());
    translation.PublishTranslated();
    return false;
  }

  if (!shader_replacements_.empty()) {
    const bool is_vertex = shader.type() == xenos::ShaderType::kVertex;
    const bool replaceable =
        !is_vertex ||
        DxbcShaderTranslator::Modification(translation.modification())
                .vertex.host_vertex_shader_type == Shader::HostVertexShaderType::kVertex;
    const ShaderReplacements::Stage stage =
        is_vertex ? ShaderReplacements::Stage::kVertex
        : render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock
            ? ShaderReplacements::Stage::kPixelRov
            : ShaderReplacements::Stage::kPixelRtv;
    if (const std::vector<uint8_t>* replacement =
            replaceable ? shader_replacements_.Find(shader.ucode_data_hash(), stage,
                                                    translation.modification())
                        : nullptr) {
      REXGPU_INFO("Shader {:016X} (modification {:016X}): title replacement used",
                  shader.ucode_data_hash(), translation.modification());
      translation.ReplaceTranslatedBinary(*replacement);
    }
  }

  const char* host_shader_type;
  if (shader.type() == xenos::ShaderType::kVertex) {
    DxbcShaderTranslator::Modification modification(translation.modification());
    switch (modification.vertex.host_vertex_shader_type) {
      case Shader::HostVertexShaderType::kLineDomainCPIndexed:
        host_shader_type = "control-point-indexed line domain";
        break;
      case Shader::HostVertexShaderType::kLineDomainPatchIndexed:
        host_shader_type = "patch-indexed line domain";
        break;
      case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
        host_shader_type = "control-point-indexed triangle domain";
        break;
      case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
        host_shader_type = "patch-indexed triangle domain";
        break;
      case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
        host_shader_type = "control-point-indexed quad domain";
        break;
      case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
        host_shader_type = "patch-indexed quad domain";
        break;
      default:
        assert(modification.vertex.host_vertex_shader_type ==
               Shader::HostVertexShaderType::kVertex);
        host_shader_type = "vertex";
    }
  } else {
    host_shader_type = "pixel";
  }
  REXGPU_NOISY_DEBUG("Generated {} shader ({}b) - hash {:016X}:\n{}\n", host_shader_type,
                     shader.ucode_dword_count() * sizeof(uint32_t), shader.ucode_data_hash(),
                     shader.ucode_disassembly().c_str());

  if (shader.EnterBindingLayoutUserUIDSetup()) {
    const std::vector<D3D12Shader::TextureBinding>& texture_bindings =
        shader.GetTextureBindingsAfterTranslation();
    size_t texture_binding_count = texture_bindings.size();
    const std::vector<D3D12Shader::SamplerBinding>& sampler_bindings =
        shader.GetSamplerBindingsAfterTranslation();
    size_t sampler_binding_count = sampler_bindings.size();
    assert_false(bindless_resources_used_ && texture_binding_count + sampler_binding_count >
                                                 D3D12_REQ_CONSTANT_BUFFER_ELEMENT_COUNT * 4);
    size_t texture_binding_layout_bytes = texture_binding_count * sizeof(*texture_bindings.data());
    uint64_t texture_binding_layout_hash = 0;
    if (texture_binding_count) {
      texture_binding_layout_hash =
          XXH3_64bits(texture_bindings.data(), texture_binding_layout_bytes);
    }
    size_t bindless_sampler_count = bindless_resources_used_ ? sampler_binding_count : 0;
    uint64_t bindless_sampler_layout_hash = 0;
    if (bindless_sampler_count) {
      XXH3_state_t hash_state;
      XXH3_64bits_reset(&hash_state);
      for (size_t i = 0; i < bindless_sampler_count; ++i) {
        XXH3_64bits_update(&hash_state, &sampler_bindings[i].bindless_descriptor_index,
                           sizeof(sampler_bindings[i].bindless_descriptor_index));
      }
      bindless_sampler_layout_hash = XXH3_64bits_digest(&hash_state);
    }

    size_t texture_binding_layout_uid = kLayoutUIDEmpty;

    static_assert(kLayoutUIDEmpty == 0,
                  "Empty layout UID is assumed to be 0 because for bindful samplers, the "
                  "UID is their count");
    size_t sampler_binding_layout_uid =
        bindless_resources_used_ ? kLayoutUIDEmpty : sampler_binding_count;
    if (texture_binding_count || bindless_sampler_count) {
      std::lock_guard<std::mutex> layouts_lock(layouts_mutex_);
      if (texture_binding_count) {
        auto found_range = texture_binding_layout_map_.equal_range(texture_binding_layout_hash);
        for (auto it = found_range.first; it != found_range.second; ++it) {
          if (it->second.vector_span_length == texture_binding_count &&
              !std::memcmp(texture_binding_layouts_.data() + it->second.vector_span_offset,
                           texture_bindings.data(), texture_binding_layout_bytes)) {
            texture_binding_layout_uid = it->second.uid;
            break;
          }
        }
        if (texture_binding_layout_uid == kLayoutUIDEmpty) {
          static_assert(kLayoutUIDEmpty == 0,
                        "Layout UID is size + 1 because it's assumed that 0 is the UID "
                        "for an empty layout");
          texture_binding_layout_uid = texture_binding_layout_map_.size() + 1;
          LayoutUID new_uid;
          new_uid.uid = texture_binding_layout_uid;
          new_uid.vector_span_offset = texture_binding_layouts_.size();
          new_uid.vector_span_length = texture_binding_count;
          texture_binding_layouts_.resize(new_uid.vector_span_offset + texture_binding_count);
          std::memcpy(texture_binding_layouts_.data() + new_uid.vector_span_offset,
                      texture_bindings.data(), texture_binding_layout_bytes);
          texture_binding_layout_map_.emplace(texture_binding_layout_hash, new_uid);
        }
      }
      if (bindless_sampler_count) {
        auto found_range = bindless_sampler_layout_map_.equal_range(sampler_binding_layout_uid);
        for (auto it = found_range.first; it != found_range.second; ++it) {
          if (it->second.vector_span_length != bindless_sampler_count) {
            continue;
          }
          sampler_binding_layout_uid = it->second.uid;
          const uint32_t* vector_bindless_sampler_layout =
              bindless_sampler_layouts_.data() + it->second.vector_span_offset;
          for (size_t i = 0; i < bindless_sampler_count; ++i) {
            if (vector_bindless_sampler_layout[i] !=
                sampler_bindings[i].bindless_descriptor_index) {
              sampler_binding_layout_uid = kLayoutUIDEmpty;
              break;
            }
          }
          if (sampler_binding_layout_uid != kLayoutUIDEmpty) {
            break;
          }
        }
        if (sampler_binding_layout_uid == kLayoutUIDEmpty) {
          sampler_binding_layout_uid = bindless_sampler_layout_map_.size();
          LayoutUID new_uid;
          static_assert(kLayoutUIDEmpty == 0,
                        "Layout UID is size + 1 because it's assumed that 0 is the UID "
                        "for an empty layout");
          new_uid.uid = sampler_binding_layout_uid + 1;
          new_uid.vector_span_offset = bindless_sampler_layouts_.size();
          new_uid.vector_span_length = sampler_binding_count;
          bindless_sampler_layouts_.resize(new_uid.vector_span_offset + sampler_binding_count);
          uint32_t* vector_bindless_sampler_layout =
              bindless_sampler_layouts_.data() + new_uid.vector_span_offset;
          for (size_t i = 0; i < bindless_sampler_count; ++i) {
            vector_bindless_sampler_layout[i] = sampler_bindings[i].bindless_descriptor_index;
          }
          bindless_sampler_layout_map_.emplace(bindless_sampler_layout_hash, new_uid);
        }
      }
    }
    shader.SetTextureBindingLayoutUserUID(texture_binding_layout_uid);
    shader.SetSamplerBindingLayoutUserUID(sampler_binding_layout_uid);
  }

  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  if (REXCVAR_GET(d3d12_dxbc_disasm_dxilconv)) {
    translation.DisassembleDxbcAndDxil(provider, REXCVAR_GET(d3d12_dxbc_disasm), dxbc_converter,
                                       dxc_utils, dxc_compiler);
  } else {
    translation.DisassembleDxbcAndDxil(provider, REXCVAR_GET(d3d12_dxbc_disasm));
  }

  if (!REXCVAR_GET(dump_shaders).empty()) {
    bool edram_rov_used =
        render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;
    translation.Dump(REXCVAR_GET(dump_shaders), (shader.type() == xenos::ShaderType::kPixel)
                                                    ? (edram_rov_used ? "d3d12_rov" : "d3d12_rtv")
                                                    : "d3d12");
  }

  translation.PublishTranslated();
  return translation.is_valid();
}

bool PipelineCache::GetCurrentStateDescription(
    D3D12Shader::D3D12Translation* vertex_shader, D3D12Shader::D3D12Translation* pixel_shader,
    const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
    reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask, bool zpd_total,
    bool viz_survey, uint32_t bound_depth_and_color_render_target_bits,
    const uint32_t* bound_depth_and_color_render_target_formats,
    PipelineRuntimeDescription& runtime_description_out, bool for_placeholder) {
  assert_true(for_placeholder || (vertex_shader->is_translated() && vertex_shader->is_valid()));
  assert_true(for_placeholder || !pixel_shader ||
              (pixel_shader->is_translated() && pixel_shader->is_valid()));

  PipelineDescription& description_out = runtime_description_out.description;

  const auto& regs = register_file_;
  auto pa_su_sc_mode_cntl = regs.Get<reg::PA_SU_SC_MODE_CNTL>();

  std::memset(&runtime_description_out, 0, sizeof(runtime_description_out));

  assert_true(DxbcShaderTranslator::Modification(vertex_shader->modification())
                  .vertex.host_vertex_shader_type ==
              primitive_processing_result.host_vertex_shader_type);
  bool tessellated = primitive_processing_result.IsTessellated();
  bool primitive_polygonal = draw_util::IsPrimitivePolygonal(regs);
  bool rasterization_enabled = draw_util::IsRasterizationPotentiallyDone(regs, primitive_polygonal);

  if (!rasterization_enabled) {
    assert_null(pixel_shader);
    if (pixel_shader) {
      return false;
    }
  }

  bool edram_rov_used =
      render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;

  runtime_description_out.root_signature = command_processor_.GetRootSignature(
      static_cast<const DxbcShader*>(&vertex_shader->shader()),
      (pixel_shader && !for_placeholder) ? static_cast<const DxbcShader*>(&pixel_shader->shader())
                                         : nullptr,
      tessellated);
  if (runtime_description_out.root_signature == nullptr) {
    return false;
  }

  runtime_description_out.vertex_shader = vertex_shader;
  description_out.vertex_shader_hash = vertex_shader->shader().ucode_data_hash();
  description_out.vertex_shader_modification = vertex_shader->modification();

  if (primitive_processing_result.host_primitive_reset_enabled) {
    description_out.strip_cut_index =
        primitive_processing_result.host_index_format == xenos::IndexFormat::kInt16
            ? PipelineStripCutIndex::kFFFF
            : PipelineStripCutIndex::kFFFFFFFF;
  } else {
    description_out.strip_cut_index = PipelineStripCutIndex::kNone;
  }

  if (tessellated) {
    description_out.primitive_topology_type_or_tessellation_mode =
        uint32_t(primitive_processing_result.tessellation_mode);
  } else {
    switch (primitive_processing_result.host_primitive_type) {
      case xenos::PrimitiveType::kPointList:
        description_out.primitive_topology_type_or_tessellation_mode =
            uint32_t(PipelinePrimitiveTopologyType::kPoint);
        break;
      case xenos::PrimitiveType::kLineList:
      case xenos::PrimitiveType::kLineStrip:

      case xenos::PrimitiveType::kQuadList:
      case xenos::PrimitiveType::k2DLineStrip:
        description_out.primitive_topology_type_or_tessellation_mode =
            uint32_t(PipelinePrimitiveTopologyType::kLine);
        break;
      default:
        description_out.primitive_topology_type_or_tessellation_mode =
            uint32_t(PipelinePrimitiveTopologyType::kTriangle);
        break;
    }
    switch (primitive_processing_result.host_primitive_type) {
      case xenos::PrimitiveType::kPointList:
        description_out.geometry_shader = PipelineGeometryShader::kPointList;
        break;
      case xenos::PrimitiveType::kRectangleList:
        description_out.geometry_shader = PipelineGeometryShader::kRectangleList;
        break;
      case xenos::PrimitiveType::kQuadList:
        description_out.geometry_shader = PipelineGeometryShader::kQuadList;
        break;
      case xenos::PrimitiveType::kLineList:
      case xenos::PrimitiveType::kLineStrip:

        description_out.geometry_shader = (render_target_cache_.draw_resolution_scale_x() > 1 ||
                                           render_target_cache_.draw_resolution_scale_y() > 1)
                                              ? PipelineGeometryShader::kLineList
                                              : PipelineGeometryShader::kNone;
        break;
      default:
        description_out.geometry_shader = PipelineGeometryShader::kNone;
        break;
    }
  }
  GeometryShaderKey geometry_shader_key;
  runtime_description_out.geometry_shader =
      GetGeometryShaderKey(
          description_out.geometry_shader,
          DxbcShaderTranslator::Modification(vertex_shader->modification()),
          DxbcShaderTranslator::Modification(pixel_shader ? pixel_shader->modification() : 0),
          geometry_shader_key)
          ? &GetGeometryShader(geometry_shader_key)
          : nullptr;

  if (!rasterization_enabled) {
    description_out.cull_mode = PipelineCullMode::kDisableRasterization;
    return true;
  }

  if (pixel_shader) {
    runtime_description_out.pixel_shader = pixel_shader;
    description_out.pixel_shader_hash = pixel_shader->shader().ucode_data_hash();
    description_out.pixel_shader_modification = pixel_shader->modification();
  }

  bool cull_front, cull_back;
  if (primitive_polygonal) {
    description_out.front_counter_clockwise = pa_su_sc_mode_cntl.face == 0;
    cull_front = pa_su_sc_mode_cntl.cull_front != 0;
    cull_back = pa_su_sc_mode_cntl.cull_back != 0;
    if (cull_front) {
      assert_false(cull_back);
      description_out.cull_mode = PipelineCullMode::kFront;
    } else if (cull_back) {
      description_out.cull_mode = PipelineCullMode::kBack;
    } else {
      description_out.cull_mode = PipelineCullMode::kNone;
    }

    if (!cull_front) {
      if (pa_su_sc_mode_cntl.polymode_front_ptype != xenos::PolygonType::kTriangles) {
        description_out.fill_mode_wireframe = 1;
      }
    }
    if (!cull_back) {
      if (pa_su_sc_mode_cntl.polymode_back_ptype != xenos::PolygonType::kTriangles) {
        description_out.fill_mode_wireframe = 1;
      }
    }
    if (pa_su_sc_mode_cntl.poly_mode != xenos::PolygonModeEnable::kDualMode) {
      description_out.fill_mode_wireframe = 0;
    }
  } else {
    cull_front = false;
    cull_back = false;
  }
  if (!edram_rov_used) {
    float polygon_offset, polygon_offset_scale;
    draw_util::GetPreferredFacePolygonOffset(regs, primitive_polygonal, polygon_offset_scale,
                                             polygon_offset);
    description_out.depth_bias = draw_util::GetD3D10IntegerPolygonOffset(
        regs.Get<reg::RB_DEPTH_INFO>().depth_format, polygon_offset);
    description_out.depth_bias_slope_scaled =
        polygon_offset_scale * xenos::kPolygonOffsetScaleSubpixelUnit;
  }
  description_out.zpd_total = uint32_t(zpd_total);
  description_out.viz_survey = uint32_t(viz_survey && edram_rov_used);
  if (tessellated && REXCVAR_GET(d3d12_tessellation_wireframe)) {
    description_out.fill_mode_wireframe = 1;
  }
  description_out.depth_clip = !regs.Get<reg::PA_CL_CLIP_CNTL>().clip_disable;
  bool depth_stencil_bound_and_used = false;
  if (!edram_rov_used) {
    if (bound_depth_and_color_render_target_bits & 1) {
      if (normalized_depth_control.z_enable) {
        description_out.depth_func = normalized_depth_control.zfunc;
        description_out.depth_write = normalized_depth_control.z_write_enable;
      } else {
        description_out.depth_func = xenos::CompareFunction::kAlways;
      }
      if (normalized_depth_control.stencil_enable) {
        description_out.stencil_enable = 1;
        bool stencil_backface_enable =
            primitive_polygonal && normalized_depth_control.backface_enable;

        Register stencil_ref_mask_reg;
        if (stencil_backface_enable && cull_front) {
          stencil_ref_mask_reg = XE_GPU_REG_RB_STENCILREFMASK_BF;
        } else {
          stencil_ref_mask_reg = XE_GPU_REG_RB_STENCILREFMASK;
        }
        auto stencil_ref_mask = regs.Get<reg::RB_STENCILREFMASK>(stencil_ref_mask_reg);
        description_out.stencil_read_mask = stencil_ref_mask.stencilmask;
        description_out.stencil_write_mask = stencil_ref_mask.stencilwritemask;
        description_out.stencil_front_fail_op = normalized_depth_control.stencilfail;
        description_out.stencil_front_depth_fail_op = normalized_depth_control.stencilzfail;
        description_out.stencil_front_pass_op = normalized_depth_control.stencilzpass;
        description_out.stencil_front_func = normalized_depth_control.stencilfunc;
        if (stencil_backface_enable) {
          description_out.stencil_back_fail_op = normalized_depth_control.stencilfail_bf;
          description_out.stencil_back_depth_fail_op = normalized_depth_control.stencilzfail_bf;
          description_out.stencil_back_pass_op = normalized_depth_control.stencilzpass_bf;
          description_out.stencil_back_func = normalized_depth_control.stencilfunc_bf;
        } else {
          description_out.stencil_back_fail_op = description_out.stencil_front_fail_op;
          description_out.stencil_back_depth_fail_op = description_out.stencil_front_depth_fail_op;
          description_out.stencil_back_pass_op = description_out.stencil_front_pass_op;
          description_out.stencil_back_func = description_out.stencil_front_func;
        }
      }

      if (description_out.depth_func != xenos::CompareFunction::kAlways ||
          description_out.depth_write || description_out.stencil_enable) {
        description_out.depth_format =
            xenos::DepthRenderTargetFormat(bound_depth_and_color_render_target_formats[0]);
        depth_stencil_bound_and_used = true;
      }
    } else {
      description_out.depth_func = xenos::CompareFunction::kAlways;
    }

    static const PipelineBlendFactor kBlendFactorMap[32] = {
        PipelineBlendFactor::kZero,           PipelineBlendFactor::kOne,
        PipelineBlendFactor::kZero,           PipelineBlendFactor::kZero,
        PipelineBlendFactor::kSrcColor,       PipelineBlendFactor::kInvSrcColor,
        PipelineBlendFactor::kSrcAlpha,       PipelineBlendFactor::kInvSrcAlpha,
        PipelineBlendFactor::kDestColor,      PipelineBlendFactor::kInvDestColor,
        PipelineBlendFactor::kDestAlpha,      PipelineBlendFactor::kInvDestAlpha,

        PipelineBlendFactor::kBlendFactor,

        PipelineBlendFactor::kInvBlendFactor,

        PipelineBlendFactor::kBlendFactor,

        PipelineBlendFactor::kInvBlendFactor, PipelineBlendFactor::kSrcAlphaSat,
    };

    static const PipelineBlendFactor kBlendFactorAlphaMap[32] = {
        PipelineBlendFactor::kZero,           PipelineBlendFactor::kOne,
        PipelineBlendFactor::kZero,           PipelineBlendFactor::kZero,
        PipelineBlendFactor::kSrcAlpha,       PipelineBlendFactor::kInvSrcAlpha,
        PipelineBlendFactor::kSrcAlpha,       PipelineBlendFactor::kInvSrcAlpha,
        PipelineBlendFactor::kDestAlpha,      PipelineBlendFactor::kInvDestAlpha,
        PipelineBlendFactor::kDestAlpha,      PipelineBlendFactor::kInvDestAlpha,
        PipelineBlendFactor::kBlendFactor,

        PipelineBlendFactor::kInvBlendFactor,

        PipelineBlendFactor::kBlendFactor,

        PipelineBlendFactor::kInvBlendFactor, PipelineBlendFactor::kSrcAlphaSat,
    };

    for (uint32_t i = 0; i < 4; ++i) {
      if (!(bound_depth_and_color_render_target_bits & (uint32_t(1) << (1 + i)))) {
        continue;
      }
      PipelineRenderTarget& rt = description_out.render_targets[i];
      rt.used = 1;
      auto color_info = regs.Get<reg::RB_COLOR_INFO>(reg::RB_COLOR_INFO::rt_register_indices[i]);
      rt.format =
          xenos::ColorRenderTargetFormat(bound_depth_and_color_render_target_formats[1 + i]);
      rt.write_mask = (normalized_color_mask >> (i * 4)) & 0xF;
      if (rt.write_mask) {
        auto blendcontrol =
            regs.Get<reg::RB_BLENDCONTROL>(reg::RB_BLENDCONTROL::rt_register_indices[i]);
        rt.src_blend = kBlendFactorMap[uint32_t(blendcontrol.color_srcblend)];
        rt.dest_blend = kBlendFactorMap[uint32_t(blendcontrol.color_destblend)];
        rt.blend_op = blendcontrol.color_comb_fcn;
        rt.src_blend_alpha = kBlendFactorAlphaMap[uint32_t(blendcontrol.alpha_srcblend)];
        rt.dest_blend_alpha = kBlendFactorAlphaMap[uint32_t(blendcontrol.alpha_destblend)];
        rt.blend_op_alpha = blendcontrol.alpha_comb_fcn;
      } else {
        rt.src_blend = PipelineBlendFactor::kOne;
        rt.dest_blend = PipelineBlendFactor::kZero;
        rt.blend_op = xenos::BlendOp::kAdd;
        rt.src_blend_alpha = PipelineBlendFactor::kOne;
        rt.dest_blend_alpha = PipelineBlendFactor::kZero;
        rt.blend_op_alpha = xenos::BlendOp::kAdd;
      }
    }
  }
  xenos::MsaaSamples host_msaa_samples = regs.Get<reg::RB_SURFACE_INFO>().msaa_samples;
  if (edram_rov_used) {
    if (host_msaa_samples == xenos::MsaaSamples::k2X) {
      host_msaa_samples = xenos::MsaaSamples::k4X;
    }
  } else {
    if (!(bound_depth_and_color_render_target_bits & ~uint32_t(1)) &&
        !depth_stencil_bound_and_used) {
      host_msaa_samples = xenos::MsaaSamples::k1X;
    }
  }
  description_out.host_msaa_samples = host_msaa_samples;

  return true;
}

ID3D12PipelineState* PipelineCache::CreateD3D12Pipeline(
    const PipelineRuntimeDescription& runtime_description) {
  const PipelineDescription& description = runtime_description.description;

  if (description.pixel_shader_hash) {
    REXGPU_DEBUG("Creating graphics pipeline with VS {:016X}, PS {:016X}{}",
                 description.vertex_shader_hash, description.pixel_shader_hash,
                 description.dxil ? " (DXIL)" : "");
  } else {
    REXGPU_DEBUG("Creating graphics pipeline with VS {:016X}{}", description.vertex_shader_hash,
                 description.dxil ? " (DXIL)" : "");
  }

  D3D12_GRAPHICS_PIPELINE_STATE_DESC state_desc;
  std::memset(&state_desc, 0, sizeof(state_desc));

  bool edram_rov_used =
      render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;

  state_desc.pRootSignature = runtime_description.root_signature;

  switch (description.strip_cut_index) {
    case PipelineStripCutIndex::kFFFF:
      state_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF;
      break;
    case PipelineStripCutIndex::kFFFFFFFF:
      state_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF;
      break;
    default:
      state_desc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
      break;
  }

  if (description.dxil) {
#if REXGLUE_SHADER_DXIL
    if (Shader::IsHostVertexShaderTypeDomain(
            SpirvShaderTranslator::Modification(description.vertex_shader_modification)
                .vertex.host_vertex_shader_type)) {
      const DxilTessellation* tessellation =
          ConvertDxilTessellation(*runtime_description.dxil_vertex_spirv);
      if (!tessellation) {
        return nullptr;
      }
      state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
      state_desc.VS.pShaderBytecode = tessellation->host_vertex.data();
      state_desc.VS.BytecodeLength = tessellation->host_vertex.size();
      state_desc.HS.pShaderBytecode = tessellation->host_hull.data();
      state_desc.HS.BytecodeLength = tessellation->host_hull.size();
      state_desc.DS.pShaderBytecode = tessellation->domain.data();
      state_desc.DS.BytecodeLength = tessellation->domain.size();
    } else {
      const std::vector<uint8_t>* dxil_vertex = ConvertDxil(*runtime_description.dxil_vertex_spirv);
      if (!dxil_vertex) {
        return nullptr;
      }
      state_desc.VS.pShaderBytecode = dxil_vertex->data();
      state_desc.VS.BytecodeLength = dxil_vertex->size();
      switch (
          PipelinePrimitiveTopologyType(description.primitive_topology_type_or_tessellation_mode)) {
        case PipelinePrimitiveTopologyType::kPoint:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
          break;
        case PipelinePrimitiveTopologyType::kLine:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
          break;
        default:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
          break;
      }
    }
    const std::vector<uint8_t>* dxil_pixel =
        runtime_description.dxil_pixel_spirv ? ConvertDxil(*runtime_description.dxil_pixel_spirv)
                                             : GetDxilHelperPixelShader(description);
    if (runtime_description.dxil_pixel_spirv && !dxil_pixel) {
      return nullptr;
    }
    if (dxil_pixel) {
      state_desc.PS.pShaderBytecode = dxil_pixel->data();
      state_desc.PS.BytecodeLength = dxil_pixel->size();
    }
#else
    return nullptr;
#endif
    if (runtime_description.dxil_geometry_shader) {
      state_desc.GS.pShaderBytecode = runtime_description.dxil_geometry_shader->data();
      state_desc.GS.BytecodeLength = runtime_description.dxil_geometry_shader->size();
    }
  } else if (!runtime_description.vertex_shader->is_translated()) {
    REXGPU_ERROR("Vertex shader {:016X} not translated",
                 runtime_description.vertex_shader->shader().ucode_data_hash());
    assert_always();
    return nullptr;
  }
  if (!description.dxil) {
    Shader::HostVertexShaderType host_vertex_shader_type =
        DxbcShaderTranslator::Modification(runtime_description.vertex_shader->modification())
            .vertex.host_vertex_shader_type;
    if (Shader::IsHostVertexShaderTypeDomain(host_vertex_shader_type)) {
      state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
      xenos::TessellationMode tessellation_mode =
          xenos::TessellationMode(description.primitive_topology_type_or_tessellation_mode);
      if (tessellation_mode == xenos::TessellationMode::kAdaptive) {
        state_desc.VS.pShaderBytecode = shaders::tessellation_adaptive_vs;
        state_desc.VS.BytecodeLength = sizeof(shaders::tessellation_adaptive_vs);
      } else {
        state_desc.VS.pShaderBytecode = shaders::tessellation_indexed_vs;
        state_desc.VS.BytecodeLength = sizeof(shaders::tessellation_indexed_vs);
      }
      switch (tessellation_mode) {
        case xenos::TessellationMode::kDiscrete:
          switch (host_vertex_shader_type) {
            case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
              state_desc.HS.pShaderBytecode = shaders::discrete_triangle_3cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::discrete_triangle_3cp_hs);
              break;
            case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::discrete_triangle_1cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::discrete_triangle_1cp_hs);
              break;
            case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
              state_desc.HS.pShaderBytecode = shaders::discrete_quad_4cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::discrete_quad_4cp_hs);
              break;
            case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::discrete_quad_1cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::discrete_quad_1cp_hs);
              break;
            default:
              assert_unhandled_case(host_vertex_shader_type);
              return nullptr;
          }
          break;
        case xenos::TessellationMode::kContinuous:
          switch (host_vertex_shader_type) {
            case Shader::HostVertexShaderType::kTriangleDomainCPIndexed:
              state_desc.HS.pShaderBytecode = shaders::continuous_triangle_3cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::continuous_triangle_3cp_hs);
              break;
            case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::continuous_triangle_1cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::continuous_triangle_1cp_hs);
              break;
            case Shader::HostVertexShaderType::kQuadDomainCPIndexed:
              state_desc.HS.pShaderBytecode = shaders::continuous_quad_4cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::continuous_quad_4cp_hs);
              break;
            case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::continuous_quad_1cp_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::continuous_quad_1cp_hs);
              break;
            default:
              assert_unhandled_case(host_vertex_shader_type);
              return nullptr;
          }
          break;
        case xenos::TessellationMode::kAdaptive:
          switch (host_vertex_shader_type) {
            case Shader::HostVertexShaderType::kTriangleDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::adaptive_triangle_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::adaptive_triangle_hs);
              break;
            case Shader::HostVertexShaderType::kQuadDomainPatchIndexed:
              state_desc.HS.pShaderBytecode = shaders::adaptive_quad_hs;
              state_desc.HS.BytecodeLength = sizeof(shaders::adaptive_quad_hs);
              break;
            default:
              assert_unhandled_case(host_vertex_shader_type);
              return nullptr;
          }
          break;
        default:
          assert_unhandled_case(tessellation_mode);
          return nullptr;
      }
      state_desc.DS.pShaderBytecode = runtime_description.vertex_shader->translated_binary().data();
      state_desc.DS.BytecodeLength = runtime_description.vertex_shader->translated_binary().size();
    } else {
      assert_true(host_vertex_shader_type == Shader::HostVertexShaderType::kVertex);
      if (host_vertex_shader_type != Shader::HostVertexShaderType::kVertex) {
        return nullptr;
      }
      state_desc.VS.pShaderBytecode = runtime_description.vertex_shader->translated_binary().data();
      state_desc.VS.BytecodeLength = runtime_description.vertex_shader->translated_binary().size();
      PipelinePrimitiveTopologyType primitive_topology_type =
          PipelinePrimitiveTopologyType(description.primitive_topology_type_or_tessellation_mode);
      switch (primitive_topology_type) {
        case PipelinePrimitiveTopologyType::kPoint:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
          break;
        case PipelinePrimitiveTopologyType::kLine:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
          break;
        case PipelinePrimitiveTopologyType::kTriangle:
          state_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
          break;
        default:
          assert_unhandled_case(primitive_topology_type);
          return nullptr;
      }
    }
  }

  if (description.dxil) {
  } else if (runtime_description.pixel_shader != nullptr) {
    if (!runtime_description.pixel_shader->is_translated()) {
      REXGPU_ERROR("Pixel shader {:016X} not translated",
                   runtime_description.pixel_shader->shader().ucode_data_hash());
      assert_always();
      return nullptr;
    }
    state_desc.PS.pShaderBytecode = runtime_description.pixel_shader->translated_binary().data();
    state_desc.PS.BytecodeLength = runtime_description.pixel_shader->translated_binary().size();
  } else if (description.zpd_total && !zpd_total_depth_only_pixel_shader_.empty()) {
    const std::vector<uint8_t>* zpd_total_pixel_shader = &zpd_total_depth_only_pixel_shader_;
    if (render_target_cache_.depth_float24_convert_in_pixel_shader() &&
        (description.depth_func != xenos::CompareFunction::kAlways || description.depth_write) &&
        description.depth_format == xenos::DepthRenderTargetFormat::kD24FS8) {
      zpd_total_pixel_shader = render_target_cache_.depth_float24_round()
                                   ? &zpd_total_float24_round_pixel_shader_
                                   : &zpd_total_float24_truncate_pixel_shader_;
    }
    state_desc.PS.pShaderBytecode = zpd_total_pixel_shader->data();
    state_desc.PS.BytecodeLength = zpd_total_pixel_shader->size();
  } else if (edram_rov_used) {
    const std::vector<uint8_t>& rov_pixel_shader =
        description.viz_survey && !viz_survey_depth_only_pixel_shader_.empty()
            ? viz_survey_depth_only_pixel_shader_
            : depth_only_pixel_shader_;
    state_desc.PS.pShaderBytecode = rov_pixel_shader.data();
    state_desc.PS.BytecodeLength = rov_pixel_shader.size();
  } else {
    if (render_target_cache_.depth_float24_convert_in_pixel_shader() &&
        (description.depth_func != xenos::CompareFunction::kAlways || description.depth_write) &&
        description.depth_format == xenos::DepthRenderTargetFormat::kD24FS8) {
      if (render_target_cache_.depth_float24_round()) {
        state_desc.PS.pShaderBytecode = shaders::float24_round_ps;
        state_desc.PS.BytecodeLength = sizeof(shaders::float24_round_ps);
      } else {
        state_desc.PS.pShaderBytecode = shaders::float24_truncate_ps;
        state_desc.PS.BytecodeLength = sizeof(shaders::float24_truncate_ps);
      }
    } else if (!description.depth_write && !description.stencil_write_mask) {
      state_desc.PS.pShaderBytecode = depth_only_pixel_shader_.data();
      state_desc.PS.BytecodeLength = depth_only_pixel_shader_.size();
    }
  }

  if (!description.dxil && runtime_description.geometry_shader != nullptr) {
    state_desc.GS.pShaderBytecode = runtime_description.geometry_shader->data();
    state_desc.GS.BytecodeLength = sizeof(*runtime_description.geometry_shader->data()) *
                                   runtime_description.geometry_shader->size();
  }

  state_desc.RasterizerState.FillMode =
      description.fill_mode_wireframe ? D3D12_FILL_MODE_WIREFRAME : D3D12_FILL_MODE_SOLID;
  switch (description.cull_mode) {
    case PipelineCullMode::kFront:
      state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
      break;
    case PipelineCullMode::kBack:
      state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
      break;
    default:
      assert_true(description.cull_mode == PipelineCullMode::kNone ||
                  description.cull_mode == PipelineCullMode::kDisableRasterization);
      state_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
      break;
  }
  state_desc.RasterizerState.FrontCounterClockwise =
      description.front_counter_clockwise ? TRUE : FALSE;
  state_desc.RasterizerState.DepthBias = description.depth_bias;
  state_desc.RasterizerState.DepthBiasClamp = 0.0f;

  state_desc.RasterizerState.SlopeScaledDepthBias =
      description.depth_bias_slope_scaled *
      float(std::max(render_target_cache_.draw_resolution_scale_x(),
                     render_target_cache_.draw_resolution_scale_y()));
  state_desc.RasterizerState.DepthClipEnable = description.depth_clip ? TRUE : FALSE;
  uint32_t msaa_sample_count = uint32_t(1) << uint32_t(description.host_msaa_samples);
  if (edram_rov_used) {
    assert_true(msaa_sample_count == 1 || msaa_sample_count == 4);
    if (msaa_sample_count != 1 && msaa_sample_count != 4) {
      return nullptr;
    }
    state_desc.RasterizerState.ForcedSampleCount = uint32_t(1)
                                                   << uint32_t(description.host_msaa_samples);
  }

  state_desc.SampleMask = UINT_MAX;

  if (edram_rov_used) {
    state_desc.SampleDesc.Count = 1;
  } else {
    assert_true(msaa_sample_count <= 4);
    if (msaa_sample_count > 4) {
      return nullptr;
    }
    if (msaa_sample_count == 2 && !render_target_cache_.msaa_2x_supported()) {
      state_desc.SampleMask = 0b1001;
      state_desc.SampleDesc.Count = 4;
    } else {
      state_desc.SampleDesc.Count = msaa_sample_count;
    }
  }

  if (!edram_rov_used) {
    if (description.depth_func != xenos::CompareFunction::kAlways || description.depth_write) {
      state_desc.DepthStencilState.DepthEnable = TRUE;
      state_desc.DepthStencilState.DepthWriteMask =
          description.depth_write ? D3D12_DEPTH_WRITE_MASK_ALL : D3D12_DEPTH_WRITE_MASK_ZERO;

      state_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC(
          uint32_t(D3D12_COMPARISON_FUNC_NEVER) + uint32_t(description.depth_func));
    }
    if (description.stencil_enable) {
      state_desc.DepthStencilState.StencilEnable = TRUE;
      state_desc.DepthStencilState.StencilReadMask = description.stencil_read_mask;
      state_desc.DepthStencilState.StencilWriteMask = description.stencil_write_mask;

      state_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_front_fail_op));
      state_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_front_depth_fail_op));
      state_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_front_pass_op));
      state_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC(
          uint32_t(D3D12_COMPARISON_FUNC_NEVER) + uint32_t(description.stencil_front_func));
      state_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_back_fail_op));
      state_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_back_depth_fail_op));
      state_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP(
          uint32_t(D3D12_STENCIL_OP_KEEP) + uint32_t(description.stencil_back_pass_op));
      state_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC(
          uint32_t(D3D12_COMPARISON_FUNC_NEVER) + uint32_t(description.stencil_back_func));
    }
    if (state_desc.DepthStencilState.DepthEnable || state_desc.DepthStencilState.StencilEnable) {
      state_desc.DSVFormat =
          D3D12RenderTargetCache::GetDepthDSVDXGIFormat(description.depth_format);
    }

    state_desc.BlendState.IndependentBlendEnable = TRUE;
    static const D3D12_BLEND kBlendFactorMap[] = {
        D3D12_BLEND_ZERO,          D3D12_BLEND_ONE,
        D3D12_BLEND_SRC_COLOR,     D3D12_BLEND_INV_SRC_COLOR,
        D3D12_BLEND_SRC_ALPHA,     D3D12_BLEND_INV_SRC_ALPHA,
        D3D12_BLEND_DEST_COLOR,    D3D12_BLEND_INV_DEST_COLOR,
        D3D12_BLEND_DEST_ALPHA,    D3D12_BLEND_INV_DEST_ALPHA,
        D3D12_BLEND_BLEND_FACTOR,  D3D12_BLEND_INV_BLEND_FACTOR,
        D3D12_BLEND_SRC_ALPHA_SAT,
    };

    static const D3D12_BLEND_OP kBlendOpMap[] = {
        D3D12_BLEND_OP_ADD, D3D12_BLEND_OP_SUBTRACT,     D3D12_BLEND_OP_MIN,
        D3D12_BLEND_OP_MAX, D3D12_BLEND_OP_REV_SUBTRACT, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_OP_ADD, D3D12_BLEND_OP_ADD};
    for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
      const PipelineRenderTarget& rt = description.render_targets[i];
      if (!rt.used) {
        state_desc.RTVFormats[i] = DXGI_FORMAT_UNKNOWN;
        continue;
      }
      state_desc.NumRenderTargets = i + 1;
      state_desc.RTVFormats[i] = render_target_cache_.GetColorDrawDXGIFormat(rt.format);
      if (state_desc.RTVFormats[i] == DXGI_FORMAT_UNKNOWN) {
        assert_always();
        return nullptr;
      }
      D3D12_RENDER_TARGET_BLEND_DESC& blend_desc = state_desc.BlendState.RenderTarget[i];
      if (rt.src_blend != PipelineBlendFactor::kOne ||
          rt.dest_blend != PipelineBlendFactor::kZero || rt.blend_op != xenos::BlendOp::kAdd ||
          rt.src_blend_alpha != PipelineBlendFactor::kOne ||
          rt.dest_blend_alpha != PipelineBlendFactor::kZero ||
          rt.blend_op_alpha != xenos::BlendOp::kAdd) {
        blend_desc.BlendEnable = TRUE;
        blend_desc.SrcBlend = kBlendFactorMap[uint32_t(rt.src_blend)];
        blend_desc.DestBlend = kBlendFactorMap[uint32_t(rt.dest_blend)];
        blend_desc.BlendOp = kBlendOpMap[uint32_t(rt.blend_op)];
        blend_desc.SrcBlendAlpha = kBlendFactorMap[uint32_t(rt.src_blend_alpha)];
        blend_desc.DestBlendAlpha = kBlendFactorMap[uint32_t(rt.dest_blend_alpha)];
        blend_desc.BlendOpAlpha = kBlendOpMap[uint32_t(rt.blend_op_alpha)];
      }
      blend_desc.RenderTargetWriteMask = rt.write_mask;
    }
  }

  if (description.cull_mode == PipelineCullMode::kDisableRasterization) {
    state_desc.PS.pShaderBytecode = nullptr;
    state_desc.PS.BytecodeLength = 0;
    state_desc.DepthStencilState.DepthEnable = FALSE;
    state_desc.DepthStencilState.StencilEnable = FALSE;
  }

  ID3D12Device* device = command_processor_.GetD3D12Provider().GetDevice();
  ID3D12PipelineState* state;
  if (FAILED(device->CreateGraphicsPipelineState(&state_desc, IID_PPV_ARGS(&state)))) {
    if (description.pixel_shader_hash) {
      REXGPU_ERROR("Failed to create graphics pipeline with VS {:016X}, PS {:016X}{}",
                   description.vertex_shader_hash, description.pixel_shader_hash,
                   description.dxil ? " (DXIL)" : "");
    } else {
      REXGPU_ERROR("Failed to create graphics pipeline with VS {:016X}{}",
                   description.vertex_shader_hash, description.dxil ? " (DXIL)" : "");
    }

    ID3D12InfoQueue* info_queue;
    if (SUCCEEDED(device->QueryInterface(IID_PPV_ARGS(&info_queue)))) {
      UINT64 message_count = info_queue->GetNumStoredMessages();
      for (UINT64 i = message_count > 8 ? message_count - 8 : 0; i < message_count; ++i) {
        SIZE_T length = 0;
        info_queue->GetMessage(i, nullptr, &length);
        std::vector<uint8_t> storage(length);
        auto* message = reinterpret_cast<D3D12_MESSAGE*>(storage.data());
        if (length && SUCCEEDED(info_queue->GetMessage(i, message, &length))) {
          REXGPU_ERROR("  D3D12: {}",
                       std::string_view(message->pDescription, message->DescriptionByteLength));
        }
      }
      info_queue->ClearStoredMessages();
      info_queue->Release();
    }
    return nullptr;
  }
  std::u16string name;
  if (description.pixel_shader_hash) {
    name = rex::string::to_utf16(fmt::format(
        "VS {:016X}, PS {:016X}", description.vertex_shader_hash, description.pixel_shader_hash));
  } else {
    name = rex::string::to_utf16(fmt::format("VS {:016X}", description.vertex_shader_hash));
  }
  state->SetName(reinterpret_cast<LPCWSTR>(name.c_str()));
  return state;
}

bool PipelineCache::PrepareRuntimeDescriptionForQueuedCreation(
    Pipeline* pipeline, PipelineRuntimeDescription& runtime_description) {
  assert_not_null(pipeline);
  std::memcpy(&runtime_description, &pipeline->description, sizeof(runtime_description));
  runtime_description.root_signature = pipeline->root_signature.load(std::memory_order_acquire);

  auto translate_pending_shader = [this](D3D12Shader::D3D12Translation* translation,
                                         const char* shader_type) -> bool {
    if (!translation) {
      return true;
    }
    if (!translation->is_translated()) {
      std::lock_guard<std::mutex> lock(translation_request_lock_);
      if (!translation->is_translated()) {
        translation->shader().AnalyzeUcode(ucode_disasm_buffer_);
        if (!TranslateAnalyzedShader(*shader_translator_, *translation, dxbc_converter_, dxc_utils_,
                                     dxc_compiler_)) {
          REXGPU_ERROR("Failed to translate queued {} shader", shader_type);
          return false;
        }
        if (shader_storage_file_ &&
            translation->shader().ucode_storage_index() != shader_storage_index_) {
          translation->shader().set_ucode_storage_index(shader_storage_index_);
          assert_not_null(storage_write_thread_);
          shader_storage_file_flush_needed_ = true;
          {
            std::lock_guard<std::mutex> storage_lock(storage_write_request_lock_);
            storage_write_shader_queue_.push_back(&translation->shader());
          }
          storage_write_request_cond_.notify_all();
        }
      }
    }
    return translation->is_valid();
  };

  if (pipeline->pending_vertex_shader) {
    D3D12Shader::D3D12Translation* pending_vertex = pipeline->pending_vertex_shader;
    pipeline->pending_vertex_shader = nullptr;
    if (!translate_pending_shader(pending_vertex, "vertex")) {
      return false;
    }
  }

  if (pipeline->pending_pixel_shader) {
    D3D12Shader::D3D12Translation* pending_pixel = pipeline->pending_pixel_shader;
    pipeline->pending_pixel_shader = nullptr;
    if (!translate_pending_shader(pending_pixel, "pixel")) {
      return false;
    }
    bool tessellated = Shader::IsHostVertexShaderTypeDomain(
        DxbcShaderTranslator::Modification(runtime_description.vertex_shader->modification())
            .vertex.host_vertex_shader_type);
    ID3D12RootSignature* root_signature = command_processor_.GetRootSignature(
        static_cast<const DxbcShader*>(&runtime_description.vertex_shader->shader()),
        static_cast<const DxbcShader*>(&pending_pixel->shader()), tessellated);
    if (!root_signature) {
      return false;
    }
    runtime_description.root_signature = root_signature;
    pipeline->root_signature.store(root_signature, std::memory_order_release);
  }

  return true;
}

void PipelineCache::CreationThread(size_t thread_index) {
  while (true) {
    Pipeline* pipeline_to_create = nullptr;

    {
      std::unique_lock<std::mutex> lock(creation_request_lock_);
      if (thread_index >= creation_threads_shutdown_from_ || creation_queue_.empty()) {
        if (creation_completion_set_event_ && creation_threads_busy_ == 0) {
          creation_completion_set_event_ = false;
          creation_completion_event_->Set();
        }
        if (thread_index >= creation_threads_shutdown_from_) {
          return;
        }
        creation_request_cond_.wait(lock);
        continue;
      }

      pipeline_to_create = creation_queue_.top();
      creation_queue_.pop();
      if (pipeline_to_create->creation_claimed.exchange(true, std::memory_order_acq_rel)) {
        continue;
      }
      ++creation_threads_busy_;
    }

    PipelineRuntimeDescription runtime_description;
    if (!PrepareRuntimeDescriptionForQueuedCreation(pipeline_to_create, runtime_description)) {
      pipeline_to_create->state.store(nullptr, std::memory_order_release);
    } else {
      pipeline_to_create->state.store(CreateD3D12Pipeline(runtime_description),
                                      std::memory_order_release);
    }
    pipeline_to_create->creation_pending.store(false, std::memory_order_release);

    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);
      --creation_threads_busy_;
    }
  }
}

void PipelineCache::CreateQueuedPipelinesOnProcessorThread() {
  assert_false(creation_threads_.empty());
  while (true) {
    Pipeline* pipeline_to_create;
    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);
      if (creation_queue_.empty()) {
        break;
      }
      pipeline_to_create = creation_queue_.top();
      creation_queue_.pop();
    }
    if (pipeline_to_create->creation_claimed.exchange(true, std::memory_order_acq_rel)) {
      continue;
    }
    PipelineRuntimeDescription runtime_description;
    if (!PrepareRuntimeDescriptionForQueuedCreation(pipeline_to_create, runtime_description)) {
      pipeline_to_create->state.store(nullptr, std::memory_order_release);
    } else {
      pipeline_to_create->state.store(CreateD3D12Pipeline(runtime_description),
                                      std::memory_order_release);
    }
    pipeline_to_create->creation_pending.store(false, std::memory_order_release);
  }
}

}

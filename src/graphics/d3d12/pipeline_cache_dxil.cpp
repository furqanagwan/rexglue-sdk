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

namespace rex::graphics::d3d12 {

#if REXGLUE_SHADER_DXIL

namespace shaders_spirv {
#include "spirv_shaders/adaptive_quad_hs.h"
#include "spirv_shaders/adaptive_triangle_hs.h"
#include "spirv_shaders/continuous_quad_1cp_hs.h"
#include "spirv_shaders/continuous_quad_4cp_hs.h"
#include "spirv_shaders/continuous_triangle_1cp_hs.h"
#include "spirv_shaders/continuous_triangle_3cp_hs.h"
#include "spirv_shaders/discrete_quad_1cp_hs.h"
#include "spirv_shaders/discrete_quad_4cp_hs.h"
#include "spirv_shaders/discrete_triangle_1cp_hs.h"
#include "spirv_shaders/discrete_triangle_3cp_hs.h"
#include "spirv_shaders/tessellation_adaptive_vs.h"
#include "spirv_shaders/tessellation_indexed_vs.h"
}
#endif

#if REXGLUE_SHADER_DXIL
std::unique_ptr<SpirvShaderTranslator> PipelineCache::DxilShaderCacheHost::CreateTranslator()
    const {
  SpirvShaderTranslator::Features features(true);

  features.fragment_shader_sample_interlock = false;

  features.fragment_shader_barycentric = true;
  features.signed_zero_inf_nan_preserve_float32 = false;
  features.denorm_flush_to_zero_float32 = true;
  features.rounding_mode_rte_float32 = false;
  const auto& render_target_cache = pipeline_cache_.render_target_cache_;
  return std::make_unique<SpirvShaderTranslator>(
      features, render_target_cache.msaa_2x_supported(), false,
      render_target_cache.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock, false,
      render_target_cache.draw_resolution_scale_x(), render_target_cache.draw_resolution_scale_y());
}

bool PipelineCache::DxilShaderCacheHost::depth_float24_round() const {
  return pipeline_cache_.render_target_cache_.depth_float24_round();
}

bool PipelineCache::DxilShaderCacheHost::depth_float24_convert_in_pixel_shader() const {
  return pipeline_cache_.render_target_cache_.depth_float24_convert_in_pixel_shader();
}

SpirvShader* PipelineCache::GetDxilShader(const Shader& shader) {
  auto it = dxil_shaders_.find(shader.ucode_data_hash());
  if (it != dxil_shaders_.end()) {
    return it->second.get();
  }
  auto twin =
      std::make_unique<SpirvShader>(shader.type(), shader.ucode_data_hash(), shader.ucode_dwords(),
                                    shader.ucode_dword_count(), std::endian::native);
  twin->AnalyzeUcode(ucode_disasm_buffer_);
  SpirvShader* result = twin.get();
  dxil_shaders_.emplace(shader.ucode_data_hash(), std::move(twin));
  return result;
}

Shader::Translation* PipelineCache::GetDxilSpirv(SpirvShader& shader, uint64_t modification) {
  bool new_translation = !shader.GetOrCreateTranslation(modification)->is_translated();
  auto translate_start = std::chrono::steady_clock::now();
  Shader::Translation* translation = dxil_shader_cache_->EnsureAndTranslate(shader, modification);
  if (new_translation) {
    REXGPU_DEBUG("SPIR-V translation {:016X}: {:.1f} ms", shader.ucode_data_hash(),
                 std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() -
                                                           translate_start)
                     .count());
  }
  if (!translation) {
    REXGPU_WARN("Guest shader {:016X} (modification {:016X}): no SPIR-V, using DXBC",
                shader.ucode_data_hash(), modification);
    return nullptr;
  }
  if (!REXCVAR_GET(dump_shaders).empty()) {
    translation->Dump(REXCVAR_GET(dump_shaders), "spirv");
  }
  return translation;
}

const std::vector<uint8_t>* PipelineCache::ConvertDxil(const Shader::Translation& translation) {
  const Shader& shader = translation.shader();
  {
    std::lock_guard<std::mutex> lock(dxil_binaries_mutex_);
    auto& by_modification = dxil_binaries_[shader.ucode_data_hash()];
    auto it = by_modification.find(translation.modification());
    if (it != by_modification.end()) {
      return it->second.empty() ? nullptr : &it->second;
    }
  }

  const std::vector<uint8_t>& spirv = translation.translated_binary();
  auto convert_start = std::chrono::steady_clock::now();
  std::vector<uint8_t> dxil = SpirvToDxilCompiler::Translate(
      reinterpret_cast<const uint32_t*>(spirv.data()), spirv.size() / sizeof(uint32_t),
      shader.type() == xenos::ShaderType::kVertex ? SpirvToDxilCompiler::Stage::kVertex
                                                  : SpirvToDxilCompiler::Stage::kPixel,
      true);
  REXGPU_DEBUG(
      "DXIL conversion {:016X}: {:.1f} ms", shader.ucode_data_hash(),
      std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - convert_start)
          .count());
  if (dxil.empty()) {
    REXGPU_WARN("Guest shader {:016X} (modification {:016X}): no DXIL", shader.ucode_data_hash(),
                translation.modification());
  }
  std::lock_guard<std::mutex> lock(dxil_binaries_mutex_);
  auto emplaced = dxil_binaries_[shader.ucode_data_hash()].try_emplace(translation.modification(),
                                                                       std::move(dxil));
  return emplaced.first->second.empty() ? nullptr : &emplaced.first->second;
}

namespace {

template <size_t kWords>
void SetSpirv(const uint32_t (&spirv)[kWords], SpirvToDxilCompiler::LinkedStage& stage) {
  stage.spirv_words = spirv;
  stage.spirv_word_count = kWords;
}
bool GetTessellationHostSpirv(xenos::TessellationMode tessellation_mode,
                              Shader::HostVertexShaderType host_vertex_shader_type,
                              SpirvToDxilCompiler::LinkedStage& vertex,
                              SpirvToDxilCompiler::LinkedStage& hull) {
  using HostVertexShaderType = Shader::HostVertexShaderType;
  if (tessellation_mode == xenos::TessellationMode::kAdaptive) {
    SetSpirv(shaders_spirv::tessellation_adaptive_vs, vertex);
  } else {
    SetSpirv(shaders_spirv::tessellation_indexed_vs, vertex);
  }
  switch (tessellation_mode) {
    case xenos::TessellationMode::kDiscrete:
      switch (host_vertex_shader_type) {
        case HostVertexShaderType::kTriangleDomainCPIndexed:
          SetSpirv(shaders_spirv::discrete_triangle_3cp_hs, hull);
          return true;
        case HostVertexShaderType::kTriangleDomainPatchIndexed:
          SetSpirv(shaders_spirv::discrete_triangle_1cp_hs, hull);
          return true;
        case HostVertexShaderType::kQuadDomainCPIndexed:
          SetSpirv(shaders_spirv::discrete_quad_4cp_hs, hull);
          return true;
        case HostVertexShaderType::kQuadDomainPatchIndexed:
          SetSpirv(shaders_spirv::discrete_quad_1cp_hs, hull);
          return true;
        default:
          return false;
      }
    case xenos::TessellationMode::kContinuous:
      switch (host_vertex_shader_type) {
        case HostVertexShaderType::kTriangleDomainCPIndexed:
          SetSpirv(shaders_spirv::continuous_triangle_3cp_hs, hull);
          return true;
        case HostVertexShaderType::kTriangleDomainPatchIndexed:
          SetSpirv(shaders_spirv::continuous_triangle_1cp_hs, hull);
          return true;
        case HostVertexShaderType::kQuadDomainCPIndexed:
          SetSpirv(shaders_spirv::continuous_quad_4cp_hs, hull);
          return true;
        case HostVertexShaderType::kQuadDomainPatchIndexed:
          SetSpirv(shaders_spirv::continuous_quad_1cp_hs, hull);
          return true;
        default:
          return false;
      }
    case xenos::TessellationMode::kAdaptive:
      switch (host_vertex_shader_type) {
        case HostVertexShaderType::kTriangleDomainPatchIndexed:
          SetSpirv(shaders_spirv::adaptive_triangle_hs, hull);
          return true;
        case HostVertexShaderType::kQuadDomainPatchIndexed:
          SetSpirv(shaders_spirv::adaptive_quad_hs, hull);
          return true;
        default:
          return false;
      }
    default:
      return false;
  }
}
}

const PipelineCache::DxilTessellation* PipelineCache::ConvertDxilTessellation(
    const Shader::Translation& translation) {
  const Shader& shader = translation.shader();
  {
    std::lock_guard<std::mutex> lock(dxil_binaries_mutex_);
    auto& by_modification = dxil_tessellation_binaries_[shader.ucode_data_hash()];
    auto it = by_modification.find(translation.modification());
    if (it != by_modification.end()) {
      return it->second.domain.empty() ? nullptr : &it->second;
    }
  }

  SpirvShaderTranslator::Modification modification(translation.modification());
  std::vector<SpirvToDxilCompiler::LinkedStage> stages(3);
  stages[0].stage = SpirvToDxilCompiler::Stage::kVertex;
  stages[1].stage = SpirvToDxilCompiler::Stage::kTessellationControl;
  stages[2].stage = SpirvToDxilCompiler::Stage::kTessellationEvaluation;
  const std::vector<uint8_t>& domain_spirv = translation.translated_binary();
  stages[2].spirv_words = reinterpret_cast<const uint32_t*>(domain_spirv.data());
  stages[2].spirv_word_count = domain_spirv.size() / sizeof(uint32_t);
  std::vector<std::vector<uint8_t>> dxil;
  auto convert_start = std::chrono::steady_clock::now();
  if (GetTessellationHostSpirv(modification.vertex.tessellation_mode,
                               modification.vertex.host_vertex_shader_type, stages[0], stages[1])) {
    dxil = SpirvToDxilCompiler::TranslateLinked(stages, true);
  }
  DxilTessellation tessellation;
  if (dxil.size() == 3 && !dxil[0].empty() && !dxil[1].empty() && !dxil[2].empty()) {
    tessellation.host_vertex = std::move(dxil[0]);
    tessellation.host_hull = std::move(dxil[1]);
    tessellation.domain = std::move(dxil[2]);

    REXGPU_INFO(
        "DXIL tessellation {:016X} (modification {:016X}): VS {} B, HS {} B, DS {} B, {:.1f} ms",
        shader.ucode_data_hash(), translation.modification(), tessellation.host_vertex.size(),
        tessellation.host_hull.size(), tessellation.domain.size(),
        std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - convert_start)
            .count());
  } else {
    REXGPU_WARN("Guest domain shader {:016X} (modification {:016X}): no linked DXIL",
                shader.ucode_data_hash(), translation.modification());
  }
  std::lock_guard<std::mutex> lock(dxil_binaries_mutex_);
  auto emplaced = dxil_tessellation_binaries_[shader.ucode_data_hash()].try_emplace(
      translation.modification(), std::move(tessellation));
  return emplaced.first->second.domain.empty() ? nullptr : &emplaced.first->second;
}

bool PipelineCache::InitializeDxilHelperPixelShaders() {
  SpirvShaderTranslator& translator = dxil_shader_cache_->translator();
  auto convert = [](const std::vector<uint8_t>& spirv) {
    if (spirv.empty()) {
      return std::vector<uint8_t>();
    }
    return SpirvToDxilCompiler::Translate(reinterpret_cast<const uint32_t*>(spirv.data()),
                                          spirv.size() / sizeof(uint32_t),
                                          SpirvToDxilCompiler::Stage::kPixel, true);
  };
  if (render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock) {
    for (uint32_t i = 0; i < 3; ++i) {
      dxil_rov_depth_only_pixel_shaders_[i] =
          convert(translator.CreateDepthOnlyFragmentShader(xenos::MsaaSamples(i)));
      dxil_rov_viz_survey_pixel_shaders_[i] =
          convert(translator.CreateDepthOnlyFragmentShader(xenos::MsaaSamples(i), true));
      if (dxil_rov_depth_only_pixel_shaders_[i].empty() ||
          dxil_rov_viz_survey_pixel_shaders_[i].empty()) {
        return false;
      }
    }
    return true;
  }
  using DepthStencilMode = SpirvShaderTranslator::Modification::DepthStencilMode;
  dxil_depth_only_pixel_shader_ = convert(translator.CreateDepthOnlyFragmentShader());
  if (dxil_depth_only_pixel_shader_.empty()) {
    return false;
  }
  if (render_target_cache_.depth_float24_convert_in_pixel_shader()) {
    dxil_float24_truncate_pixel_shader_ =
        convert(translator.CreateDepthOnlyFragmentShader(DepthStencilMode::kFloat24Truncating));
    dxil_float24_round_pixel_shader_ =
        convert(translator.CreateDepthOnlyFragmentShader(DepthStencilMode::kFloat24Rounding));
    if (dxil_float24_truncate_pixel_shader_.empty() || dxil_float24_round_pixel_shader_.empty()) {
      return false;
    }
  }
  if (zpd_hybrid_supported_) {
    dxil_zpd_total_depth_only_pixel_shader_ =
        convert(translator.CreateDepthOnlyFragmentShader(DepthStencilMode::kNoModifiers, true));
    if (dxil_zpd_total_depth_only_pixel_shader_.empty()) {
      return false;
    }
    if (render_target_cache_.depth_float24_convert_in_pixel_shader()) {
      dxil_zpd_total_float24_truncate_pixel_shader_ = convert(
          translator.CreateDepthOnlyFragmentShader(DepthStencilMode::kFloat24Truncating, true));
      dxil_zpd_total_float24_round_pixel_shader_ = convert(
          translator.CreateDepthOnlyFragmentShader(DepthStencilMode::kFloat24Rounding, true));
      if (dxil_zpd_total_float24_truncate_pixel_shader_.empty() ||
          dxil_zpd_total_float24_round_pixel_shader_.empty()) {
        return false;
      }
    }
  }
  return true;
}

const std::vector<uint8_t>* PipelineCache::GetDxilHelperPixelShader(
    const PipelineDescription& description) const {
  if (render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock) {
    size_t msaa_samples =
        size_t(SpirvShaderTranslator::Modification(description.pixel_shader_modification)
                   .pixel.fsi_msaa_samples());
    if (msaa_samples >= 3) {
      return nullptr;
    }
    return description.viz_survey ? &dxil_rov_viz_survey_pixel_shaders_[msaa_samples]
                                  : &dxil_rov_depth_only_pixel_shaders_[msaa_samples];
  }

  const bool float24_converted =
      render_target_cache_.depth_float24_convert_in_pixel_shader() &&
      (description.depth_func != xenos::CompareFunction::kAlways || description.depth_write) &&
      description.depth_format == xenos::DepthRenderTargetFormat::kD24FS8;
  if (description.zpd_total) {
    if (dxil_zpd_total_depth_only_pixel_shader_.empty()) {
      return nullptr;
    }
    if (float24_converted) {
      return render_target_cache_.depth_float24_round()
                 ? &dxil_zpd_total_float24_round_pixel_shader_
                 : &dxil_zpd_total_float24_truncate_pixel_shader_;
    }
    return &dxil_zpd_total_depth_only_pixel_shader_;
  }
  if (float24_converted) {
    return render_target_cache_.depth_float24_round() ? &dxil_float24_round_pixel_shader_
                                                      : &dxil_float24_truncate_pixel_shader_;
  }
  if (!description.depth_write && !description.stencil_write_mask) {
    return &dxil_depth_only_pixel_shader_;
  }
  return nullptr;
}

const std::vector<uint8_t>* PipelineCache::GetDxilGeometryShader(
    GuestSpirvShaderCache::GeometryShaderKey key) {
  auto it = dxil_geometry_shaders_.find(key.key);
  if (it != dxil_geometry_shaders_.end()) {
    return it->second.empty() ? nullptr : &it->second;
  }

  const SpirvShaderTranslator::Features& features = dxil_shader_cache_->translator().features();
  std::vector<unsigned int> spirv = BuildGuestPrimitiveGeometryShaderSpirv(
      BuiltinGeometryShaderType(uint32_t(key.type)), key.interpolator_count,
      key.user_clip_plane_count, key.user_clip_plane_cull, key.has_vertex_kill_and,
      key.has_point_size, key.has_point_coordinates, features.spirv_version,
      features.denorm_flush_to_zero_float32, features.signed_zero_inf_nan_preserve_float32,
      features.rounding_mode_rte_float32);
  std::vector<uint8_t> dxil = SpirvToDxilCompiler::Translate(
      spirv.data(), spirv.size(), SpirvToDxilCompiler::Stage::kGeometry, true,
      key.user_clip_plane_cull ? 0 : key.user_clip_plane_count);
  auto emplaced = dxil_geometry_shaders_.emplace(key.key, std::move(dxil));
  return emplaced.first->second.empty() ? nullptr : &emplaced.first->second;
}

PipelineCache::DxilPipelineResult PipelineCache::ConfigurePipelineDxil(
    D3D12Shader::D3D12Translation* dxbc_vertex_shader,
    D3D12Shader::D3D12Translation* dxbc_pixel_shader,
    const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
    uint32_t interpolator_mask, uint32_t ps_param_gen_pos,
    reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask,
    uint32_t bound_depth_and_color_render_target_bits,
    const uint32_t* bound_depth_and_color_render_target_formats, bool zpd_total, bool viz_survey,
    void** pipeline_handle_out, SpirvShader** vertex_shader_out, SpirvShader** pixel_shader_out) {
  if (!dxil_shader_cache_ || (primitive_processing_result.host_vertex_shader_type !=
                                  Shader::HostVertexShaderType::kVertex &&
                              !primitive_processing_result.IsTessellated())) {
    return DxilPipelineResult::kUnsupported;
  }
  bool edram_rov_used =
      render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;
  if (zpd_total && edram_rov_used) {
    return DxilPipelineResult::kUnsupported;
  }

  if (!shader_replacements_.empty()) {
    auto replaced = [&](const D3D12Shader::D3D12Translation& translation,
                        ShaderReplacements::Stage stage) {
      return shader_replacements_.Find(translation.shader().ucode_data_hash(), stage,
                                       translation.modification()) != nullptr;
    };
    if (replaced(*dxbc_vertex_shader, ShaderReplacements::Stage::kVertex) ||
        (dxbc_pixel_shader &&
         replaced(*dxbc_pixel_shader, edram_rov_used ? ShaderReplacements::Stage::kPixelRov
                                                     : ShaderReplacements::Stage::kPixelRtv))) {
      return DxilPipelineResult::kUnsupported;
    }
  }

  SpirvShader* vertex_shader = GetDxilShader(dxbc_vertex_shader->shader());
  SpirvShader* pixel_shader =
      dxbc_pixel_shader ? GetDxilShader(dxbc_pixel_shader->shader()) : nullptr;
  uint64_t vertex_modification = dxil_shader_cache_->GetVertexShaderModification(
      *vertex_shader, primitive_processing_result.host_vertex_shader_type, interpolator_mask,
      false);
  uint64_t pixel_modification = pixel_shader
                                    ? dxil_shader_cache_->GetPixelShaderModification(
                                          *pixel_shader, interpolator_mask, ps_param_gen_pos,
                                          normalized_depth_control, normalized_color_mask, false)
                                    : 0;
  if (zpd_total) {
    SpirvShaderTranslator::Modification counting_modification(pixel_modification);
    counting_modification.pixel.set_zpd_total(true);
    pixel_modification = counting_modification.value;
  }

  const Shader::Translation* vertex_spirv = GetDxilSpirv(*vertex_shader, vertex_modification);
  const Shader::Translation* pixel_spirv =
      pixel_shader ? GetDxilSpirv(*pixel_shader, pixel_modification) : nullptr;
  if (!vertex_spirv || (pixel_shader && !pixel_spirv)) {
    return DxilPipelineResult::kFailed;
  }

  PipelineRuntimeDescription runtime_description;
  if (!GetCurrentStateDescription(
          dxbc_vertex_shader, dxbc_pixel_shader, primitive_processing_result,
          normalized_depth_control, normalized_color_mask, zpd_total, viz_survey,
          bound_depth_and_color_render_target_bits, bound_depth_and_color_render_target_formats,
          runtime_description, true)) {
    return DxilPipelineResult::kFailed;
  }
  PipelineDescription& description = runtime_description.description;
  description.dxil = 1;
  description.vertex_shader_modification = vertex_modification;
  description.pixel_shader_modification = pixel_modification;
  runtime_description.root_signature = command_processor_.GetDxilRootSignature();
  runtime_description.geometry_shader = nullptr;
  runtime_description.dxil_vertex_spirv = vertex_spirv;
  runtime_description.dxil_pixel_spirv = pixel_spirv;
  GuestSpirvShaderCache::GeometryShaderKey geometry_shader_key;
  if (GuestSpirvShaderCache::GetGeometryShaderKey(
          rex::graphics::PipelineGeometryShader(uint32_t(description.geometry_shader)),
          vertex_modification, pixel_modification, geometry_shader_key)) {
    runtime_description.dxil_geometry_shader = GetDxilGeometryShader(geometry_shader_key);
    if (!runtime_description.dxil_geometry_shader) {
      return DxilPipelineResult::kFailed;
    }
  }
  if (edram_rov_used && !pixel_shader) {
    SpirvShaderTranslator::Modification rov_depth_only_modification(0);
    rov_depth_only_modification.pixel.set_fsi_msaa_samples(
        register_file_.Get<reg::RB_SURFACE_INFO>().msaa_samples);
    description.pixel_shader_modification = rov_depth_only_modification.value;
  }

  uint64_t hash = XXH3_64bits(&description, sizeof(description));
  Pipeline* pipeline = nullptr;
  auto found_range = pipelines_.equal_range(hash);
  for (auto it = found_range.first; it != found_range.second; ++it) {
    if (!std::memcmp(&it->second->description.description, &description, sizeof(description))) {
      pipeline = it->second;
      break;
    }
  }
  if (!pipeline) {
    pipeline = new Pipeline;
    std::memcpy(&pipeline->description, &runtime_description, sizeof(runtime_description));
    pipeline->root_signature.store(runtime_description.root_signature, std::memory_order_release);
    pipelines_.emplace(hash, pipeline);
    StoreDxilPipeline(hash, description, dxbc_vertex_shader->shader(),
                      dxbc_pixel_shader ? &dxbc_pixel_shader->shader() : nullptr);
    if (REXCVAR_GET(async_shader_compilation) && !creation_threads_.empty()) {
      pipeline->priority = pipeline_util::CalculatePipelinePriority(
          pipeline_util::GetBoundRTMaskFromNormalizedColorMask(normalized_color_mask),
          pixel_shader ? pixel_shader->writes_color_targets() : 0,
          pixel_shader ? pixel_shader->writes_depth()
                       : normalized_depth_control.z_write_enable != 0);
      pipeline->creation_pending.store(true, std::memory_order_relaxed);
      {
        std::lock_guard<std::mutex> lock(creation_request_lock_);
        creation_queue_.push(pipeline);
      }
      creation_request_cond_.notify_one();
      current_pipeline_ = pipeline;
      *pipeline_handle_out = pipeline;
      *vertex_shader_out = vertex_shader;
      *pixel_shader_out = pixel_shader;
      return DxilPipelineResult::kConfigured;
    }
    pipeline->state.store(CreateD3D12Pipeline(runtime_description), std::memory_order_release);
    REXGPU_DEBUG("DXIL pipeline: VS {:016X} ({:016X}), PS {:016X} ({:016X}){}",
                 vertex_shader->ucode_data_hash(), vertex_modification,
                 pixel_shader ? pixel_shader->ucode_data_hash() : 0, pixel_modification,
                 pipeline->state.load(std::memory_order_relaxed) ? "" : " - creation failed");
  }

  if (!pipeline->state.load(std::memory_order_acquire) &&
      !pipeline->creation_pending.load(std::memory_order_acquire)) {
    return DxilPipelineResult::kFailed;
  }
  current_pipeline_ = pipeline;
  *pipeline_handle_out = pipeline;
  *vertex_shader_out = vertex_shader;
  *pixel_shader_out = pixel_shader;
  return DxilPipelineResult::kConfigured;
}
void PipelineCache::StoreDxilPipeline(uint64_t hash, const PipelineDescription& description,
                                      Shader& vertex_shader, Shader* pixel_shader) {
  if (shader_storage_file_) {
    for (Shader* shader : {&vertex_shader, pixel_shader}) {
      if (shader && shader->ucode_storage_index() != shader_storage_index_) {
        shader->set_ucode_storage_index(shader_storage_index_);
        shader_storage_file_flush_needed_ = true;
        {
          std::lock_guard<std::mutex> storage_lock(storage_write_request_lock_);
          storage_write_shader_queue_.push_back(shader);
        }
        storage_write_request_cond_.notify_all();
      }
    }
  }
  if (pipeline_storage_file_) {
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
}

bool PipelineCache::CreateStoredDxilPipeline(const PipelineStoredDescription& stored_description) {
  if (!dxil_shader_cache_) {
    return false;
  }
  const PipelineDescription& description = stored_description.description;
  auto vertex_shader_it = shaders_.find(description.vertex_shader_hash);
  if (vertex_shader_it == shaders_.end()) {
    return false;
  }
  SpirvShader* vertex_shader = GetDxilShader(*vertex_shader_it->second);
  SpirvShader* pixel_shader = nullptr;
  if (description.pixel_shader_hash) {
    auto pixel_shader_it = shaders_.find(description.pixel_shader_hash);
    if (pixel_shader_it == shaders_.end()) {
      return false;
    }
    pixel_shader = GetDxilShader(*pixel_shader_it->second);
  }
  PipelineRuntimeDescription runtime_description;
  std::memset(&runtime_description, 0, sizeof(runtime_description));
  runtime_description.dxil_vertex_spirv =
      GetDxilSpirv(*vertex_shader, description.vertex_shader_modification);
  runtime_description.dxil_pixel_spirv =
      pixel_shader ? GetDxilSpirv(*pixel_shader, description.pixel_shader_modification) : nullptr;
  if (!runtime_description.dxil_vertex_spirv ||
      (pixel_shader && !runtime_description.dxil_pixel_spirv)) {
    return false;
  }
  GuestSpirvShaderCache::GeometryShaderKey geometry_shader_key;
  if (GuestSpirvShaderCache::GetGeometryShaderKey(
          rex::graphics::PipelineGeometryShader(uint32_t(description.geometry_shader)),
          description.vertex_shader_modification,
          description.pixel_shader_hash ? description.pixel_shader_modification : 0,
          geometry_shader_key)) {
    runtime_description.dxil_geometry_shader = GetDxilGeometryShader(geometry_shader_key);
    if (!runtime_description.dxil_geometry_shader) {
      return false;
    }
  }
  runtime_description.root_signature = command_processor_.GetDxilRootSignature();
  std::memcpy(&runtime_description.description, &description, sizeof(description));

  Pipeline* pipeline = new Pipeline;
  std::memcpy(&pipeline->description, &runtime_description, sizeof(runtime_description));
  pipeline->root_signature.store(runtime_description.root_signature, std::memory_order_release);
  uint32_t bound_rts = 0;
  for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
    if (description.render_targets[i].used) {
      bound_rts |= uint32_t(1) << i;
    }
  }
  pipeline->priority = pipeline_util::CalculatePipelinePriority(
      bound_rts, pixel_shader ? pixel_shader->writes_color_targets() : 0,
      pixel_shader ? pixel_shader->writes_depth() : description.depth_write != 0);
  pipelines_.emplace(stored_description.description_hash, pipeline);
  if (!creation_threads_.empty()) {
    pipeline->creation_pending.store(true, std::memory_order_relaxed);
    {
      std::lock_guard<std::mutex> lock(creation_request_lock_);
      creation_queue_.push(pipeline);
    }
    creation_request_cond_.notify_one();
  } else {
    pipeline->state.store(CreateD3D12Pipeline(runtime_description), std::memory_order_release);
  }
  return true;
}
#endif

}

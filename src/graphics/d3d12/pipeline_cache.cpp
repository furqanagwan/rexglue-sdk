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

void PipelineCache::InitializeShaderStorage(const std::filesystem::path& cache_root,
                                            uint32_t title_id, bool blocking) {
  ShutdownShaderStorage();

  auto shader_storage_root = cache_root / "shaders";

  auto shader_storage_shareable_root = shader_storage_root / "shareable";
  if (!std::filesystem::exists(shader_storage_shareable_root)) {
    if (!std::filesystem::create_directories(shader_storage_shareable_root)) {
      REXGPU_ERROR(
          "Failed to create the shareable shader storage directory, persistent "
          "shader storage will be disabled: {}",
          rex::path_to_utf8(shader_storage_shareable_root));
      return;
    }
  }

  bool edram_rov_used =
      render_target_cache_.GetPath() == RenderTargetCache::Path::kPixelShaderInterlock;

  std::vector<PipelineStoredDescription> pipeline_stored_descriptions;

  std::set<std::pair<uint64_t, uint64_t>> shader_translations_needed;
  auto pipeline_storage_file_path =
      shader_storage_shareable_root /
      fmt::format("{:08X}.{}{}.d3d12.xpso", title_id, edram_rov_used ? "rov" : "rtv",

                  edram_rov_used && REXCVAR_GET(occlusion_query_full_counters) ? "-fc" : "");

  const std::filesystem::path shipped_root =
      REXCVAR_GET(shader_cache_shipped).empty()
          ? rex::filesystem::GetExecutableFolder() / "shader_cache"
          : std::filesystem::path(REXCVAR_GET(shader_cache_shipped));
  auto seed = [&](const std::filesystem::path& file, const StorageFormat& format) {
    const SeedOutcome outcome = SeedStorageFile(shipped_root / file.filename(), file, format);
    switch (outcome.result) {
      case SeedResult::kCopied:
      case SeedResult::kMerged:
        REXGPU_INFO("Shipped shader cache: {} records of {} added", outcome.added,
                    rex::path_to_utf8(file.filename()));
        break;
      case SeedResult::kStale:
        REXGPU_WARN("Shipped shader cache: {} is from another SDK version; not used",
                    rex::path_to_utf8(file.filename()));
        break;
      case SeedResult::kFailed:
        REXGPU_WARN("Shipped shader cache: {}", outcome.error);
        break;
      default:
        break;
    }
  };
  {
    const struct {
      uint32_t magic, magic_api, version_swapped;
    } header = {0x53504558, edram_rov_used ? 0x4F525844u : 0x54525844u,
                rex::byte_swap(std::max(PipelineDescription::kVersion,
                                        DxbcShaderTranslator::Modification::kVersion))};
    seed(pipeline_storage_file_path,
         {std::span(reinterpret_cast<const uint8_t*>(&header), sizeof(header)),
          sizeof(PipelineStoredDescription)});
  }
  pipeline_storage_file_ = rex::filesystem::OpenFile(pipeline_storage_file_path, "a+b");
  if (!pipeline_storage_file_) {
    REXGPU_ERROR(
        "Failed to open the Direct3D 12 pipeline description storage file for "
        "writing, persistent shader storage will be disabled: {}",
        rex::path_to_utf8(pipeline_storage_file_path));
    return;
  }
  pipeline_storage_file_flush_needed_ = false;

  const uint32_t pipeline_storage_magic = 0x53504558;

  const uint32_t pipeline_storage_magic_api = edram_rov_used ? 0x4F525844 : 0x54525844;
  const uint32_t pipeline_storage_version_swapped = rex::byte_swap(
      std::max(PipelineDescription::kVersion, DxbcShaderTranslator::Modification::kVersion));
  struct {
    uint32_t magic;
    uint32_t magic_api;
    uint32_t version_swapped;
  } pipeline_storage_file_header;
  if (fread(&pipeline_storage_file_header, sizeof(pipeline_storage_file_header), 1,
            pipeline_storage_file_) &&
      pipeline_storage_file_header.magic == pipeline_storage_magic &&
      pipeline_storage_file_header.magic_api == pipeline_storage_magic_api &&
      pipeline_storage_file_header.version_swapped == pipeline_storage_version_swapped) {
    rex::filesystem::Seek(pipeline_storage_file_, 0, SEEK_END);
    int64_t pipeline_storage_told_end = rex::filesystem::Tell(pipeline_storage_file_);
    size_t pipeline_storage_told_count =
        size_t(pipeline_storage_told_end >= int64_t(sizeof(pipeline_storage_file_header))
                   ? (uint64_t(pipeline_storage_told_end) - sizeof(pipeline_storage_file_header)) /
                         sizeof(PipelineStoredDescription)
                   : 0);
    if (pipeline_storage_told_count &&
        rex::filesystem::Seek(pipeline_storage_file_, int64_t(sizeof(pipeline_storage_file_header)),
                              SEEK_SET)) {
      pipeline_stored_descriptions.resize(pipeline_storage_told_count);
      pipeline_stored_descriptions.resize(
          fread(pipeline_stored_descriptions.data(), sizeof(PipelineStoredDescription),
                pipeline_storage_told_count, pipeline_storage_file_));
      size_t pipeline_storage_read_count = pipeline_stored_descriptions.size();
      for (size_t i = 0; i < pipeline_storage_read_count; ++i) {
        const PipelineStoredDescription& pipeline_stored_description =
            pipeline_stored_descriptions[i];

        if (XXH3_64bits(&pipeline_stored_description.description,
                        sizeof(pipeline_stored_description.description)) !=
            pipeline_stored_description.description_hash) {
          pipeline_stored_descriptions.resize(i);
          break;
        }

        if (pipeline_stored_description.description.dxil) {
          continue;
        }
        shader_translations_needed.emplace(
            pipeline_stored_description.description.vertex_shader_hash,
            pipeline_stored_description.description.vertex_shader_modification);
        if (pipeline_stored_description.description.pixel_shader_hash) {
          shader_translations_needed.emplace(
              pipeline_stored_description.description.pixel_shader_hash,
              pipeline_stored_description.description.pixel_shader_modification);
        }
      }
    }
  }

  size_t logical_processor_count = rex::thread::logical_processor_count();
  if (!logical_processor_count) {
    logical_processor_count = 6;
  }

  uint64_t shader_storage_initialization_start = rex::chrono::Clock::QueryHostTickCount();
  auto shader_storage_file_path =
      shader_storage_shareable_root / fmt::format("{:08X}.xsh", title_id);
  {
    const struct {
      uint32_t magic, version_swapped;
    } header = {0x48534558, rex::byte_swap(ShaderStoredHeader::kVersion)};
    static_assert(sizeof(ShaderStoredHeader) == 12);
    seed(shader_storage_file_path,
         {std::span(reinterpret_cast<const uint8_t*>(&header), sizeof(header)), 0});
  }
  shader_storage_file_ = rex::filesystem::OpenFile(shader_storage_file_path, "a+b");
  if (!shader_storage_file_) {
    REXGPU_ERROR(
        "Failed to open the guest shader storage file for writing, persistent "
        "shader storage will be disabled: {}",
        rex::path_to_utf8(shader_storage_file_path));
    fclose(pipeline_storage_file_);
    pipeline_storage_file_ = nullptr;
    return;
  }
  ++shader_storage_index_;
  shader_storage_file_flush_needed_ = false;
  struct {
    uint32_t magic;
    uint32_t version_swapped;
  } shader_storage_file_header;

  const uint32_t shader_storage_magic = 0x48534558;
  if (fread(&shader_storage_file_header, sizeof(shader_storage_file_header), 1,
            shader_storage_file_) &&
      shader_storage_file_header.magic == shader_storage_magic &&
      rex::byte_swap(shader_storage_file_header.version_swapped) == ShaderStoredHeader::kVersion) {
    uint64_t shader_storage_valid_bytes = sizeof(shader_storage_file_header);

    ShaderStoredHeader shader_header;
    std::vector<uint32_t> ucode_dwords;
    ucode_dwords.reserve(0xFFFF);
    size_t shaders_translated = 0;

    std::mutex shaders_translation_thread_mutex;
    std::condition_variable shaders_translation_thread_cond;
    std::deque<D3D12Shader*> shaders_to_translate;
    size_t shader_translation_threads_busy = 0;
    bool shader_translation_threads_shutdown = false;
    std::mutex shaders_failed_to_translate_mutex;
    std::vector<D3D12Shader::D3D12Translation*> shaders_failed_to_translate;
    auto shader_translation_thread_function = [&]() {
      const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
      string::StringBuffer ucode_disasm_buffer;
      DxbcShaderTranslator translator(
          provider.GetAdapterVendorID(), bindless_resources_used_, edram_rov_used,
          !render_target_cache_.gamma_render_target_as_unorm16(),
          render_target_cache_.msaa_2x_supported(), render_target_cache_.draw_resolution_scale_x(),
          render_target_cache_.draw_resolution_scale_y(),
          provider.GetGraphicsAnalysis() != nullptr);

      IDxbcConverter* dxbc_converter = nullptr;
      IDxcUtils* dxc_utils = nullptr;
      IDxcCompiler* dxc_compiler = nullptr;
      if (REXCVAR_GET(d3d12_dxbc_disasm_dxilconv) && dxbc_converter_ && dxc_utils_ &&
          dxc_compiler_) {
        provider.DxbcConverterCreateInstance(CLSID_DxbcConverter, IID_PPV_ARGS(&dxbc_converter));
        provider.DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxc_utils));
        provider.DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxc_compiler));
      }
      for (;;) {
        D3D12Shader* shader_to_translate;
        for (;;) {
          std::unique_lock<std::mutex> lock(shaders_translation_thread_mutex);
          if (shaders_to_translate.empty()) {
            if (shader_translation_threads_shutdown) {
              return;
            }
            shaders_translation_thread_cond.wait(lock);
            continue;
          }
          shader_to_translate = shaders_to_translate.front();
          shaders_to_translate.pop_front();
          ++shader_translation_threads_busy;
          break;
        }
        shader_to_translate->AnalyzeUcode(ucode_disasm_buffer);

        uint64_t ucode_data_hash = shader_to_translate->ucode_data_hash();
        for (auto modification_it = shader_translations_needed.lower_bound(
                 std::make_pair(ucode_data_hash, uint64_t(0)));
             modification_it != shader_translations_needed.end() &&
             modification_it->first == ucode_data_hash;
             ++modification_it) {
          D3D12Shader::D3D12Translation* translation = static_cast<D3D12Shader::D3D12Translation*>(
              shader_to_translate->GetOrCreateTranslation(modification_it->second));

          if (!translation->is_translated() &&
              !TranslateAnalyzedShader(translator, *translation, dxbc_converter, dxc_utils,
                                       dxc_compiler)) {
            std::lock_guard<std::mutex> lock(shaders_failed_to_translate_mutex);
            shaders_failed_to_translate.push_back(translation);
          }
        }
        {
          std::lock_guard<std::mutex> lock(shaders_translation_thread_mutex);
          --shader_translation_threads_busy;
        }
      }
      if (dxc_compiler) {
        dxc_compiler->Release();
      }
      if (dxc_utils) {
        dxc_utils->Release();
      }
      if (dxbc_converter) {
        dxbc_converter->Release();
      }
    };
    std::vector<std::unique_ptr<rex::thread::Thread>> shader_translation_threads;

    while (true) {
      if (!fread(&shader_header, sizeof(shader_header), 1, shader_storage_file_)) {
        break;
      }
      size_t ucode_byte_count = shader_header.ucode_dword_count * sizeof(uint32_t);
      ucode_dwords.resize(shader_header.ucode_dword_count);
      if (shader_header.ucode_dword_count &&
          !fread(ucode_dwords.data(), ucode_byte_count, 1, shader_storage_file_)) {
        break;
      }
      uint64_t ucode_data_hash = XXH3_64bits(ucode_dwords.data(), ucode_byte_count);
      if (shader_header.ucode_data_hash != ucode_data_hash) {
        break;
      }
      shader_storage_valid_bytes += sizeof(shader_header) + ucode_byte_count;
      D3D12Shader* shader = LoadShader(shader_header.type, ucode_dwords.data(),
                                       shader_header.ucode_dword_count, ucode_data_hash);
      if (shader->ucode_storage_index() == shader_storage_index_) {
        continue;
      }

      shader->set_ucode_storage_index(shader_storage_index_);

      size_t shader_translation_threads_needed;
      {
        std::lock_guard<std::mutex> lock(shaders_translation_thread_mutex);
        shader_translation_threads_needed =
            std::min(shader_translation_threads_busy + shaders_to_translate.size() + size_t(1),
                     logical_processor_count - size_t(1));
      }
      while (shader_translation_threads.size() < shader_translation_threads_needed) {
        auto thread = rex::thread::Thread::Create({}, shader_translation_thread_function);
        assert_not_null(thread);
        thread->set_name("Shader Translation");
        shader_translation_threads.push_back(std::move(thread));
      }

      {
        std::lock_guard<std::mutex> lock(shaders_translation_thread_mutex);
        shaders_to_translate.push_back(shader);
      }
      shaders_translation_thread_cond.notify_one();
      ++shaders_translated;
    }
    if (!shader_translation_threads.empty()) {
      {
        std::lock_guard<std::mutex> lock(shaders_translation_thread_mutex);
        shader_translation_threads_shutdown = true;
      }
      shaders_translation_thread_cond.notify_all();
      for (auto& shader_translation_thread : shader_translation_threads) {
        rex::thread::Wait(shader_translation_thread.get(), false);
      }
      shader_translation_threads.clear();
      for (D3D12Shader::D3D12Translation* translation : shaders_failed_to_translate) {
        D3D12Shader* shader = static_cast<D3D12Shader*>(&translation->shader());
        shader->DestroyTranslation(translation->modification());
        if (shader->translations().empty()) {
          shaders_.erase(shader->ucode_data_hash());
          delete shader;
        }
      }
    }
    REXGPU_INFO("Translated {} shaders from the storage in {} milliseconds", shaders_translated,
                (rex::chrono::Clock::QueryHostTickCount() - shader_storage_initialization_start) *
                    1000 / rex::chrono::Clock::QueryHostTickFrequency());
    rex::filesystem::TruncateStdioFile(shader_storage_file_, shader_storage_valid_bytes);
  } else {
    rex::filesystem::TruncateStdioFile(shader_storage_file_, 0);
    shader_storage_file_header.magic = shader_storage_magic;
    shader_storage_file_header.version_swapped = rex::byte_swap(ShaderStoredHeader::kVersion);
    fwrite(&shader_storage_file_header, sizeof(shader_storage_file_header), 1,
           shader_storage_file_);
  }

  if (!pipeline_stored_descriptions.empty()) {
    uint64_t pipeline_creation_start_ = rex::chrono::Clock::QueryHostTickCount();

    size_t creation_thread_original_count = creation_threads_.size();
    size_t creation_thread_needed_count =
        std::max(std::min(pipeline_stored_descriptions.size(), logical_processor_count) - size_t(1),
                 creation_thread_original_count);
    while (creation_threads_.size() < creation_thread_original_count) {
      size_t creation_thread_index = creation_threads_.size();
      std::unique_ptr<rex::thread::Thread> creation_thread = rex::thread::Thread::Create(
          {}, [this, creation_thread_index]() { CreationThread(creation_thread_index); });
      assert_not_null(creation_thread);
      creation_thread->set_name("D3D12 Pipelines");
      creation_threads_.push_back(std::move(creation_thread));
    }

    size_t pipelines_created = 0;
    for (const PipelineStoredDescription& pipeline_stored_description :
         pipeline_stored_descriptions) {
      const PipelineDescription& pipeline_description = pipeline_stored_description.description;

      auto found_range = pipelines_.equal_range(pipeline_stored_description.description_hash);
      bool pipeline_found = false;
      for (auto it = found_range.first; it != found_range.second; ++it) {
        Pipeline* found_pipeline = it->second;
        if (!std::memcmp(&found_pipeline->description.description, &pipeline_description,
                         sizeof(pipeline_description))) {
          pipeline_found = true;
          break;
        }
      }
      if (pipeline_found) {
        continue;
      }

      if (pipeline_description.dxil) {
#if REXGLUE_SHADER_DXIL
        if (CreateStoredDxilPipeline(pipeline_stored_description)) {
          ++pipelines_created;
        }
#endif
        continue;
      }

      PipelineRuntimeDescription pipeline_runtime_description;
      auto vertex_shader_it = shaders_.find(pipeline_description.vertex_shader_hash);
      if (vertex_shader_it == shaders_.end()) {
        continue;
      }
      D3D12Shader* vertex_shader = vertex_shader_it->second;
      pipeline_runtime_description.vertex_shader = static_cast<D3D12Shader::D3D12Translation*>(
          vertex_shader->GetTranslation(pipeline_description.vertex_shader_modification));
      if (!pipeline_runtime_description.vertex_shader ||
          !pipeline_runtime_description.vertex_shader->is_translated() ||
          !pipeline_runtime_description.vertex_shader->is_valid()) {
        continue;
      }
      D3D12Shader* pixel_shader;
      if (pipeline_description.pixel_shader_hash) {
        auto pixel_shader_it = shaders_.find(pipeline_description.pixel_shader_hash);
        if (pixel_shader_it == shaders_.end()) {
          continue;
        }
        pixel_shader = pixel_shader_it->second;
        pipeline_runtime_description.pixel_shader = static_cast<D3D12Shader::D3D12Translation*>(
            pixel_shader->GetTranslation(pipeline_description.pixel_shader_modification));
        if (!pipeline_runtime_description.pixel_shader ||
            !pipeline_runtime_description.pixel_shader->is_translated() ||
            !pipeline_runtime_description.pixel_shader->is_valid()) {
          continue;
        }
      } else {
        pixel_shader = nullptr;
        pipeline_runtime_description.pixel_shader = nullptr;
      }
      GeometryShaderKey pipeline_geometry_shader_key;
      pipeline_runtime_description.geometry_shader =
          GetGeometryShaderKey(
              pipeline_description.geometry_shader,
              DxbcShaderTranslator::Modification(pipeline_description.vertex_shader_modification),
              DxbcShaderTranslator::Modification(pipeline_description.pixel_shader_modification),
              pipeline_geometry_shader_key)
              ? &GetGeometryShader(pipeline_geometry_shader_key)
              : nullptr;
      pipeline_runtime_description.root_signature = command_processor_.GetRootSignature(
          vertex_shader, pixel_shader,
          Shader::IsHostVertexShaderTypeDomain(
              DxbcShaderTranslator::Modification(pipeline_description.vertex_shader_modification)
                  .vertex.host_vertex_shader_type));
      if (!pipeline_runtime_description.root_signature) {
        continue;
      }
      std::memcpy(&pipeline_runtime_description.description, &pipeline_description,
                  sizeof(pipeline_description));

      Pipeline* new_pipeline = new Pipeline;
      std::memcpy(&new_pipeline->description, &pipeline_runtime_description,
                  sizeof(pipeline_runtime_description));
      new_pipeline->root_signature.store(pipeline_runtime_description.root_signature,
                                         std::memory_order_release);
      uint32_t bound_rts = 0;
      for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
        if (pipeline_runtime_description.description.render_targets[i].used) {
          bound_rts |= uint32_t(1) << i;
        }
      }
      uint32_t shader_writes_color_targets =
          pipeline_runtime_description.pixel_shader
              ? pipeline_runtime_description.pixel_shader->shader().writes_color_targets()
              : 0;
      bool shader_writes_depth =
          pipeline_runtime_description.pixel_shader
              ? pipeline_runtime_description.pixel_shader->shader().writes_depth()
              : pipeline_runtime_description.description.depth_write != 0;
      new_pipeline->priority = pipeline_util::CalculatePipelinePriority(
          bound_rts, shader_writes_color_targets, shader_writes_depth);
      pipelines_.emplace(pipeline_stored_description.description_hash, new_pipeline);
      COUNT_profile_set("gpu/pipeline_cache/pipelines", pipelines_.size());
      if (!creation_threads_.empty()) {
        new_pipeline->creation_pending.store(true, std::memory_order_relaxed);
        {
          std::lock_guard<std::mutex> lock(creation_request_lock_);
          creation_queue_.push(new_pipeline);
        }
        creation_request_cond_.notify_one();
      } else {
        new_pipeline->state.store(CreateD3D12Pipeline(pipeline_runtime_description),
                                  std::memory_order_release);
      }
      ++pipelines_created;
    }

    if (!creation_threads_.empty()) {
      CreateQueuedPipelinesOnProcessorThread();
      if (creation_threads_.size() > creation_thread_original_count) {
        {
          std::lock_guard<std::mutex> lock(creation_request_lock_);
          creation_threads_shutdown_from_ = creation_thread_original_count;
        }
        creation_request_cond_.notify_all();
        while (creation_threads_.size() > creation_thread_original_count) {
          rex::thread::Wait(creation_threads_.back().get(), false);
          creation_threads_.pop_back();
        }
        bool await_creation_completion_event;
        {
          std::lock_guard<std::mutex> lock(creation_request_lock_);
          creation_threads_shutdown_from_ = SIZE_MAX;

          await_creation_completion_event = blocking && creation_threads_busy_ != 0;
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

    REXGPU_INFO(
        "Created {} graphics pipelines (not including reading the "
        "descriptions) from the storage in {} milliseconds",
        pipelines_created,
        (rex::chrono::Clock::QueryHostTickCount() - pipeline_creation_start_) * 1000 /
            rex::chrono::Clock::QueryHostTickFrequency());

    rex::filesystem::TruncateStdioFile(
        pipeline_storage_file_,
        uint64_t(sizeof(pipeline_storage_file_header) +
                 sizeof(PipelineStoredDescription) * pipeline_stored_descriptions.size()));
  } else {
    rex::filesystem::TruncateStdioFile(pipeline_storage_file_, 0);
    pipeline_storage_file_header.magic = pipeline_storage_magic;
    pipeline_storage_file_header.magic_api = pipeline_storage_magic_api;
    pipeline_storage_file_header.version_swapped = pipeline_storage_version_swapped;
    fwrite(&pipeline_storage_file_header, sizeof(pipeline_storage_file_header), 1,
           pipeline_storage_file_);
  }

  shader_storage_cache_root_ = cache_root;
  shader_storage_title_id_ = title_id;

  storage_write_flush_shaders_ = false;
  storage_write_flush_pipelines_ = false;
  storage_write_thread_shutdown_ = false;
  storage_write_thread_ = rex::thread::Thread::Create({}, [this]() { StorageWriteThread(); });
  assert_not_null(storage_write_thread_);
  storage_write_thread_->set_name("D3D12 Storage writer");
}

void PipelineCache::ShutdownShaderStorage() {
  if (storage_write_thread_) {
    {
      std::lock_guard<std::mutex> lock(storage_write_request_lock_);
      storage_write_thread_shutdown_ = true;
    }
    storage_write_request_cond_.notify_all();
    rex::thread::Wait(storage_write_thread_.get(), false);
    storage_write_thread_.reset();
  }
  storage_write_shader_queue_.clear();
  storage_write_pipeline_queue_.clear();

  if (pipeline_storage_file_) {
    fclose(pipeline_storage_file_);
    pipeline_storage_file_ = nullptr;
    pipeline_storage_file_flush_needed_ = false;
  }

  if (shader_storage_file_) {
    fclose(shader_storage_file_);
    shader_storage_file_ = nullptr;
    shader_storage_file_flush_needed_ = false;
  }

  shader_storage_cache_root_.clear();
  shader_storage_title_id_ = 0;
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

bool PipelineCache::GetGeometryShaderKey(
    PipelineGeometryShader geometry_shader_type,
    DxbcShaderTranslator::Modification vertex_shader_modification,
    DxbcShaderTranslator::Modification pixel_shader_modification, GeometryShaderKey& key_out) {
  if (geometry_shader_type == PipelineGeometryShader::kNone) {
    return false;
  }
  assert_true(vertex_shader_modification.vertex.interpolator_mask ==
              pixel_shader_modification.pixel.interpolator_mask);
  GeometryShaderKey key;
  key.type = geometry_shader_type;
  key.interpolator_count = rex::bit_count(vertex_shader_modification.vertex.interpolator_mask);
  key.user_clip_plane_count = vertex_shader_modification.vertex.user_clip_plane_count;
  key.user_clip_plane_cull = vertex_shader_modification.vertex.user_clip_plane_cull;
  key.has_vertex_kill_and = vertex_shader_modification.vertex.vertex_kill_and;
  key.has_point_size = vertex_shader_modification.vertex.output_point_size;
  key.has_point_coordinates = pixel_shader_modification.pixel.param_gen_point;
  key.point_ps_ucp_mode = vertex_shader_modification.vertex.point_ps_ucp_mode;
  key_out = key;
  return true;
}

void PipelineCache::CreateDxbcGeometryShader(GeometryShaderKey key,
                                             std::vector<uint32_t>& shader_out) {
  shader_out.clear();
  uint32_t point_clip_distance_count = key.user_clip_plane_cull ? 0 : key.user_clip_plane_count;
  uint32_t point_user_cull_distance_count =
      key.type == PipelineGeometryShader::kPointList && key.user_clip_plane_cull
          ? key.user_clip_plane_count
          : 0;
  bool point_recalculate_clip_distances = key.type == PipelineGeometryShader::kPointList &&
                                          point_clip_distance_count && key.point_ps_ucp_mode >= 2;
  bool point_recalculate_cull_distances = key.type == PipelineGeometryShader::kPointList &&
                                          point_user_cull_distance_count &&
                                          key.point_ps_ucp_mode >= 3;

  constexpr uint32_t kBlobCount = 5;

  shader_out.resize(sizeof(dxbc::ContainerHeader) / sizeof(uint32_t) + kBlobCount);
  uint32_t blob_offset_position_dwords = sizeof(dxbc::ContainerHeader) / sizeof(uint32_t);
  uint32_t blob_position_dwords = uint32_t(shader_out.size());
  constexpr uint32_t kBlobHeaderSizeDwords = sizeof(dxbc::BlobHeader) / sizeof(uint32_t);

  uint32_t name_ptr;

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t rdef_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;

  shader_out.resize(rdef_position_dwords + sizeof(dxbc::RdefHeader) / sizeof(uint32_t));

  dxbc::AppendAlignedString(shader_out, "Xenia");
  {
    auto& rdef_header =
        *reinterpret_cast<dxbc::RdefHeader*>(shader_out.data() + rdef_position_dwords);
    rdef_header.shader_model = dxbc::RdefShaderModel::kGeometryShader5_1;
    rdef_header.compile_flags =
        dxbc::kCompileFlagNoPreshader | dxbc::kCompileFlagPreferFlowControl |
        dxbc::kCompileFlagIeeeStrictness | dxbc::kCompileFlagAllResourcesBound;

    rdef_header.generator_name_ptr = sizeof(dxbc::RdefHeader);
    rdef_header.fourcc = dxbc::RdefHeader::FourCC::k5_1;
    rdef_header.InitializeSizes();
  }

  uint32_t system_cbuffer_size_vector_aligned_bytes = 0;

  if (key.type == PipelineGeometryShader::kPointList ||
      key.type == PipelineGeometryShader::kLineList) {
    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_float2 = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "float2");

    uint32_t rdef_type_float2_position_dwords = uint32_t(shader_out.size());
    uint32_t rdef_type_float2_ptr =
        uint32_t((rdef_type_float2_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    shader_out.resize(rdef_type_float2_position_dwords + sizeof(dxbc::RdefType) / sizeof(uint32_t));
    {
      auto& rdef_type_float2 =
          *reinterpret_cast<dxbc::RdefType*>(shader_out.data() + rdef_type_float2_position_dwords);
      rdef_type_float2.variable_class = dxbc::RdefVariableClass::kVector;
      rdef_type_float2.variable_type = dxbc::RdefVariableType::kFloat;
      rdef_type_float2.row_count = 1;
      rdef_type_float2.column_count = 2;
      rdef_type_float2.name_ptr = rdef_name_ptr_float2;
    }

    enum PointConstant : uint32_t {
      kPointConstantConstantDiameter,
      kPointConstantScreenDiameterToNDCRadius,
      kPointConstantCount,
    };

    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_xe_point_constant_diameter = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_point_constant_diameter");
    uint32_t rdef_name_ptr_xe_point_screen_diameter_to_ndc_radius = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_point_screen_diameter_to_ndc_radius");

    uint32_t rdef_constants_position_dwords = uint32_t(shader_out.size());
    uint32_t rdef_constants_ptr =
        uint32_t((rdef_constants_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    shader_out.resize(rdef_constants_position_dwords +
                      sizeof(dxbc::RdefVariable) / sizeof(uint32_t) * kPointConstantCount);
    {
      auto rdef_constants =
          reinterpret_cast<dxbc::RdefVariable*>(shader_out.data() + rdef_constants_position_dwords);

      static_assert(sizeof(DxbcShaderTranslator::SystemConstants ::point_constant_diameter) ==
                        sizeof(float) * 2,
                    "DxbcShaderTranslator point_constant_diameter system constant size "
                    "differs between the shader translator and geometry shader "
                    "generation");
      static_assert_size(DxbcShaderTranslator::SystemConstants::point_constant_diameter,
                         sizeof(float) * 2);
      dxbc::RdefVariable& rdef_constant_point_constant_diameter =
          rdef_constants[kPointConstantConstantDiameter];
      rdef_constant_point_constant_diameter.name_ptr = rdef_name_ptr_xe_point_constant_diameter;
      rdef_constant_point_constant_diameter.start_offset_bytes =
          offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter);
      rdef_constant_point_constant_diameter.size_bytes = sizeof(float) * 2;
      rdef_constant_point_constant_diameter.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_point_constant_diameter.type_ptr = rdef_type_float2_ptr;
      rdef_constant_point_constant_diameter.start_texture = UINT32_MAX;
      rdef_constant_point_constant_diameter.start_sampler = UINT32_MAX;

      static_assert(
          sizeof(DxbcShaderTranslator::SystemConstants ::point_screen_diameter_to_ndc_radius) ==
              sizeof(float) * 2,
          "DxbcShaderTranslator point_screen_diameter_to_ndc_radius system "
          "constant size differs between the shader translator and geometry "
          "shader generation");
      dxbc::RdefVariable& rdef_constant_point_screen_diameter_to_ndc_radius =
          rdef_constants[kPointConstantScreenDiameterToNDCRadius];
      rdef_constant_point_screen_diameter_to_ndc_radius.name_ptr =
          rdef_name_ptr_xe_point_screen_diameter_to_ndc_radius;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_offset_bytes =
          offsetof(DxbcShaderTranslator::SystemConstants, point_screen_diameter_to_ndc_radius);
      rdef_constant_point_screen_diameter_to_ndc_radius.size_bytes = sizeof(float) * 2;
      rdef_constant_point_screen_diameter_to_ndc_radius.flags = dxbc::kRdefVariableFlagUsed;
      rdef_constant_point_screen_diameter_to_ndc_radius.type_ptr = rdef_type_float2_ptr;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_texture = UINT32_MAX;
      rdef_constant_point_screen_diameter_to_ndc_radius.start_sampler = UINT32_MAX;
    }

    name_ptr = uint32_t((shader_out.size() - rdef_position_dwords) * sizeof(uint32_t));
    uint32_t rdef_name_ptr_xe_system_cbuffer = name_ptr;
    name_ptr += dxbc::AppendAlignedString(shader_out, "xe_system_cbuffer");

    uint32_t rdef_cbuffer_position_dwords = uint32_t(shader_out.size());
    shader_out.resize(rdef_cbuffer_position_dwords + sizeof(dxbc::RdefCbuffer) / sizeof(uint32_t));
    {
      auto& rdef_cbuffer_system =
          *reinterpret_cast<dxbc::RdefCbuffer*>(shader_out.data() + rdef_cbuffer_position_dwords);
      rdef_cbuffer_system.name_ptr = rdef_name_ptr_xe_system_cbuffer;
      rdef_cbuffer_system.variable_count = kPointConstantCount;
      rdef_cbuffer_system.variables_ptr = rdef_constants_ptr;
      auto rdef_constants = reinterpret_cast<const dxbc::RdefVariable*>(
          shader_out.data() + rdef_constants_position_dwords);
      for (uint32_t i = 0; i < kPointConstantCount; ++i) {
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     rdef_constants[i].start_offset_bytes + rdef_constants[i].size_bytes);
      }
      if (point_recalculate_clip_distances || point_recalculate_cull_distances) {
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) +
                              sizeof(float) * 3));
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) +
                              sizeof(float) * 3));
        system_cbuffer_size_vector_aligned_bytes =
            std::max(system_cbuffer_size_vector_aligned_bytes,
                     uint32_t(offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                              sizeof(float) * 4 * 6));
      }
      system_cbuffer_size_vector_aligned_bytes =
          rex::align(system_cbuffer_size_vector_aligned_bytes, uint32_t(sizeof(uint32_t) * 4));
      rdef_cbuffer_system.size_vector_aligned_bytes = system_cbuffer_size_vector_aligned_bytes;
    }

    uint32_t rdef_binding_position_dwords = uint32_t(shader_out.size());
    shader_out.resize(rdef_binding_position_dwords +
                      sizeof(dxbc::RdefInputBind) / sizeof(uint32_t));
    {
      auto& rdef_binding_cbuffer_system =
          *reinterpret_cast<dxbc::RdefInputBind*>(shader_out.data() + rdef_binding_position_dwords);
      rdef_binding_cbuffer_system.name_ptr = rdef_name_ptr_xe_system_cbuffer;
      rdef_binding_cbuffer_system.type = dxbc::RdefInputType::kCbuffer;
      rdef_binding_cbuffer_system.bind_point =
          uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants);
      rdef_binding_cbuffer_system.bind_count = 1;
      rdef_binding_cbuffer_system.flags = dxbc::kRdefInputFlagUserPacked;
    }

    {
      auto& rdef_header =
          *reinterpret_cast<dxbc::RdefHeader*>(shader_out.data() + rdef_position_dwords);
      rdef_header.cbuffer_count = 1;
      rdef_header.cbuffers_ptr =
          uint32_t((rdef_cbuffer_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
      rdef_header.input_bind_count = 1;
      rdef_header.input_binds_ptr =
          uint32_t((rdef_binding_position_dwords - rdef_position_dwords) * sizeof(uint32_t));
    }
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kResourceDefinition;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t input_clip_distance_count = key.user_clip_plane_cull ? 0 : key.user_clip_plane_count;
  uint32_t input_cull_distance_count =
      (key.user_clip_plane_cull ? key.user_clip_plane_count : 0) + key.has_vertex_kill_and;
  uint32_t input_clip_and_cull_distance_count =
      input_clip_distance_count + input_cull_distance_count;

  uint32_t isgn_parameter_count =
      key.interpolator_count + 1 + ((input_clip_and_cull_distance_count + 3) / 4) +
      uint32_t(input_cull_distance_count && (input_clip_distance_count & 3) != 0) +
      key.has_point_size;

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t isgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                    sizeof(dxbc::SignatureParameter) / sizeof(uint32_t) * isgn_parameter_count);

  name_ptr = uint32_t((shader_out.size() - isgn_position_dwords) * sizeof(uint32_t));
  uint32_t isgn_name_ptr_texcoord = name_ptr;
  if (key.interpolator_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "TEXCOORD");
  }
  uint32_t isgn_name_ptr_sv_position = name_ptr;
  name_ptr += dxbc::AppendAlignedString(shader_out, "SV_Position");
  uint32_t isgn_name_ptr_sv_clip_distance = name_ptr;
  if (input_clip_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_ClipDistance");
  }
  uint32_t isgn_name_ptr_sv_cull_distance = name_ptr;
  if (input_cull_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_CullDistance");
  }
  uint32_t isgn_name_ptr_xepsize = name_ptr;
  if (key.has_point_size) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "XEPSIZE");
  }

  uint32_t input_register_interpolators = UINT32_MAX;
  uint32_t input_register_position;
  uint32_t input_register_clip_and_cull_distances = UINT32_MAX;
  uint32_t input_register_point_size = UINT32_MAX;
  {
    auto& isgn_header =
        *reinterpret_cast<dxbc::Signature*>(shader_out.data() + isgn_position_dwords);
    isgn_header.parameter_count = isgn_parameter_count;
    isgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto isgn_parameters = reinterpret_cast<dxbc::SignatureParameter*>(
        shader_out.data() + isgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    uint32_t isgn_parameter_index = 0;
    uint32_t input_register_index = 0;

    if (key.interpolator_count) {
      input_register_interpolators = input_register_index;
      for (uint32_t i = 0; i < key.interpolator_count; ++i) {
        assert_true(isgn_parameter_index < isgn_parameter_count);
        dxbc::SignatureParameter& isgn_interpolator = isgn_parameters[isgn_parameter_index++];
        isgn_interpolator.semantic_name_ptr = isgn_name_ptr_texcoord;
        isgn_interpolator.semantic_index = i;
        isgn_interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        isgn_interpolator.register_index = input_register_index++;
        isgn_interpolator.mask = 0b1111;
        isgn_interpolator.always_reads_mask = 0b1111;
      }
    }

    input_register_position = input_register_index;
    assert_true(isgn_parameter_index < isgn_parameter_count);
    dxbc::SignatureParameter& isgn_sv_position = isgn_parameters[isgn_parameter_index++];
    isgn_sv_position.semantic_name_ptr = isgn_name_ptr_sv_position;
    isgn_sv_position.system_value = dxbc::Name::kPosition;
    isgn_sv_position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
    isgn_sv_position.register_index = input_register_index++;
    isgn_sv_position.mask = 0b1111;
    isgn_sv_position.always_reads_mask = 0b1111;

    if (input_clip_and_cull_distance_count) {
      input_register_clip_and_cull_distances = input_register_index;
      uint32_t isgn_cull_distance_semantic_index = 0;
      for (uint32_t i = 0; i < input_clip_and_cull_distance_count; i += 4) {
        if (i < input_clip_distance_count) {
          dxbc::SignatureParameter& isgn_sv_clip_distance = isgn_parameters[isgn_parameter_index++];
          isgn_sv_clip_distance.semantic_name_ptr = isgn_name_ptr_sv_clip_distance;
          isgn_sv_clip_distance.semantic_index = i / 4;
          isgn_sv_clip_distance.system_value = dxbc::Name::kClipDistance;
          isgn_sv_clip_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          isgn_sv_clip_distance.register_index = input_register_index;
          uint8_t isgn_sv_clip_distance_mask =
              (UINT8_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1;
          isgn_sv_clip_distance.mask = isgn_sv_clip_distance_mask;
          isgn_sv_clip_distance.always_reads_mask = isgn_sv_clip_distance_mask;
        }
        if (input_cull_distance_count && i + 4 > input_clip_distance_count) {
          dxbc::SignatureParameter& isgn_sv_cull_distance = isgn_parameters[isgn_parameter_index++];
          isgn_sv_cull_distance.semantic_name_ptr = isgn_name_ptr_sv_cull_distance;
          isgn_sv_cull_distance.semantic_index = isgn_cull_distance_semantic_index++;
          isgn_sv_cull_distance.system_value = dxbc::Name::kCullDistance;
          isgn_sv_cull_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
          isgn_sv_cull_distance.register_index = input_register_index;
          uint8_t isgn_sv_cull_distance_mask =
              (UINT8_C(1) << std::min(input_clip_and_cull_distance_count - i, UINT32_C(4))) - 1;
          if (i < input_clip_distance_count) {
            isgn_sv_cull_distance_mask &= ~((UINT8_C(1) << (input_clip_distance_count - i)) - 1);
          }
          isgn_sv_cull_distance.mask = isgn_sv_cull_distance_mask;
          isgn_sv_cull_distance.always_reads_mask = isgn_sv_cull_distance_mask;
        }
        ++input_register_index;
      }
    }

    if (key.has_point_size) {
      input_register_point_size = input_register_index;
      assert_true(isgn_parameter_index < isgn_parameter_count);
      dxbc::SignatureParameter& isgn_point_size = isgn_parameters[isgn_parameter_index++];
      isgn_point_size.semantic_name_ptr = isgn_name_ptr_xepsize;
      isgn_point_size.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      isgn_point_size.register_index = input_register_index++;
      isgn_point_size.mask = 0b0001;
      isgn_point_size.always_reads_mask =
          key.type == PipelineGeometryShader::kPointList ? 0b0001 : 0;
    }

    assert_true(isgn_parameter_index == isgn_parameter_count);
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kInputSignature;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t osgn_parameter_count = key.interpolator_count + key.has_point_coordinates + 1 +
                                  ((input_clip_distance_count + 3) / 4);

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t osgn_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t) +
                    sizeof(dxbc::SignatureParameterForGS) / sizeof(uint32_t) *
                        osgn_parameter_count);

  name_ptr = uint32_t((shader_out.size() - osgn_position_dwords) * sizeof(uint32_t));
  uint32_t osgn_name_ptr_texcoord = name_ptr;
  if (key.interpolator_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "TEXCOORD");
  }
  uint32_t osgn_name_ptr_xespritetexcoord = name_ptr;
  if (key.has_point_coordinates) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "XESPRITETEXCOORD");
  }
  uint32_t osgn_name_ptr_sv_position = name_ptr;
  name_ptr += dxbc::AppendAlignedString(shader_out, "SV_Position");
  uint32_t osgn_name_ptr_sv_clip_distance = name_ptr;
  if (input_clip_distance_count) {
    name_ptr += dxbc::AppendAlignedString(shader_out, "SV_ClipDistance");
  }

  uint32_t output_register_interpolators = UINT32_MAX;
  uint32_t output_register_point_coordinates = UINT32_MAX;
  uint32_t output_register_position;
  uint32_t output_register_clip_distances = UINT32_MAX;
  {
    auto& osgn_header =
        *reinterpret_cast<dxbc::Signature*>(shader_out.data() + osgn_position_dwords);
    osgn_header.parameter_count = osgn_parameter_count;
    osgn_header.parameter_info_ptr = sizeof(dxbc::Signature);

    auto osgn_parameters = reinterpret_cast<dxbc::SignatureParameterForGS*>(
        shader_out.data() + osgn_position_dwords + sizeof(dxbc::Signature) / sizeof(uint32_t));
    uint32_t osgn_parameter_index = 0;
    uint32_t output_register_index = 0;

    if (key.interpolator_count) {
      output_register_interpolators = output_register_index;
      for (uint32_t i = 0; i < key.interpolator_count; ++i) {
        assert_true(osgn_parameter_index < osgn_parameter_count);
        dxbc::SignatureParameterForGS& osgn_interpolator = osgn_parameters[osgn_parameter_index++];
        osgn_interpolator.semantic_name_ptr = osgn_name_ptr_texcoord;
        osgn_interpolator.semantic_index = i;
        osgn_interpolator.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        osgn_interpolator.register_index = output_register_index++;
        osgn_interpolator.mask = 0b1111;
      }
    }

    if (key.has_point_coordinates) {
      output_register_point_coordinates = output_register_index;
      assert_true(osgn_parameter_index < osgn_parameter_count);
      dxbc::SignatureParameterForGS& osgn_point_coordinates =
          osgn_parameters[osgn_parameter_index++];
      osgn_point_coordinates.semantic_name_ptr = osgn_name_ptr_xespritetexcoord;
      osgn_point_coordinates.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
      osgn_point_coordinates.register_index = output_register_index++;
      osgn_point_coordinates.mask = 0b0011;
      osgn_point_coordinates.never_writes_mask = 0b1100;
    }

    output_register_position = output_register_index;
    assert_true(osgn_parameter_index < osgn_parameter_count);
    dxbc::SignatureParameterForGS& osgn_sv_position = osgn_parameters[osgn_parameter_index++];
    osgn_sv_position.semantic_name_ptr = osgn_name_ptr_sv_position;
    osgn_sv_position.system_value = dxbc::Name::kPosition;
    osgn_sv_position.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
    osgn_sv_position.register_index = output_register_index++;
    osgn_sv_position.mask = 0b1111;

    if (input_clip_distance_count) {
      output_register_clip_distances = output_register_index;
      for (uint32_t i = 0; i < input_clip_distance_count; i += 4) {
        dxbc::SignatureParameterForGS& osgn_sv_clip_distance =
            osgn_parameters[osgn_parameter_index++];
        osgn_sv_clip_distance.semantic_name_ptr = osgn_name_ptr_sv_clip_distance;
        osgn_sv_clip_distance.semantic_index = i / 4;
        osgn_sv_clip_distance.system_value = dxbc::Name::kClipDistance;
        osgn_sv_clip_distance.component_type = dxbc::SignatureRegisterComponentType::kFloat32;
        osgn_sv_clip_distance.register_index = output_register_index++;
        uint8_t osgn_sv_clip_distance_mask =
            (UINT8_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1;
        osgn_sv_clip_distance.mask = osgn_sv_clip_distance_mask;
        osgn_sv_clip_distance.never_writes_mask = osgn_sv_clip_distance_mask ^ 0b1111;
      }
    }

    assert_true(osgn_parameter_index == osgn_parameter_count);
  }

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kOutputSignatureForGS;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t shex_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(shex_position_dwords);

  shader_out.push_back(dxbc::VersionToken(dxbc::ProgramType::kGeometryShader, 5, 1));

  shader_out.push_back(0);

  dxbc::Statistics stat;
  std::memset(&stat, 0, sizeof(dxbc::Statistics));
  dxbc::Assembler a(shader_out, stat);

  a.OpDclGlobalFlags(dxbc::kGlobalFlagAllResourcesBound);

  if (system_cbuffer_size_vector_aligned_bytes) {
    a.OpDclConstantBuffer(
        dxbc::Src::CB(dxbc::Src::Dcl, 0,
                      uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                      uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants)),
        system_cbuffer_size_vector_aligned_bytes / (sizeof(uint32_t) * 4));
  }

  dxbc::Primitive input_primitive = dxbc::Primitive::kUndefined;
  uint32_t input_primitive_vertex_count = 0;
  dxbc::PrimitiveTopology output_primitive_topology = dxbc::PrimitiveTopology::kUndefined;
  uint32_t max_output_vertex_count = 0;
  switch (key.type) {
    case PipelineGeometryShader::kPointList:

      input_primitive = dxbc::Primitive::kPoint;
      input_primitive_vertex_count = 1;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kRectangleList:

      input_primitive = dxbc::Primitive::kTriangle;
      input_primitive_vertex_count = 3;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kQuadList:

      input_primitive = dxbc::Primitive::kLineWithAdjacency;
      input_primitive_vertex_count = 4;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    case PipelineGeometryShader::kLineList:

      input_primitive = dxbc::Primitive::kLine;
      input_primitive_vertex_count = 2;
      output_primitive_topology = dxbc::PrimitiveTopology::kTriangleStrip;
      max_output_vertex_count = 4;
      break;
    default:
      assert_unhandled_case(key.type);
  }

  assert_false(key.interpolator_count && input_register_interpolators == UINT32_MAX);
  for (uint32_t i = 0; i < key.interpolator_count; ++i) {
    a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_interpolators + i));
  }
  a.OpDclInputSIV(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_position),
                  dxbc::Name::kPosition);

  assert_false(input_clip_and_cull_distance_count &&
               input_register_clip_and_cull_distances == UINT32_MAX);
  for (uint32_t i = 0; i < input_clip_and_cull_distance_count; i += 4) {
    if (i < input_clip_distance_count) {
      a.OpDclInput(dxbc::Dest::V2D(
          input_primitive_vertex_count, input_register_clip_and_cull_distances + (i >> 2),
          (UINT32_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1));
    }
    if (input_cull_distance_count && i + 4 > input_clip_distance_count) {
      uint32_t cull_distance_mask =
          (UINT32_C(1) << std::min(input_clip_and_cull_distance_count - i, UINT32_C(4))) - 1;
      if (i < input_clip_distance_count) {
        cull_distance_mask &= ~((UINT32_C(1) << (input_clip_distance_count - i)) - 1);
      }
      a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count,
                                   input_register_clip_and_cull_distances + (i >> 2),
                                   cull_distance_mask));
    }
  }
  if (key.has_point_size && key.type == PipelineGeometryShader::kPointList) {
    assert_true(input_register_point_size != UINT32_MAX);
    a.OpDclInput(dxbc::Dest::V2D(input_primitive_vertex_count, input_register_point_size, 0b0001));
  }

  size_t dcl_temps_count_position_dwords = a.OpDclTemps(1);

  a.OpDclInputPrimitive(input_primitive);
  dxbc::Dest stream(dxbc::Dest::M(0));
  a.OpDclStream(stream);
  a.OpDclOutputTopology(output_primitive_topology);

  assert_false(key.interpolator_count && output_register_interpolators == UINT32_MAX);
  for (uint32_t i = 0; i < key.interpolator_count; ++i) {
    a.OpDclOutput(dxbc::Dest::O(output_register_interpolators + i));
  }
  if (key.has_point_coordinates) {
    assert_true(output_register_point_coordinates != UINT32_MAX);
    a.OpDclOutput(dxbc::Dest::O(output_register_point_coordinates, 0b0011));
  }
  a.OpDclOutputSIV(dxbc::Dest::O(output_register_position), dxbc::Name::kPosition);
  assert_false(input_clip_distance_count && output_register_clip_distances == UINT32_MAX);
  for (uint32_t i = 0; i < input_clip_distance_count; i += 4) {
    a.OpDclOutputSIV(
        dxbc::Dest::O(output_register_clip_distances + (i >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - i, UINT32_C(4))) - 1),
        dxbc::Name::kClipDistance);
  }

  a.OpDclMaxOutputVertexCount(max_output_vertex_count);

  for (uint32_t i = 0; i < input_primitive_vertex_count; ++i) {
    a.OpNE(dxbc::Dest::R(0), dxbc::Src::V2D(i, input_register_position),
           dxbc::Src::V2D(i, input_register_position));
    a.OpOr(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0, 0b0100), dxbc::Src::R(0, 0b1110));
    a.OpOr(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
           dxbc::Src::R(0, dxbc::Src::kYYYY));
    a.OpRetC(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
  }

  if (input_cull_distance_count) {
    uint32_t cull_distance_start =
        point_recalculate_cull_distances ? point_user_cull_distance_count : 0;
    for (uint32_t i = cull_distance_start; i < input_cull_distance_count; ++i) {
      uint32_t cull_distance_register =
          input_register_clip_and_cull_distances + ((input_clip_distance_count + i) >> 2);
      uint32_t cull_distance_component = (input_clip_distance_count + i) & 3;
      a.OpLT(dxbc::Dest::R(0, 0b0001),
             dxbc::Src::V2D(0, cull_distance_register).Select(cull_distance_component),
             dxbc::Src::LF(0.0f));
      for (uint32_t j = 1; j < input_primitive_vertex_count; ++j) {
        a.OpLT(dxbc::Dest::R(0, 0b0010),
               dxbc::Src::V2D(j, cull_distance_register).Select(cull_distance_component),
               dxbc::Src::LF(0.0f));
        a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kXXXX),
                dxbc::Src::R(0, dxbc::Src::kYYYY));
      }
      a.OpRetC(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
    }
  }

  switch (key.type) {
    case PipelineGeometryShader::kPointList: {
      dxbc::Src point_size_src(dxbc::Src::CB(
          0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
          offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter) >> 4,
          ((offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter[0]) >> 2) & 3) |
              (((offsetof(DxbcShaderTranslator::SystemConstants, point_constant_diameter[1]) >> 2) &
                3)
               << 2)));
      if (key.has_point_size) {
        a.OpGE(dxbc::Dest::R(0, 0b0001),
               dxbc::Src::V2D(0, input_register_point_size, dxbc::Src::kXXXX), dxbc::Src::LF(0.0f));
        a.OpMovC(dxbc::Dest::R(0, 0b0011), dxbc::Src::R(0, dxbc::Src::kXXXX),
                 dxbc::Src::V2D(0, input_register_point_size, dxbc::Src::kXXXX), point_size_src);
        point_size_src = dxbc::Src::R(0, 0b0100);
      }

      for (uint32_t i = 0; i < 2; ++i) {
        a.OpLT(dxbc::Dest::R(0, 0b0100), dxbc::Src::LF(0.0f), point_size_src.SelectFromSwizzled(i));
        a.OpRetC(false, dxbc::Src::R(0, dxbc::Src::kZZZZ));
      }

      a.OpMul(dxbc::Dest::R(0, 0b0011), point_size_src,
              dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                            offsetof(DxbcShaderTranslator::SystemConstants,
                                     point_screen_diameter_to_ndc_radius) >>
                                4,
                            ((offsetof(DxbcShaderTranslator::SystemConstants,
                                       point_screen_diameter_to_ndc_radius[0]) >>
                              2) &
                             3) |
                                (((offsetof(DxbcShaderTranslator::SystemConstants,
                                            point_screen_diameter_to_ndc_radius[1]) >>
                                   2) &
                                  3)
                                 << 2)));
      point_size_src = dxbc::Src::R(0, 0b0100);
      a.OpMul(dxbc::Dest::R(0, 0b0011), point_size_src,
              dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
      dxbc::Src point_radius_x_src(point_size_src.SelectFromSwizzled(0));
      dxbc::Src point_radius_y_src(point_size_src.SelectFromSwizzled(1));

      if (point_recalculate_cull_distances) {
        stat.temp_register_count = std::max(UINT32_C(4), stat.temp_register_count);
        dxbc::Src ndc_scale_xy(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4,
            ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[0]) >> 2) & 3) |
                (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[1]) >> 2) & 3) << 2)));
        dxbc::Src ndc_scale_z(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4, dxbc::Src::kZZZZ));
        dxbc::Src ndc_offset_xy(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4,
            ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[0]) >> 2) & 3) |
                (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[1]) >> 2) & 3)
                 << 2)));
        dxbc::Src ndc_offset_z(dxbc::Src::CB(
            0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
            offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4, dxbc::Src::kZZZZ));
        for (uint32_t j = 0; j < point_user_cull_distance_count; ++j) {
          for (uint32_t i = 0; i < 4; ++i) {
            a.OpAdd(dxbc::Dest::R(2, 0b0001),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kXXXX),
                    (i & 1) ? point_radius_x_src : -point_radius_x_src);
            a.OpAdd(dxbc::Dest::R(2, 0b0010),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kYYYY),
                    (i >> 1) ? -point_radius_y_src : point_radius_y_src);
            a.OpMov(dxbc::Dest::R(2, 0b0100),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kZZZZ));
            a.OpMov(dxbc::Dest::R(2, 0b1000),
                    dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
            a.OpMAd(dxbc::Dest::R(2, 0b0011), -ndc_offset_xy, dxbc::Src::R(2, dxbc::Src::kWWWW),
                    dxbc::Src::R(2, 0b0011));
            a.OpDiv(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2, 0b0011), ndc_scale_xy);
            a.OpMAd(dxbc::Dest::R(2, 0b0100), -ndc_offset_z, dxbc::Src::R(2, dxbc::Src::kWWWW),
                    dxbc::Src::R(2, dxbc::Src::kZZZZ));
            a.OpDiv(dxbc::Dest::R(2, 0b0100), dxbc::Src::R(2, dxbc::Src::kZZZZ), ndc_scale_z);
            a.OpDP4(
                dxbc::Dest::R(2, 0b0001), dxbc::Src::R(2),
                dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                              (offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                               sizeof(float) * 4 * j) >>
                                  4,
                              dxbc::Src::kXYZW));
            a.OpLT(dxbc::Dest::R(2, 0b0001), dxbc::Src::R(2, dxbc::Src::kXXXX),
                   dxbc::Src::LF(0.0f));
            if (i == 0) {
              a.OpMov(dxbc::Dest::R(3, 0b0001), dxbc::Src::R(2, dxbc::Src::kXXXX));
            } else {
              a.OpAnd(dxbc::Dest::R(3, 0b0001), dxbc::Src::R(3, dxbc::Src::kXXXX),
                      dxbc::Src::R(2, dxbc::Src::kXXXX));
            }
          }
          a.OpRetC(true, dxbc::Src::R(3, dxbc::Src::kXXXX));
        }
      }

      for (uint32_t i = 0; i < 4; ++i) {
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(0, input_register_interpolators + j));
        }

        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011),
                  dxbc::Src::LF(float(i & 1), float(i >> 1), 0.0f, 0.0f));
        }

        a.OpAdd(dxbc::Dest::R(0, 0b0100),
                dxbc::Src::V2D(0, input_register_position, dxbc::Src::kXXXX),
                (i & 1) ? point_radius_x_src : -point_radius_x_src);
        a.OpAdd(dxbc::Dest::R(0, 0b1000),
                dxbc::Src::V2D(0, input_register_position, dxbc::Src::kYYYY),
                (i >> 1) ? -point_radius_y_src : point_radius_y_src);
        a.OpMov(dxbc::Dest::O(output_register_position, 0b0011), dxbc::Src::R(0, 0b1110));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b1100),
                dxbc::Src::V2D(0, input_register_position));
        if (point_recalculate_clip_distances) {
          dxbc::Src ndc_scale_xy(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4,
              ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[0]) >> 2) & 3) |
                  (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale[1]) >> 2) & 3)
                   << 2)));
          dxbc::Src ndc_scale_z(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_scale) >> 4, dxbc::Src::kZZZZ));
          dxbc::Src ndc_offset_xy(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4,
              ((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[0]) >> 2) & 3) |
                  (((offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset[1]) >> 2) & 3)
                   << 2)));
          dxbc::Src ndc_offset_z(dxbc::Src::CB(
              0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
              offsetof(DxbcShaderTranslator::SystemConstants, ndc_offset) >> 4, dxbc::Src::kZZZZ));
          a.OpMov(dxbc::Dest::R(1, 0b0011), dxbc::Src::R(0, 0b1110));
          a.OpMov(dxbc::Dest::R(1, 0b0100),
                  dxbc::Src::V2D(0, input_register_position, dxbc::Src::kZZZZ));
          a.OpMov(dxbc::Dest::R(1, 0b1000),
                  dxbc::Src::V2D(0, input_register_position, dxbc::Src::kWWWW));
          a.OpMAd(dxbc::Dest::R(1, 0b0011), -ndc_offset_xy, dxbc::Src::R(1, dxbc::Src::kWWWW),
                  dxbc::Src::R(1, 0b0100));
          a.OpDiv(dxbc::Dest::R(1, 0b0011), dxbc::Src::R(1, 0b0100), ndc_scale_xy);
          a.OpMAd(dxbc::Dest::R(1, 0b0100), -ndc_offset_z, dxbc::Src::R(1, dxbc::Src::kWWWW),
                  dxbc::Src::R(1, dxbc::Src::kZZZZ));
          a.OpDiv(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(1, dxbc::Src::kZZZZ), ndc_scale_z);
          for (uint32_t j = 0; j < input_clip_distance_count; ++j) {
            a.OpDP4(
                dxbc::Dest::O(output_register_clip_distances + (j >> 2), UINT32_C(1) << (j & 3)),
                dxbc::Src::R(1),
                dxbc::Src::CB(0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
                              (offsetof(DxbcShaderTranslator::SystemConstants, user_clip_planes) +
                               sizeof(float) * 4 * j) >>
                                  4,
                              dxbc::Src::kXYZW));
          }
        } else {
          for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
            a.OpMov(dxbc::Dest::O(
                        output_register_clip_distances + (j >> 2),
                        (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                    dxbc::Src::V2D(0, input_register_clip_and_cull_distances + (j >> 2)));
          }
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kRectangleList: {
      a.OpAdd(dxbc::Dest::R(0, 0b0011), dxbc::Src::V2D(2, input_register_position, 0b0100),
              -dxbc::Src::V2D(1, input_register_position, 0b0100));
      a.OpDP2(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, 0b0100), dxbc::Src::R(0, 0b0100));

      a.OpAdd(dxbc::Dest::R(0, 0b0110), dxbc::Src::V2D(0, input_register_position, 0b0100 << 2),
              -dxbc::Src::V2D(2, input_register_position, 0b0100 << 2));
      a.OpDP2(dxbc::Dest::R(0, 0b0010), dxbc::Src::R(0, 0b1001), dxbc::Src::R(0, 0b1001));

      a.OpAdd(dxbc::Dest::R(0, 0b1100), dxbc::Src::V2D(1, input_register_position, 0b0100 << 4),
              -dxbc::Src::V2D(0, input_register_position, 0b0100 << 4));
      a.OpDP2(dxbc::Dest::R(0, 0b0100), dxbc::Src::R(0, 0b1110), dxbc::Src::R(0, 0b1110));

      a.OpLT(dxbc::Dest::R(0, 0b1000), dxbc::Src::R(0, dxbc::Src::kYYYY),
             dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpLT(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kZZZZ),
             dxbc::Src::R(0, dxbc::Src::kXXXX));

      a.OpAnd(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kWWWW),
              dxbc::Src::R(0, dxbc::Src::kXXXX));
      a.OpIf(true, dxbc::Src::R(0, dxbc::Src::kXXXX));
      { a.OpMov(dxbc::Dest::R(0, 0b0111), dxbc::Src::LU(0, 1, 2, 0)); }
      a.OpElse();
      {
        a.OpLT(dxbc::Dest::R(0, 0b0001), dxbc::Src::R(0, dxbc::Src::kZZZZ),
               dxbc::Src::R(0, dxbc::Src::kYYYY));

        a.OpMovC(dxbc::Dest::R(0, 0b0111), dxbc::Src::R(0, dxbc::Src::kXXXX),
                 dxbc::Src::LU(1, 2, 0, 0), dxbc::Src::LU(2, 0, 1, 0));
      }
      a.OpEndIf();

      for (uint32_t i = 0; i < 3; ++i) {
        dxbc::Index input_vertex_index(0, i);
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(input_vertex_index, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }
        a.OpMov(dxbc::Dest::O(output_register_position),
                dxbc::Src::V2D(input_vertex_index, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(input_vertex_index,
                                 input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }

      stat.temp_register_count = std::max(UINT32_C(2), stat.temp_register_count);
      for (uint32_t j = 0; j < key.interpolator_count; ++j) {
        uint32_t input_register_interpolator = input_register_interpolators + j;
        a.OpAdd(dxbc::Dest::R(1), -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_interpolator),
                dxbc::Src::V2D(dxbc::Index(0, 1), input_register_interpolator));
        a.OpAdd(dxbc::Dest::R(1), dxbc::Src::R(1),
                dxbc::Src::V2D(dxbc::Index(0, 2), input_register_interpolator));
        a.OpMov(dxbc::Dest::O(output_register_interpolators + j), dxbc::Src::R(1));
      }
      if (key.has_point_coordinates) {
        a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
      }
      a.OpAdd(dxbc::Dest::R(1), -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_position),
              dxbc::Src::V2D(dxbc::Index(0, 1), input_register_position));
      a.OpAdd(dxbc::Dest::R(1), dxbc::Src::R(1),
              dxbc::Src::V2D(dxbc::Index(0, 2), input_register_position));
      a.OpMov(dxbc::Dest::O(output_register_position), dxbc::Src::R(1));
      for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
        uint32_t clip_distance_mask =
            (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1;
        uint32_t input_register_clip_distance = input_register_clip_and_cull_distances + (j >> 2);
        a.OpAdd(dxbc::Dest::R(1, clip_distance_mask),
                -dxbc::Src::V2D(dxbc::Index(0, 0), input_register_clip_distance),
                dxbc::Src::V2D(dxbc::Index(0, 1), input_register_clip_distance));
        a.OpAdd(dxbc::Dest::R(1, clip_distance_mask), dxbc::Src::R(1),
                dxbc::Src::V2D(dxbc::Index(0, 2), input_register_clip_distance));
        a.OpMov(dxbc::Dest::O(output_register_clip_distances + (j >> 2), clip_distance_mask),
                dxbc::Src::R(1));
      }
      a.OpEmitStream(stream);
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kQuadList: {
      for (uint32_t i = 0; i < 4; ++i) {
        uint32_t input_vertex_index = i ^ (i >> 1);
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(input_vertex_index, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }
        a.OpMov(dxbc::Dest::O(output_register_position),
                dxbc::Src::V2D(input_vertex_index, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(input_vertex_index,
                                 input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    case PipelineGeometryShader::kLineList: {
      stat.temp_register_count = std::max(UINT32_C(3), stat.temp_register_count);

      dxbc::Src half_pixel_ndc(dxbc::Src::CB(
          0, uint32_t(DxbcShaderTranslator::CbufferRegister::kSystemConstants),
          offsetof(DxbcShaderTranslator::SystemConstants, point_screen_diameter_to_ndc_radius) >> 4,
          ((offsetof(DxbcShaderTranslator::SystemConstants,
                     point_screen_diameter_to_ndc_radius[0]) >>
            2) &
           3) |
              (((offsetof(DxbcShaderTranslator::SystemConstants,
                          point_screen_diameter_to_ndc_radius[1]) >>
                 2) &
                3)
               << 2)));

      for (uint32_t i = 0; i < 2; ++i) {
        a.OpDiv(dxbc::Dest::R(1 + i, 0b0011), dxbc::Src::V2D(i, input_register_position),
                dxbc::Src::V2D(i, input_register_position, dxbc::Src::kWWWW));
        a.OpDiv(dxbc::Dest::R(1 + i, 0b0011), dxbc::Src::R(1 + i), half_pixel_ndc);
      }

      a.OpAdd(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2), -dxbc::Src::R(1));

      a.OpDP2(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(2), dxbc::Src::R(2));
      a.OpLT(dxbc::Dest::R(1, 0b1000), dxbc::Src::LF(0.0f), dxbc::Src::R(1, dxbc::Src::kZZZZ));
      a.OpRetC(false, dxbc::Src::R(1, dxbc::Src::kWWWW));
      a.OpRSq(dxbc::Dest::R(1, 0b0100), dxbc::Src::R(1, dxbc::Src::kZZZZ));

      a.OpMul(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2).Swizzle(0b11100001),
              dxbc::Src::R(1, dxbc::Src::kZZZZ));
      a.OpMul(dxbc::Dest::R(2, 0b0011), dxbc::Src::R(2), half_pixel_ndc);
      a.OpMov(dxbc::Dest::R(2, 0b0001), -dxbc::Src::R(2, dxbc::Src::kXXXX));

      for (uint32_t i = 0; i < 4; ++i) {
        uint32_t vertex = i >> 1;
        for (uint32_t j = 0; j < key.interpolator_count; ++j) {
          a.OpMov(dxbc::Dest::O(output_register_interpolators + j),
                  dxbc::Src::V2D(vertex, input_register_interpolators + j));
        }
        if (key.has_point_coordinates) {
          a.OpMov(dxbc::Dest::O(output_register_point_coordinates, 0b0011), dxbc::Src::LF(0.0f));
        }

        a.OpMAd(dxbc::Dest::R(0, 0b0011), (i & 1) ? dxbc::Src::R(2) : -dxbc::Src::R(2),
                dxbc::Src::V2D(vertex, input_register_position, dxbc::Src::kWWWW),
                dxbc::Src::V2D(vertex, input_register_position));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b0011), dxbc::Src::R(0));
        a.OpMov(dxbc::Dest::O(output_register_position, 0b1100),
                dxbc::Src::V2D(vertex, input_register_position));
        for (uint32_t j = 0; j < input_clip_distance_count; j += 4) {
          a.OpMov(dxbc::Dest::O(
                      output_register_clip_distances + (j >> 2),
                      (UINT32_C(1) << std::min(input_clip_distance_count - j, UINT32_C(4))) - 1),
                  dxbc::Src::V2D(vertex, input_register_clip_and_cull_distances + (j >> 2)));
        }
        a.OpEmitStream(stream);
      }
      a.OpCutStream(stream);
    } break;

    default:
      assert_unhandled_case(key.type);
  }

  a.OpRet();

  shader_out[dcl_temps_count_position_dwords] = stat.temp_register_count;

  shader_out[shex_position_dwords + 1] = uint32_t(shader_out.size()) - shex_position_dwords;

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kShaderEx;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  shader_out[blob_offset_position_dwords] = uint32_t(blob_position_dwords * sizeof(uint32_t));
  uint32_t stat_position_dwords = blob_position_dwords + kBlobHeaderSizeDwords;
  shader_out.resize(stat_position_dwords + sizeof(dxbc::Statistics) / sizeof(uint32_t));
  std::memcpy(shader_out.data() + stat_position_dwords, &stat, sizeof(dxbc::Statistics));

  {
    auto& blob_header =
        *reinterpret_cast<dxbc::BlobHeader*>(shader_out.data() + blob_position_dwords);
    blob_header.fourcc = dxbc::BlobHeader::FourCC::kStatistics;
    blob_position_dwords = uint32_t(shader_out.size());
    blob_header.size_bytes = (blob_position_dwords - kBlobHeaderSizeDwords) * sizeof(uint32_t) -
                             shader_out[blob_offset_position_dwords++];
  }

  uint32_t shader_size_bytes = uint32_t(shader_out.size() * sizeof(uint32_t));
  {
    auto& container_header = *reinterpret_cast<dxbc::ContainerHeader*>(shader_out.data());
    container_header.InitializeIdentification();
    container_header.size_bytes = shader_size_bytes;
    container_header.blob_count = kBlobCount;
    CalculateDXBCChecksum(reinterpret_cast<unsigned char*>(shader_out.data()),
                          static_cast<unsigned int>(shader_size_bytes),
                          reinterpret_cast<unsigned int*>(&container_header.hash));
  }
}

const std::vector<uint32_t>& PipelineCache::GetGeometryShader(GeometryShaderKey key) {
  auto it = geometry_shaders_.find(key);
  if (it != geometry_shaders_.end()) {
    return it->second;
  }
  std::vector<uint32_t> shader;
  CreateDxbcGeometryShader(key, shader);
  return geometry_shaders_.emplace(key, std::move(shader)).first->second;
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

void PipelineCache::StorageWriteThread() {
  ShaderStoredHeader shader_header;

  std::memset(&shader_header, 0, sizeof(shader_header));

  std::vector<uint32_t> ucode_guest_endian;
  ucode_guest_endian.reserve(0xFFFF);

  bool flush_shaders = false;
  bool flush_pipelines = false;

  while (true) {
    if (flush_shaders) {
      flush_shaders = false;
      assert_not_null(shader_storage_file_);
      fflush(shader_storage_file_);
    }
    if (flush_pipelines) {
      flush_pipelines = false;
      assert_not_null(pipeline_storage_file_);
      fflush(pipeline_storage_file_);
    }

    const Shader* shader = nullptr;
    PipelineStoredDescription pipeline_description;
    bool write_pipeline = false;
    {
      std::unique_lock<std::mutex> lock(storage_write_request_lock_);
      if (storage_write_thread_shutdown_) {
        return;
      }
      if (!storage_write_shader_queue_.empty()) {
        shader = storage_write_shader_queue_.front();
        storage_write_shader_queue_.pop_front();
      } else if (storage_write_flush_shaders_) {
        storage_write_flush_shaders_ = false;
        flush_shaders = true;
      }
      if (!storage_write_pipeline_queue_.empty()) {
        std::memcpy(&pipeline_description, &storage_write_pipeline_queue_.front(),
                    sizeof(pipeline_description));
        storage_write_pipeline_queue_.pop_front();
        write_pipeline = true;
      } else if (storage_write_flush_pipelines_) {
        storage_write_flush_pipelines_ = false;
        flush_pipelines = true;
      }
      if (!shader && !write_pipeline) {
        storage_write_request_cond_.wait(lock);
        continue;
      }
    }

    if (shader) {
      shader_header.ucode_data_hash = shader->ucode_data_hash();
      shader_header.ucode_dword_count = shader->ucode_dword_count();
      shader_header.type = shader->type();
      assert_not_null(shader_storage_file_);
      fwrite(&shader_header, sizeof(shader_header), 1, shader_storage_file_);
      if (shader_header.ucode_dword_count) {
        ucode_guest_endian.resize(shader_header.ucode_dword_count);

        memory::copy_and_swap(ucode_guest_endian.data(), shader->ucode_dwords(),
                              shader_header.ucode_dword_count);
        fwrite(ucode_guest_endian.data(), shader_header.ucode_dword_count * sizeof(uint32_t), 1,
               shader_storage_file_);
      }
    }

    if (write_pipeline) {
      assert_not_null(pipeline_storage_file_);
      fwrite(&pipeline_description, sizeof(pipeline_description), 1, pipeline_storage_file_);
    }
  }
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

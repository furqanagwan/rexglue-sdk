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

REXCVAR_DECLARE(bool, d3d12_dxbc_disasm_dxilconv);
REXCVAR_DECLARE(std::string, shader_cache_shipped);

namespace rex::graphics::d3d12 {

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

}

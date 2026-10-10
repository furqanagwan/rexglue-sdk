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

#pragma once

#include <atomic>
#include <condition_variable>
#include <cstdio>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/d3d12/shader.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/pipeline/shader/replacements.h>
#include <rex/graphics/primitive_processor.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>
#include <rex/hash.h>
#include <rex/platform.h>
#include <rex/string/buffer.h>
#include <rex/thread.h>
#include <rex/ui/d3d12/d3d12_api.h>

#if REXGLUE_SHADER_DXIL
#include <rex/graphics/pipeline/shader/spirv.h>
#include <rex/graphics/pipeline/shader/spirv_shader_cache.h>
#endif

namespace rex::graphics::d3d12 {

class D3D12CommandProcessor;

class PipelineCache {
 public:
  static constexpr size_t kLayoutUIDEmpty = 0;

  PipelineCache(D3D12CommandProcessor& command_processor, const RegisterFile& register_file,
                const D3D12RenderTargetCache& render_target_cache, bool bindless_resources_used,
                bool zpd_hybrid_supported = false);
  ~PipelineCache();

  bool Initialize();
  void Shutdown();

  void InitializeShaderStorage(const std::filesystem::path& cache_root, uint32_t title_id,
                               bool blocking);
  void ShutdownShaderStorage();

  void EndSubmission();
  bool IsCreatingPipelines();

  void AwaitPipelineCompletion();

  void AwaitQueuedPipelines();

  void AwaitPipeline(void* handle);

  D3D12Shader* LoadShader(xenos::ShaderType shader_type, const uint32_t* host_address,
                          uint32_t dword_count);

  void AnalyzeShaderUcode(Shader& shader) { shader.AnalyzeUcode(ucode_disasm_buffer_); }

  DxbcShaderTranslator::Modification GetCurrentVertexShaderModification(
      const Shader& shader, Shader::HostVertexShaderType host_vertex_shader_type,
      uint32_t interpolator_mask) const;
  DxbcShaderTranslator::Modification GetCurrentPixelShaderModification(
      const Shader& shader, uint32_t interpolator_mask, uint32_t param_gen_pos,
      reg::RB_DEPTHCONTROL normalized_depth_control) const;

  bool ConfigurePipeline(D3D12Shader::D3D12Translation* vertex_shader,
                         D3D12Shader::D3D12Translation* pixel_shader,
                         const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
                         reg::RB_DEPTHCONTROL normalized_depth_control,
                         uint32_t normalized_color_mask, bool zpd_total, bool viz_survey,
                         uint32_t bound_depth_and_color_render_target_bits,
                         const uint32_t* bound_depth_and_color_render_targets_formats,
                         void** pipeline_handle_out, ID3D12RootSignature** root_signature_out);

#if REXGLUE_SHADER_DXIL

  bool IsDxilShaderPathEnabled() const { return dxil_shader_cache_ != nullptr; }
  enum class DxilPipelineResult {
    kConfigured,

    kUnsupported,

    kFailed,
  };

  DxilPipelineResult ConfigurePipelineDxil(
      D3D12Shader::D3D12Translation* dxbc_vertex_shader,
      D3D12Shader::D3D12Translation* dxbc_pixel_shader,
      const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
      uint32_t interpolator_mask, uint32_t ps_param_gen_pos,
      reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask,
      uint32_t bound_depth_and_color_render_target_bits,
      const uint32_t* bound_depth_and_color_render_targets_formats, bool zpd_total, bool viz_survey,
      void** pipeline_handle_out, SpirvShader** vertex_shader_out, SpirvShader** pixel_shader_out);
#endif

  ID3D12PipelineState* GetD3D12PipelineByHandle(void* handle) const {
    return reinterpret_cast<const Pipeline*>(handle)->state.load(std::memory_order_acquire);
  }

  bool IsPipelineCreationPending(void* handle) const {
    return reinterpret_cast<const Pipeline*>(handle)->creation_pending.load(
        std::memory_order_acquire);
  }

 private:
  REXPACKEDSTRUCT(ShaderStoredHeader, {
    uint64_t ucode_data_hash;

    uint32_t ucode_dword_count : 31;
    xenos::ShaderType type : 1;

    static constexpr uint32_t kVersion = 0x20201219;
  });

  enum class PipelineStripCutIndex : uint32_t {
    kNone,
    kFFFF,
    kFFFFFFFF,
  };

  enum class PipelineTessellationMode : uint32_t {
    kNone,
    kDiscrete,
    kContinuous,
    kAdaptive,
  };

  enum class PipelinePatchType : uint32_t {
    kNone,
    kLine,
    kTriangle,
    kQuad,
  };

  enum class PipelinePrimitiveTopologyType : uint32_t {
    kPoint,
    kLine,
    kTriangle,
  };

  enum class PipelineGeometryShader : uint32_t {
    kNone,
    kPointList,
    kRectangleList,
    kQuadList,

    kLineList,
  };

  enum class PipelineCullMode : uint32_t {
    kNone,
    kFront,
    kBack,

    kDisableRasterization,
  };

  enum class PipelineBlendFactor : uint32_t {
    kZero,
    kOne,
    kSrcColor,
    kInvSrcColor,
    kSrcAlpha,
    kInvSrcAlpha,
    kDestColor,
    kInvDestColor,
    kDestAlpha,
    kInvDestAlpha,
    kBlendFactor,
    kInvBlendFactor,
    kSrcAlphaSat,
  };

  REXPACKEDSTRUCT(PipelineRenderTarget, {
    uint32_t used : 1;
    xenos::ColorRenderTargetFormat format : 4;
    PipelineBlendFactor src_blend : 4;
    PipelineBlendFactor dest_blend : 4;
    xenos::BlendOp blend_op : 3;
    PipelineBlendFactor src_blend_alpha : 4;
    PipelineBlendFactor dest_blend_alpha : 4;
    xenos::BlendOp blend_op_alpha : 3;
    uint32_t write_mask : 4;
  });

  REXPACKEDSTRUCT(PipelineDescription, {
    uint64_t vertex_shader_hash;
    uint64_t vertex_shader_modification;

    uint64_t pixel_shader_hash;
    uint64_t pixel_shader_modification;

    int32_t depth_bias;
    float depth_bias_slope_scaled;

    PipelineStripCutIndex strip_cut_index : 2;

    uint32_t primitive_topology_type_or_tessellation_mode : 2;

    PipelineGeometryShader geometry_shader : 3;
    uint32_t fill_mode_wireframe : 1;
    PipelineCullMode cull_mode : 2;
    uint32_t front_counter_clockwise : 1;
    uint32_t depth_clip : 1;
    xenos::MsaaSamples host_msaa_samples : 2;
    xenos::DepthRenderTargetFormat depth_format : 1;
    xenos::CompareFunction depth_func : 3;
    uint32_t depth_write : 1;
    uint32_t stencil_enable : 1;
    uint32_t stencil_read_mask : 8;

    uint32_t zpd_total : 1;

    uint32_t viz_survey : 1;

    uint32_t dxil : 1;

    uint32_t stencil_write_mask : 8;
    xenos::StencilOp stencil_front_fail_op : 3;
    xenos::StencilOp stencil_front_depth_fail_op : 3;
    xenos::StencilOp stencil_front_pass_op : 3;
    xenos::CompareFunction stencil_front_func : 3;
    xenos::StencilOp stencil_back_fail_op : 3;
    xenos::StencilOp stencil_back_depth_fail_op : 3;
    xenos::StencilOp stencil_back_pass_op : 3;
    xenos::CompareFunction stencil_back_func : 3;

    PipelineRenderTarget render_targets[xenos::kMaxColorRenderTargets];

    static constexpr uint32_t kVersion = 0x20261005;
  });

  REXPACKEDSTRUCT(PipelineStoredDescription, {
    uint64_t description_hash;
    PipelineDescription description;
  });

  struct PipelineRuntimeDescription {
    ID3D12RootSignature* root_signature;
    D3D12Shader::D3D12Translation* vertex_shader;
    D3D12Shader::D3D12Translation* pixel_shader;
    const std::vector<uint32_t>* geometry_shader;

    const Shader::Translation* dxil_vertex_spirv;
    const Shader::Translation* dxil_pixel_spirv;
    const std::vector<uint8_t>* dxil_geometry_shader;
    PipelineDescription description;
  };

  struct Pipeline;

  union GeometryShaderKey {
    uint32_t key;
    struct {
      PipelineGeometryShader type : 3;
      uint32_t interpolator_count : 5;
      uint32_t user_clip_plane_count : 3;
      uint32_t user_clip_plane_cull : 1;
      uint32_t has_vertex_kill_and : 1;
      uint32_t has_point_size : 1;
      uint32_t has_point_coordinates : 1;

      uint32_t point_ps_ucp_mode : 2;
    };

    GeometryShaderKey() : key(0) { static_assert_size(*this, sizeof(key)); }

    struct Hasher {
      size_t operator()(const GeometryShaderKey& key) const {
        return std::hash<uint32_t>{}(key.key);
      }
    };
    bool operator==(const GeometryShaderKey& other_key) const { return key == other_key.key; }
    bool operator!=(const GeometryShaderKey& other_key) const { return !(*this == other_key); }
  };

  D3D12Shader* LoadShader(xenos::ShaderType shader_type, const uint32_t* host_address,
                          uint32_t dword_count, uint64_t data_hash);

  bool TranslateAnalyzedShader(DxbcShaderTranslator& translator,
                               D3D12Shader::D3D12Translation& translation,
                               IDxbcConverter* dxbc_converter = nullptr,
                               IDxcUtils* dxc_utils = nullptr,
                               IDxcCompiler* dxc_compiler = nullptr);

  bool GetCurrentStateDescription(
      D3D12Shader::D3D12Translation* vertex_shader, D3D12Shader::D3D12Translation* pixel_shader,
      const PrimitiveProcessor::ProcessingResult& primitive_processing_result,
      reg::RB_DEPTHCONTROL normalized_depth_control, uint32_t normalized_color_mask, bool zpd_total,
      bool viz_survey, uint32_t bound_depth_and_color_render_target_bits,
      const uint32_t* bound_depth_and_color_render_target_formats,
      PipelineRuntimeDescription& runtime_description_out, bool for_placeholder = false);

  static bool GetGeometryShaderKey(PipelineGeometryShader geometry_shader_type,
                                   DxbcShaderTranslator::Modification vertex_shader_modification,
                                   DxbcShaderTranslator::Modification pixel_shader_modification,
                                   GeometryShaderKey& key_out);
  static void CreateDxbcGeometryShader(GeometryShaderKey key, std::vector<uint32_t>& shader_out);
  const std::vector<uint32_t>& GetGeometryShader(GeometryShaderKey key);

  ID3D12PipelineState* CreateD3D12Pipeline(const PipelineRuntimeDescription& runtime_description);
  bool PrepareRuntimeDescriptionForQueuedCreation(Pipeline* pipeline,
                                                  PipelineRuntimeDescription& runtime_description);

  D3D12CommandProcessor& command_processor_;
  const RegisterFile& register_file_;
  const D3D12RenderTargetCache& render_target_cache_;
  bool bindless_resources_used_;
  bool zpd_hybrid_supported_;

  string::StringBuffer ucode_disasm_buffer_;

  std::unique_ptr<DxbcShaderTranslator> shader_translator_;

  ShaderReplacements shader_replacements_;
  std::mutex translation_request_lock_;

  IDxbcConverter* dxbc_converter_ = nullptr;
  IDxcUtils* dxc_utils_ = nullptr;
  IDxcCompiler* dxc_compiler_ = nullptr;

  std::unordered_map<uint64_t, D3D12Shader*, rex::IdentityHasher<uint64_t>> shaders_;

  struct LayoutUID {
    size_t uid;
    size_t vector_span_offset;
    size_t vector_span_length;
  };
  std::mutex layouts_mutex_;

  std::vector<D3D12Shader::TextureBinding> texture_binding_layouts_;

  std::unordered_multimap<uint64_t, LayoutUID, rex::IdentityHasher<uint64_t>>
      texture_binding_layout_map_;

  std::vector<uint32_t> bindless_sampler_layouts_;

  std::unordered_multimap<uint64_t, LayoutUID, rex::IdentityHasher<uint64_t>>
      bindless_sampler_layout_map_;

  std::unordered_map<GeometryShaderKey, std::vector<uint32_t>, GeometryShaderKey::Hasher>
      geometry_shaders_;

  std::vector<uint8_t> depth_only_pixel_shader_;

  std::vector<uint8_t> zpd_total_depth_only_pixel_shader_;
  std::vector<uint8_t> viz_survey_depth_only_pixel_shader_;

#if REXGLUE_SHADER_DXIL
  class DxilShaderCacheHost : public GuestSpirvShaderCache::Host {
   public:
    explicit DxilShaderCacheHost(const PipelineCache& pipeline_cache)
        : pipeline_cache_(pipeline_cache) {}
    std::unique_ptr<SpirvShaderTranslator> CreateTranslator() const override;
    bool depth_float24_round() const override;
    bool depth_float24_convert_in_pixel_shader() const override;

   private:
    const PipelineCache& pipeline_cache_;
  };

  SpirvShader* GetDxilShader(const Shader& shader);

  Shader::Translation* GetDxilSpirv(SpirvShader& shader, uint64_t modification);

  const std::vector<uint8_t>* ConvertDxil(const Shader::Translation& translation);
  struct DxilTessellation {
    std::vector<uint8_t> host_vertex;
    std::vector<uint8_t> host_hull;
    std::vector<uint8_t> domain;
  };

  const DxilTessellation* ConvertDxilTessellation(const Shader::Translation& translation);
  const std::vector<uint8_t>* GetDxilGeometryShader(GuestSpirvShaderCache::GeometryShaderKey key);

  bool InitializeDxilHelperPixelShaders();

  const std::vector<uint8_t>* GetDxilHelperPixelShader(
      const PipelineDescription& description) const;

  void StoreDxilPipeline(uint64_t hash, const PipelineDescription& description,
                         Shader& vertex_shader, Shader* pixel_shader);

  bool CreateStoredDxilPipeline(const PipelineStoredDescription& stored_description);

  std::unique_ptr<DxilShaderCacheHost> dxil_shader_cache_host_;
  std::unique_ptr<GuestSpirvShaderCache> dxil_shader_cache_;
  std::unordered_map<uint64_t, std::unique_ptr<SpirvShader>> dxil_shaders_;
  std::mutex dxil_binaries_mutex_;
  std::unordered_map<uint64_t, std::unordered_map<uint64_t, std::vector<uint8_t>>> dxil_binaries_;
  std::unordered_map<uint64_t, std::unordered_map<uint64_t, DxilTessellation>>
      dxil_tessellation_binaries_;
  std::unordered_map<uint32_t, std::vector<uint8_t>> dxil_geometry_shaders_;

  std::vector<uint8_t> dxil_depth_only_pixel_shader_;
  std::vector<uint8_t> dxil_float24_truncate_pixel_shader_;
  std::vector<uint8_t> dxil_float24_round_pixel_shader_;
  std::vector<uint8_t> dxil_zpd_total_depth_only_pixel_shader_;
  std::vector<uint8_t> dxil_zpd_total_float24_truncate_pixel_shader_;
  std::vector<uint8_t> dxil_zpd_total_float24_round_pixel_shader_;

  std::vector<uint8_t> dxil_rov_depth_only_pixel_shaders_[3];
  std::vector<uint8_t> dxil_rov_viz_survey_pixel_shaders_[3];
#endif
  std::vector<uint8_t> zpd_total_float24_truncate_pixel_shader_;
  std::vector<uint8_t> zpd_total_float24_round_pixel_shader_;

  struct Pipeline {
    std::atomic<ID3D12PipelineState*> state{nullptr};
    std::atomic<ID3D12RootSignature*> root_signature{nullptr};
    PipelineRuntimeDescription description;
    D3D12Shader::D3D12Translation* pending_vertex_shader = nullptr;
    D3D12Shader::D3D12Translation* pending_pixel_shader = nullptr;
    uint8_t priority = 0;

    std::atomic<bool> creation_pending{false};

    std::atomic<bool> creation_claimed{false};
  };
  struct PipelineCreationPriorityComparator {
    bool operator()(const Pipeline* a, const Pipeline* b) const {
      uint8_t priority_a = a ? a->priority : 0;
      uint8_t priority_b = b ? b->priority : 0;
      return priority_a < priority_b;
    }
  };

  std::unordered_multimap<uint64_t, Pipeline*, rex::IdentityHasher<uint64_t>> pipelines_;

  Pipeline* current_pipeline_ = nullptr;

  std::filesystem::path shader_storage_cache_root_;
  uint32_t shader_storage_title_id_ = 0;

  FILE* shader_storage_file_ = nullptr;

  uint32_t shader_storage_index_ = 0;
  bool shader_storage_file_flush_needed_ = false;

  FILE* pipeline_storage_file_ = nullptr;
  bool pipeline_storage_file_flush_needed_ = false;

  void StorageWriteThread();
  std::mutex storage_write_request_lock_;
  std::condition_variable storage_write_request_cond_;

  std::deque<const Shader*> storage_write_shader_queue_;
  std::deque<PipelineStoredDescription> storage_write_pipeline_queue_;
  bool storage_write_flush_shaders_ = false;
  bool storage_write_flush_pipelines_ = false;
  bool storage_write_thread_shutdown_ = false;
  std::unique_ptr<rex::thread::Thread> storage_write_thread_;

  void CreationThread(size_t thread_index);
  void CreateQueuedPipelinesOnProcessorThread();
  std::mutex creation_request_lock_;
  std::condition_variable creation_request_cond_;

  std::priority_queue<Pipeline*, std::vector<Pipeline*>, PipelineCreationPriorityComparator>
      creation_queue_;

  size_t creation_threads_busy_ = 0;

  std::unique_ptr<rex::thread::Event> creation_completion_event_;

  bool creation_completion_set_event_ = false;

  size_t creation_threads_shutdown_from_ = SIZE_MAX;
  std::vector<std::unique_ptr<rex::thread::Thread>> creation_threads_;
};

}

/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/d3d12/shared_memory.h>
#include <rex/graphics/d3d12/texture_cache.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/memory.h>
#include <rex/ui/d3d12/d3d12_cpu_descriptor_pool.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_upload_buffer_pool.h>
#include <rex/ui/d3d12/d3d12_util.h>
namespace rex::graphics::d3d12 {

class D3D12CommandProcessor;

class D3D12RenderTargetCache final : public RenderTargetCache {
 public:
  D3D12RenderTargetCache(const RegisterFile& register_file, const memory::Memory& memory,
                         uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y,
                         D3D12CommandProcessor& command_processor, bool bindless_resources_used)
      : RenderTargetCache(register_file, memory, draw_resolution_scale_x, draw_resolution_scale_y),
        command_processor_(command_processor),
        bindless_resources_used_(bindless_resources_used) {}
  ~D3D12RenderTargetCache() override;

  bool Initialize();
  void Shutdown(bool from_destructor = false);

  void CompletedSubmissionUpdated();
  void BeginSubmission();

  Path GetPath() const override { return path_; }

  bool Update(bool is_rasterization_done, reg::RB_DEPTHCONTROL normalized_depth_control,
              uint32_t normalized_color_mask, const Shader& vertex_shader) override;

  void InvalidateCommandListRenderTargets() {
    are_current_command_list_render_targets_valid_ = false;
  }

  bool msaa_2x_supported() const { return msaa_2x_supported_; }

  void WriteEdramRawSRVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle);
  void WriteEdramRawUAVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle);
  void WriteEdramUintPow2SRVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                       uint32_t element_size_bytes_pow2);
  void WriteEdramUintPow2UAVDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE handle,
                                       uint32_t element_size_bytes_pow2);

  bool Resolve(const memory::Memory& memory, D3D12SharedMemory& shared_memory,
               D3D12TextureCache& texture_cache, uint32_t& written_address_out,
               uint32_t& written_length_out, reg::RB_COPY_DEST_INFO* copy_dest_info_out = nullptr);

  bool gamma_render_target_as_unorm16() const { return gamma_render_target_as_unorm16_; }

  bool IsFixed16TruncatedToMinus1To1() const {
    return GetPath() == Path::kHostRenderTargets && !REXCVAR_GET(snorm16_render_target_full_range);
  }

  bool depth_float24_round() const { return depth_float24_round_; }
  bool depth_float24_convert_in_pixel_shader() const {
    return depth_float24_convert_in_pixel_shader_;
  }

  DXGI_FORMAT GetColorResourceDXGIFormat(xenos::ColorRenderTargetFormat format) const;
  DXGI_FORMAT GetColorDrawDXGIFormat(xenos::ColorRenderTargetFormat format) const;
  DXGI_FORMAT GetColorOwnershipTransferDXGIFormat(xenos::ColorRenderTargetFormat format,
                                                  bool* is_integer_out = nullptr) const;
  static DXGI_FORMAT GetDepthResourceDXGIFormat(xenos::DepthRenderTargetFormat format);
  static DXGI_FORMAT GetDepthDSVDXGIFormat(xenos::DepthRenderTargetFormat format);
  static DXGI_FORMAT GetDepthSRVDepthDXGIFormat(xenos::DepthRenderTargetFormat format);
  static DXGI_FORMAT GetDepthSRVStencilDXGIFormat(xenos::DepthRenderTargetFormat format);

 protected:
  uint32_t GetMaxRenderTargetWidth() const override { return D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION; }
  uint32_t GetMaxRenderTargetHeight() const override {
    return D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION;
  }

  RenderTarget* CreateRenderTarget(RenderTargetKey key) override;

  bool IsHostDepthEncodingDifferent(xenos::DepthRenderTargetFormat format) const override;

  bool IsGammaFormatHostStorageSeparate() const override;

  void RequestPixelShaderInterlockBarrier() override;

 private:
  enum class EdramBufferModificationStatus {

    kUnmodified,

    kAsROV,

    kAsUAV,
  };
  void TransitionEdramBuffer(D3D12_RESOURCE_STATES new_state);
  void MarkEdramBufferModified(
      EdramBufferModificationStatus modification_status = EdramBufferModificationStatus::kAsUAV);
  void CommitEdramBufferUAVWrites(
      EdramBufferModificationStatus commit_status = EdramBufferModificationStatus::kAsROV);

  D3D12CommandProcessor& command_processor_;
  bool bindless_resources_used_;

  Path path_ = Path::kHostRenderTargets;

  ID3D12Resource* edram_buffer_ = nullptr;
  D3D12_RESOURCE_STATES edram_buffer_state_;
  EdramBufferModificationStatus edram_buffer_modification_status_ =
      EdramBufferModificationStatus::kUnmodified;

  enum class EdramBufferDescriptorIndex : uint32_t {
    kRawSRV,
    kR32UintSRV,
    kR32G32UintSRV,
    kR32G32B32A32UintSRV,
    kRawUAV,
    kR32UintUAV,
    kR32G32UintUAV,
    kR32G32B32A32UintUAV,

    kCount,
  };
  ID3D12DescriptorHeap* edram_buffer_descriptor_heap_ = nullptr;
  D3D12_CPU_DESCRIPTOR_HANDLE edram_buffer_descriptor_heap_start_;

  ID3D12RootSignature* resolve_copy_root_signature_ = nullptr;
  struct ResolveCopyShaderCode {
    const void* unscaled;
    size_t unscaled_size;
    const void* scaled;
    size_t scaled_size;
  };
  static const ResolveCopyShaderCode
      kResolveCopyShaders[size_t(draw_util::ResolveCopyShaderIndex::kCount)];
  ID3D12PipelineState* resolve_copy_pipelines_[size_t(draw_util::ResolveCopyShaderIndex::kCount)] =
      {};

  class D3D12RenderTarget final : public RenderTarget {
   public:
    D3D12RenderTarget(RenderTargetKey key, ID3D12Resource* resource,
                      ui::d3d12::D3D12CpuDescriptorPool::Descriptor&& descriptor_draw,
                      ui::d3d12::D3D12CpuDescriptorPool::Descriptor&& descriptor_load_separate,
                      ui::d3d12::D3D12CpuDescriptorPool::Descriptor&& descriptor_srv,
                      ui::d3d12::D3D12CpuDescriptorPool::Descriptor&& descriptor_srv_stencil,
                      D3D12_RESOURCE_STATES resource_state)
        : RenderTarget(key),
          resource_(resource),
          descriptor_draw_(std::move(descriptor_draw)),
          descriptor_load_separate_(std::move(descriptor_load_separate)),
          descriptor_srv_(std::move(descriptor_srv)),
          descriptor_srv_stencil_(std::move(descriptor_srv_stencil)),
          resource_state_(resource_state) {}

    ID3D12Resource* resource() const { return resource_.Get(); }
    const ui::d3d12::D3D12CpuDescriptorPool::Descriptor& descriptor_draw() const {
      return descriptor_draw_;
    }
    const ui::d3d12::D3D12CpuDescriptorPool::Descriptor& descriptor_srv() const {
      return descriptor_srv_;
    }
    const ui::d3d12::D3D12CpuDescriptorPool::Descriptor& descriptor_srv_stencil() const {
      return descriptor_srv_stencil_;
    }
    const ui::d3d12::D3D12CpuDescriptorPool::Descriptor& descriptor_load_separate() const {
      return descriptor_load_separate_;
    }

    D3D12_RESOURCE_STATES SetResourceState(D3D12_RESOURCE_STATES new_state) {
      D3D12_RESOURCE_STATES old_state = resource_state_;
      resource_state_ = new_state;
      return old_state;
    }

    uint32_t temporary_srv_descriptor_index() const { return temporary_srv_descriptor_index_; }
    void SetTemporarySRVDescriptorIndex(uint32_t index) { temporary_srv_descriptor_index_ = index; }
    uint32_t temporary_srv_descriptor_index_stencil() const {
      return temporary_srv_descriptor_index_stencil_;
    }
    void SetTemporarySRVDescriptorIndexStencil(uint32_t index) {
      temporary_srv_descriptor_index_stencil_ = index;
    }
    uint32_t temporary_sort_index() const { return temporary_sort_index_; }
    void SetTemporarySortIndex(uint32_t index) { temporary_sort_index_ = index; }

   private:
    Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
    ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_draw_;
    ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_load_separate_;

    ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_srv_;
    ui::d3d12::D3D12CpuDescriptorPool::Descriptor descriptor_srv_stencil_;
    D3D12_RESOURCE_STATES resource_state_;

    uint32_t temporary_srv_descriptor_index_ = UINT32_MAX;
    uint32_t temporary_srv_descriptor_index_stencil_ = UINT32_MAX;
    uint32_t temporary_sort_index_ = 0;
  };

  enum TransferCBVRegister : uint32_t {
    kTransferCBVRegisterStencilMask,
    kTransferCBVRegisterAddress,
    kTransferCBVRegisterHostDepthAddress,
  };
  enum TransferSRVRegister : uint32_t {
    kTransferSRVRegisterColor,
    kTransferSRVRegisterDepth,
    kTransferSRVRegisterStencil,
    kTransferSRVRegisterHostDepth,
    kTransferSRVRegisterCount,
  };
  enum TransferUsedRootParameter : uint32_t {

    kTransferUsedRootParameterStencilMaskConstant,
    kTransferUsedRootParameterColorSRV,

    kTransferUsedRootParameterDepthSRV,

    kTransferUsedRootParameterStencilSRV,

    kTransferUsedRootParameterAddressConstant,
    kTransferUsedRootParameterHostDepthSRV,
    kTransferUsedRootParameterHostDepthAddressConstant,
    kTransferUsedRootParameterCount,

    kTransferUsedRootParameterStencilMaskConstantBit =
        uint32_t(1) << kTransferUsedRootParameterStencilMaskConstant,
    kTransferUsedRootParameterColorSRVBit = uint32_t(1) << kTransferUsedRootParameterColorSRV,
    kTransferUsedRootParameterDepthSRVBit = uint32_t(1) << kTransferUsedRootParameterDepthSRV,
    kTransferUsedRootParameterStencilSRVBit = uint32_t(1) << kTransferUsedRootParameterStencilSRV,
    kTransferUsedRootParameterAddressConstantBit = uint32_t(1)
                                                   << kTransferUsedRootParameterAddressConstant,
    kTransferUsedRootParameterHostDepthSRVBit = uint32_t(1)
                                                << kTransferUsedRootParameterHostDepthSRV,
    kTransferUsedRootParameterHostDepthAddressConstantBit =
        uint32_t(1) << kTransferUsedRootParameterHostDepthAddressConstant,

    kTransferUsedRootParametersDescriptorMask =
        kTransferUsedRootParameterColorSRVBit | kTransferUsedRootParameterDepthSRVBit |
        kTransferUsedRootParameterStencilSRVBit | kTransferUsedRootParameterHostDepthSRVBit,
  };
  enum class TransferRootSignatureIndex {
    kColor,
    kDepth,
    kDepthStencil,
    kColorToStencilBit,
    kStencilToStencilBit,
    kColorAndHostDepth,
    kDepthAndHostDepth,
    kDepthStencilAndHostDepth,
    kCount,
  };
  static const uint32_t kTransferUsedRootParameters[size_t(TransferRootSignatureIndex::kCount)];
  enum class TransferMode : uint32_t {

    kColorToDepth,

    kColorToColor,

    kDepthToDepth,

    kDepthToColor,

    kColorToStencilBit,

    kDepthToStencilBit,

    kColorAndHostDepthToDepth,

    kDepthAndHostDepthToDepth,

    kCount,
  };
  enum class TransferOutput {
    kColor,
    kDepth,

    kStencilBit,
  };
  struct TransferModeInfo {
    TransferOutput output;
    TransferRootSignatureIndex root_signature_no_stencil_ref;
    TransferRootSignatureIndex root_signature_with_stencil_ref;
  };
  static const TransferModeInfo kTransferModes[size_t(TransferMode::kCount)];

  union TransferShaderKey {
    uint32_t key;
    struct {
      xenos::MsaaSamples dest_msaa_samples : xenos::kMsaaSamplesBits;
      uint32_t dest_resource_format : xenos::kRenderTargetFormatBits;
      xenos::MsaaSamples source_msaa_samples : xenos::kMsaaSamplesBits;

      xenos::MsaaSamples host_depth_source_msaa_samples : xenos::kMsaaSamplesBits;
      uint32_t source_resource_format : xenos::kRenderTargetFormatBits;

      uint32_t host_depth_source_is_copy : 1;

      static_assert(size_t(TransferMode::kCount) <= (size_t(1) << 3));
      TransferMode mode : 3;
    };

    TransferShaderKey() : key(0) { static_assert_size(*this, sizeof(key)); }

    struct Hasher {
      size_t operator()(const TransferShaderKey& key) const {
        return std::hash<uint32_t>{}(key.key);
      }
    };
    bool operator==(const TransferShaderKey& other_key) const { return key == other_key.key; }
    bool operator!=(const TransferShaderKey& other_key) const { return !(*this == other_key); }
    bool operator<(const TransferShaderKey& other_key) const { return key < other_key.key; }
  };

  union TransferAddressConstant {
    uint32_t constant;
    struct {
      uint32_t dest_pitch : xenos::kEdramPitchTilesBits;
      uint32_t source_pitch : xenos::kEdramPitchTilesBits;

      int32_t source_to_dest : xenos::kEdramBaseTilesBits + 1;
    };
    TransferAddressConstant() : constant(0) { static_assert_size(*this, sizeof(constant)); }
    bool operator==(const TransferAddressConstant& other_constant) const {
      return constant == other_constant.constant;
    }
    bool operator!=(const TransferAddressConstant& other_constant) const {
      return !(*this == other_constant);
    }
  };

  struct TransferInvocation {
    Transfer transfer;
    TransferShaderKey shader_key;
    TransferInvocation(const Transfer& transfer, const TransferShaderKey& shader_key)
        : transfer(transfer), shader_key(shader_key) {}
    bool operator<(const TransferInvocation& other_invocation) const {
      if (shader_key != other_invocation.shader_key) {
        return shader_key < other_invocation.shader_key;
      }

      assert_not_null(transfer.source);
      assert_not_null(other_invocation.transfer.source);
      uint32_t source_index =
          static_cast<const D3D12RenderTarget*>(transfer.source)->temporary_sort_index();
      uint32_t other_source_index =
          static_cast<const D3D12RenderTarget*>(other_invocation.transfer.source)
              ->temporary_sort_index();
      if (source_index != other_source_index) {
        return source_index < other_source_index;
      }
      return transfer.start_tiles < other_invocation.transfer.start_tiles;
    }
    bool CanBeMergedIntoOneDraw(const TransferInvocation& other_invocation) const {
      return shader_key == other_invocation.shader_key &&
             transfer.AreSourcesSame(other_invocation.transfer);
    }
  };

  enum {
    kHostDepthStoreRootParameterConstants,
    kHostDepthStoreRootParameterSource,
    kHostDepthStoreRootParameterDest,
    kHostDepthStoreRootParameterCount,
  };

  union DumpPipelineKey {
    uint32_t key;
    struct {
      xenos::MsaaSamples msaa_samples : 2;
      uint32_t resource_format : 4;

      uint32_t is_depth : 1;
    };

    DumpPipelineKey() : key(0) { static_assert_size(*this, sizeof(key)); }

    struct Hasher {
      size_t operator()(const DumpPipelineKey& key) const { return std::hash<uint32_t>{}(key.key); }
    };
    bool operator==(const DumpPipelineKey& other_key) const { return key == other_key.key; }
    bool operator!=(const DumpPipelineKey& other_key) const { return !(*this == other_key); }
    bool operator<(const DumpPipelineKey& other_key) const { return key < other_key.key; }

    xenos::ColorRenderTargetFormat GetColorFormat() const {
      assert_false(is_depth);
      return xenos::ColorRenderTargetFormat(resource_format);
    }
    xenos::DepthRenderTargetFormat GetDepthFormat() const {
      assert_true(is_depth);
      return xenos::DepthRenderTargetFormat(resource_format);
    }
  };

  union DumpOffsets {
    uint32_t offsets;
    struct {
      uint32_t dispatch_first_tile : xenos::kEdramBaseTilesBits + 1;
      uint32_t source_base_tiles : xenos::kEdramBaseTilesBits;
    };
    DumpOffsets() : offsets(0) { static_assert_size(*this, sizeof(offsets)); }
    bool operator==(const DumpOffsets& other_offsets) const {
      return offsets == other_offsets.offsets;
    }
    bool operator!=(const DumpOffsets& other_offsets) const { return !(*this == other_offsets); }
  };

  union DumpPitches {
    uint32_t pitches;
    struct {
      uint32_t dest_pitch : xenos::kEdramPitchTilesBits;
      uint32_t source_pitch : xenos::kEdramPitchTilesBits;
    };
    DumpPitches() : pitches(0) { static_assert_size(*this, sizeof(pitches)); }
    bool operator==(const DumpPitches& other_pitches) const {
      return pitches == other_pitches.pitches;
    }
    bool operator!=(const DumpPitches& other_pitches) const { return !(*this == other_pitches); }
  };

  enum DumpCbuffer : uint32_t {
    kDumpCbufferOffsets,
    kDumpCbufferPitches,
    kDumpCbufferCount,
  };

  enum DumpRootParameter : uint32_t {

    kDumpRootParameterOffsets,

    kDumpRootParameterSource,

    kDumpRootParameterColorPitches = kDumpRootParameterSource + 1,

    kDumpRootParameterColorEdram,

    kDumpRootParameterColorCount,

    kDumpRootParameterDepthStencil = kDumpRootParameterSource + 1,
    kDumpRootParameterDepthPitches,
    kDumpRootParameterDepthEdram,

    kDumpRootParameterDepthCount,
  };

  struct DumpInvocation {
    ResolveCopyDumpRectangle rectangle;
    DumpPipelineKey pipeline_key;
    DumpInvocation(const ResolveCopyDumpRectangle& rectangle, const DumpPipelineKey& pipeline_key)
        : rectangle(rectangle), pipeline_key(pipeline_key) {}
    bool operator<(const DumpInvocation& other_invocation) const {
      if (pipeline_key != other_invocation.pipeline_key) {
        return pipeline_key < other_invocation.pipeline_key;
      }
      assert_not_null(rectangle.render_target);
      uint32_t render_target_index =
          static_cast<const D3D12RenderTarget*>(rectangle.render_target)->temporary_sort_index();
      const ResolveCopyDumpRectangle& other_rectangle = other_invocation.rectangle;
      uint32_t other_render_target_index =
          static_cast<const D3D12RenderTarget*>(other_rectangle.render_target)
              ->temporary_sort_index();
      if (render_target_index != other_render_target_index) {
        return render_target_index < other_render_target_index;
      }
      if (rectangle.row_first != other_rectangle.row_first) {
        return rectangle.row_first < other_rectangle.row_first;
      }
      return rectangle.row_first_start < other_rectangle.row_first_start;
    }
  };

  struct DirectResolvePushConstants {
    draw_util::ResolveCopyShaderConstants resolve;
    uint32_t source_base_tiles;
    uint32_t source_pitch_tiles;
    uint32_t dispatch_first_tile;
  };

  struct DirectResolvePipelineKey {
    DumpPipelineKey dump_pipeline_key;
    draw_util::ResolveCopyShaderIndex copy_shader;
    bool draw_resolution_scaled;

    uint64_t packed() const {
      return uint64_t(dump_pipeline_key.key) | (uint64_t(size_t(copy_shader)) << 32) |
             (uint64_t(draw_resolution_scaled ? 1 : 0) << 40);
    }
    struct Hasher {
      size_t operator()(const DirectResolvePipelineKey& key) const {
        return std::hash<uint64_t>{}(key.packed());
      }
    };
    bool operator==(const DirectResolvePipelineKey& other_key) const {
      return packed() == other_key.packed();
    }
  };

  ID3D12PipelineState* const* GetOrCreateTransferPipelines(TransferShaderKey key);

  static TransferMode GetTransferMode(bool dest_is_stencil_bit, bool dest_is_depth,
                                      bool source_is_depth, bool source_has_host_depth) {
    assert_true(dest_is_depth || (!dest_is_stencil_bit && !source_has_host_depth));
    if (dest_is_stencil_bit) {
      return source_is_depth ? TransferMode::kDepthToStencilBit : TransferMode::kColorToStencilBit;
    }
    if (dest_is_depth) {
      if (source_is_depth) {
        return source_has_host_depth ? TransferMode::kDepthAndHostDepthToDepth
                                     : TransferMode::kDepthToDepth;
      }
      return source_has_host_depth ? TransferMode::kColorAndHostDepthToDepth
                                   : TransferMode::kColorToDepth;
    }
    return source_is_depth ? TransferMode::kDepthToColor : TransferMode::kColorToColor;
  }

  void PerformTransfersAndResolveClears(
      uint32_t render_target_count, RenderTarget* const* render_targets,
      const std::vector<Transfer>* render_target_transfers,
      const uint64_t* render_target_resolve_clear_values = nullptr,
      const Transfer::Rectangle* resolve_clear_rectangle = nullptr);

  void SetCommandListRenderTargets(RenderTarget* const* depth_and_color_render_targets);

  ID3D12PipelineState* GetOrCreateDumpPipeline(DumpPipelineKey key);
  ID3D12PipelineState* GetOrCreateDirectResolvePipeline(DirectResolvePipelineKey key);
  bool TryResolveCopyDirectly(const draw_util::ResolveInfo& resolve_info,
                              draw_util::ResolveCopyShaderIndex copy_shader,
                              bool draw_resolution_scaled);

  bool DumpRenderTargets(uint32_t dump_base, uint32_t dump_row_length_used, uint32_t dump_rows,
                         uint32_t dump_pitch);

  bool use_stencil_reference_output_ = false;

  bool gamma_render_target_as_unorm16_ = false;

  bool depth_float24_round_ = false;
  bool depth_float24_convert_in_pixel_shader_ = false;

  bool msaa_2x_supported_ = false;

  std::shared_ptr<ui::d3d12::D3D12CpuDescriptorPool> descriptor_pool_color_;
  std::shared_ptr<ui::d3d12::D3D12CpuDescriptorPool> descriptor_pool_depth_;
  std::shared_ptr<ui::d3d12::D3D12CpuDescriptorPool> descriptor_pool_srv_;
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor null_rtv_descriptor_ss_;
  ui::d3d12::D3D12CpuDescriptorPool::Descriptor null_rtv_descriptor_ms_;

  const RenderTarget* const*
      current_command_list_render_targets_[1 + xenos::kMaxColorRenderTargets];
  bool are_current_command_list_render_targets_valid_ = false;

  std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> current_temporary_descriptors_cpu_;
  std::vector<ui::d3d12::util::DescriptorCpuGpuHandlePair> current_temporary_descriptors_gpu_;

  ID3D12RootSignature* host_depth_store_root_signature_ = nullptr;
  ID3D12PipelineState* host_depth_store_pipelines_[size_t(xenos::MsaaSamples::k4X) + 1] = {};

  std::unique_ptr<ui::d3d12::D3D12UploadBufferPool> transfer_vertex_buffer_pool_;

  ID3D12RootSignature* transfer_root_signatures_[size_t(TransferRootSignatureIndex::kCount)] = {};
  std::unordered_map<TransferShaderKey, ID3D12PipelineState*, TransferShaderKey::Hasher>
      transfer_pipelines_;
  std::unordered_map<TransferShaderKey, std::array<ID3D12PipelineState*, 8>,
                     TransferShaderKey::Hasher>
      transfer_stencil_bit_pipelines_;

  std::vector<TransferInvocation> current_transfer_invocations_;

  std::vector<ResolveCopyDumpRectangle> dump_rectangles_;
  std::vector<DumpInvocation> dump_invocations_;
  std::vector<ResolveCopyDispatch> direct_resolve_dispatches_;

  ID3D12RootSignature* dump_root_signature_color_ = nullptr;
  ID3D12RootSignature* dump_root_signature_depth_ = nullptr;

  std::unordered_map<DumpPipelineKey, ID3D12PipelineState*, DumpPipelineKey::Hasher>
      dump_pipelines_;
  ID3D12RootSignature* direct_resolve_root_signature_color_ = nullptr;
  ID3D12RootSignature* direct_resolve_root_signature_depth_ = nullptr;
  std::unordered_map<DirectResolvePipelineKey, ID3D12PipelineState*,
                     DirectResolvePipelineKey::Hasher>
      direct_resolve_pipelines_;
  uint64_t direct_resolve_attempt_count_ = 0;
  uint64_t direct_resolve_success_count_ = 0;
  uint64_t direct_resolve_fallback_count_ = 0;

  ID3D12RootSignature* uint32_rtv_clear_root_signature_ = nullptr;

  ID3D12PipelineState* uint32_rtv_clear_pipelines_[2][size_t(xenos::MsaaSamples::k4X) + 1] = {};

  std::vector<Transfer> clear_transfers_[2];

  std::vector<uint32_t> built_shader_;

  ID3D12RootSignature* resolve_rov_clear_root_signature_ = nullptr;

  ID3D12PipelineState* resolve_rov_clear_32bpp_pipeline_ = nullptr;

  ID3D12PipelineState* resolve_rov_clear_64bpp_pipeline_ = nullptr;
};

}

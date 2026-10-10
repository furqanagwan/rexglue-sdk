

#include "thirdparty/dxbc/DXBCChecksum.h"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <iterator>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/d3d12/command_processor.h>
#include <rex/graphics/d3d12/deferred_command_list.h>
#include <rex/graphics/d3d12/render_target_cache.h>
#include <rex/graphics/d3d12/texture_cache.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/format/dxbc.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/string.h>
#include <rex/ui/d3d12/d3d12_provider.h>
#include <rex/ui/d3d12/d3d12_util.h>

namespace rex::graphics::d3d12 {

void D3D12RenderTargetCache::PerformTransfersAndResolveClears(
    uint32_t render_target_count, RenderTarget* const* render_targets,
    const std::vector<Transfer>* render_target_transfers,
    const uint64_t* render_target_resolve_clear_values,
    const Transfer::Rectangle* resolve_clear_rectangle) {
  assert_true(GetPath() == Path::kHostRenderTargets);

  const ui::d3d12::D3D12Provider& provider = command_processor_.GetD3D12Provider();
  ID3D12Device* device = provider.GetDevice();
  uint64_t current_submission = command_processor_.GetCurrentSubmission();
  DeferredCommandList& command_list = command_processor_.GetDeferredCommandList();

  bool resolve_clear_needed = render_target_resolve_clear_values && resolve_clear_rectangle;
  D3D12_RECT clear_rect;
  if (resolve_clear_needed) {
    clear_rect.left = LONG(resolve_clear_rectangle->x_pixels * draw_resolution_scale_x());
    clear_rect.top = LONG(resolve_clear_rectangle->y_pixels * draw_resolution_scale_y());
    clear_rect.right =
        LONG((resolve_clear_rectangle->x_pixels + resolve_clear_rectangle->width_pixels) *
             draw_resolution_scale_x());
    clear_rect.bottom =
        LONG((resolve_clear_rectangle->y_pixels + resolve_clear_rectangle->height_pixels) *
             draw_resolution_scale_y());
  }

  bool host_depth_store_set_up = false;
  for (uint32_t i = 0; i < render_target_count; ++i) {
    RenderTarget* dest_rt = render_targets[i];
    if (!dest_rt) {
      continue;
    }
    auto& dest_d3d12_rt = *static_cast<D3D12RenderTarget*>(dest_rt);
    RenderTargetKey dest_rt_key = dest_d3d12_rt.key();
    if (!dest_rt_key.is_depth) {
      continue;
    }
    const std::vector<Transfer>& depth_transfers = render_target_transfers[i];
    for (const Transfer& transfer : depth_transfers) {
      if (transfer.host_depth_source != dest_rt) {
        continue;
      }
      if (!host_depth_store_set_up) {
        ui::d3d12::util::DescriptorCpuGpuHandlePair host_depth_store_descriptors[2];
        if (!command_processor_.RequestOneUseSingleViewDescriptors(
                1 + uint32_t(!bindless_resources_used_), host_depth_store_descriptors)) {
          continue;
        }
        command_list.D3DSetComputeRootSignature(host_depth_store_root_signature_);

        if (bindless_resources_used_) {
          command_list.D3DSetComputeRootDescriptorTable(
              kHostDepthStoreRootParameterDest,
              command_processor_.GetEdramUintPow2BindlessUAVHandlePair(4).second);
        } else {
          const ui::d3d12::util::DescriptorCpuGpuHandlePair& host_depth_store_descriptor_dest =
              host_depth_store_descriptors[1];
          WriteEdramUintPow2UAVDescriptor(host_depth_store_descriptor_dest.first, 4);
          command_list.D3DSetComputeRootDescriptorTable(kHostDepthStoreRootParameterDest,
                                                        host_depth_store_descriptor_dest.second);
        }

        const ui::d3d12::util::DescriptorCpuGpuHandlePair& host_depth_store_descriptor_source =
            host_depth_store_descriptors[0];
        device->CopyDescriptorsSimple(1, host_depth_store_descriptor_source.first,
                                      dest_d3d12_rt.descriptor_srv().GetHandle(),
                                      D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
        command_list.D3DSetComputeRootDescriptorTable(kHostDepthStoreRootParameterSource,
                                                      host_depth_store_descriptor_source.second);

        HostDepthStoreRenderTargetConstant host_depth_store_render_target_constant =
            GetHostDepthStoreRenderTargetConstant(dest_rt_key.pitch_tiles_at_32bpp,
                                                  msaa_2x_supported_);
        command_list.D3DSetComputeRoot32BitConstants(
            kHostDepthStoreRootParameterConstants,
            sizeof(host_depth_store_render_target_constant) / sizeof(uint32_t),
            &host_depth_store_render_target_constant,
            offsetof(HostDepthStoreConstants, render_target) / sizeof(uint32_t));

        TransitionEdramBuffer(D3D12_RESOURCE_STATE_UNORDERED_ACCESS);
        command_processor_.PushTransitionBarrier(
            dest_d3d12_rt.resource(),
            dest_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE),
            D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE);

        command_processor_.SetExternalPipeline(
            host_depth_store_pipelines_[size_t(dest_rt_key.msaa_samples)]);
        host_depth_store_set_up = true;
      }
      Transfer::Rectangle transfer_rectangles[Transfer::kMaxRectanglesWithCutout];
      uint32_t transfer_rectangle_count = transfer.GetRectangles(
          dest_rt_key.base_tiles, dest_rt_key.pitch_tiles_at_32bpp, dest_rt_key.msaa_samples, false,
          transfer_rectangles, resolve_clear_rectangle);
      assert_not_zero(transfer_rectangle_count);
      HostDepthStoreRectangleConstant host_depth_store_rectangle_constant;
      for (uint32_t j = 0; j < transfer_rectangle_count; ++j) {
        uint32_t group_count_x, group_count_y;
        GetHostDepthStoreRectangleInfo(transfer_rectangles[j], dest_rt_key.msaa_samples,
                                       host_depth_store_rectangle_constant, group_count_x,
                                       group_count_y);
        command_list.D3DSetComputeRoot32BitConstants(
            kHostDepthStoreRootParameterConstants,
            sizeof(host_depth_store_rectangle_constant) / sizeof(uint32_t),
            &host_depth_store_rectangle_constant,
            offsetof(HostDepthStoreConstants, rectangle) / sizeof(uint32_t));
        command_processor_.SubmitBarriers();
        command_list.D3DDispatch(group_count_x, group_count_y, 1);
        MarkEdramBufferModified();
      }
    }
    break;
  }

  for (uint32_t i = 0; i < render_target_count; ++i) {
    RenderTarget* dest_rt = render_targets[i];
    if (!dest_rt) {
      continue;
    }
    auto& dest_d3d12_rt = *static_cast<D3D12RenderTarget*>(dest_rt);
    const std::vector<Transfer>& dest_transfers = render_target_transfers[i];
    if (!resolve_clear_needed && dest_transfers.empty()) {
      continue;
    }

    for (const Transfer& transfer : render_target_transfers[i]) {
      bool source_previously_used_as_dest = false;
      bool host_depth_source_previously_used_as_dest = false;
      for (uint32_t j = 0; j < i; ++j) {
        if (render_target_transfers[j].empty()) {
          continue;
        }
        const RenderTarget* previous_rt = render_targets[j];
        if (transfer.source == previous_rt) {
          source_previously_used_as_dest = true;
        }
        if (transfer.host_depth_source == previous_rt) {
          host_depth_source_previously_used_as_dest = true;
        }
      }
      if (!source_previously_used_as_dest) {
        auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(transfer.source);
        command_processor_.PushTransitionBarrier(
            source_d3d12_rt.resource(),
            source_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
      }

      if (transfer.host_depth_source && transfer.host_depth_source != dest_rt &&
          !host_depth_source_previously_used_as_dest) {
        auto& host_depth_source_d3d12_rt =
            *static_cast<D3D12RenderTarget*>(transfer.host_depth_source);
        command_processor_.PushTransitionBarrier(
            host_depth_source_d3d12_rt.resource(),
            host_depth_source_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
      }
    }

    bool dest_used_previously_as_source = false;
    for (uint32_t j = 0; j < i; ++j) {
      for (const Transfer& previous_transfer : render_target_transfers[j]) {
        if (previous_transfer.source == dest_rt || previous_transfer.host_depth_source == dest_rt) {
          dest_used_previously_as_source = true;
          break;
        }
      }
    }
    if (!dest_used_previously_as_source) {
      D3D12_RESOURCE_STATES dest_state = dest_d3d12_rt.key().is_depth
                                             ? D3D12_RESOURCE_STATE_DEPTH_WRITE
                                             : D3D12_RESOURCE_STATE_RENDER_TARGET;
      command_processor_.PushTransitionBarrier(
          dest_d3d12_rt.resource(), dest_d3d12_rt.SetResourceState(dest_state), dest_state);
    }
  }
  if (host_depth_store_set_up) {
    TransitionEdramBuffer(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
  }

  for (uint32_t i = 0; i < render_target_count; ++i) {
    RenderTarget* dest_rt = render_targets[i];
    if (!dest_rt) {
      continue;
    }
    for (const Transfer& transfer : render_target_transfers[i]) {
      assert_not_null(transfer.source);
      auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(transfer.source);
      source_d3d12_rt.SetTemporarySRVDescriptorIndex(UINT32_MAX);
      source_d3d12_rt.SetTemporarySRVDescriptorIndexStencil(UINT32_MAX);
      auto* host_depth_source_d3d12_rt =
          static_cast<D3D12RenderTarget*>(transfer.host_depth_source);
      if (host_depth_source_d3d12_rt) {
        host_depth_source_d3d12_rt->SetTemporarySRVDescriptorIndex(UINT32_MAX);
        host_depth_source_d3d12_rt->SetTemporarySRVDescriptorIndexStencil(UINT32_MAX);
      }
    }
  }
  current_temporary_descriptors_cpu_.clear();
  uint32_t host_depth_copy_srv_index;
  if (host_depth_store_set_up && !bindless_resources_used_) {
    host_depth_copy_srv_index = uint32_t(current_temporary_descriptors_cpu_.size());
    current_temporary_descriptors_cpu_.push_back(provider.OffsetViewDescriptor(
        edram_buffer_descriptor_heap_start_, uint32_t(EdramBufferDescriptorIndex::kR32UintSRV)));
  } else {
    host_depth_copy_srv_index = UINT32_MAX;
  }
  for (uint32_t i = 0; i < render_target_count; ++i) {
    RenderTarget* dest_rt = render_targets[i];
    if (!dest_rt) {
      continue;
    }
    bool dest_is_depth = dest_rt->key().is_depth;
    for (const Transfer& transfer : render_target_transfers[i]) {
      assert_not_null(transfer.source);
      auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(transfer.source);
      if (source_d3d12_rt.temporary_srv_descriptor_index() == UINT32_MAX) {
        source_d3d12_rt.SetTemporarySRVDescriptorIndex(
            uint32_t(current_temporary_descriptors_cpu_.size()));
        current_temporary_descriptors_cpu_.push_back(source_d3d12_rt.descriptor_srv().GetHandle());
      }
      if (source_d3d12_rt.key().is_depth &&
          source_d3d12_rt.temporary_srv_descriptor_index_stencil() == UINT32_MAX) {
        source_d3d12_rt.SetTemporarySRVDescriptorIndexStencil(
            uint32_t(current_temporary_descriptors_cpu_.size()));
        current_temporary_descriptors_cpu_.push_back(
            source_d3d12_rt.descriptor_srv_stencil().GetHandle());
      }
      bool source_is_depth = source_d3d12_rt.key().is_depth;
      auto* host_depth_source_d3d12_rt =
          static_cast<D3D12RenderTarget*>(transfer.host_depth_source);

      if (host_depth_source_d3d12_rt && host_depth_source_d3d12_rt != dest_rt &&
          host_depth_source_d3d12_rt->temporary_srv_descriptor_index() == UINT32_MAX) {
        host_depth_source_d3d12_rt->SetTemporarySRVDescriptorIndex(
            uint32_t(current_temporary_descriptors_cpu_.size()));
        current_temporary_descriptors_cpu_.push_back(
            host_depth_source_d3d12_rt->descriptor_srv().GetHandle());
      }
    }
  }
  uint32_t descriptor_count = uint32_t(current_temporary_descriptors_cpu_.size());
  current_temporary_descriptors_gpu_.resize(descriptor_count);
  if (!command_processor_.RequestOneUseSingleViewDescriptors(
          descriptor_count, current_temporary_descriptors_gpu_.data())) {
    return;
  }
  for (uint32_t i = 0; i < descriptor_count; ++i) {
    device->CopyDescriptorsSimple(1, current_temporary_descriptors_gpu_[i].first,
                                  current_temporary_descriptors_cpu_[i],
                                  D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  }

  bool transfer_viewport_set = false;
  float pixels_to_ndc_unscaled = 2.0f / float(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION);
  float pixels_to_ndc_x = pixels_to_ndc_unscaled * draw_resolution_scale_x();
  float pixels_to_ndc_y = pixels_to_ndc_unscaled * draw_resolution_scale_y();

  TransferRootSignatureIndex last_transfer_root_signature_index =
      TransferRootSignatureIndex::kCount;
  uint32_t transfer_root_parameters_set = 0;
  uint32_t last_descriptor_index_color = UINT32_MAX;
  uint32_t last_descriptor_index_depth = UINT32_MAX;
  uint32_t last_descriptor_index_stencil = UINT32_MAX;
  uint32_t last_descriptor_index_host_depth_non_copy = UINT32_MAX;
  bool last_descriptor_host_depth_is_copy = false;
  TransferAddressConstant last_address_constant;
  TransferAddressConstant last_host_depth_address_constant;

  for (uint32_t i = 0; i < render_target_count; ++i) {
    RenderTarget* dest_rt = render_targets[i];
    if (!dest_rt) {
      continue;
    }

    const std::vector<Transfer>& current_transfers = render_target_transfers[i];
    if (current_transfers.empty() && !resolve_clear_needed) {
      continue;
    }

    auto& dest_d3d12_rt = *static_cast<D3D12RenderTarget*>(dest_rt);
    RenderTargetKey dest_rt_key = dest_d3d12_rt.key();

    D3D12_RESOURCE_STATES dest_state = dest_rt_key.is_depth ? D3D12_RESOURCE_STATE_DEPTH_WRITE
                                                            : D3D12_RESOURCE_STATE_RENDER_TARGET;
    command_processor_.PushTransitionBarrier(
        dest_d3d12_rt.resource(), dest_d3d12_rt.SetResourceState(dest_state), dest_state);

    if (!current_transfers.empty()) {
      are_current_command_list_render_targets_valid_ = false;
      if (dest_rt_key.is_depth) {
        D3D12_CPU_DESCRIPTOR_HANDLE dsv_handle = dest_d3d12_rt.descriptor_draw().GetHandle();
        command_list.D3DOMSetRenderTargets(0, nullptr, FALSE, &dsv_handle);
        if (!use_stencil_reference_output_) {
          command_processor_.SetStencilReference(UINT8_MAX);
        }
      } else {
        D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle =
            dest_d3d12_rt.descriptor_load_separate().IsValid()
                ? dest_d3d12_rt.descriptor_load_separate().GetHandle()
                : dest_d3d12_rt.descriptor_draw().GetHandle();
        command_list.D3DOMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);
      }

      uint32_t dest_pitch_tiles = dest_rt_key.GetPitchTiles();
      bool dest_is_64bpp = dest_rt_key.Is64bpp();

      bool need_stencil_bit_draws = dest_rt_key.is_depth && !use_stencil_reference_output_;
      current_transfer_invocations_.clear();
      current_transfer_invocations_.reserve(current_transfers.size()
                                            << uint32_t(need_stencil_bit_draws));
      uint32_t rt_sort_index = 0;
      TransferShaderKey new_transfer_shader_key;
      new_transfer_shader_key.dest_msaa_samples = dest_rt_key.msaa_samples;
      new_transfer_shader_key.dest_resource_format = dest_rt_key.resource_format;
      uint32_t stencil_clear_rectangle_count = 0;
      for (uint32_t j = 0; j <= uint32_t(need_stencil_bit_draws); ++j) {
        for (const Transfer& transfer : current_transfers) {
          auto* host_depth_source_d3d12_rt =
              static_cast<D3D12RenderTarget*>(transfer.host_depth_source);
          if (host_depth_source_d3d12_rt) {
            host_depth_source_d3d12_rt->SetTemporarySortIndex(UINT32_MAX);
          }
          assert_not_null(transfer.source);
          auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(transfer.source);
          source_d3d12_rt.SetTemporarySortIndex(UINT32_MAX);
        }
        for (const Transfer& transfer : current_transfers) {
          assert_not_null(transfer.source);
          auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(transfer.source);
          D3D12RenderTarget* host_depth_source_d3d12_rt =
              j ? nullptr : static_cast<D3D12RenderTarget*>(transfer.host_depth_source);
          if (host_depth_source_d3d12_rt &&
              host_depth_source_d3d12_rt->temporary_sort_index() == UINT32_MAX) {
            host_depth_source_d3d12_rt->SetTemporarySortIndex(rt_sort_index++);
          }
          if (source_d3d12_rt.temporary_sort_index() == UINT32_MAX) {
            source_d3d12_rt.SetTemporarySortIndex(rt_sort_index++);
          }
          RenderTargetKey source_rt_key = source_d3d12_rt.key();
          new_transfer_shader_key.source_msaa_samples = source_rt_key.msaa_samples;
          new_transfer_shader_key.source_resource_format = source_rt_key.resource_format;
          bool host_depth_source_is_copy = host_depth_source_d3d12_rt == &dest_d3d12_rt;
          new_transfer_shader_key.host_depth_source_is_copy = host_depth_source_is_copy;

          new_transfer_shader_key.host_depth_source_msaa_samples =
              (host_depth_source_d3d12_rt && !host_depth_source_is_copy)
                  ? host_depth_source_d3d12_rt->key().msaa_samples
                  : xenos::MsaaSamples::k1X;
          if (j) {
            new_transfer_shader_key.mode = source_rt_key.is_depth
                                               ? TransferMode::kDepthToStencilBit
                                               : TransferMode::kColorToStencilBit;
            stencil_clear_rectangle_count += transfer.GetRectangles(
                dest_rt_key.base_tiles, dest_pitch_tiles, dest_rt_key.msaa_samples, dest_is_64bpp,
                nullptr, resolve_clear_rectangle);
          } else {
            if (dest_rt_key.is_depth) {
              if (host_depth_source_d3d12_rt) {
                new_transfer_shader_key.mode = source_rt_key.is_depth
                                                   ? TransferMode::kDepthAndHostDepthToDepth
                                                   : TransferMode::kColorAndHostDepthToDepth;
              } else {
                new_transfer_shader_key.mode = source_rt_key.is_depth ? TransferMode::kDepthToDepth
                                                                      : TransferMode::kColorToDepth;
              }
            } else {
              new_transfer_shader_key.mode = source_rt_key.is_depth ? TransferMode::kDepthToColor
                                                                    : TransferMode::kColorToColor;
            }
          }
          current_transfer_invocations_.emplace_back(transfer, new_transfer_shader_key);
          if (j) {
            current_transfer_invocations_.back().transfer.host_depth_source = nullptr;
          }
        }
      }
      std::sort(current_transfer_invocations_.begin(), current_transfer_invocations_.end());

      if (stencil_clear_rectangle_count) {
        command_processor_.SubmitBarriers();
        D3D12_RECT* stencil_clear_rect_write_ptr = command_list.ClearDepthStencilViewAllocatedRects(
            dest_d3d12_rt.descriptor_draw().GetHandle(), D3D12_CLEAR_FLAG_STENCIL, 0.0f, 0,
            stencil_clear_rectangle_count);
        assert_not_null(stencil_clear_rect_write_ptr);
        for (const Transfer& transfer : current_transfers) {
          Transfer::Rectangle transfer_stencil_clear_rectangles[Transfer::kMaxRectanglesWithCutout];
          uint32_t transfer_stencil_clear_rectangle_count = transfer.GetRectangles(
              dest_rt_key.base_tiles, dest_pitch_tiles, dest_rt_key.msaa_samples, dest_is_64bpp,
              transfer_stencil_clear_rectangles, resolve_clear_rectangle);
          for (uint32_t j = 0; j < transfer_stencil_clear_rectangle_count; ++j) {
            const Transfer::Rectangle& stencil_clear_rectangle =
                transfer_stencil_clear_rectangles[j];
            stencil_clear_rect_write_ptr->left =
                LONG(stencil_clear_rectangle.x_pixels * draw_resolution_scale_x());
            stencil_clear_rect_write_ptr->top =
                LONG(stencil_clear_rectangle.y_pixels * draw_resolution_scale_y());
            stencil_clear_rect_write_ptr->right =
                LONG((stencil_clear_rectangle.x_pixels + stencil_clear_rectangle.width_pixels) *
                     draw_resolution_scale_x());
            stencil_clear_rect_write_ptr->bottom =
                LONG((stencil_clear_rectangle.y_pixels + stencil_clear_rectangle.height_pixels) *
                     draw_resolution_scale_y());
            ++stencil_clear_rect_write_ptr;
          }
        }
      }

      if (!transfer_viewport_set) {
        transfer_viewport_set = true;

        D3D12_VIEWPORT transfer_viewport;
        transfer_viewport.TopLeftX = 0.0f;
        transfer_viewport.TopLeftY = 0.0f;
        transfer_viewport.Width = float(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION);
        transfer_viewport.Height = float(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION);
        transfer_viewport.MinDepth = 0.0f;
        transfer_viewport.MaxDepth = 1.0f;
        command_processor_.SetViewport(transfer_viewport);

        D3D12_RECT transfer_scissor;
        transfer_scissor.left = 0;
        transfer_scissor.top = 0;
        transfer_scissor.right = LONG(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION);
        transfer_scissor.bottom = LONG(D3D12_REQ_TEXTURE2D_U_OR_V_DIMENSION);
        command_processor_.SetScissorRect(transfer_scissor);
      }

      for (auto it = current_transfer_invocations_.cbegin();
           it != current_transfer_invocations_.cend(); ++it) {
        const TransferInvocation& transfer_invocation_first = *it;

        auto it_merged_first = it, it_merged_last = it;
        uint32_t transfer_rectangle_count = transfer_invocation_first.transfer.GetRectangles(
            dest_rt_key.base_tiles, dest_pitch_tiles, dest_rt_key.msaa_samples, dest_is_64bpp,
            nullptr, resolve_clear_rectangle);
        for (auto it_merge = std::next(it_merged_first);
             it_merge != current_transfer_invocations_.cend(); ++it_merge) {
          if (!transfer_invocation_first.CanBeMergedIntoOneDraw(*it_merge)) {
            break;
          }
          transfer_rectangle_count += it_merge->transfer.GetRectangles(
              dest_rt_key.base_tiles, dest_pitch_tiles, dest_rt_key.msaa_samples, dest_is_64bpp,
              nullptr, resolve_clear_rectangle);
          it_merged_last = it_merge;
        }
        assert_not_zero(transfer_rectangle_count);

        it = it_merged_last;

        assert_not_null(it->transfer.source);
        auto& source_d3d12_rt = *static_cast<D3D12RenderTarget*>(it->transfer.source);
        auto* host_depth_source_d3d12_rt =
            static_cast<D3D12RenderTarget*>(it->transfer.host_depth_source);
        TransferShaderKey transfer_shader_key = it->shader_key;
        const TransferModeInfo& transfer_mode_info =
            kTransferModes[size_t(transfer_shader_key.mode)];
        TransferRootSignatureIndex transfer_root_signature_index =
            use_stencil_reference_output_ ? transfer_mode_info.root_signature_with_stencil_ref
                                          : transfer_mode_info.root_signature_no_stencil_ref;
        uint32_t transfer_root_parameters_used =
            kTransferUsedRootParameters[size_t(transfer_root_signature_index)];
        bool is_stencil_bit =
            (transfer_root_parameters_used & kTransferUsedRootParameterStencilMaskConstantBit) != 0;

        command_processor_.PushTransitionBarrier(
            source_d3d12_rt.resource(),
            source_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
            D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
        if (host_depth_source_d3d12_rt) {
          if (transfer_shader_key.host_depth_source_is_copy) {
            TransitionEdramBuffer(D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
          } else {
            command_processor_.PushTransitionBarrier(
                host_depth_source_d3d12_rt->resource(),
                host_depth_source_d3d12_rt->SetResourceState(
                    D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE),
                D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
          }
        }

        uint32_t transfer_vertex_count = 6 * transfer_rectangle_count;
        D3D12_VERTEX_BUFFER_VIEW transfer_rectangle_buffer_view;
        transfer_rectangle_buffer_view.StrideInBytes = sizeof(float) * 2;
        transfer_rectangle_buffer_view.SizeInBytes =
            transfer_rectangle_buffer_view.StrideInBytes * transfer_vertex_count;
        float* transfer_rectangle_write_ptr =
            reinterpret_cast<float*>(transfer_vertex_buffer_pool_->Request(
                current_submission, transfer_rectangle_buffer_view.SizeInBytes, sizeof(float),
                nullptr, nullptr, &transfer_rectangle_buffer_view.BufferLocation));
        if (!transfer_rectangle_write_ptr) {
          continue;
        }
        for (auto it_merged = it_merged_first; it_merged <= it_merged_last; ++it_merged) {
          Transfer::Rectangle transfer_invocation_rectangles[Transfer::kMaxRectanglesWithCutout];
          uint32_t transfer_invocation_rectangle_count = it_merged->transfer.GetRectangles(
              dest_rt_key.base_tiles, dest_pitch_tiles, dest_rt_key.msaa_samples, dest_is_64bpp,
              transfer_invocation_rectangles, resolve_clear_rectangle);
          assert_not_zero(transfer_invocation_rectangle_count);
          for (uint32_t j = 0; j < transfer_invocation_rectangle_count; ++j) {
            const Transfer::Rectangle& transfer_rectangle = transfer_invocation_rectangles[j];
            float transfer_rectangle_x0 = -1.0f + transfer_rectangle.x_pixels * pixels_to_ndc_x;
            float transfer_rectangle_y0 = 1.0f - transfer_rectangle.y_pixels * pixels_to_ndc_y;
            float transfer_rectangle_x1 =
                transfer_rectangle_x0 + transfer_rectangle.width_pixels * pixels_to_ndc_x;
            float transfer_rectangle_y1 =
                transfer_rectangle_y0 - transfer_rectangle.height_pixels * pixels_to_ndc_y;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x0;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y0;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x1;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y0;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x0;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y1;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x0;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y1;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x1;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y0;

            *(transfer_rectangle_write_ptr++) = transfer_rectangle_x1;
            *(transfer_rectangle_write_ptr++) = transfer_rectangle_y1;
          }
        }
        command_processor_.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        command_list.D3DIASetVertexBuffers(0, 1, &transfer_rectangle_buffer_view);

        ID3D12PipelineState* const* transfer_pipelines =
            GetOrCreateTransferPipelines(transfer_shader_key);
        if (!transfer_pipelines) {
          continue;
        }
        if (last_transfer_root_signature_index != transfer_root_signature_index) {
          last_transfer_root_signature_index = transfer_root_signature_index;
          command_processor_.SetExternalGraphicsRootSignature(
              transfer_root_signatures_[size_t(transfer_root_signature_index)]);
          transfer_root_parameters_set = 0;
        }

        if (transfer_root_parameters_used & kTransferUsedRootParameterColorSRVBit) {
          uint32_t descriptor_index_color = source_d3d12_rt.temporary_srv_descriptor_index();
          assert_true(descriptor_index_color != UINT32_MAX);
          if (last_descriptor_index_color != descriptor_index_color) {
            last_descriptor_index_color = descriptor_index_color;
            transfer_root_parameters_set &= ~kTransferUsedRootParameterColorSRVBit;
          }
        }
        if (transfer_root_parameters_used & kTransferUsedRootParameterDepthSRVBit) {
          uint32_t descriptor_index_depth = source_d3d12_rt.temporary_srv_descriptor_index();
          assert_true(descriptor_index_depth != UINT32_MAX);
          if (last_descriptor_index_depth != descriptor_index_depth) {
            last_descriptor_index_depth = descriptor_index_depth;
            transfer_root_parameters_set &= ~kTransferUsedRootParameterDepthSRVBit;
          }
        }
        if (transfer_root_parameters_used & kTransferUsedRootParameterStencilSRVBit) {
          uint32_t descriptor_index_stencil =
              source_d3d12_rt.temporary_srv_descriptor_index_stencil();
          assert_true(descriptor_index_stencil != UINT32_MAX);
          if (last_descriptor_index_stencil != descriptor_index_stencil) {
            last_descriptor_index_stencil = descriptor_index_stencil;
            transfer_root_parameters_set &= ~kTransferUsedRootParameterStencilSRVBit;
          }
        }
        if (transfer_root_parameters_used & kTransferUsedRootParameterHostDepthSRVBit) {
          if (transfer_shader_key.host_depth_source_is_copy) {
            if (!last_descriptor_host_depth_is_copy) {
              last_descriptor_host_depth_is_copy = true;
              transfer_root_parameters_set &= ~kTransferUsedRootParameterHostDepthSRVBit;
            }
          } else {
            assert_not_null(host_depth_source_d3d12_rt);
            uint32_t descriptor_index_host_depth =
                host_depth_source_d3d12_rt->temporary_srv_descriptor_index();
            assert_true(descriptor_index_host_depth != UINT32_MAX);
            if (last_descriptor_host_depth_is_copy ||
                last_descriptor_index_host_depth_non_copy != descriptor_index_host_depth) {
              transfer_root_parameters_set &= ~kTransferUsedRootParameterHostDepthSRVBit;
            }
            last_descriptor_host_depth_is_copy = false;
            last_descriptor_index_host_depth_non_copy = descriptor_index_host_depth;
          }
        }
        if (transfer_root_parameters_used & kTransferUsedRootParameterAddressConstantBit) {
          RenderTargetKey source_rt_key = source_d3d12_rt.key();
          TransferAddressConstant address_constant;
          address_constant.dest_pitch = dest_pitch_tiles;
          address_constant.source_pitch = source_rt_key.GetPitchTiles();
          address_constant.source_to_dest =
              int32_t(dest_rt_key.base_tiles) - int32_t(source_rt_key.base_tiles);
          if (last_address_constant != address_constant) {
            last_address_constant = address_constant;
            transfer_root_parameters_set &= ~kTransferUsedRootParameterAddressConstantBit;
          }
        }
        if (transfer_root_parameters_used & kTransferUsedRootParameterHostDepthAddressConstantBit) {
          assert_not_null(host_depth_source_d3d12_rt);
          RenderTargetKey host_depth_source_rt_key = host_depth_source_d3d12_rt->key();
          TransferAddressConstant host_depth_address_constant;
          host_depth_address_constant.dest_pitch = dest_pitch_tiles;
          host_depth_address_constant.source_pitch = host_depth_source_rt_key.GetPitchTiles();
          host_depth_address_constant.source_to_dest =
              int32_t(dest_rt_key.base_tiles) - int32_t(host_depth_source_rt_key.base_tiles);
          if (last_host_depth_address_constant != host_depth_address_constant) {
            last_host_depth_address_constant = host_depth_address_constant;
            transfer_root_parameters_set &= ~kTransferUsedRootParameterHostDepthAddressConstantBit;
          }
        }

        uint32_t transfer_root_parameters_unset =
            transfer_root_parameters_used & ~transfer_root_parameters_set;
        if (transfer_root_parameters_unset &
            kTransferUsedRootParameterHostDepthAddressConstantBit) {
          command_list.D3DSetGraphicsRoot32BitConstants(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterHostDepthAddressConstantBit - 1)),
              sizeof(last_host_depth_address_constant) / sizeof(uint32_t),
              &last_host_depth_address_constant, 0);
          transfer_root_parameters_set |= kTransferUsedRootParameterHostDepthAddressConstantBit;
        }
        if (transfer_root_parameters_unset & kTransferUsedRootParameterHostDepthSRVBit) {
          D3D12_GPU_DESCRIPTOR_HANDLE descriptor_gpu_handle;
          if (last_descriptor_host_depth_is_copy) {
            if (bindless_resources_used_) {
              descriptor_gpu_handle =
                  command_processor_
                      .GetSystemBindlessViewHandlePair(
                          D3D12CommandProcessor::SystemBindlessView ::kEdramR32UintSRV)
                      .second;
            } else {
              assert_true(host_depth_copy_srv_index != UINT32_MAX);
              descriptor_gpu_handle =
                  current_temporary_descriptors_gpu_[host_depth_copy_srv_index].second;
            }
          } else {
            assert_true(last_descriptor_index_host_depth_non_copy != UINT32_MAX);
            descriptor_gpu_handle =
                current_temporary_descriptors_gpu_[last_descriptor_index_host_depth_non_copy]
                    .second;
          }
          command_list.D3DSetGraphicsRootDescriptorTable(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterHostDepthSRVBit - 1)),
              descriptor_gpu_handle);
          transfer_root_parameters_set |= kTransferUsedRootParameterHostDepthSRVBit;
        }
        if (transfer_root_parameters_unset & kTransferUsedRootParameterAddressConstantBit) {
          command_list.D3DSetGraphicsRoot32BitConstants(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterAddressConstantBit - 1)),
              sizeof(last_address_constant) / sizeof(uint32_t), &last_address_constant, 0);
          transfer_root_parameters_set |= kTransferUsedRootParameterAddressConstantBit;
        }
        if (transfer_root_parameters_unset & kTransferUsedRootParameterStencilSRVBit) {
          assert_true(last_descriptor_index_stencil != UINT32_MAX);
          command_list.D3DSetGraphicsRootDescriptorTable(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterStencilSRVBit - 1)),
              current_temporary_descriptors_gpu_[last_descriptor_index_stencil].second);
          transfer_root_parameters_set |= kTransferUsedRootParameterStencilSRVBit;
        }
        if (transfer_root_parameters_unset & kTransferUsedRootParameterDepthSRVBit) {
          assert_true(last_descriptor_index_depth != UINT32_MAX);
          command_list.D3DSetGraphicsRootDescriptorTable(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterDepthSRVBit - 1)),
              current_temporary_descriptors_gpu_[last_descriptor_index_depth].second);
          transfer_root_parameters_set |= kTransferUsedRootParameterDepthSRVBit;
        }
        if (transfer_root_parameters_unset & kTransferUsedRootParameterColorSRVBit) {
          assert_true(last_descriptor_index_color != UINT32_MAX);
          command_list.D3DSetGraphicsRootDescriptorTable(
              rex::bit_count(transfer_root_parameters_used &
                             (kTransferUsedRootParameterColorSRVBit - 1)),
              current_temporary_descriptors_gpu_[last_descriptor_index_color].second);
          transfer_root_parameters_set |= kTransferUsedRootParameterColorSRVBit;
        }

        command_processor_.SubmitBarriers();
        for (uint32_t j = 0; j <= uint32_t(is_stencil_bit) * 7; ++j) {
          if (is_stencil_bit) {
            uint32_t transfer_stencil_bit = uint32_t(1) << j;
            command_list.D3DSetGraphicsRoot32BitConstants(
                rex::bit_count(transfer_root_parameters_used &
                               (kTransferUsedRootParameterStencilMaskConstantBit - 1)),
                sizeof(transfer_stencil_bit) / sizeof(uint32_t), &transfer_stencil_bit, 0);
          }
          command_processor_.SetExternalPipeline(transfer_pipelines[j]);
          command_list.D3DDrawInstanced(transfer_vertex_count, 1, 0, 0);
        }
      }
    }

    if (resolve_clear_needed) {
      uint64_t clear_value = render_target_resolve_clear_values[i];
      if (dest_rt_key.is_depth) {
        uint32_t depth_guest_clear_value = (uint32_t(clear_value) >> 8) & 0xFFFFFF;
        float depth_host_clear_value = 0.0f;
        switch (dest_rt_key.GetDepthFormat()) {
          case xenos::DepthRenderTargetFormat::kD24S8:
            depth_host_clear_value = xenos::UNorm24To32(depth_guest_clear_value);
            break;
          case xenos::DepthRenderTargetFormat::kD24FS8:

            depth_host_clear_value = xenos::Float20e4To32(depth_guest_clear_value) * 0.5f;
            break;
        }
        command_processor_.PushTransitionBarrier(
            dest_d3d12_rt.resource(),
            dest_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_DEPTH_WRITE),
            D3D12_RESOURCE_STATE_DEPTH_WRITE);
        command_processor_.SubmitBarriers();
        command_list.D3DClearDepthStencilView(dest_d3d12_rt.descriptor_draw().GetHandle(),
                                              D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
                                              depth_host_clear_value, UINT(clear_value) & 0xFF, 1,
                                              &clear_rect);
      } else {
        float color_clear_value[4] = {};
        bool clear_via_drawing = false;
        switch (dest_rt_key.GetColorFormat()) {
          case xenos::ColorRenderTargetFormat::k_8_8_8_8: {
            for (uint32_t j = 0; j < 4; ++j) {
              color_clear_value[j] = ((clear_value >> (j * 8)) & 0xFF) * (1.0f / 0xFF);
            }
          } break;
          case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
            for (uint32_t j = 0; j < 4; ++j) {
              color_clear_value[j] = ((clear_value >> (j * 8)) & 0xFF) * (1.0f / 0xFF);
            }
            for (uint32_t j = 0; j < 3; ++j) {
              color_clear_value[j] = xenos::PWLGammaToLinear(color_clear_value[j]);
            }
          } break;
          case xenos::ColorRenderTargetFormat::k_2_10_10_10:
          case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
            for (uint32_t j = 0; j < 3; ++j) {
              color_clear_value[j] = ((clear_value >> (j * 10)) & 0x3FF) * (1.0f / 0x3FF);
            }
            color_clear_value[3] = ((clear_value >> 30) & 0x3) * (1.0f / 0x3);
          } break;
          case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
          case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
            for (uint32_t j = 0; j < 3; ++j) {
              color_clear_value[j] = xenos::Float7e3To32((clear_value >> (j * 10)) & 0x3FF);
            }
            color_clear_value[3] = ((clear_value >> 30) & 0x3) * (1.0f / 0x3);
          } break;
          case xenos::ColorRenderTargetFormat::k_16_16:
          case xenos::ColorRenderTargetFormat::k_16_16_FLOAT: {
            for (uint32_t j = 0; j < 2; ++j) {
              color_clear_value[j] = float((clear_value >> (j * 16)) & 0xFFFF);
            }
          } break;
          case xenos::ColorRenderTargetFormat::k_16_16_16_16:
          case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT: {
            for (uint32_t j = 0; j < 4; ++j) {
              color_clear_value[j] = float((clear_value >> (j * 16)) & 0xFFFF);
            }
          } break;
          case xenos::ColorRenderTargetFormat::k_32_FLOAT: {
            color_clear_value[0] = float(uint32_t(clear_value));

            if (uint64_t(color_clear_value[0]) != uint32_t(clear_value)) {
              clear_via_drawing = true;
            }
          } break;
          case xenos::ColorRenderTargetFormat::k_32_32_FLOAT: {
            color_clear_value[0] = float(uint32_t(clear_value));
            color_clear_value[1] = float(uint32_t(clear_value >> 32));

            if (uint64_t(color_clear_value[0]) != uint32_t(clear_value) ||
                uint64_t(color_clear_value[1]) != uint32_t(clear_value >> 32)) {
              clear_via_drawing = true;
            }
          } break;
        }
        command_processor_.PushTransitionBarrier(
            dest_d3d12_rt.resource(),
            dest_d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_RENDER_TARGET),
            D3D12_RESOURCE_STATE_RENDER_TARGET);
        if (clear_via_drawing) {
          D3D12_CPU_DESCRIPTOR_HANDLE clear_rtv_handle =
              dest_d3d12_rt.descriptor_load_separate().IsValid()
                  ? dest_d3d12_rt.descriptor_load_separate().GetHandle()
                  : dest_d3d12_rt.descriptor_draw().GetHandle();
          command_list.D3DOMSetRenderTargets(1, &clear_rtv_handle, FALSE, nullptr);
          are_current_command_list_render_targets_valid_ = true;
          D3D12_VIEWPORT clear_viewport;
          clear_viewport.TopLeftX = float(clear_rect.left);
          clear_viewport.TopLeftY = float(clear_rect.top);
          clear_viewport.Width = float(clear_rect.right - clear_rect.left);
          clear_viewport.Height = float(clear_rect.bottom - clear_rect.top);
          clear_viewport.MinDepth = 0.0f;
          clear_viewport.MaxDepth = 1.0f;
          command_processor_.SetViewport(clear_viewport);
          command_processor_.SetScissorRect(clear_rect);
          command_processor_.SetExternalGraphicsRootSignature(uint32_rtv_clear_root_signature_);
          uint32_t clear_via_drawing_value[2] = {uint32_t(clear_value),
                                                 uint32_t(clear_value >> 32)};
          command_list.D3DSetGraphicsRoot32BitConstants(0, 2, clear_via_drawing_value, 0);
          command_processor_.SetExternalPipeline(uint32_rtv_clear_pipelines_[size_t(
              dest_rt_key.GetColorFormat() ==
              xenos::ColorRenderTargetFormat::k_32_32_FLOAT)][size_t(dest_rt_key.msaa_samples)]);
          command_processor_.SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
          command_list.D3DDrawInstanced(3, 1, 0, 0);
        } else {
          command_processor_.SubmitBarriers();
          command_list.D3DClearRenderTargetView(
              dest_d3d12_rt.descriptor_load_separate().IsValid()
                  ? dest_d3d12_rt.descriptor_load_separate().GetHandle()
                  : dest_d3d12_rt.descriptor_draw().GetHandle(),
              color_clear_value, 1, &clear_rect);
        }
      }
    }
  }
}

void D3D12RenderTargetCache::SetCommandListRenderTargets(
    RenderTarget* const* depth_and_color_render_targets) {
  assert_true(GetPath() == Path::kHostRenderTargets);

  if (depth_and_color_render_targets[0]) {
    auto& d3d12_rt = *static_cast<D3D12RenderTarget*>(depth_and_color_render_targets[0]);
    command_processor_.PushTransitionBarrier(
        d3d12_rt.resource(), d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_DEPTH_WRITE),
        D3D12_RESOURCE_STATE_DEPTH_WRITE);
  }
  for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
    RenderTarget* render_target = depth_and_color_render_targets[1 + i];
    if (!render_target) {
      continue;
    }
    auto& d3d12_rt = *static_cast<D3D12RenderTarget*>(render_target);
    command_processor_.PushTransitionBarrier(
        d3d12_rt.resource(), d3d12_rt.SetResourceState(D3D12_RESOURCE_STATE_RENDER_TARGET),
        D3D12_RESOURCE_STATE_RENDER_TARGET);
  }

  if (are_current_command_list_render_targets_valid_ &&
      std::memcmp(current_command_list_render_targets_, depth_and_color_render_targets,
                  sizeof(current_command_list_render_targets_))) {
    are_current_command_list_render_targets_valid_ = false;
  }
  if (!are_current_command_list_render_targets_valid_) {
    std::memcpy(current_command_list_render_targets_, depth_and_color_render_targets,
                sizeof(current_command_list_render_targets_));
    D3D12_CPU_DESCRIPTOR_HANDLE dsv_handle;
    if (depth_and_color_render_targets[0]) {
      dsv_handle = static_cast<const D3D12RenderTarget*>(depth_and_color_render_targets[0])
                       ->descriptor_draw()
                       .GetHandle();
    }
    D3D12_CPU_DESCRIPTOR_HANDLE rtv_handles[xenos::kMaxColorRenderTargets];
    uint32_t rtv_count = 0;
    for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
      const RenderTarget* render_target = depth_and_color_render_targets[1 + i];
      if (!render_target) {
        continue;
      }

      while (rtv_count < i) {
        rtv_handles[rtv_count++] = render_target->key().msaa_samples != xenos::MsaaSamples::k1X
                                       ? null_rtv_descriptor_ms_.GetHandle()
                                       : null_rtv_descriptor_ss_.GetHandle();
      }
      auto& d3d12_rt = *static_cast<const D3D12RenderTarget*>(render_target);
      rtv_handles[rtv_count++] = d3d12_rt.descriptor_draw().GetHandle();
    }
    command_processor_.GetDeferredCommandList().D3DOMSetRenderTargets(
        rtv_count, rtv_handles, FALSE, depth_and_color_render_targets[0] ? &dsv_handle : nullptr);
    are_current_command_list_render_targets_valid_ = true;
  }
}

}

#pragma once
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

#include <cmath>
#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#include <fmt/format.h>

#include <rex/assert.h>
#include <rex/graphics/pipeline/render_target/scaling_list.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/util/draw_extent_estimator.h>
#include <rex/graphics/xenos.h>

namespace rex::graphics {

class RenderTargetCache {
 public:
  enum class Path {

    kHostRenderTargets,

    kPixelShaderInterlock,
  };

  enum : uint32_t {
    kPSIColorFormatFlag_64bpp_Shift = xenos::kColorRenderTargetFormatBits,

    kPSIColorFormatFlag_FixedPointColor_Shift,
    kPSIColorFormatFlag_FixedPointAlpha_Shift,

    kPSIColorFormatFlag_64bpp = uint32_t(1) << kPSIColorFormatFlag_64bpp_Shift,
    kPSIColorFormatFlag_FixedPointColor = uint32_t(1) << kPSIColorFormatFlag_FixedPointColor_Shift,
    kPSIColorFormatFlag_FixedPointAlpha = uint32_t(1) << kPSIColorFormatFlag_FixedPointAlpha_Shift,
  };

  static constexpr uint32_t AddPSIColorFormatFlags(xenos::ColorRenderTargetFormat format) {
    uint32_t format_flags = uint32_t(format);
    if (format == xenos::ColorRenderTargetFormat::k_16_16_16_16 ||
        format == xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT ||
        format == xenos::ColorRenderTargetFormat::k_32_32_FLOAT) {
      format_flags |= kPSIColorFormatFlag_64bpp;
    }
    if (format == xenos::ColorRenderTargetFormat::k_8_8_8_8 ||
        format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA ||
        format == xenos::ColorRenderTargetFormat::k_2_10_10_10 ||
        format == xenos::ColorRenderTargetFormat::k_16_16 ||
        format == xenos::ColorRenderTargetFormat::k_16_16_16_16 ||
        format == xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10) {
      format_flags |= kPSIColorFormatFlag_FixedPointColor | kPSIColorFormatFlag_FixedPointAlpha;
    } else if (format == xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT ||
               format == xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16) {
      format_flags |= kPSIColorFormatFlag_FixedPointAlpha;
    }
    return format_flags;
  }

  static void GetPSIColorFormatInfo(xenos::ColorRenderTargetFormat format, uint32_t write_mask,
                                    float& clamp_rgb_low, float& clamp_alpha_low,
                                    float& clamp_rgb_high, float& clamp_alpha_high,
                                    uint32_t& keep_mask_low, uint32_t& keep_mask_high);

  static bool ColorOverlapsDepthStencil(xenos::ColorRenderTargetFormat color_format,
                                        uint32_t color_keep_mask_low, uint32_t color_keep_mask_high,
                                        reg::RB_DEPTHCONTROL normalized_depth_control);

  virtual ~RenderTargetCache();

  virtual Path GetPath() const = 0;

  uint32_t draw_resolution_scale_x() const { return draw_resolution_scale_x_; }
  uint32_t draw_resolution_scale_y() const { return draw_resolution_scale_y_; }

  bool IsResolveNative(const draw_util::ResolveInfo& resolve_info);

  bool IsNativeResolveAveraged(const draw_util::ResolveInfo& resolve_info);

  bool IsDrawResolutionScaled() const {
    return draw_resolution_scale_x() > 1 || draw_resolution_scale_y() > 1;
  }

  virtual void ClearCache();

  virtual void BeginFrame();

  virtual bool Update(bool is_rasterization_done, reg::RB_DEPTHCONTROL normalized_depth_control,
                      uint32_t normalized_color_mask, const Shader& vertex_shader);

  uint32_t GetLastUpdateBoundRenderTargets(uint32_t* depth_and_color_formats_out = nullptr) const;

  static constexpr uint64_t kDrawTargetRecurringFrames = 4;
  bool TrackLastUpdateDrawTarget(uint64_t frame);

  static constexpr uint32_t kDrawTargetSmallPitchTiles = 2;
  bool IsLastUpdateDrawTargetSmall() const {
    return !last_update_draw_target_.IsEmpty() &&
           last_update_draw_target_.pitch_tiles_at_32bpp <= kDrawTargetSmallPitchTiles;
  }
  std::string GetLastUpdateDrawTargetName() const;

 protected:
  RenderTargetCache(const RegisterFile& register_file, const memory::Memory& memory,
                    uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y)
      : register_file_(register_file),
        draw_extent_estimator_(register_file, memory),
        draw_resolution_scale_x_(draw_resolution_scale_x),
        draw_resolution_scale_y_(draw_resolution_scale_y) {
    assert_not_zero(draw_resolution_scale_x);
    assert_not_zero(draw_resolution_scale_y);
  }

  const RegisterFile& register_file() const { return register_file_; }

  virtual bool IsGammaFormatHostStorageSeparate() const = 0;

  void InitializeCommon();

  void DestroyAllRenderTargets(bool shutting_down);

  void ShutdownCommon();

  union RenderTargetKey {
    uint32_t key;
    struct {
      uint32_t base_tiles : xenos::kEdramBaseTilesBits;

      uint32_t pitch_tiles_at_32bpp : 8;
      xenos::MsaaSamples msaa_samples : xenos::kMsaaSamplesBits;
      uint32_t is_depth : 1;

      uint32_t resource_format : xenos::kRenderTargetFormatBits;
    };

    RenderTargetKey() : key(0) { static_assert_size(*this, sizeof(key)); }

    struct Hasher {
      size_t operator()(const RenderTargetKey& render_target_key) const {
        return std::hash<uint32_t>{}(render_target_key.key);
      }
    };
    bool operator==(const RenderTargetKey& other_key) const { return key == other_key.key; }
    bool operator!=(const RenderTargetKey& other_key) const { return !(*this == other_key); }

    bool IsEmpty() const { return key == 0; }

    xenos::ColorRenderTargetFormat GetColorFormat() const {
      assert_false(is_depth);
      return xenos::ColorRenderTargetFormat(resource_format);
    }
    xenos::DepthRenderTargetFormat GetDepthFormat() const {
      assert_true(is_depth);
      return xenos::DepthRenderTargetFormat(resource_format);
    }
    bool Is64bpp() const {
      if (is_depth) {
        return false;
      }
      return xenos::IsColorRenderTargetFormat64bpp(GetColorFormat());
    }
    const char* GetFormatName() const {
      return is_depth ? xenos::GetDepthRenderTargetFormatName(GetDepthFormat())
                      : xenos::GetColorRenderTargetFormatName(GetColorFormat());
    }

    uint32_t GetPitchTiles() const { return pitch_tiles_at_32bpp << uint32_t(Is64bpp()); }
    static constexpr uint32_t GetWidth(uint32_t pitch_tiles_at_32bpp,
                                       xenos::MsaaSamples msaa_samples) {
      return pitch_tiles_at_32bpp *
             (xenos::kEdramTileWidthSamples >> uint32_t(msaa_samples >= xenos::MsaaSamples::k4X));
    }
    uint32_t GetWidth() const { return GetWidth(pitch_tiles_at_32bpp, msaa_samples); }

    std::string GetDebugName() const {
      return fmt::format("RT @ {}t, <{}t>, {}xMSAA, {}", base_tiles, GetPitchTiles(),
                         uint32_t(1) << uint32_t(msaa_samples), GetFormatName());
    }
  };

  class RenderTarget {
   public:
    virtual ~RenderTarget() = default;

    RenderTarget(const RenderTarget& render_target) = delete;
    RenderTarget& operator=(const RenderTarget& render_target) = delete;
    RenderTarget(RenderTarget&& render_target) = delete;
    RenderTarget& operator=(RenderTarget&& render_target) = delete;
    RenderTargetKey key() const { return key_; }

   protected:
    RenderTarget(RenderTargetKey key) : key_(key) {}

   private:
    RenderTargetKey key_;
  };

  struct Transfer {
    uint32_t start_tiles;
    uint32_t end_tiles;
    RenderTarget* source;
    RenderTarget* host_depth_source;
    Transfer(uint32_t start_tiles, uint32_t end_tiles, RenderTarget* source,
             RenderTarget* host_depth_source)
        : start_tiles(start_tiles),
          end_tiles(end_tiles),
          source(source),
          host_depth_source(host_depth_source) {
      assert_true(start_tiles < end_tiles);
    }
    struct Rectangle {
      uint32_t x_pixels;
      uint32_t y_pixels;
      uint32_t width_pixels;
      uint32_t height_pixels;
    };
    static constexpr uint32_t kMaxRectanglesWithoutCutout = 3;
    static constexpr uint32_t kMaxCutoutBorderRectangles = 4;
    static constexpr uint32_t kMaxRectanglesWithCutout =
        kMaxRectanglesWithoutCutout * kMaxCutoutBorderRectangles;

    static uint32_t GetRangeRectangles(uint32_t start_tiles, uint32_t end_tiles,
                                       uint32_t base_tiles, uint32_t pitch_tiles,
                                       xenos::MsaaSamples msaa_samples, bool is_64bpp,
                                       Rectangle* rectangles_out,
                                       const Rectangle* cutout = nullptr);
    uint32_t GetRectangles(uint32_t base_tiles, uint32_t pitch_tiles,
                           xenos::MsaaSamples msaa_samples, bool is_64bpp,
                           Rectangle* rectangles_out, const Rectangle* cutout = nullptr) const {
      return GetRangeRectangles(start_tiles, end_tiles, base_tiles, pitch_tiles, msaa_samples,
                                is_64bpp, rectangles_out, cutout);
    }
    bool AreSourcesSame(const Transfer& other_transfer) const {
      return source == other_transfer.source &&
             host_depth_source == other_transfer.host_depth_source;
    }

   private:
    static uint32_t AddRectangle(const Rectangle& rectangle, Rectangle* rectangles_out,
                                 const Rectangle* cutout = nullptr);
  };

  union HostDepthStoreRectangleConstant {
    uint32_t constant;
    struct {
      uint32_t x_pixels_div_8 : xenos::kResolveSizeBits - 1 - xenos::kResolveAlignmentPixelsLog2;
      uint32_t y_pixels_div_8 : xenos::kResolveSizeBits - 1 - xenos::kResolveAlignmentPixelsLog2;
      uint32_t width_pixels_div_8_minus_1 : xenos::kResolveSizeBits - 1 -
                                            xenos::kResolveAlignmentPixelsLog2;
    };
    HostDepthStoreRectangleConstant() : constant(0) { static_assert_size(*this, sizeof(constant)); }
  };

  union HostDepthStoreRenderTargetConstant {
    uint32_t constant;
    struct {
      uint32_t pitch_tiles : xenos::kEdramPitchTilesBits;
      uint32_t resolution_scale_x : 3;
      uint32_t resolution_scale_y : 3;

      uint32_t msaa_2x_supported : 1;
    };
    HostDepthStoreRenderTargetConstant() : constant(0) {
      static_assert_size(*this, sizeof(constant));
    }
  };

  struct HostDepthStoreConstants {
    HostDepthStoreRectangleConstant rectangle;
    HostDepthStoreRenderTargetConstant render_target;
  };

  struct ResolveCopyDumpRectangle {
    RenderTarget* render_target;

    uint32_t row_first;
    uint32_t rows;
    uint32_t row_first_start;
    uint32_t row_last_end;
    ResolveCopyDumpRectangle(RenderTarget* render_target, uint32_t row_first, uint32_t rows,
                             uint32_t row_first_start, uint32_t row_last_end)
        : render_target(render_target),
          row_first(row_first),
          rows(rows),
          row_first_start(row_first_start),
          row_last_end(row_last_end) {}
    struct Dispatch {
      uint32_t offset;
      uint32_t width_tiles;
      uint32_t height_tiles;
    };
    static constexpr uint32_t kMaxDispatches = 3;
    uint32_t GetDispatches(uint32_t pitch_tiles, uint32_t row_length_used,
                           Dispatch* dispatches_out) const {
      if (!rows) {
        return 0;
      }

      uint32_t dispatch_count = 0;
      if (rows == 1 || row_first_start) {
        Dispatch& dispatch_first = dispatches_out[dispatch_count++];
        dispatch_first.offset = row_first * pitch_tiles + row_first_start;
        dispatch_first.width_tiles = (rows == 1 ? row_last_end : row_length_used) - row_first_start;
        dispatch_first.height_tiles = 1;
        if (rows == 1) {
          return dispatch_count;
        }
      }
      uint32_t mid_row_first = row_first + 1;
      uint32_t mid_rows = rows - 2;
      if (!row_first_start) {
        --mid_row_first;
        ++mid_rows;
      }
      if (row_last_end == row_length_used) {
        ++mid_rows;
      }
      if (mid_rows) {
        Dispatch& dispatch_mid = dispatches_out[dispatch_count++];
        dispatch_mid.offset = mid_row_first * pitch_tiles;
        dispatch_mid.width_tiles = row_length_used;
        dispatch_mid.height_tiles = mid_rows;
      }
      if (row_last_end != row_length_used) {
        Dispatch& dispatch_last = dispatches_out[dispatch_count++];
        dispatch_last.offset = (row_first + rows - 1) * pitch_tiles;
        dispatch_last.width_tiles = row_last_end;
        dispatch_last.height_tiles = 1;
      }
      return dispatch_count;
    }
  };

  struct ResolveCopyDispatch {
    uint32_t rectangle_index;
    ResolveCopyDumpRectangle::Dispatch dispatch;
    ResolveCopyDispatch(uint32_t rectangle_index,
                        const ResolveCopyDumpRectangle::Dispatch& dispatch)
        : rectangle_index(rectangle_index), dispatch(dispatch) {}
  };

  virtual uint32_t GetMaxRenderTargetWidth() const = 0;
  virtual uint32_t GetMaxRenderTargetHeight() const = 0;

  uint32_t GetRenderTargetHeight(uint32_t pitch_tiles_at_32bpp,
                                 xenos::MsaaSamples msaa_samples) const;

  virtual RenderTarget* CreateRenderTarget(RenderTargetKey key) = 0;

  virtual bool IsHostDepthEncodingDifferent(xenos::DepthRenderTargetFormat format) const = 0;

  void ResetAccumulatedRenderTargets() { are_accumulated_render_targets_valid_ = false; }
  RenderTarget* const* last_update_accumulated_render_targets() const {
    assert_true(GetPath() == Path::kHostRenderTargets);
    return last_update_accumulated_render_targets_;
  }
  const std::vector<Transfer>* last_update_transfers() const {
    assert_true(GetPath() == Path::kHostRenderTargets);
    return last_update_transfers_;
  }

  HostDepthStoreRenderTargetConstant GetHostDepthStoreRenderTargetConstant(
      uint32_t pitch_tiles, bool msaa_2x_supported) const {
    HostDepthStoreRenderTargetConstant constant;
    constant.pitch_tiles = pitch_tiles;

    assert_true(draw_resolution_scale_x() <= 7);
    assert_true(draw_resolution_scale_y() <= 7);
    constant.resolution_scale_x = draw_resolution_scale_x();
    constant.resolution_scale_y = draw_resolution_scale_y();
    constant.msaa_2x_supported = uint32_t(msaa_2x_supported);
    return constant;
  }
  void GetHostDepthStoreRectangleInfo(const Transfer::Rectangle& transfer_rectangle,
                                      xenos::MsaaSamples msaa_samples,
                                      HostDepthStoreRectangleConstant& rectangle_constant_out,
                                      uint32_t& group_count_x_out,
                                      uint32_t& group_count_y_out) const;

  void GetResolveCopyRectanglesToDump(uint32_t base, uint32_t row_length, uint32_t rows,
                                      uint32_t pitch,
                                      std::vector<ResolveCopyDumpRectangle>& rectangles_out) const;
  void GetResolveCopyDispatchesToDump(uint32_t base, uint32_t row_length, uint32_t rows,
                                      uint32_t pitch,
                                      std::vector<ResolveCopyDumpRectangle>& rectangles_out,
                                      std::vector<ResolveCopyDispatch>& dispatches_out) const;

  bool PrepareHostRenderTargetsResolveClear(const draw_util::ResolveInfo& resolve_info,
                                            Transfer::Rectangle& clear_rectangle_out,
                                            RenderTarget*& depth_render_target_out,
                                            std::vector<Transfer>& depth_transfers_out,
                                            RenderTarget*& color_render_target_out,
                                            std::vector<Transfer>& color_transfers_out);

  virtual void RequestPixelShaderInterlockBarrier() {}

  void PixelShaderInterlockFullEdramBarrierPlaced();

 private:
  const RegisterFile& register_file_;
  uint32_t draw_resolution_scale_x_;
  uint32_t draw_resolution_scale_y_;

  DrawExtentEstimator draw_extent_estimator_;

  ScalingResolutionList scaling_list_;
  std::set<uint64_t> logged_render_target_sizes_;

  struct OwnershipRange {
    uint32_t end_tiles;

    RenderTargetKey render_target;

    RenderTargetKey depth_bits_target;

    RenderTargetKey host_depth_render_target_unorm24;
    RenderTargetKey host_depth_render_target_float24;
    OwnershipRange(uint32_t end_tiles, RenderTargetKey render_target,
                   RenderTargetKey host_depth_render_target_unorm24,
                   RenderTargetKey host_depth_render_target_float24)
        : end_tiles(end_tiles),
          render_target(render_target),
          depth_bits_target(render_target),
          host_depth_render_target_unorm24(host_depth_render_target_unorm24),
          host_depth_render_target_float24(host_depth_render_target_float24) {}
    const RenderTargetKey& GetHostDepthRenderTarget(
        xenos::DepthRenderTargetFormat resource_format) const {
      assert_true(resource_format == xenos::DepthRenderTargetFormat::kD24S8 ||
                      resource_format == xenos::DepthRenderTargetFormat::kD24FS8,
                  "Illegal resource format");
      return resource_format == xenos::DepthRenderTargetFormat::kD24S8
                 ? host_depth_render_target_unorm24
                 : host_depth_render_target_float24;
    }
    RenderTargetKey& GetHostDepthRenderTarget(xenos::DepthRenderTargetFormat resource_format) {
      return const_cast<RenderTargetKey&>(
          const_cast<const OwnershipRange*>(this)->GetHostDepthRenderTarget(resource_format));
    }
    bool IsOwnedBy(RenderTargetKey key, bool host_depth_encoding_different) const {
      if (render_target != key) {
        return false;
      }
      if (host_depth_encoding_different && !key.is_depth &&
          GetHostDepthRenderTarget(key.GetDepthFormat()) != key) {
        return false;
      }
      return true;
    }
    bool AreOwnersSame(const OwnershipRange& other_range) const {
      return render_target == other_range.render_target &&
             depth_bits_target == other_range.depth_bits_target &&
             host_depth_render_target_unorm24 == other_range.host_depth_render_target_unorm24 &&
             host_depth_render_target_float24 == other_range.host_depth_render_target_float24;
    }
  };

  xenos::ColorRenderTargetFormat GetColorResourceFormat(
      xenos::ColorRenderTargetFormat format) const {
    if (format == xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA &&
        !IsGammaFormatHostStorageSeparate()) {
      return xenos::ColorRenderTargetFormat::k_8_8_8_8;
    }
    return xenos::GetStorageColorFormat(format);
  }

  RenderTarget* GetOrCreateRenderTarget(RenderTargetKey key);

  bool WouldOwnershipChangeRequireTransfers(RenderTargetKey dest,
                                            uint32_t start_tiles_base_relative,
                                            uint32_t length_tiles) const;
  bool IsHostDepthCurrent(RenderTargetKey depth_target, uint32_t start_tiles_base_relative,
                          uint32_t length_tiles) const;

  void ChangeOwnership(RenderTargetKey dest, uint32_t start_tiles_base_relative,
                       uint32_t length_tiles, std::vector<Transfer>* transfers_append_out,
                       const Transfer::Rectangle* resolve_clear_cutout = nullptr,
                       bool keep_depth_bits = false);

  std::unordered_map<RenderTargetKey, RenderTarget*, RenderTargetKey::Hasher> render_targets_;

  std::map<uint32_t, OwnershipRange> ownership_ranges_;

  RenderTarget* last_update_used_render_targets_[1 + xenos::kMaxColorRenderTargets];

  RenderTarget* last_update_accumulated_render_targets_[1 + xenos::kMaxColorRenderTargets];

  bool are_accumulated_render_targets_valid_ = false;

  RenderTargetKey last_update_draw_target_;
  std::unordered_map<RenderTargetKey, std::pair<uint64_t, uint64_t>, RenderTargetKey::Hasher>
      draw_target_last_frames_;

  std::vector<Transfer> last_update_transfers_[1 + xenos::kMaxColorRenderTargets];
};

}

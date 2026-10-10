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

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iterator>
#include <tuple>
#include <unordered_set>
#include <utility>

#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/util/draw.h>
#include <rex/graphics/xenos.h>
#include <rex/logging.h>
#include <rex/math.h>

REXCVAR_DEFINE_STRING(resolution_scale_targets, "", "GPU",
                      "Resolve sizes kept upscaled, as WxH with 0 for any (\"720x0 0x240\"); "
                      "other resolves are written at the guest's size. Empty: all upscaled; none: "
                      "none "
                      "(ADR-012)")
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);
REXCVAR_DEFINE_BOOL(resolve_downscale_average, false, "GPU",
                    "Resolves written at the guest's size average each pixel's upscaled samples "
                    "(supersampling) instead of taking the center one; formats of 8-bit "
                    "channels (ADR-012)");
REXCVAR_DEFINE_BOOL(log_resolution_scale_targets, false, "GPU",
                    "Log each resolved size once, with whether resolution_scale_targets "
                    "keeps it upscaled");
REXCVAR_DEFINE_BOOL(mrt_edram_used_range_clamp_to_min, true, "GPU",
                    "Clamp MRT EDRAM used range to minimum");

REXCVAR_DEFINE_BOOL(execute_unclipped_draw_vs_on_cpu_for_psi_render_backend, true, "GPU",
                    "Execute unclipped draw VS on CPU for PSI render backend");

REXCVAR_DEFINE_BOOL(snorm16_render_target_full_range, true, "GPU",
                    "Use full range for SNORM16 render targets");

REXCVAR_DEFINE_BOOL(direct_host_resolve, true, "GPU",
                    "Resolve from host render targets directly to shared memory when possible")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_BOOL(aliased_depth_read_only, true, "GPU",
                    "Matches interlock behavior by handling disjoint color and depth aliases for "
                    "host render targets, keeping read-only depth bound when color writes only the "
                    "unused stencil bits. May slightly increase overhead from keeping both host "
                    "targets live and bound.");

namespace rex::graphics {

void RenderTargetCache::GetPSIColorFormatInfo(xenos::ColorRenderTargetFormat format,
                                              uint32_t write_mask, float& clamp_rgb_low,
                                              float& clamp_alpha_low, float& clamp_rgb_high,
                                              float& clamp_alpha_high, uint32_t& keep_mask_low,
                                              uint32_t& keep_mask_high) {
  keep_mask_low = keep_mask_high = 0;
  switch (format) {
    case xenos::ColorRenderTargetFormat::k_8_8_8_8:
    case xenos::ColorRenderTargetFormat::k_8_8_8_8_GAMMA: {
      clamp_rgb_low = clamp_alpha_low = 0.0f;
      clamp_rgb_high = clamp_alpha_high = 1.0f;
      for (uint32_t i = 0; i < 4; ++i) {
        if (!(write_mask & (1 << i))) {
          keep_mask_low |= uint32_t(0xFF) << (i * 8);
        }
      }
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10: {
      clamp_rgb_low = clamp_alpha_low = 0.0f;
      clamp_rgb_high = clamp_alpha_high = 1.0f;
      for (uint32_t i = 0; i < 3; ++i) {
        if (!(write_mask & (1 << i))) {
          keep_mask_low |= uint32_t(0x3FF) << (i * 10);
        }
      }
      if (!(write_mask & 0b1000)) {
        keep_mask_low |= uint32_t(3) << 30;
      }
    } break;
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
    case xenos::ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16: {
      clamp_rgb_low = clamp_alpha_low = 0.0f;
      clamp_rgb_high = 31.875f;
      clamp_alpha_high = 1.0f;
      for (uint32_t i = 0; i < 3; ++i) {
        if (!(write_mask & (1 << i))) {
          keep_mask_low |= uint32_t(0x3FF) << (i * 10);
        }
      }
      if (!(write_mask & 0b1000)) {
        keep_mask_low |= uint32_t(3) << 30;
      }
    } break;
    case xenos::ColorRenderTargetFormat::k_16_16:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16:

      clamp_rgb_low = clamp_alpha_low = -32.0f;
      clamp_rgb_high = clamp_alpha_high = 32.0f;
      if (!(write_mask & 0b0001)) {
        keep_mask_low |= 0xFFFFu;
      }
      if (!(write_mask & 0b0010)) {
        keep_mask_low |= 0xFFFF0000u;
      }
      if (format == xenos::ColorRenderTargetFormat::k_16_16_16_16) {
        if (!(write_mask & 0b0100)) {
          keep_mask_high |= 0xFFFFu;
        }
        if (!(write_mask & 0b1000)) {
          keep_mask_high |= 0xFFFF0000u;
        }
      } else {
        write_mask &= 0b0011;
      }
      break;
    case xenos::ColorRenderTargetFormat::k_16_16_FLOAT:
    case xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT:

      clamp_rgb_low = clamp_alpha_low = -65504.0f;
      clamp_rgb_high = clamp_alpha_high = 65504.0f;
      if (!(write_mask & 0b0001)) {
        keep_mask_low |= 0xFFFFu;
      }
      if (!(write_mask & 0b0010)) {
        keep_mask_low |= 0xFFFF0000u;
      }
      if (format == xenos::ColorRenderTargetFormat::k_16_16_16_16_FLOAT) {
        if (!(write_mask & 0b0100)) {
          keep_mask_high |= 0xFFFFu;
        }
        if (!(write_mask & 0b1000)) {
          keep_mask_high |= 0xFFFF0000u;
        }
      } else {
        write_mask &= 0b0011;
      }
      break;
    case xenos::ColorRenderTargetFormat::k_32_FLOAT:

      clamp_rgb_low = clamp_alpha_low = clamp_rgb_high = clamp_alpha_high = std::nanf("");
      write_mask &= 0b0001;
      if (!(write_mask & 0b0001)) {
        keep_mask_low = ~uint32_t(0);
      }
      break;
    case xenos::ColorRenderTargetFormat::k_32_32_FLOAT:

      clamp_rgb_low = clamp_alpha_low = clamp_rgb_high = clamp_alpha_high = std::nanf("");
      write_mask &= 0b0011;
      if (!(write_mask & 0b0001)) {
        keep_mask_low = ~uint32_t(0);
      }
      if (!(write_mask & 0b0010)) {
        keep_mask_high = ~uint32_t(0);
      }
      break;
    default:
      assert_unhandled_case(format);

      write_mask = 0;
      break;
  }

  if (!write_mask) {
    keep_mask_low = keep_mask_high = ~uint32_t(0);
  }
}

bool RenderTargetCache::ColorOverlapsDepthStencil(xenos::ColorRenderTargetFormat color_format,
                                                  uint32_t color_keep_mask_low,
                                                  uint32_t color_keep_mask_high,
                                                  reg::RB_DEPTHCONTROL normalized_depth_control) {
  uint32_t depth_stencil_used_bits = 0;
  if (normalized_depth_control.z_enable) {
    depth_stencil_used_bits |= 0xFFFFFF00u;
  }
  if (normalized_depth_control.stencil_enable) {
    depth_stencil_used_bits |= 0x000000FFu;
  }
  uint32_t color_written_bits = ~color_keep_mask_low;
  if (xenos::IsColorRenderTargetFormat64bpp(color_format)) {
    color_written_bits |= ~color_keep_mask_high;
  }
  return (color_written_bits & depth_stencil_used_bits) != 0;
}

uint32_t RenderTargetCache::Transfer::GetRangeRectangles(uint32_t start_tiles, uint32_t end_tiles,
                                                         uint32_t base_tiles, uint32_t pitch_tiles,
                                                         xenos::MsaaSamples msaa_samples,
                                                         bool is_64bpp, Rectangle* rectangles_out,
                                                         const Rectangle* cutout) {
  assert_true(start_tiles < xenos::kEdramTileCount);
  assert_true(end_tiles <= xenos::kEdramTileCount);
  assert_true(start_tiles <= end_tiles);

  assert_true(start_tiles >= base_tiles || end_tiles <= base_tiles);
  assert_not_zero(pitch_tiles);
  if (start_tiles == end_tiles) {
    return 0;
  }
  uint32_t tile_width = xenos::kEdramTileWidthSamples >>
                        (uint32_t(msaa_samples >= xenos::MsaaSamples::k4X) + uint32_t(is_64bpp));
  uint32_t tile_height =
      xenos::kEdramTileHeightSamples >> uint32_t(msaa_samples >= xenos::MsaaSamples::k2X);

  uint32_t rectangle_count = 0;

  uint32_t local_offset = start_tiles < base_tiles ? xenos::kEdramTileCount : 0;
  uint32_t local_start = local_offset + start_tiles - base_tiles;
  uint32_t local_end = local_offset + end_tiles - base_tiles;

  uint32_t rows_start = local_start / pitch_tiles;

  uint32_t rows_end = (local_end + (pitch_tiles - 1)) / pitch_tiles;
  uint32_t row_first_start = local_start - rows_start * pitch_tiles;
  uint32_t row_last_end = pitch_tiles - (rows_end * pitch_tiles - local_end);
  uint32_t rows = rows_end - rows_start;
  if (rows == 1 || row_first_start) {
    Rectangle rectangle_first;
    rectangle_first.x_pixels = row_first_start * tile_width;
    rectangle_first.y_pixels = rows_start * tile_height;
    rectangle_first.width_pixels =
        ((rows == 1 ? row_last_end : pitch_tiles) - row_first_start) * tile_width;
    rectangle_first.height_pixels = tile_height;
    rectangle_count += AddRectangle(
        rectangle_first, rectangles_out ? rectangles_out + rectangle_count : nullptr, cutout);
    if (rows == 1) {
      return rectangle_count;
    }
  }
  uint32_t mid_rows_start = rows_start + 1;
  uint32_t mid_rows = rows - 2;
  if (!row_first_start) {
    --mid_rows_start;
    ++mid_rows;
  }
  if (row_last_end == pitch_tiles) {
    ++mid_rows;
  }
  if (mid_rows) {
    Rectangle rectangle_mid;
    rectangle_mid.x_pixels = 0;
    rectangle_mid.y_pixels = mid_rows_start * tile_height;
    rectangle_mid.width_pixels = pitch_tiles * tile_width;
    rectangle_mid.height_pixels = mid_rows * tile_height;
    rectangle_count += AddRectangle(
        rectangle_mid, rectangles_out ? rectangles_out + rectangle_count : nullptr, cutout);
  }
  if (row_last_end != pitch_tiles) {
    Rectangle rectangle_last;
    rectangle_last.x_pixels = 0;
    rectangle_last.y_pixels = (rows_end - 1) * tile_height;
    rectangle_last.width_pixels = row_last_end * tile_width;
    rectangle_last.height_pixels = tile_height;
    rectangle_count += AddRectangle(
        rectangle_last, rectangles_out ? rectangles_out + rectangle_count : nullptr, cutout);
  }
  assert_true(rectangle_count <= (cutout ? kMaxRectanglesWithCutout : kMaxRectanglesWithoutCutout));
  return rectangle_count;
}

uint32_t RenderTargetCache::Transfer::AddRectangle(const Rectangle& rectangle,
                                                   Rectangle* rectangles_out,
                                                   const Rectangle* cutout) {
  uint32_t rectangle_right = rectangle.x_pixels + rectangle.width_pixels;
  uint32_t rectangle_bottom = rectangle.y_pixels + rectangle.height_pixels;

  if (!cutout || !cutout->width_pixels || !cutout->height_pixels ||
      cutout->x_pixels >= rectangle_right ||
      cutout->x_pixels + cutout->width_pixels <= rectangle.x_pixels ||
      cutout->y_pixels >= rectangle_bottom ||
      cutout->y_pixels + cutout->height_pixels <= rectangle.y_pixels) {
    if (rectangles_out) {
      rectangles_out[0] = rectangle;
    }
    return 1;
  }
  uint32_t rectangle_count = 0;
  uint32_t cutout_right = cutout->x_pixels + cutout->width_pixels;
  uint32_t cutout_bottom = cutout->y_pixels + cutout->height_pixels;

  if (cutout->y_pixels > rectangle.y_pixels) {
    assert_true(cutout->y_pixels < rectangle_bottom);
    if (rectangles_out) {
      Rectangle& rectangle_upper = rectangles_out[rectangle_count];
      rectangle_upper.x_pixels = rectangle.x_pixels;
      rectangle_upper.y_pixels = rectangle.y_pixels;
      rectangle_upper.width_pixels = rectangle.width_pixels;

      rectangle_upper.height_pixels = cutout->y_pixels - rectangle.y_pixels;
    }
    ++rectangle_count;
  }

  uint32_t middle_top = std::max(cutout->y_pixels, rectangle.y_pixels);
  uint32_t middle_height = std::min(cutout_bottom, rectangle_bottom) - middle_top;

  if (cutout->x_pixels > rectangle.x_pixels) {
    assert_true(cutout->x_pixels < rectangle_right);
    if (rectangles_out) {
      Rectangle& rectangle_middle_left = rectangles_out[rectangle_count];
      rectangle_middle_left.x_pixels = rectangle.x_pixels;
      rectangle_middle_left.y_pixels = middle_top;
      rectangle_middle_left.width_pixels = cutout->x_pixels - rectangle.x_pixels;
      rectangle_middle_left.height_pixels = middle_height;
    }
    ++rectangle_count;
  }

  if (cutout_right < rectangle_right) {
    assert_true(cutout_right > rectangle.x_pixels);
    if (rectangles_out) {
      Rectangle& rectangle_middle_right = rectangles_out[rectangle_count];
      rectangle_middle_right.x_pixels = cutout_right;
      rectangle_middle_right.y_pixels = middle_top;
      rectangle_middle_right.width_pixels = rectangle_right - cutout_right;
      rectangle_middle_right.height_pixels = middle_height;
    }
    ++rectangle_count;
  }

  if (cutout_bottom < rectangle_bottom) {
    assert_true(cutout_bottom > rectangle.y_pixels);
    if (rectangles_out) {
      Rectangle& rectangle_upper = rectangles_out[rectangle_count];
      rectangle_upper.x_pixels = rectangle.x_pixels;
      rectangle_upper.y_pixels = cutout_bottom;
      rectangle_upper.width_pixels = rectangle.width_pixels;
      rectangle_upper.height_pixels = rectangle_bottom - cutout_bottom;
    }
    ++rectangle_count;
  }
  assert_true(rectangle_count <= kMaxCutoutBorderRectangles);
  return rectangle_count;
}

RenderTargetCache::~RenderTargetCache() {
  ShutdownCommon();
}

void RenderTargetCache::InitializeCommon() {
  if (const std::string& list = REXCVAR_GET(resolution_scale_targets); !list.empty()) {
    std::string bad_entry;
    if (!scaling_list_.Parse(list, &bad_entry)) {
      REXGPU_ERROR("resolution_scale_targets: \"{}\" is not WxH; list ignored", bad_entry);
    }
  }
  assert_true(ownership_ranges_.empty());
  ownership_ranges_.emplace(std::piecewise_construct, std::forward_as_tuple(uint32_t(0)),
                            std::forward_as_tuple(xenos::kEdramTileCount, RenderTargetKey(),
                                                  RenderTargetKey(), RenderTargetKey()));
}

void RenderTargetCache::DestroyAllRenderTargets(bool shutting_down) {
  ownership_ranges_.clear();
  if (!shutting_down) {
    ownership_ranges_.emplace(std::piecewise_construct, std::forward_as_tuple(uint32_t(0)),
                              std::forward_as_tuple(xenos::kEdramTileCount, RenderTargetKey(),
                                                    RenderTargetKey(), RenderTargetKey()));
  }

  for (const auto& render_target_pair : render_targets_) {
    if (render_target_pair.second) {
      delete render_target_pair.second;
    }
  }
  render_targets_.clear();
}

void RenderTargetCache::ShutdownCommon() {
  DestroyAllRenderTargets(true);
}

void RenderTargetCache::ClearCache() {
  if (!render_targets_.empty()) {
    std::unordered_set<RenderTargetKey, RenderTargetKey::Hasher> used_render_targets;
    for (const auto& ownership_range_pair : ownership_ranges_) {
      const OwnershipRange& ownership_range = ownership_range_pair.second;
      if (!ownership_range.render_target.IsEmpty()) {
        used_render_targets.emplace(ownership_range.render_target);
      }
      if (!ownership_range.depth_bits_target.IsEmpty()) {
        used_render_targets.emplace(ownership_range.depth_bits_target);
      }
      if (!ownership_range.host_depth_render_target_unorm24.IsEmpty()) {
        used_render_targets.emplace(ownership_range.host_depth_render_target_unorm24);
      }
      if (!ownership_range.host_depth_render_target_float24.IsEmpty()) {
        used_render_targets.emplace(ownership_range.host_depth_render_target_float24);
      }
    }
    if (render_targets_.size() != used_render_targets.size()) {
      typename decltype(render_targets_)::iterator it_next;
      for (auto it = render_targets_.begin(); it != render_targets_.end(); it = it_next) {
        it_next = std::next(it);
        if (!it->second) {
          render_targets_.erase(it);
          continue;
        }
        if (used_render_targets.find(it->second->key()) == used_render_targets.end()) {
          delete it->second;
          render_targets_.erase(it);
        }
      }
    }
  }
}

void RenderTargetCache::BeginFrame() {
  ResetAccumulatedRenderTargets();
}

bool RenderTargetCache::TrackLastUpdateDrawTarget(uint64_t frame) {
  if (last_update_draw_target_.IsEmpty()) {
    return true;
  }
  std::pair<uint64_t, uint64_t>& frames = draw_target_last_frames_[last_update_draw_target_];
  if (frames.first != frame) {
    frames.second = frames.first;
    frames.first = frame;
  }

  return frames.second && frame - frames.second <= kDrawTargetRecurringFrames;
}

std::string RenderTargetCache::GetLastUpdateDrawTargetName() const {
  return last_update_draw_target_.IsEmpty() ? std::string("no render target")
                                            : last_update_draw_target_.GetDebugName();
}

bool RenderTargetCache::IsNativeResolveAveraged(const draw_util::ResolveInfo& resolve_info) {
  if (!REXCVAR_GET(resolve_downscale_average)) {
    return false;
  }
  switch (resolve_info.copy_dest_info.copy_dest_format) {
    case xenos::ColorFormat::k_8:
    case xenos::ColorFormat::k_8_A:
    case xenos::ColorFormat::k_8_B:
    case xenos::ColorFormat::k_8_8:
    case xenos::ColorFormat::k_8_8_8_8:
    case xenos::ColorFormat::k_8_8_8_8_A:
      return true;
    default: {
      static bool logged = false;
      if (!logged) {
        logged = true;
        REXGPU_WARN(
            "resolve_downscale_average: format {} isn't of 8-bit channels; its resolves take the "
            "center sample",
            uint32_t(resolve_info.copy_dest_info.copy_dest_format));
      }
      return false;
    }
  }
}

bool RenderTargetCache::IsResolveNative(const draw_util::ResolveInfo& resolve_info) {
  const uint32_t width = uint32_t(resolve_info.coordinate_info.width_div_8) << 3;
  const uint32_t height = resolve_info.height_div_8 << 3;
  const bool listed = scaling_list_.Matches(width, height);
  if (REXCVAR_GET(log_resolution_scale_targets)) {
    const uint64_t size = (uint64_t(width) << 32) | height;
    if (logged_render_target_sizes_.size() < 4096 &&
        logged_render_target_sizes_.insert(size).second) {
      REXGPU_INFO("Resolve {}x{}: {}", width, height, listed ? "scaled" : "native");
    }
  }
  if (listed || !IsDrawResolutionScaled()) {
    return false;
  }
  const reg::RB_COPY_DEST_INFO dest_info = resolve_info.copy_dest_info;
  const draw_util::ResolveCopyDestCoordinateInfo dest = resolve_info.copy_dest_coordinate_info;
  const uint32_t pixel_size_log2 = draw_util::GetResolveDownscalePixelSizeLog2(dest_info);
  const uint32_t group_bytes_log2 = pixel_size_log2 <= 2 ? 7 : 6;
  const uint32_t group_mask = (UINT32_C(1) << group_bytes_log2) - 1;
  const bool whole = !dest_info.copy_dest_array && pixel_size_log2 <= 3 && !dest.offset_x_div_8 &&
                     !dest.offset_y_div_8 && ((width + 31) >> 5) >= dest.pitch_aligned_div_32 &&
                     ((height + 31) >> 5) >= dest.height_aligned_div_32 &&
                     !(resolve_info.copy_dest_extent_start & group_mask) &&
                     !(resolve_info.copy_dest_extent_length & group_mask);
  if (!whole) {
    static bool logged = false;
    if (!logged) {
      logged = true;
      REXGPU_WARN(
          "resolution_scale_targets: a {}x{} resolve stays scaled (it doesn't cover its whole "
          "destination, or the format can't be downscaled)",
          width, height);
    }
  }
  return whole;
}

bool RenderTargetCache::Update(bool is_rasterization_done,
                               reg::RB_DEPTHCONTROL normalized_depth_control,
                               uint32_t normalized_color_mask, const Shader& vertex_shader) {
  const RegisterFile& regs = register_file();
  bool interlock_barrier_only = GetPath() == Path::kPixelShaderInterlock;
  last_update_draw_target_ = RenderTargetKey();

  auto rb_surface_info = regs.Get<reg::RB_SURFACE_INFO>();
  xenos::MsaaSamples msaa_samples = rb_surface_info.msaa_samples;
  assert_true(msaa_samples <= xenos::MsaaSamples::k4X);
  if (msaa_samples > xenos::MsaaSamples::k4X) {
    assert_always();
    REXGPU_ERROR("{}x MSAA requested by the guest, Xenos only supports up to 4x",
                 uint32_t(1) << uint32_t(msaa_samples));
    return false;
  }
  uint32_t msaa_samples_x_log2 = uint32_t(msaa_samples >= xenos::MsaaSamples::k4X);
  uint32_t pitch_pixels = rb_surface_info.surface_pitch;

  assert_true(pitch_pixels || !is_rasterization_done);
  if (!pitch_pixels) {
    is_rasterization_done = false;
  } else if (pitch_pixels > xenos::kTexture2DCubeMaxWidthHeight) {
    REXGPU_ERROR(
        "Surface pitch {} larger than the maximum texture width {} specified "
        "by the guest",
        pitch_pixels, xenos::kTexture2DCubeMaxWidthHeight);
    return false;
  }
  uint32_t pitch_tiles_at_32bpp =
      ((pitch_pixels << msaa_samples_x_log2) + (xenos::kEdramTileWidthSamples - 1)) /
      xenos::kEdramTileWidthSamples;
  if (!interlock_barrier_only) {
    uint32_t pitch_pixels_tile_aligned_scaled =
        pitch_tiles_at_32bpp * (xenos::kEdramTileWidthSamples >> msaa_samples_x_log2) *
        draw_resolution_scale_x();
    uint32_t max_render_target_width = GetMaxRenderTargetWidth();
    if (pitch_pixels_tile_aligned_scaled > max_render_target_width) {
      REXGPU_ERROR(
          "Surface pitch aligned to EDRAM tiles and resolution-scaled {} "
          "larger than the maximum host render target width {}",
          pitch_pixels_tile_aligned_scaled, max_render_target_width);
      return false;
    }
  }

  uint32_t depth_and_color_rts_used_bits = 0;

  uint32_t edram_bases[1 + xenos::kMaxColorRenderTargets];
  uint32_t resource_formats[1 + xenos::kMaxColorRenderTargets];
  uint32_t rts_are_64bpp = 0;

  bool rts_keep_depth_bits[1 + xenos::kMaxColorRenderTargets] = {};
  if (is_rasterization_done) {
    if (normalized_depth_control.z_enable || normalized_depth_control.stencil_enable) {
      depth_and_color_rts_used_bits |= 1;
      auto rb_depth_info = regs.Get<reg::RB_DEPTH_INFO>();
      edram_bases[0] = rb_depth_info.depth_base;

      resource_formats[0] = interlock_barrier_only ? 0 : uint32_t(rb_depth_info.depth_format);
    }
    for (uint32_t i = 0; i < xenos::kMaxColorRenderTargets; ++i) {
      if (!(normalized_color_mask & (uint32_t(0b1111) << (4 * i)))) {
        continue;
      }
      auto color_info = regs.Get<reg::RB_COLOR_INFO>(reg::RB_COLOR_INFO::rt_register_indices[i]);
      uint32_t rt_bit_index = 1 + i;
      depth_and_color_rts_used_bits |= uint32_t(1) << rt_bit_index;
      edram_bases[rt_bit_index] = color_info.color_base;
      xenos::ColorRenderTargetFormat color_format =
          regs.Get<reg::RB_COLOR_INFO>(reg::RB_COLOR_INFO::rt_register_indices[i]).color_format;
      bool is_64bpp = xenos::IsColorRenderTargetFormat64bpp(color_format);
      if (is_64bpp) {
        rts_are_64bpp |= uint32_t(1) << rt_bit_index;
      }
      xenos::ColorRenderTargetFormat color_resource_format;
      if (interlock_barrier_only) {
        color_resource_format = is_64bpp ? xenos::ColorRenderTargetFormat::k_16_16_16_16
                                         : xenos::ColorRenderTargetFormat::k_8_8_8_8;
      } else {
        color_resource_format = GetColorResourceFormat(xenos::GetStorageColorFormat(color_format));
      }
      resource_formats[rt_bit_index] = uint32_t(color_resource_format);
      if (!interlock_barrier_only && !is_64bpp) {
        float unused_clamp[4];
        uint32_t keep_mask_low, keep_mask_high;
        GetPSIColorFormatInfo(color_format, (normalized_color_mask >> (i * 4)) & 0b1111,
                              unused_clamp[0], unused_clamp[1], unused_clamp[2], unused_clamp[3],
                              keep_mask_low, keep_mask_high);
        rts_keep_depth_bits[rt_bit_index] = !(~keep_mask_low & 0xFFFFFF00u);
      }
    }
  }

  uint32_t rts_remaining;
  uint32_t rt_index;

  bool keep_aliased_depth = false;
  if (!interlock_barrier_only && REXCVAR_GET(aliased_depth_read_only) &&
      (depth_and_color_rts_used_bits & 1) && normalized_depth_control.z_enable &&
      !normalized_depth_control.z_write_enable && !normalized_depth_control.stencil_enable) {
    uint32_t depth_base = edram_bases[0];
    for (uint32_t i = 1; i < 1 + xenos::kMaxColorRenderTargets; ++i) {
      if (!(depth_and_color_rts_used_bits & (uint32_t(1) << i)) || edram_bases[i] != depth_base) {
        continue;
      }
      if (!rts_keep_depth_bits[i]) {
        keep_aliased_depth = false;
        break;
      }
      keep_aliased_depth = true;
    }
  }

  if (!interlock_barrier_only && (depth_and_color_rts_used_bits & 1) &&
      normalized_depth_control.z_write_enable) {
    uint32_t depth_base = edram_bases[0];
    for (uint32_t i = 1; i < 1 + xenos::kMaxColorRenderTargets; ++i) {
      if ((depth_and_color_rts_used_bits & (uint32_t(1) << i)) && edram_bases[i] == depth_base) {
        rts_keep_depth_bits[i] = false;
      }
    }
  }

  rts_remaining = depth_and_color_rts_used_bits & ~(uint32_t(1));
  while (rex::bit_scan_forward(rts_remaining, &rt_index)) {
    rts_remaining &= ~(uint32_t(1) << rt_index);
    uint32_t edram_base = edram_bases[rt_index];
    uint32_t rts_other_remaining =
        depth_and_color_rts_used_bits & (~((uint32_t(1) << (rt_index + 1)) - 1) | uint32_t(1));
    uint32_t rt_other_index;
    while (rex::bit_scan_forward(rts_other_remaining, &rt_other_index)) {
      rts_other_remaining &= ~(uint32_t(1) << rt_other_index);
      if (edram_bases[rt_other_index] == edram_base) {
        if (rt_other_index == 0 && keep_aliased_depth) {
          continue;
        }
        depth_and_color_rts_used_bits &= ~(uint32_t(1) << rt_other_index);
      }
    }
  }

  if (!interlock_barrier_only) {
    for (size_t i = 0; i < rex::countof(last_update_transfers_); ++i) {
      last_update_transfers_[i].clear();
    }
  }

  if (!depth_and_color_rts_used_bits) {
    std::memset(last_update_used_render_targets_, 0, sizeof(last_update_used_render_targets_));
    if (are_accumulated_render_targets_valid_) {
      for (size_t i = 0; i < rex::countof(last_update_accumulated_render_targets_); ++i) {
        const RenderTarget* render_target = last_update_accumulated_render_targets_[i];
        if (!render_target) {
          continue;
        }
        RenderTargetKey rt_key = render_target->key();
        if (rt_key.pitch_tiles_at_32bpp != pitch_tiles_at_32bpp ||
            rt_key.msaa_samples != msaa_samples) {
          are_accumulated_render_targets_valid_ = false;
          break;
        }
      }
    }
    if (!are_accumulated_render_targets_valid_) {
      std::memset(last_update_accumulated_render_targets_, 0,
                  sizeof(last_update_accumulated_render_targets_));
    }
    return true;
  }

  uint32_t height_used =
      std::min(GetRenderTargetHeight(pitch_tiles_at_32bpp, msaa_samples),
               draw_extent_estimator_.EstimateMaxY(
                   interlock_barrier_only
                       ? REXCVAR_GET(execute_unclipped_draw_vs_on_cpu_for_psi_render_backend)
                       : true,
                   vertex_shader));

  RenderTargetKey rt_keys[1 + xenos::kMaxColorRenderTargets] = {};
  RenderTarget* rts[1 + xenos::kMaxColorRenderTargets] = {};

  uint32_t ownership_rts_used_bits = depth_and_color_rts_used_bits;
  if (keep_aliased_depth) {
    ownership_rts_used_bits &= ~uint32_t(1);
    RenderTargetKey& depth_key = rt_keys[0];
    depth_key.base_tiles = edram_bases[0];
    depth_key.pitch_tiles_at_32bpp = pitch_tiles_at_32bpp;
    depth_key.msaa_samples = msaa_samples;
    depth_key.is_depth = 1;
    depth_key.resource_format = resource_formats[0];
  }

  std::pair<uint32_t, uint32_t> edram_bases_sorted[1 + xenos::kMaxColorRenderTargets];
  uint32_t edram_bases_sorted_count = 0;
  rts_remaining = ownership_rts_used_bits;
  while (rex::bit_scan_forward(rts_remaining, &rt_index)) {
    rts_remaining &= ~(uint32_t(1) << rt_index);
    edram_bases_sorted[edram_bases_sorted_count++] =
        std::make_pair(edram_bases[rt_index], rt_index);
  }
  std::sort(edram_bases_sorted, edram_bases_sorted + edram_bases_sorted_count);

  uint32_t rt_max_distance_tiles_at_64bpp = xenos::kEdramTileCount * 2;
  if (REXCVAR_GET(mrt_edram_used_range_clamp_to_min) && edram_bases_sorted_count >= 2) {
    for (uint32_t i = 1; i < edram_bases_sorted_count; ++i) {
      const std::pair<uint32_t, uint32_t>& rt_base_prev = edram_bases_sorted[i - 1];
      rt_max_distance_tiles_at_64bpp =
          std::min(rt_max_distance_tiles_at_64bpp,
                   (edram_bases_sorted[i].first - rt_base_prev.first)
                       << (((rts_are_64bpp >> rt_base_prev.second) & 1) ^ 1));
    }

    const std::pair<uint32_t, uint32_t>& rt_base_last =
        edram_bases_sorted[edram_bases_sorted_count - 1];
    rt_max_distance_tiles_at_64bpp =
        std::min(rt_max_distance_tiles_at_64bpp,
                 (xenos::kEdramTileCount + edram_bases_sorted[0].first - rt_base_last.first)
                     << (((rts_are_64bpp >> rt_base_last.second) & 1) ^ 1));
  }

  uint32_t rt_lengths_tiles[1 + xenos::kMaxColorRenderTargets];
  uint32_t length_used_tiles_at_32bpp =
      ((height_used << uint32_t(msaa_samples >= xenos::MsaaSamples::k2X)) +
       (xenos::kEdramTileHeightSamples - 1)) /
      xenos::kEdramTileHeightSamples * pitch_tiles_at_32bpp;
  for (uint32_t i = 0; i < edram_bases_sorted_count; ++i) {
    const std::pair<uint32_t, uint32_t>& rt_base_index = edram_bases_sorted[i];
    uint32_t rt_base = rt_base_index.first;
    uint32_t rt_bit_index = rt_base_index.second;
    RenderTargetKey& rt_key = rt_keys[rt_bit_index];
    rt_key.base_tiles = rt_base;
    rt_key.pitch_tiles_at_32bpp = pitch_tiles_at_32bpp;
    rt_key.msaa_samples = msaa_samples;
    rt_key.is_depth = rt_bit_index == 0;
    rt_key.resource_format = resource_formats[rt_bit_index];
    if (!interlock_barrier_only) {
      RenderTarget* render_target = GetOrCreateRenderTarget(rt_key);
      if (!render_target) {
        return false;
      }
      rts[rt_bit_index] = render_target;
    }
    uint32_t rt_is_64bpp = (rts_are_64bpp >> rt_bit_index) & 1;

    rt_lengths_tiles[i] = std::min(std::min(length_used_tiles_at_32bpp << rt_is_64bpp,
                                            rt_max_distance_tiles_at_64bpp >> (rt_is_64bpp ^ 1)),
                                   ((i + 1 < edram_bases_sorted_count)
                                        ? edram_bases_sorted[i + 1].first
                                        : (xenos::kEdramTileCount + edram_bases_sorted[0].first)) -
                                       rt_base);
  }

  uint32_t draw_target_index;
  if (rex::bit_scan_forward(depth_and_color_rts_used_bits & ~uint32_t(1), &draw_target_index) ||
      rex::bit_scan_forward(depth_and_color_rts_used_bits, &draw_target_index)) {
    last_update_draw_target_ = rt_keys[draw_target_index];
  }

  if (keep_aliased_depth) {
    uint32_t alias_length_tiles = 0;
    for (uint32_t i = 0; i < edram_bases_sorted_count; ++i) {
      if (edram_bases_sorted[i].first == edram_bases[0]) {
        alias_length_tiles = rt_lengths_tiles[i];
        break;
      }
    }
    if (IsHostDepthCurrent(rt_keys[0], 0, alias_length_tiles)) {
      rts[0] = GetOrCreateRenderTarget(rt_keys[0]);
      if (!rts[0]) {
        return false;
      }
    } else {
      keep_aliased_depth = false;
      depth_and_color_rts_used_bits &= ~uint32_t(1);

      are_accumulated_render_targets_valid_ = false;
    }
  }

  if (interlock_barrier_only) {
    bool interlock_barrier_needed = false;
    for (uint32_t i = 0; i < edram_bases_sorted_count; ++i) {
      const std::pair<uint32_t, uint32_t>& rt_base_index = edram_bases_sorted[i];
      if (WouldOwnershipChangeRequireTransfers(rt_keys[rt_base_index.second], 0,
                                               rt_lengths_tiles[i])) {
        interlock_barrier_needed = true;
        break;
      }
    }
    if (interlock_barrier_needed) {
      RequestPixelShaderInterlockBarrier();
    }
  }

  for (uint32_t i = 0; i < edram_bases_sorted_count; ++i) {
    const std::pair<uint32_t, uint32_t>& rt_base_index = edram_bases_sorted[i];
    uint32_t rt_bit_index = rt_base_index.second;
    ChangeOwnership(rt_keys[rt_bit_index], 0, rt_lengths_tiles[i],
                    interlock_barrier_only ? nullptr : &last_update_transfers_[rt_bit_index],
                    nullptr, rts_keep_depth_bits[rt_bit_index]);
  }

  if (interlock_barrier_only) {
    return true;
  }

  for (uint32_t i = 0; i < 1 + xenos::kMaxColorRenderTargets; ++i) {
    last_update_used_render_targets_[i] =
        (depth_and_color_rts_used_bits & (uint32_t(1) << i)) ? rts[i] : nullptr;
  }
  if (are_accumulated_render_targets_valid_) {
    for (uint32_t i = 0; i < 1 + xenos::kMaxColorRenderTargets; ++i) {
      RenderTarget* current_rt =
          (depth_and_color_rts_used_bits & (uint32_t(1) << i)) ? rts[i] : nullptr;
      const RenderTarget* accumulated_rt = last_update_accumulated_render_targets_[i];
      if (!accumulated_rt) {
        if (current_rt) {
          are_accumulated_render_targets_valid_ = false;
          break;
        }

        last_update_accumulated_render_targets_[i] = current_rt;
        continue;
      }
      if (current_rt) {
        if (current_rt != accumulated_rt) {
          are_accumulated_render_targets_valid_ = false;
          break;
        }
      } else {
        RenderTargetKey accumulated_rt_key = accumulated_rt->key();
        if (accumulated_rt_key.pitch_tiles_at_32bpp != pitch_tiles_at_32bpp ||
            accumulated_rt_key.msaa_samples != msaa_samples) {
          are_accumulated_render_targets_valid_ = false;
          break;
        }
      }
    }

    for (uint32_t i = 1;
         are_accumulated_render_targets_valid_ && i < 1 + xenos::kMaxColorRenderTargets; ++i) {
      const RenderTarget* render_target = last_update_accumulated_render_targets_[i];
      if (!render_target) {
        continue;
      }
      for (uint32_t j = 0; j < i; ++j) {
        if (last_update_accumulated_render_targets_[j] == render_target) {
          are_accumulated_render_targets_valid_ = false;
          break;
        }
      }
    }
  }
  if (!are_accumulated_render_targets_valid_) {
    std::memcpy(last_update_accumulated_render_targets_, last_update_used_render_targets_,
                sizeof(last_update_accumulated_render_targets_));
    are_accumulated_render_targets_valid_ = true;
  }

  return true;
}

uint32_t RenderTargetCache::GetLastUpdateBoundRenderTargets(
    uint32_t* depth_and_color_formats_out) const {
  if (GetPath() != Path::kHostRenderTargets) {
    if (depth_and_color_formats_out) {
      std::memset(depth_and_color_formats_out, 0,
                  sizeof(uint32_t) * (1 + xenos::kMaxColorRenderTargets));
    }
    return 0;
  }
  uint32_t rts_used = 0;
  for (uint32_t i = 0; i < 1 + xenos::kMaxColorRenderTargets; ++i) {
    const RenderTarget* render_target = last_update_accumulated_render_targets_[i];
    if (!render_target) {
      if (depth_and_color_formats_out) {
        depth_and_color_formats_out[i] = 0;
      }
      continue;
    }
    rts_used |= uint32_t(1) << i;
    if (depth_and_color_formats_out) {
      depth_and_color_formats_out[i] = render_target->key().resource_format;
    }
  }
  return rts_used;
}

uint32_t RenderTargetCache::GetRenderTargetHeight(uint32_t pitch_tiles_at_32bpp,
                                                  xenos::MsaaSamples msaa_samples) const {
  if (!pitch_tiles_at_32bpp) {
    return 0;
  }

  uint32_t tile_rows = (xenos::kEdramTileCount + (pitch_tiles_at_32bpp - 1)) / pitch_tiles_at_32bpp;

  static_assert(!(xenos::kTexture2DCubeMaxWidthHeight % xenos::kEdramTileHeightSamples),
                "Maximum guest render target height is assumed to always be a multiple "
                "of an EDRAM tile height");
  uint32_t max_height_scaled = std::min(
      xenos::kTexture2DCubeMaxWidthHeight * draw_resolution_scale_y(), GetMaxRenderTargetHeight());
  uint32_t msaa_samples_y_log2 = uint32_t(msaa_samples >= xenos::MsaaSamples::k2X);
  uint32_t tile_height_samples_scaled = xenos::kEdramTileHeightSamples * draw_resolution_scale_y();
  tile_rows =
      std::min(tile_rows, (max_height_scaled << msaa_samples_y_log2) / tile_height_samples_scaled);
  assert_not_zero(tile_rows);
  return tile_rows * (xenos::kEdramTileHeightSamples >> msaa_samples_y_log2);
}

void RenderTargetCache::GetHostDepthStoreRectangleInfo(
    const Transfer::Rectangle& transfer_rectangle, xenos::MsaaSamples msaa_samples,
    HostDepthStoreRectangleConstant& rectangle_constant_out, uint32_t& group_count_x_out,
    uint32_t& group_count_y_out) const {
  HostDepthStoreRectangleConstant rectangle_constant;

  assert_zero(transfer_rectangle.x_pixels & 7);
  assert_zero(transfer_rectangle.y_pixels & 7);
  assert_zero(transfer_rectangle.width_pixels & 7);
  assert_zero(transfer_rectangle.height_pixels & 7);
  assert_not_zero(transfer_rectangle.width_pixels);
  rectangle_constant.x_pixels_div_8 = transfer_rectangle.x_pixels >> 3;
  rectangle_constant.y_pixels_div_8 = transfer_rectangle.y_pixels >> 3;
  rectangle_constant.width_pixels_div_8_minus_1 = (transfer_rectangle.width_pixels >> 3) - 1;
  rectangle_constant_out = rectangle_constant;

  uint32_t pixel_size_x = draw_resolution_scale_x()
                          << uint32_t(msaa_samples >= xenos::MsaaSamples::k4X);
  uint32_t pixel_size_y = draw_resolution_scale_y()
                          << uint32_t(msaa_samples >= xenos::MsaaSamples::k2X);
  group_count_x_out = (transfer_rectangle.width_pixels * pixel_size_x + 63) >> 6;
  group_count_y_out = (transfer_rectangle.height_pixels * pixel_size_y) >> 3;
}

void RenderTargetCache::GetResolveCopyRectanglesToDump(
    uint32_t base, uint32_t row_length, uint32_t rows, uint32_t pitch,
    std::vector<ResolveCopyDumpRectangle>& rectangles_out) const {
  rectangles_out.clear();
  assert_true(row_length <= pitch);
  row_length = std::min(row_length, pitch);
  if (!row_length || !rows) {
    return;
  }
  auto get_rectangles_in_extent = [&](uint32_t extent_start, uint32_t extent_end,
                                      uint32_t range_local_offset) {
    auto it = ownership_ranges_.lower_bound(extent_start);
    if (it != ownership_ranges_.cbegin()) {
      auto it_pre = std::prev(it);
      if (it_pre->second.end_tiles > extent_start) {
        it = it_pre;
      }
    }
    for (; it != ownership_ranges_.cend(); ++it) {
      uint32_t range_global_start = std::max(it->first, extent_start);
      if (range_global_start >= extent_end) {
        break;
      }
      RenderTargetKey rt_key = it->second.render_target;
      if (rt_key.IsEmpty()) {
        continue;
      }

      while (it != ownership_ranges_.cend()) {
        auto it_next = std::next(it);
        if (it_next == ownership_ranges_.cend() || it_next->first >= extent_end ||
            it_next->second.render_target != rt_key) {
          break;
        }
        it = it_next;
      }

      uint32_t range_local_start =
          range_local_offset + std::max(range_global_start, extent_start) - base;
      uint32_t range_local_end =
          range_local_offset + std::min(it->second.end_tiles, extent_end) - base;
      assert_true(range_local_start < range_local_end);

      uint32_t rows_start = range_local_start / pitch;
      uint32_t rows_end = (range_local_end + (pitch - 1)) / pitch;
      uint32_t row_first_start = range_local_start - rows_start * pitch;
      if (row_first_start >= row_length) {
        if (rows_start + 1 < rows_end) {
          ++rows_start;
          row_first_start = 0;
        } else {
          continue;
        }
      }

      auto it_rt = render_targets_.find(rt_key);
      assert_true(it_rt != render_targets_.cend());
      assert_not_null(it_rt->second);

      rectangles_out.emplace_back(
          it_rt->second, rows_start, rows_end - rows_start, row_first_start,
          std::min(pitch - (rows_end * pitch - range_local_end), row_length));
    }
  };
  uint32_t resolve_area_end = base + (rows - 1) * pitch + row_length;
  get_rectangles_in_extent(base, std::min(resolve_area_end, xenos::kEdramTileCount), 0);
  if (resolve_area_end > xenos::kEdramTileCount) {
    get_rectangles_in_extent(0, std::min(resolve_area_end & (xenos::kEdramTileCount - 1), base),
                             xenos::kEdramTileCount);
  }
}

void RenderTargetCache::GetResolveCopyDispatchesToDump(
    uint32_t base, uint32_t row_length, uint32_t rows, uint32_t pitch,
    std::vector<ResolveCopyDumpRectangle>& rectangles_out,
    std::vector<ResolveCopyDispatch>& dispatches_out) const {
  GetResolveCopyRectanglesToDump(base, row_length, rows, pitch, rectangles_out);
  dispatches_out.clear();
  for (uint32_t rectangle_index = 0; rectangle_index < uint32_t(rectangles_out.size());
       ++rectangle_index) {
    const ResolveCopyDumpRectangle& rectangle = rectangles_out[rectangle_index];
    ResolveCopyDumpRectangle::Dispatch
        rectangle_dispatches[ResolveCopyDumpRectangle::kMaxDispatches];
    uint32_t dispatch_count = rectangle.GetDispatches(pitch, row_length, rectangle_dispatches);
    for (uint32_t i = 0; i < dispatch_count; ++i) {
      dispatches_out.emplace_back(rectangle_index, rectangle_dispatches[i]);
    }
  }
}

bool RenderTargetCache::PrepareHostRenderTargetsResolveClear(
    const draw_util::ResolveInfo& resolve_info, Transfer::Rectangle& clear_rectangle_out,
    RenderTarget*& depth_render_target_out, std::vector<Transfer>& depth_transfers_out,
    RenderTarget*& color_render_target_out, std::vector<Transfer>& color_transfers_out) {
  assert_true(GetPath() == Path::kHostRenderTargets);

  uint32_t pitch_tiles_at_32bpp;
  uint32_t base_offset_tiles_at_32bpp;
  xenos::MsaaSamples msaa_samples;
  if (resolve_info.IsClearingDepth()) {
    pitch_tiles_at_32bpp = resolve_info.depth_edram_info.pitch_tiles;
    base_offset_tiles_at_32bpp =
        resolve_info.depth_edram_info.base_tiles - resolve_info.depth_original_base;
    msaa_samples = resolve_info.depth_edram_info.msaa_samples;
  } else if (resolve_info.IsClearingColor()) {
    pitch_tiles_at_32bpp = resolve_info.color_edram_info.pitch_tiles;
    base_offset_tiles_at_32bpp =
        resolve_info.color_edram_info.base_tiles - resolve_info.color_original_base;
    if (resolve_info.color_edram_info.format_is_64bpp) {
      assert_zero(pitch_tiles_at_32bpp & 1);
      pitch_tiles_at_32bpp >>= 1;
      assert_zero(base_offset_tiles_at_32bpp & 1);
      base_offset_tiles_at_32bpp >>= 1;
    }
    msaa_samples = resolve_info.color_edram_info.msaa_samples;
  } else {
    return false;
  }
  assert_true(msaa_samples <= xenos::MsaaSamples::k4X);
  if (!pitch_tiles_at_32bpp) {
    return false;
  }
  uint32_t msaa_samples_x_log2 = uint32_t(msaa_samples >= xenos::MsaaSamples::k4X);
  uint32_t msaa_samples_y_log2 = uint32_t(msaa_samples >= xenos::MsaaSamples::k2X);
  if (pitch_tiles_at_32bpp > ((xenos::kTexture2DCubeMaxWidthHeight << msaa_samples_x_log2) +
                              (xenos::kEdramTileWidthSamples - 1)) /
                                 xenos::kEdramTileWidthSamples) {
    REXGPU_ERROR(
        "Surface pitch in 80-sample groups {} at {}x MSAA larger than the "
        "maximum texture width {} specified by the guest in a resolve",
        pitch_tiles_at_32bpp, uint32_t(1) << uint32_t(msaa_samples),
        xenos::kTexture2DCubeMaxWidthHeight);
    return false;
  }
  uint32_t pitch_pixels =
      pitch_tiles_at_32bpp * (xenos::kEdramTileWidthSamples >> msaa_samples_x_log2);
  uint32_t pitch_pixels_scaled = pitch_pixels * draw_resolution_scale_x();
  uint32_t max_render_target_width = GetMaxRenderTargetWidth();
  if (pitch_pixels_scaled > max_render_target_width) {
    REXGPU_ERROR(
        "Surface pitch aligned to EDRAM tiles and resolution-scaled {} larger "
        "than the maximum host render target width {} in a resolve",
        pitch_pixels_scaled, max_render_target_width);
    return false;
  }

  uint32_t render_target_height_pixels = GetRenderTargetHeight(pitch_tiles_at_32bpp, msaa_samples);
  uint32_t base_offset_rows_at_32bpp = base_offset_tiles_at_32bpp / pitch_tiles_at_32bpp;
  Transfer::Rectangle clear_rectangle;
  clear_rectangle.x_pixels =
      std::min((base_offset_tiles_at_32bpp - base_offset_rows_at_32bpp * pitch_tiles_at_32bpp) *
                       (xenos::kEdramTileWidthSamples >> msaa_samples_x_log2) +
                   (uint32_t(resolve_info.coordinate_info.edram_offset_x_div_8) << 3),
               pitch_pixels);
  clear_rectangle.y_pixels =
      std::min(base_offset_rows_at_32bpp * (xenos::kEdramTileHeightSamples >> msaa_samples_y_log2) +
                   (uint32_t(resolve_info.coordinate_info.edram_offset_y_div_8) << 3),
               render_target_height_pixels);
  clear_rectangle.width_pixels = std::min(uint32_t(resolve_info.coordinate_info.width_div_8) << 3,
                                          pitch_pixels - clear_rectangle.x_pixels);
  clear_rectangle.height_pixels = std::min(uint32_t(resolve_info.height_div_8) << 3,
                                           render_target_height_pixels - clear_rectangle.y_pixels);
  if (!clear_rectangle.width_pixels || !clear_rectangle.height_pixels) {
    return false;
  }

  uint32_t clear_start_tiles_at_32bpp =
      ((clear_rectangle.y_pixels << msaa_samples_y_log2) / xenos::kEdramTileHeightSamples) *
          pitch_tiles_at_32bpp +
      (clear_rectangle.x_pixels << msaa_samples_x_log2) / xenos::kEdramTileWidthSamples;
  uint32_t clear_length_tiles_at_32bpp =
      (((clear_rectangle.y_pixels + clear_rectangle.height_pixels - 1) << msaa_samples_y_log2) /
       xenos::kEdramTileHeightSamples) *
          pitch_tiles_at_32bpp +
      ((clear_rectangle.x_pixels + clear_rectangle.width_pixels - 1) << msaa_samples_x_log2) /
          xenos::kEdramTileWidthSamples +
      1 - clear_start_tiles_at_32bpp;

  uint32_t depth_clear_start_tiles_base_relative = 0;
  uint32_t depth_clear_length_tiles = 0;
  if (resolve_info.IsClearingDepth()) {
    depth_clear_start_tiles_base_relative =
        std::min(clear_start_tiles_at_32bpp, xenos::kEdramTileCount);
    depth_clear_length_tiles =
        std::min(clear_start_tiles_at_32bpp + clear_length_tiles_at_32bpp, xenos::kEdramTileCount) -
        depth_clear_start_tiles_base_relative;
  }
  uint32_t color_clear_start_tiles_base_relative = 0;
  uint32_t color_clear_length_tiles = 0;
  if (resolve_info.IsClearingColor()) {
    color_clear_start_tiles_base_relative =
        std::min(clear_start_tiles_at_32bpp << resolve_info.color_edram_info.format_is_64bpp,
                 xenos::kEdramTileCount);
    color_clear_length_tiles = std::min((clear_start_tiles_at_32bpp + clear_length_tiles_at_32bpp)
                                            << resolve_info.color_edram_info.format_is_64bpp,
                                        xenos::kEdramTileCount) -
                               color_clear_start_tiles_base_relative;
  }
  if (depth_clear_length_tiles && color_clear_length_tiles) {
    uint32_t depth_clear_start_tiles_wrapped =
        (resolve_info.depth_original_base + depth_clear_start_tiles_base_relative) &
        (xenos::kEdramTileCount - 1);
    uint32_t color_clear_start_tiles_wrapped =
        (resolve_info.color_original_base + color_clear_start_tiles_base_relative) &
        (xenos::kEdramTileCount - 1);
    depth_clear_length_tiles =
        std::min(depth_clear_length_tiles,
                 ((color_clear_start_tiles_wrapped < depth_clear_start_tiles_wrapped)
                      ? xenos::kEdramTileCount
                      : 0) +
                     color_clear_start_tiles_wrapped - depth_clear_start_tiles_wrapped);
    color_clear_length_tiles =
        std::min(color_clear_length_tiles,
                 ((depth_clear_start_tiles_wrapped < color_clear_start_tiles_wrapped)
                      ? xenos::kEdramTileCount
                      : 0) +
                     depth_clear_start_tiles_wrapped - color_clear_start_tiles_wrapped);
  }

  RenderTargetKey depth_render_target_key;
  RenderTarget* depth_render_target = nullptr;
  if (depth_clear_length_tiles) {
    depth_render_target_key.base_tiles = resolve_info.depth_original_base;
    depth_render_target_key.pitch_tiles_at_32bpp = pitch_tiles_at_32bpp;
    depth_render_target_key.msaa_samples = msaa_samples;
    depth_render_target_key.is_depth = 1;
    depth_render_target_key.resource_format = resolve_info.depth_edram_info.format;
    depth_render_target = GetOrCreateRenderTarget(depth_render_target_key);
    if (!depth_render_target) {
      depth_render_target_key = RenderTargetKey();
      depth_clear_length_tiles = 0;
    }
  }
  RenderTargetKey color_render_target_key;
  RenderTarget* color_render_target = nullptr;
  if (color_clear_length_tiles) {
    color_render_target_key.base_tiles = resolve_info.color_original_base;
    color_render_target_key.pitch_tiles_at_32bpp = pitch_tiles_at_32bpp;
    color_render_target_key.msaa_samples = msaa_samples;
    color_render_target_key.is_depth = 0;
    color_render_target_key.resource_format = uint32_t(GetColorResourceFormat(
        xenos::ColorRenderTargetFormat(resolve_info.color_edram_info.format)));
    color_render_target = GetOrCreateRenderTarget(color_render_target_key);
    if (!color_render_target) {
      color_render_target_key = RenderTargetKey();
      color_clear_length_tiles = 0;
    }
  }
  if (!depth_clear_length_tiles && !color_clear_length_tiles) {
    return false;
  }

  clear_rectangle_out = clear_rectangle;
  depth_render_target_out = depth_render_target;
  depth_transfers_out.clear();
  if (depth_render_target) {
    ChangeOwnership(depth_render_target_key, depth_clear_start_tiles_base_relative,
                    depth_clear_length_tiles, &depth_transfers_out, &clear_rectangle);
  }
  color_render_target_out = color_render_target;
  color_transfers_out.clear();
  if (color_render_target) {
    ChangeOwnership(color_render_target_key, color_clear_start_tiles_base_relative,
                    color_clear_length_tiles, &color_transfers_out, &clear_rectangle);
  }
  return true;
}

void RenderTargetCache::PixelShaderInterlockFullEdramBarrierPlaced() {
  assert_true(GetPath() == Path::kPixelShaderInterlock);

  OwnershipRange empty_range(xenos::kEdramTileCount, RenderTargetKey(), RenderTargetKey(),
                             RenderTargetKey());
  if (ownership_ranges_.size() == 1) {
    assert_true(!ownership_ranges_.begin()->first);
    OwnershipRange& all_edram_range = ownership_ranges_.begin()->second;
    assert_true(all_edram_range.end_tiles == xenos::kEdramTileCount);
    all_edram_range = empty_range;
    return;
  }
  ownership_ranges_.clear();
  ownership_ranges_.emplace(0, empty_range);
}

RenderTargetCache::RenderTarget* RenderTargetCache::GetOrCreateRenderTarget(RenderTargetKey key) {
  assert_true(GetPath() == Path::kHostRenderTargets);
  auto it_rt = render_targets_.find(key);
  RenderTarget* render_target;
  if (it_rt != render_targets_.end()) {
    render_target = it_rt->second;
  } else {
    render_target = CreateRenderTarget(key);
    uint32_t width = key.GetWidth();
    uint32_t height = GetRenderTargetHeight(key.pitch_tiles_at_32bpp, key.msaa_samples);
    if (render_target) {
      REXGPU_DEBUG(
          "Created a {}x{} {}xMSAA {} render target with guest format {} at "
          "EDRAM base {}",
          width, height, uint32_t(1) << uint32_t(key.msaa_samples),
          key.is_depth ? "depth" : "color", static_cast<uint32_t>(key.resource_format),
          static_cast<uint32_t>(key.base_tiles));
    } else {
      REXGPU_ERROR(
          "Failed to create a {}x{} {}xMSAA {} render target with guest format "
          "{} at EDRAM base {}",
          width, height, uint32_t(1) << uint32_t(key.msaa_samples),
          key.is_depth ? "depth" : "color", static_cast<uint32_t>(key.resource_format),
          static_cast<uint32_t>(key.base_tiles));
    }

    render_targets_.emplace(key, render_target);
  }
  return render_target;
}

bool RenderTargetCache::WouldOwnershipChangeRequireTransfers(RenderTargetKey dest,
                                                             uint32_t start_tiles_base_relative,
                                                             uint32_t length_tiles) const {
  assert_true(start_tiles_base_relative <= (xenos::kEdramTileCount - uint32_t(length_tiles != 0)));
  assert_true(length_tiles <= xenos::kEdramTileCount);
  if (length_tiles == 0) {
    return false;
  }
  bool host_depth_encoding_different = dest.is_depth && GetPath() == Path::kHostRenderTargets &&
                                       IsHostDepthEncodingDifferent(dest.GetDepthFormat());
  auto would_require_transfers_in_extent = [&](uint32_t extent_start, uint32_t extent_end) -> bool {
    auto it = ownership_ranges_.lower_bound(extent_start);
    if (it != ownership_ranges_.begin()) {
      auto it_pre = std::prev(it);
      if (it_pre->second.end_tiles > extent_start) {
        it = it_pre;
      }
    }
    for (; it != ownership_ranges_.end(); ++it) {
      if (it->first >= extent_end) {
        break;
      }
      if (it->second.IsOwnedBy(dest, host_depth_encoding_different)) {
        continue;
      }
      RenderTargetKey transfer_source = it->second.render_target;

      if (!transfer_source.IsEmpty() && transfer_source != dest) {
        return true;
      }
    }
    return false;
  };

  uint32_t start_tiles =
      (dest.base_tiles + start_tiles_base_relative) & (xenos::kEdramTileCount - 1);
  uint32_t end_tiles = start_tiles + length_tiles;
  if (would_require_transfers_in_extent(start_tiles, std::min(end_tiles, xenos::kEdramTileCount))) {
    return true;
  }
  if (end_tiles > xenos::kEdramTileCount) {
    if (would_require_transfers_in_extent(
            0, std::min(end_tiles & (xenos::kEdramTileCount - 1), start_tiles))) {
      return true;
    }
  }
  return false;
}

bool RenderTargetCache::IsHostDepthCurrent(RenderTargetKey depth_target,
                                           uint32_t start_tiles_base_relative,
                                           uint32_t length_tiles) const {
  assert_true(GetPath() == Path::kHostRenderTargets);
  assert_true(depth_target.is_depth);
  assert_true(length_tiles <= xenos::kEdramTileCount);
  if (!length_tiles) {
    return true;
  }
  auto is_current_in_extent = [&](uint32_t extent_start, uint32_t extent_end) -> bool {
    auto it = ownership_ranges_.lower_bound(extent_start);
    if (it != ownership_ranges_.cbegin()) {
      auto it_pre = std::prev(it);
      if (it_pre->second.end_tiles > extent_start) {
        it = it_pre;
      }
    }
    for (; it != ownership_ranges_.cend() && it->first < extent_end; ++it) {
      if (it->second.depth_bits_target != depth_target) {
        return false;
      }
    }
    return true;
  };
  uint32_t start_tiles =
      (depth_target.base_tiles + start_tiles_base_relative) & (xenos::kEdramTileCount - 1);
  uint32_t end_tiles = start_tiles + length_tiles;
  if (!is_current_in_extent(start_tiles, std::min(end_tiles, xenos::kEdramTileCount))) {
    return false;
  }
  return end_tiles <= xenos::kEdramTileCount ||
         is_current_in_extent(0, end_tiles & (xenos::kEdramTileCount - 1));
}

void RenderTargetCache::ChangeOwnership(RenderTargetKey dest, uint32_t start_tiles_base_relative,
                                        uint32_t length_tiles,
                                        std::vector<Transfer>* transfers_append_out,
                                        const Transfer::Rectangle* resolve_clear_cutout,
                                        bool keep_depth_bits) {
  assert_true(start_tiles_base_relative <= (xenos::kEdramTileCount - uint32_t(length_tiles != 0)));
  assert_true(length_tiles <= xenos::kEdramTileCount);
  if (length_tiles == 0) {
    return;
  }
  uint32_t dest_pitch_tiles = dest.GetPitchTiles();
  bool dest_is_64bpp = dest.Is64bpp();
  bool host_depth_encoding_different = dest.is_depth && GetPath() == Path::kHostRenderTargets &&
                                       IsHostDepthEncodingDifferent(dest.GetDepthFormat());

  bool dest_writes_depth_bits =
      GetPath() == Path::kHostRenderTargets && (dest.is_depth || !keep_depth_bits);

  auto is_claim_needed = [&](const OwnershipRange& range) -> bool {
    if (!range.IsOwnedBy(dest, host_depth_encoding_different)) {
      return true;
    }
    return dest_writes_depth_bits && range.depth_bits_target != dest;
  };
  auto change_ownership_in_extent = [&](uint32_t extent_start, uint32_t extent_end) {
    auto it = ownership_ranges_.lower_bound(extent_start);
    if (it != ownership_ranges_.begin()) {
      auto it_pre = std::prev(it);
      if (it_pre->second.end_tiles > extent_start && is_claim_needed(it_pre->second)) {
        ownership_ranges_.emplace(extent_start, it_pre->second);
        it_pre->second.end_tiles = extent_start;

        it = std::next(it_pre);
      }
    }
    while (it != ownership_ranges_.end()) {
      if (it->first >= extent_end) {
        break;
      }
      if (!is_claim_needed(it->second)) {
        ++it;
        continue;
      }

      if (it->second.end_tiles > extent_end) {
        ownership_ranges_.emplace(extent_end, it->second);
        it->second.end_tiles = extent_end;
      }
      if (transfers_append_out) {
        RenderTargetKey transfer_source = it->second.render_target;

        if (!transfer_source.IsEmpty() && transfer_source != dest) {
          uint32_t transfer_end_tiles = std::min(it->second.end_tiles, extent_end);
          if (!resolve_clear_cutout ||
              Transfer::GetRangeRectangles(it->first, transfer_end_tiles, dest.base_tiles,
                                           dest_pitch_tiles, dest.msaa_samples, dest_is_64bpp,
                                           nullptr, resolve_clear_cutout)) {
            RenderTargetKey transfer_host_depth_source =
                host_depth_encoding_different
                    ? it->second.GetHostDepthRenderTarget(dest.GetDepthFormat())
                    : RenderTargetKey();
            if (transfer_host_depth_source == transfer_source) {
              transfer_host_depth_source = RenderTargetKey();
            }
            if (!transfers_append_out->empty() &&
                transfers_append_out->back().end_tiles == it->first &&
                transfers_append_out->back().source->key() == transfer_source &&
                ((transfers_append_out->back().host_depth_source == nullptr) ==
                 transfer_host_depth_source.IsEmpty()) &&
                (transfer_host_depth_source.IsEmpty() ||
                 transfers_append_out->back().host_depth_source->key() ==
                     transfer_host_depth_source)) {
              transfers_append_out->back().end_tiles = transfer_end_tiles;
            } else {
              auto transfer_source_rt_it = render_targets_.find(transfer_source);
              if (transfer_source_rt_it != render_targets_.end()) {
                assert_not_null(transfer_source_rt_it->second);
                auto transfer_host_depth_source_rt_it =
                    !transfer_host_depth_source.IsEmpty()
                        ? render_targets_.find(transfer_host_depth_source)
                        : render_targets_.end();
                if (transfer_host_depth_source.IsEmpty() ||
                    transfer_host_depth_source_rt_it != render_targets_.end()) {
                  assert_false(transfer_host_depth_source_rt_it != render_targets_.end() &&
                               !transfer_host_depth_source_rt_it->second);
                  transfers_append_out->emplace_back(
                      it->first, transfer_end_tiles, transfer_source_rt_it->second,
                      transfer_host_depth_source_rt_it != render_targets_.end()
                          ? transfer_host_depth_source_rt_it->second
                          : nullptr);
                }
              }
            }
          }
        }
      }

      it->second.render_target = dest;
      if (dest_writes_depth_bits) {
        it->second.depth_bits_target = dest;
      }
      if (host_depth_encoding_different) {
        it->second.GetHostDepthRenderTarget(dest.GetDepthFormat()) = dest;
      }

      std::map<uint32_t, OwnershipRange>::iterator it_next;
      if (it != ownership_ranges_.end()) {
        it_next = std::next(it);
        if (it_next != ownership_ranges_.end() && it_next->second.AreOwnersSame(it->second)) {
          it->second.end_tiles = it_next->second.end_tiles;
          auto it_after = std::next(it_next);
          ownership_ranges_.erase(it_next);
          it_next = it_after;
        }
      } else {
        it_next = ownership_ranges_.end();
      }

      if (it != ownership_ranges_.begin()) {
        auto it_prev = std::prev(it);
        if (it_prev->second.AreOwnersSame(it->second)) {
          it_prev->second.end_tiles = it->second.end_tiles;
          ownership_ranges_.erase(it);
        }
      }
      it = it_next;
    }
  };

  uint32_t start_tiles =
      (dest.base_tiles + start_tiles_base_relative) & (xenos::kEdramTileCount - 1);
  uint32_t end_tiles = start_tiles + length_tiles;
  change_ownership_in_extent(start_tiles, std::min(end_tiles, xenos::kEdramTileCount));
  if (end_tiles > xenos::kEdramTileCount) {
    change_ownership_in_extent(0, std::min(end_tiles & (xenos::kEdramTileCount - 1), start_tiles));
  }
}

}

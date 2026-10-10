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
#include <utility>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/pipeline/shader/shader.h>
#include <rex/graphics/register_file.h>
#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>
#include <rex/memory.h>

namespace rex::graphics::draw_util {

constexpr bool IsPrimitiveLine(bool vgt_output_path_is_tessellation_enable,
                               xenos::PrimitiveType type) {
  if (vgt_output_path_is_tessellation_enable && type == xenos::PrimitiveType::kLinePatch) {
    return true;
  }
  switch (type) {
    case xenos::PrimitiveType::kLineList:
    case xenos::PrimitiveType::kLineStrip:
    case xenos::PrimitiveType::kLineLoop:
    case xenos::PrimitiveType::k2DLineStrip:
      return true;
    default:
      break;
  }
  return false;
}

inline bool IsPrimitiveLine(const RegisterFile& regs) {
  return IsPrimitiveLine(regs.Get<reg::VGT_OUTPUT_PATH_CNTL>().path_select ==
                             xenos::VGTOutputPath::kTessellationEnable,
                         regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type);
}

constexpr bool IsPrimitivePolygonal(bool vgt_output_path_is_tessellation_enable,
                                    xenos::PrimitiveType type) {
  if (vgt_output_path_is_tessellation_enable &&
      (type == xenos::PrimitiveType::kTrianglePatch || type == xenos::PrimitiveType::kQuadPatch)) {
    return true;
  }
  switch (type) {
    case xenos::PrimitiveType::kTriangleList:
    case xenos::PrimitiveType::kTriangleFan:
    case xenos::PrimitiveType::kTriangleStrip:
    case xenos::PrimitiveType::kTriangleWithWFlags:
    case xenos::PrimitiveType::kQuadList:
    case xenos::PrimitiveType::kQuadStrip:
    case xenos::PrimitiveType::kPolygon:
      return true;
    default:
      break;
  }

  return false;
}

inline bool IsPrimitivePolygonal(const RegisterFile& regs) {
  return IsPrimitivePolygonal(regs.Get<reg::VGT_OUTPUT_PATH_CNTL>().path_select ==
                                  xenos::VGTOutputPath::kTessellationEnable,
                              regs.Get<reg::VGT_DRAW_INITIATOR>().prim_type);
}

bool IsRasterizationPotentiallyDone(const RegisterFile& regs, bool primitive_polygonal);

bool IsVIZSurveyDraw(const RegisterFile& regs);

extern const int8_t kD3D10StandardSamplePositions2x[2][2];
extern const int8_t kD3D10StandardSamplePositions4x[4][2];

reg::RB_DEPTHCONTROL GetNormalizedDepthControl(const RegisterFile& regs);

constexpr float kD3D10PolygonOffsetFactorUnorm24 = float((UINT32_C(1) << 24) - 1);

constexpr float kD3D10PolygonOffsetFactorFloat24 = float(UINT32_C(1) << (21 + 3));

inline int32_t GetD3D10IntegerPolygonOffset(xenos::DepthRenderTargetFormat depth_format,
                                            float polygon_offset) {
  bool is_float24 = depth_format == xenos::DepthRenderTargetFormat::kD24FS8;

  int32_t polygon_offset_int = int32_t(std::ceil(
      std::abs(polygon_offset) * (is_float24 ? kD3D10PolygonOffsetFactorFloat24 * (1.0f / 8.0f)
                                             : kD3D10PolygonOffsetFactorUnorm24)));

  if (is_float24) {
    polygon_offset_int <<= 3;
  }
  return polygon_offset < 0 ? -polygon_offset_int : polygon_offset_int;
}

void GetPreferredFacePolygonOffset(const RegisterFile& regs, bool primitive_polygonal,
                                   float& scale_out, float& offset_out);

inline bool DoesCoverageDependOnAlpha(reg::RB_COLORCONTROL rb_colorcontrol) {
  return (rb_colorcontrol.alpha_test_enable &&
          rb_colorcontrol.alpha_func != xenos::CompareFunction::kAlways) ||
         rb_colorcontrol.alpha_to_mask_enable;
}

bool IsPixelShaderNeededWithRasterization(const Shader& shader, const RegisterFile& regs,
                                          bool include_memory_export = true);

struct ViewportInfo {
  uint32_t xy_offset[2];

  uint32_t xy_extent[2];
  float z_min;
  float z_max;

  float ndc_scale[3];
  float ndc_offset[3];
};

void GetHostViewportInfo(const RegisterFile& regs, uint32_t draw_resolution_scale_x,
                         uint32_t draw_resolution_scale_y, bool origin_bottom_left, uint32_t x_max,
                         uint32_t y_max, bool allow_reverse_z,
                         reg::RB_DEPTHCONTROL normalized_depth_control, bool convert_z_to_float24,
                         bool full_float24_in_0_to_1, bool pixel_shader_writes_depth,
                         ViewportInfo& viewport_info_out);

struct Scissor {
  uint32_t offset[2];

  uint32_t extent[2];
};
void GetScissor(const RegisterFile& regs, Scissor& scissor_out, bool clamp_to_surface_pitch = true);

uint32_t GetNormalizedColorMask(const RegisterFile& regs,
                                uint32_t pixel_shader_writes_color_targets);

inline uint32_t GetD3D10SampleIndexForGuest2xMSAA(uint32_t guest_sample_index,
                                                  bool native_2x_msaa_supported) {
  assert(guest_sample_index <= 1);
  if (native_2x_msaa_supported) {
    return guest_sample_index ? 0 : 1;
  }

  return guest_sample_index ? 3 : 0;
}

struct MemExportRange {
  uint32_t base_address_dwords;
  uint32_t size_bytes;

  explicit MemExportRange(uint32_t base_address_dwords, uint32_t size_bytes)
      : base_address_dwords(base_address_dwords), size_bytes(size_bytes) {}
};

void AddMemExportRanges(const RegisterFile& regs, const Shader& shader,
                        std::vector<MemExportRange>& ranges_out);

xenos::CopySampleSelect SanitizeCopySampleSelect(xenos::CopySampleSelect copy_sample_select,
                                                 xenos::MsaaSamples msaa_samples, bool is_depth);

union ResolveEdramInfo {
  uint32_t packed;
  struct {
    uint32_t pitch_tiles : xenos::kEdramPitchTilesBits;
    xenos::MsaaSamples msaa_samples : xenos::kMsaaSamplesBits;
    uint32_t is_depth : 1;

    uint32_t base_tiles : xenos::kEdramBaseTilesBits;
    uint32_t format : xenos::kRenderTargetFormatBits;
    uint32_t format_is_64bpp : 1;

    uint32_t fill_half_pixel_offset : 1;
  };
  ResolveEdramInfo() : packed(0) { static_assert_size(*this, sizeof(packed)); }
};

union ResolveCoordinateInfo {
  uint32_t packed;
  struct {
    uint32_t edram_offset_x_div_8 : 4;

    uint32_t edram_offset_y_div_8 : 1;

    uint32_t width_div_8 : xenos::kResolveSizeBits - xenos::kResolveAlignmentPixelsLog2;

    uint32_t draw_resolution_scale_x : 3;
    uint32_t draw_resolution_scale_y : 3;
  };
  ResolveCoordinateInfo() : packed(0) { static_assert_size(*this, sizeof(packed)); }
};

void GetResolveEdramTileSpan(ResolveEdramInfo edram_info, ResolveCoordinateInfo coordinate_info,
                             uint32_t height_div_8, uint32_t& base_out,
                             uint32_t& row_length_used_out, uint32_t& rows_out);

union ResolveCopyDestCoordinateInfo {
  uint32_t packed;
  struct {
    uint32_t pitch_aligned_div_32 : xenos::kTexture2DCubeMaxWidthHeightLog2 + 2 -
                                    xenos::kTextureTileWidthHeightLog2;
    uint32_t height_aligned_div_32 : xenos::kTexture2DCubeMaxWidthHeightLog2 + 2 -
                                     xenos::kTextureTileWidthHeightLog2;

    uint32_t offset_x_div_8 : 7 - xenos::kResolveAlignmentPixelsLog2;
    uint32_t offset_y_div_8 : 7 - xenos::kResolveAlignmentPixelsLog2;

    xenos::CopySampleSelect copy_sample_select : 3;
  };
  ResolveCopyDestCoordinateInfo() : packed(0) { static_assert_size(*this, sizeof(packed)); }
};

enum class ResolveCopyShaderIndex {
  kFast32bpp1x2xMSAA,
  kFast32bpp4xMSAA,
  kFast64bpp1x2xMSAA,
  kFast64bpp4xMSAA,

  kFull8bpp,
  kFull16bpp,
  kFull32bpp,
  kFull64bpp,
  kFull128bpp,

  kCount,
  kUnknown = kCount,
};

struct ResolveCopyShaderInfo {
  const char* debug_name;

  bool source_is_raw;

  uint32_t source_bpe_log2;

  uint32_t dest_bpe_log2;

  uint32_t group_size_x_log2, group_size_y_log2;
};

extern const ResolveCopyShaderInfo resolve_copy_shader_info[size_t(ResolveCopyShaderIndex::kCount)];

struct ResolveCopyShaderConstants {
  struct DestRelative {
    ResolveEdramInfo edram_info;
    ResolveCoordinateInfo coordinate_info;
    reg::RB_COPY_DEST_INFO dest_info;
    ResolveCopyDestCoordinateInfo dest_coordinate_info;
  };
  DestRelative dest_relative;
  uint32_t dest_base;
};

struct ResolveClearShaderConstants {
  struct RenderTargetSpecific {
    uint32_t clear_value[2];
    ResolveEdramInfo edram_info;
  };
  RenderTargetSpecific rt_specific;
  ResolveCoordinateInfo coordinate_info;
};

struct ResolveInfo {
  reg::RB_COPY_CONTROL rb_copy_control;

  ResolveEdramInfo depth_edram_info;
  ResolveEdramInfo color_edram_info;

  uint32_t depth_original_base;
  uint32_t color_original_base;

  ResolveCoordinateInfo coordinate_info;

  uint32_t height_div_8;

  reg::RB_COPY_DEST_INFO copy_dest_info;
  ResolveCopyDestCoordinateInfo copy_dest_coordinate_info;

  uint32_t copy_dest_base;

  uint32_t copy_dest_extent_start;
  uint32_t copy_dest_extent_length;

  uint32_t rb_depth_clear;
  uint32_t rb_color_clear;
  uint32_t rb_color_clear_lo;

  bool IsCopyingDepth() const {
    return rb_copy_control.copy_src_select >= xenos::kMaxColorRenderTargets;
  }

  void GetCopyEdramTileSpan(uint32_t& base_out, uint32_t& row_length_used_out, uint32_t& rows_out,
                            uint32_t& pitch_out) const {
    ResolveEdramInfo edram_info = IsCopyingDepth() ? depth_edram_info : color_edram_info;
    GetResolveEdramTileSpan(edram_info, coordinate_info, height_div_8, base_out,
                            row_length_used_out, rows_out);
    pitch_out = edram_info.pitch_tiles;
  }

  ResolveCopyShaderIndex GetCopyShader(uint32_t draw_resolution_scale_x,
                                       uint32_t draw_resolution_scale_y,
                                       ResolveCopyShaderConstants& constants_out,
                                       uint32_t& group_count_x_out,
                                       uint32_t& group_count_y_out) const;

  bool IsClearingDepth() const { return rb_copy_control.depth_clear_enable != 0; }

  bool IsClearingColor() const {
    return !IsCopyingDepth() && rb_copy_control.color_clear_enable != 0;
  }

  void GetDepthClearShaderConstants(ResolveClearShaderConstants& constants_out) const {
    assert_true(IsClearingDepth());
    constants_out.rt_specific.clear_value[0] = rb_depth_clear;
    constants_out.rt_specific.clear_value[1] = rb_depth_clear;
    constants_out.rt_specific.edram_info = depth_edram_info;
    constants_out.coordinate_info = coordinate_info;
  }

  void GetColorClearShaderConstants(ResolveClearShaderConstants& constants_out) const {
    assert_true(IsClearingColor());

    constants_out.rt_specific.clear_value[0] = rb_color_clear;
    constants_out.rt_specific.clear_value[1] = rb_color_clear_lo;
    constants_out.rt_specific.edram_info = color_edram_info;
    constants_out.coordinate_info = coordinate_info;
  }

  std::pair<uint32_t, uint32_t> GetClearShaderGroupCount(uint32_t draw_resolution_scale_x,
                                                         uint32_t draw_resolution_scale_y) const {
    uint32_t width_samples_div_8 = coordinate_info.width_div_8;
    uint32_t height_samples_div_8 = height_div_8;
    xenos::MsaaSamples samples =
        IsCopyingDepth() ? depth_edram_info.msaa_samples : color_edram_info.msaa_samples;
    if (samples >= xenos::MsaaSamples::k2X) {
      height_samples_div_8 <<= 1;
      if (samples >= xenos::MsaaSamples::k4X) {
        width_samples_div_8 <<= 1;
      }
    }
    width_samples_div_8 *= draw_resolution_scale_x;
    height_samples_div_8 *= draw_resolution_scale_y;
    return std::make_pair((width_samples_div_8 + uint32_t(7)) >> 3, height_samples_div_8);
  }
};

bool GetResolveInfo(const RegisterFile& regs, const memory::Memory& memory,
                    uint32_t draw_resolution_scale_x, uint32_t draw_resolution_scale_y,
                    bool fixed_rg16_truncated_to_minus_1_to_1,
                    bool fixed_rgba16_truncated_to_minus_1_to_1, ResolveInfo& info_out);

uint32_t GetResolveDownscalePixelSizeLog2(reg::RB_COPY_DEST_INFO copy_dest_info);

}

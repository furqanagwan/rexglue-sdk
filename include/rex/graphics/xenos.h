/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <algorithm>

#include <rex/assert.h>
#include <rex/math.h>
#include <rex/memory.h>
#include <rex/platform.h>
#include <rex/types.h>

namespace rex::graphics {
namespace xenos {

constexpr memory::fourcc_t kSwapSignature = memory::make_fourcc("SWAP");

enum class ShaderType : uint32_t {
  kVertex = 0,
  kPixel = 1,
};

constexpr uint32_t kVertexIndexBits = 24;
constexpr uint32_t kVertexIndexMask = (uint32_t(1) << kVertexIndexBits) - 1;

enum class PrimitiveType : uint32_t {
  kNone = 0x00,
  kPointList = 0x01,
  kLineList = 0x02,
  kLineStrip = 0x03,
  kTriangleList = 0x04,
  kTriangleFan = 0x05,
  kTriangleStrip = 0x06,
  kTriangleWithWFlags = 0x07,
  kRectangleList = 0x08,
  kLineLoop = 0x0C,
  kQuadList = 0x0D,
  kQuadStrip = 0x0E,
  kPolygon = 0x0F,

  kExplicitMajorModeForceStart = 0x10,

  k2DCopyRectListV0 = 0x10,
  k2DCopyRectListV1 = 0x11,
  k2DCopyRectListV2 = 0x12,
  k2DCopyRectListV3 = 0x13,
  k2DFillRectList = 0x14,
  k2DLineStrip = 0x15,
  k2DTriStrip = 0x16,

  kLinePatch = 0x10,
  kTrianglePatch = 0x11,
  kQuadPatch = 0x12,
};

enum class DataDimension : uint32_t {
  k1D = 0,
  k2DOrStacked = 1,
  k3D = 2,
  kCube = 3,
};

enum class ClampMode : uint32_t {
  kRepeat = 0,
  kMirroredRepeat = 1,
  kClampToEdge = 2,
  kMirrorClampToEdge = 3,
  kClampToHalfway = 4,
  kMirrorClampToHalfway = 5,
  kClampToBorder = 6,
  kMirrorClampToBorder = 7,
};

constexpr bool ClampModeUsesBorder(ClampMode clamp_mode) {
  return clamp_mode == ClampMode::kClampToBorder || clamp_mode == ClampMode::kMirrorClampToBorder;
}

enum class TextureSign : uint32_t {
  kUnsigned = 0,

  kSigned = 1,

  kUnsignedBiased = 2,

  kGamma = 3,
};

enum class TextureFilter : uint32_t {
  kPoint = 0,
  kLinear = 1,

  kBaseMap = 2,
  kUseFetchConst = 3,
};

enum class AnisoFilter : uint32_t {
  kDisabled = 0,
  kMax_1_1 = 1,
  kMax_2_1 = 2,
  kMax_4_1 = 3,
  kMax_8_1 = 4,
  kMax_16_1 = 5,
  kUseFetchConst = 7,
};

enum class BorderColor : uint32_t {

  k_ABGR_Black = 0,

  k_ABGR_White = 1,

  k_ACBYCR_Black = 2,

  k_ACBCRY_Black = 3,
};

enum class FetchOpDimension : uint32_t {
  k1D = 0,
  k2D = 1,
  k3DOrStacked = 2,
  kCube = 3,
};

inline int GetFetchOpDimensionComponentCount(FetchOpDimension dimension) {
  switch (dimension) {
    case FetchOpDimension::k1D:
      return 1;
    case FetchOpDimension::k2D:
      return 2;
    case FetchOpDimension::k3DOrStacked:
    case FetchOpDimension::kCube:
      return 3;
    default:
      assert_unhandled_case(dimension);
      return 1;
  }
}

enum class SampleLocation : uint32_t {
  kCentroid = 0,
  kCenter = 1,
};

enum class Endian : uint32_t {
  kNone = 0,
  k8in16 = 1,
  k8in32 = 2,
  k16in32 = 3,
};

enum class Endian128 : uint32_t {
  kNone = 0,
  k8in16 = 1,
  k8in32 = 2,
  k16in32 = 3,
  k8in64 = 4,
  k8in128 = 5,
};

enum class IndexFormat : uint32_t {
  kInt16,

  kInt32,
};

enum class SurfaceNumberFormat : uint32_t {
  kUnsignedRepeatingFraction = 0,

  kSignedRepeatingFraction = 1,
  kUnsignedInteger = 2,
  kSignedInteger = 3,
  kFloat = 7,
};

enum class MsaaSamples : uint32_t {
  k1X = 0,
  k2X = 1,
  k4X = 2,
};

constexpr uint32_t kMsaaSamplesBits = 2;

constexpr uint32_t kColorRenderTargetIndexBits = 2;
constexpr uint32_t kMaxColorRenderTargets = 4;

enum class ColorRenderTargetFormat : uint32_t {
  k_8_8_8_8 = 0,
  k_8_8_8_8_GAMMA = 1,
  k_2_10_10_10 = 2,

  k_2_10_10_10_FLOAT = 3,

  k_16_16 = 4,

  k_16_16_16_16 = 5,
  k_16_16_FLOAT = 6,
  k_16_16_16_16_FLOAT = 7,
  k_2_10_10_10_AS_10_10_10_10 = 10,

  k_2_10_10_10_FLOAT_AS_16_16_16_16 = 12,
  k_32_FLOAT = 14,
  k_32_32_FLOAT = 15,
};

const char* GetColorRenderTargetFormatName(ColorRenderTargetFormat format);

constexpr bool IsColorRenderTargetFormat64bpp(ColorRenderTargetFormat format) {
  return format == ColorRenderTargetFormat::k_16_16_16_16 ||
         format == ColorRenderTargetFormat::k_16_16_16_16_FLOAT ||
         format == ColorRenderTargetFormat::k_32_32_FLOAT;
}

inline uint32_t GetColorRenderTargetFormatComponentCount(ColorRenderTargetFormat format) {
  switch (format) {
    case ColorRenderTargetFormat::k_8_8_8_8:
    case ColorRenderTargetFormat::k_8_8_8_8_GAMMA:
    case ColorRenderTargetFormat::k_2_10_10_10:
    case ColorRenderTargetFormat::k_2_10_10_10_FLOAT:
    case ColorRenderTargetFormat::k_16_16_16_16:
    case ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
    case ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10:
    case ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16:
      return 4;
    case ColorRenderTargetFormat::k_16_16:
    case ColorRenderTargetFormat::k_16_16_FLOAT:
    case ColorRenderTargetFormat::k_32_32_FLOAT:
      return 2;
    case ColorRenderTargetFormat::k_32_FLOAT:
      return 1;
    default:
      assert_unhandled_case(format);
      return 0;
  }
}

constexpr ColorRenderTargetFormat GetStorageColorFormat(ColorRenderTargetFormat format) {
  switch (format) {
    case ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10:
      return ColorRenderTargetFormat::k_2_10_10_10;
    case ColorRenderTargetFormat::k_2_10_10_10_FLOAT_AS_16_16_16_16:
      return ColorRenderTargetFormat::k_2_10_10_10_FLOAT;
    default:
      return format;
  }
}

enum class DepthRenderTargetFormat : uint32_t {
  kD24S8 = 0,

  kD24FS8 = 1,
};

const char* GetDepthRenderTargetFormatName(DepthRenderTargetFormat format);

float PWLGammaToLinear(float gamma);
float LinearToPWLGamma(float linear);

float Float7e3To32(uint32_t f10);

uint32_t Float32To20e4(float f32, bool round_to_nearest_even);

float Float20e4To32(uint32_t f24);

constexpr float UNorm24To32(uint32_t n24) {
  return float(n24 + (n24 >> 23)) * (1.0f / float(1 << 24));
}

constexpr float kPolygonOffsetScaleSubpixelUnit = 1.0f / 16.0f;

constexpr uint32_t kColorRenderTargetFormatBits = 4;
constexpr uint32_t kDepthRenderTargetFormatBits = 1;
constexpr uint32_t kRenderTargetFormatBits =
    std::max(kColorRenderTargetFormatBits, kDepthRenderTargetFormatBits);

constexpr uint32_t kEdramTileWidthSamples = 80;
constexpr uint32_t kEdramTileHeightSamples = 16;
constexpr uint32_t kEdramTileCount = 2048;
constexpr uint32_t kEdramSizeBytes =
    kEdramTileCount * kEdramTileHeightSamples * kEdramTileWidthSamples * sizeof(uint32_t);

constexpr uint32_t kEdramPitchPixelsBits = 14;

constexpr uint32_t kEdramBaseTilesBits = 11;

constexpr uint32_t GetSurfacePitchTiles(uint32_t pitch_pixels, MsaaSamples msaa_samples,
                                        bool is_64bpp) {
  uint32_t pitch_samples = pitch_pixels << uint32_t(msaa_samples >= MsaaSamples::k4X);
  uint32_t pitch_tiles = (pitch_samples + (kEdramTileWidthSamples - 1)) / kEdramTileWidthSamples;
  if (is_64bpp) {
    pitch_tiles <<= 1;
  }
  return pitch_tiles;
}

constexpr uint32_t kEdramPitchTilesBits = 10;

constexpr uint32_t kFormatBits = 6;

enum class TextureFormat : uint32_t {
  k_1_REVERSE = 0,
  k_1 = 1,
  k_8 = 2,
  k_1_5_5_5 = 3,
  k_5_6_5 = 4,
  k_6_5_5 = 5,
  k_8_8_8_8 = 6,
  k_2_10_10_10 = 7,

  k_8_A = 8,
  k_8_B = 9,
  k_8_8 = 10,

  k_Cr_Y1_Cb_Y0_REP = 11,

  k_Y1_Cr_Y0_Cb_REP = 12,
  k_16_16_EDRAM = 13,

  k_8_8_8_8_A = 14,
  k_4_4_4_4 = 15,
  k_10_11_11 = 16,
  k_11_11_10 = 17,
  k_DXT1 = 18,
  k_DXT2_3 = 19,
  k_DXT4_5 = 20,
  k_16_16_16_16_EDRAM = 21,
  k_24_8 = 22,
  k_24_8_FLOAT = 23,
  k_16 = 24,
  k_16_16 = 25,
  k_16_16_16_16 = 26,
  k_16_EXPAND = 27,
  k_16_16_EXPAND = 28,
  k_16_16_16_16_EXPAND = 29,
  k_16_FLOAT = 30,
  k_16_16_FLOAT = 31,
  k_16_16_16_16_FLOAT = 32,
  k_32 = 33,
  k_32_32 = 34,
  k_32_32_32_32 = 35,
  k_32_FLOAT = 36,
  k_32_32_FLOAT = 37,
  k_32_32_32_32_FLOAT = 38,
  k_32_AS_8 = 39,
  k_32_AS_8_8 = 40,
  k_16_MPEG = 41,
  k_16_16_MPEG = 42,
  k_8_INTERLACED = 43,
  k_32_AS_8_INTERLACED = 44,
  k_32_AS_8_8_INTERLACED = 45,
  k_16_INTERLACED = 46,
  k_16_MPEG_INTERLACED = 47,
  k_16_16_MPEG_INTERLACED = 48,
  k_DXN = 49,
  k_8_8_8_8_AS_16_16_16_16 = 50,
  k_DXT1_AS_16_16_16_16 = 51,
  k_DXT2_3_AS_16_16_16_16 = 52,
  k_DXT4_5_AS_16_16_16_16 = 53,
  k_2_10_10_10_AS_16_16_16_16 = 54,
  k_10_11_11_AS_16_16_16_16 = 55,
  k_11_11_10_AS_16_16_16_16 = 56,
  k_32_32_32_FLOAT = 57,
  k_DXT3A = 58,
  k_DXT5A = 59,
  k_CTX1 = 60,
  k_DXT3A_AS_1_1_1_1 = 61,
  k_8_8_8_8_GAMMA_EDRAM = 62,
  k_2_10_10_10_FLOAT_EDRAM = 63,
};

enum class ColorFormat : uint32_t {
  k_8 = 2,
  k_1_5_5_5 = 3,
  k_5_6_5 = 4,
  k_6_5_5 = 5,
  k_8_8_8_8 = 6,
  k_2_10_10_10 = 7,
  k_8_A = 8,
  k_8_B = 9,
  k_8_8 = 10,
  k_8_8_8_8_A = 14,
  k_4_4_4_4 = 15,
  k_10_11_11 = 16,
  k_11_11_10 = 17,
  k_16 = 24,
  k_16_16 = 25,
  k_16_16_16_16 = 26,
  k_16_FLOAT = 30,
  k_16_16_FLOAT = 31,
  k_16_16_16_16_FLOAT = 32,
  k_32_FLOAT = 36,
  k_32_32_FLOAT = 37,
  k_32_32_32_32_FLOAT = 38,
  k_8_8_8_8_AS_16_16_16_16 = 50,
  k_2_10_10_10_AS_16_16_16_16 = 54,
  k_10_11_11_AS_16_16_16_16 = 55,
  k_11_11_10_AS_16_16_16_16 = 56,
};

constexpr bool IsColorResolveFormatBitwiseEquivalent(ColorRenderTargetFormat render_target_format,
                                                     ColorFormat color_format) {
  switch (render_target_format) {
    case ColorRenderTargetFormat::k_8_8_8_8:

    case ColorRenderTargetFormat::k_8_8_8_8_GAMMA:

      return color_format == ColorFormat::k_8_8_8_8 || color_format == ColorFormat::k_8_8_8_8_A ||
             color_format == ColorFormat::k_8_8_8_8_AS_16_16_16_16;
    case ColorRenderTargetFormat::k_2_10_10_10:
    case ColorRenderTargetFormat::k_2_10_10_10_AS_10_10_10_10:
      return color_format == ColorFormat::k_2_10_10_10 ||
             color_format == ColorFormat::k_2_10_10_10_AS_16_16_16_16;
    case ColorRenderTargetFormat::k_16_16_FLOAT:
      return color_format == ColorFormat::k_16_16_FLOAT;
    case ColorRenderTargetFormat::k_16_16_16_16_FLOAT:
      return color_format == ColorFormat::k_16_16_16_16_FLOAT;
    case ColorRenderTargetFormat::k_32_FLOAT:
      return color_format == ColorFormat::k_32_FLOAT;
    case ColorRenderTargetFormat::k_32_32_FLOAT:
      return color_format == ColorFormat::k_32_32_FLOAT;
    default:
      return false;
  }
}

enum class VertexFormat : uint32_t {
  kUndefined = 0,
  k_8_8_8_8 = 6,
  k_2_10_10_10 = 7,
  k_10_11_11 = 16,
  k_11_11_10 = 17,
  k_16_16 = 25,
  k_16_16_16_16 = 26,
  k_16_16_FLOAT = 31,
  k_16_16_16_16_FLOAT = 32,
  k_32 = 33,
  k_32_32 = 34,
  k_32_32_32_32 = 35,
  k_32_FLOAT = 36,
  k_32_32_FLOAT = 37,
  k_32_32_32_32_FLOAT = 38,
  k_32_32_32_FLOAT = 57,
};

inline int GetVertexFormatComponentCount(VertexFormat format) {
  switch (format) {
    case VertexFormat::k_32:
    case VertexFormat::k_32_FLOAT:
      return 1;
    case VertexFormat::k_16_16:
    case VertexFormat::k_16_16_FLOAT:
    case VertexFormat::k_32_32:
    case VertexFormat::k_32_32_FLOAT:
      return 2;
    case VertexFormat::k_10_11_11:
    case VertexFormat::k_11_11_10:
    case VertexFormat::k_32_32_32_FLOAT:
      return 3;
    case VertexFormat::k_8_8_8_8:
    case VertexFormat::k_2_10_10_10:
    case VertexFormat::k_16_16_16_16:
    case VertexFormat::k_16_16_16_16_FLOAT:
    case VertexFormat::k_32_32_32_32:
    case VertexFormat::k_32_32_32_32_FLOAT:
      return 4;
    default:
      assert_unhandled_case(format);
      return 0;
  }
}

inline uint32_t GetVertexFormatNeededWords(VertexFormat format, uint32_t used_components) {
  assert_zero(used_components & ~uint32_t(0b1111));
  if (!used_components) {
    return 0;
  }
  switch (format) {
    case VertexFormat::k_8_8_8_8:
    case VertexFormat::k_2_10_10_10:
      return 0b0001;
    case VertexFormat::k_10_11_11:
    case VertexFormat::k_11_11_10:
      return (used_components & 0b0111) ? 0b0001 : 0b0000;
    case VertexFormat::k_16_16:
    case VertexFormat::k_16_16_FLOAT:
      return (used_components & 0b0011) ? 0b0001 : 0b0000;
    case VertexFormat::k_16_16_16_16:
    case VertexFormat::k_16_16_16_16_FLOAT:
      return ((used_components & 0b0011) ? 0b0001 : 0b0000) |
             ((used_components & 0b1100) ? 0b0010 : 0b0000);
    case VertexFormat::k_32:
    case VertexFormat::k_32_FLOAT:
      return used_components & 0b0001;
    case VertexFormat::k_32_32:
    case VertexFormat::k_32_32_FLOAT:
      return used_components & 0b0011;
    case VertexFormat::k_32_32_32_32:
    case VertexFormat::k_32_32_32_32_FLOAT:
      return used_components;
    case VertexFormat::k_32_32_32_FLOAT:
      return used_components & 0b0111;
    default:
      assert_unhandled_case(format);
      return 0b0000;
  }
}

enum class CompareFunction : uint32_t {
  kNever = 0b000,
  kLess = 0b001,
  kEqual = 0b010,
  kLessEqual = 0b011,
  kGreater = 0b100,
  kNotEqual = 0b101,
  kGreaterEqual = 0b110,
  kAlways = 0b111,
};

enum class StencilOp : uint32_t {
  kKeep = 0,
  kZero = 1,
  kReplace = 2,
  kIncrementClamp = 3,
  kDecrementClamp = 4,
  kInvert = 5,
  kIncrementWrap = 6,
  kDecrementWrap = 7,
};

enum class BlendFactor : uint32_t {
  kZero = 0,
  kOne = 1,
  kSrcColor = 4,
  kOneMinusSrcColor = 5,
  kSrcAlpha = 6,
  kOneMinusSrcAlpha = 7,
  kDstColor = 8,
  kOneMinusDstColor = 9,
  kDstAlpha = 10,
  kOneMinusDstAlpha = 11,
  kConstantColor = 12,
  kOneMinusConstantColor = 13,
  kConstantAlpha = 14,
  kOneMinusConstantAlpha = 15,
  kSrcAlphaSaturate = 16,

};

enum class BlendOp : uint32_t {
  kAdd = 0,
  kSubtract = 1,
  kMin = 2,
  kMax = 3,
  kRevSubtract = 4,
};

typedef enum {
  XE_GPU_INVALIDATE_MASK_VERTEX_SHADER = 1 << 8,
  XE_GPU_INVALIDATE_MASK_PIXEL_SHADER = 1 << 9,

  XE_GPU_INVALIDATE_MASK_ALL = 0x7FFF,
} XE_GPU_INVALIDATE_MASK;

enum class SourceSelect : uint32_t {
  kDMA,
  kImmediate,
  kAutoIndex,
};

enum class MajorMode : uint32_t {
  kImplicit,
  kExplicit,
};

inline bool IsMajorModeExplicit(MajorMode major_mode, PrimitiveType primitive_type) {
  return major_mode != MajorMode::kImplicit ||
         primitive_type >= PrimitiveType::kExplicitMajorModeForceStart;
}

enum class SignedRepeatingFractionMode : uint32_t {

  kZeroClampMinusOne,

  kNoZero,
};

enum class ArbitraryFilter : uint32_t {
  k2x4Sym = 0,
  k2x4Asym = 1,
  k4x2Sym = 2,
  k4x2Asym = 3,
  k4x4Sym = 4,
  k4x4Asym = 5,
  kUseFetchConst = 7,
};

constexpr uint32_t kMaxShaderTempRegistersLog2 = 6;
constexpr uint32_t kMaxShaderTempRegisters = UINT32_C(1) << kMaxShaderTempRegistersLog2;

enum class VertexShaderExportMode : uint32_t {
  kPosition1Vector = 0,
  kPosition2VectorsSprite = 2,
  kPosition2VectorsEdge = 3,
  kPosition2VectorsKill = 4,
  kPosition2VectorsSpriteKill = 5,
  kPosition2VectorsEdgeKill = 6,

  kMultipass = 7,
};

constexpr uint32_t kMaxInterpolators = 16;

enum class SampleControl : uint32_t {
  kCentroidsOnly = 0,
  kCentersOnly = 1,
  kCentroidsAndCenters = 2,
};

inline uint32_t GetInterpolatorSamplingPattern(MsaaSamples msaa_samples,
                                               SampleControl sample_control,
                                               uint32_t interpolator_control_sampling_pattern) {
  if (msaa_samples == MsaaSamples::k1X || sample_control == SampleControl::kCentersOnly) {
    return ((1 << kMaxInterpolators) - 1) * uint32_t(SampleLocation::kCenter);
  }
  if (sample_control == SampleControl::kCentroidsOnly) {
    return ((1 << kMaxInterpolators) - 1) * uint32_t(SampleLocation::kCentroid);
  }
  assert_true(sample_control == SampleControl::kCentroidsAndCenters);
  return interpolator_control_sampling_pattern;
}

enum class VGTOutputPath : uint32_t {
  kVertexReuse = 0,
  kTessellationEnable = 1,
  kPassthru = 2,
};

enum class TessellationMode : uint32_t {
  kDiscrete = 0,
  kContinuous = 1,
  kAdaptive = 2,
};

enum class PolygonModeEnable : uint32_t {
  kDisabled = 0,
  kDualMode = 1,

};

enum class PolygonType : uint32_t {
  kPoints = 0,
  kLines = 1,
  kTriangles = 2,
};

enum class PixelCenter : uint32_t {

  kD3DZero = 0,

  kOGLHalf = 1,
};

enum class VertexRounding : uint32_t {
  kTruncate = 0,
  kRound = 1,
  kRoundToEven = 2,
  kRoundToOdd = 3,
};

enum class VertexQuantization : uint32_t {
  k_1_16th = 0,
  k_1_8th = 1,
  k_1_4th = 2,
  k_1_2 = 3,
  k_1 = 4,

};

enum class EdramMode : uint32_t {
  kNoOperation = 0,
  kColorDepth = 4,

  kDepthOnly = 5,
  kCopy = 6,
};

constexpr uint32_t kResolveAlignmentPixelsLog2 = 3;
constexpr uint32_t kResolveAlignmentPixels = 1 << kResolveAlignmentPixelsLog2;

constexpr uint32_t kResolveSizeBits = 14;
constexpr uint32_t kMaxResolveSize = (1 << kResolveSizeBits) - kResolveAlignmentPixels;

enum class CopyCommand : uint32_t {
  kRaw = 0,
  kConvert = 1,
  kConstantOne = 2,
  kNull = 3,
};

enum class CopySampleSelect : uint32_t {
  k0,
  k1,
  k2,
  k3,
  k01,
  k23,
  k0123,
};

constexpr bool IsSingleCopySampleSelected(CopySampleSelect copy_sample_select) {
  return copy_sample_select >= CopySampleSelect::k0 && copy_sample_select <= CopySampleSelect::k3;
}

#define XE_GPU_MAKE_TEXTURE_SWIZZLE(x, y, z, w)                \
  (((rex::graphics::xenos::XE_GPU_TEXTURE_SWIZZLE_##x) << 0) | \
   ((rex::graphics::xenos::XE_GPU_TEXTURE_SWIZZLE_##y) << 3) | \
   ((rex::graphics::xenos::XE_GPU_TEXTURE_SWIZZLE_##z) << 6) | \
   ((rex::graphics::xenos::XE_GPU_TEXTURE_SWIZZLE_##w) << 9))
typedef enum {
  XE_GPU_TEXTURE_SWIZZLE_X = 0,
  XE_GPU_TEXTURE_SWIZZLE_R = 0,
  XE_GPU_TEXTURE_SWIZZLE_Y = 1,
  XE_GPU_TEXTURE_SWIZZLE_G = 1,
  XE_GPU_TEXTURE_SWIZZLE_Z = 2,
  XE_GPU_TEXTURE_SWIZZLE_B = 2,
  XE_GPU_TEXTURE_SWIZZLE_W = 3,
  XE_GPU_TEXTURE_SWIZZLE_A = 3,
  XE_GPU_TEXTURE_SWIZZLE_0 = 4,
  XE_GPU_TEXTURE_SWIZZLE_1 = 5,
  XE_GPU_TEXTURE_SWIZZLE_RRRR = XE_GPU_MAKE_TEXTURE_SWIZZLE(R, R, R, R),
  XE_GPU_TEXTURE_SWIZZLE_RGGG = XE_GPU_MAKE_TEXTURE_SWIZZLE(R, G, G, G),
  XE_GPU_TEXTURE_SWIZZLE_RGBB = XE_GPU_MAKE_TEXTURE_SWIZZLE(R, G, B, B),
  XE_GPU_TEXTURE_SWIZZLE_RGBA = XE_GPU_MAKE_TEXTURE_SWIZZLE(R, G, B, A),
  XE_GPU_TEXTURE_SWIZZLE_0000 = XE_GPU_MAKE_TEXTURE_SWIZZLE(0, 0, 0, 0),
} XE_GPU_TEXTURE_SWIZZLE;

inline uint16_t GpuSwap(uint16_t value, Endian endianness) {
  switch (endianness) {
    case Endian::kNone:

      return value;
    case Endian::k8in16:

      return ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0x00FF00FF);
    default:
      assert_unhandled_case(endianness);
      return value;
  }
}

inline uint32_t GpuSwap(uint32_t value, Endian endianness) {
  switch (endianness) {
    default:
    case Endian::kNone:

      return value;
    case Endian::k8in16:

      return ((value << 8) & 0xFF00FF00) | ((value >> 8) & 0x00FF00FF);
    case Endian::k8in32:

      return rex::byte_swap(value);
    case Endian::k16in32:

      return ((value >> 16) & 0xFFFF) | (value << 16);
  }
}

inline float GpuSwap(float value, Endian endianness) {
  union {
    uint32_t i;
    float f;
  } v;
  v.f = value;
  v.i = GpuSwap(v.i, endianness);
  return v.f;
}

inline uint32_t GpuToCpu(uint32_t p) {
  return p;
}

inline uint32_t CpuToGpu(uint32_t p) {
  return p & 0x1FFFFFFF;
}

union alignas(uint32_t) LoopConstant {
  uint32_t value;
  struct {
    uint32_t count : 8;

    uint32_t start : 8;
    int32_t step : 8;
    uint32_t _pad_24 : 8;
  };
};
static_assert_size(LoopConstant, sizeof(uint32_t));

enum class FetchConstantType : uint32_t {
  kInvalidTexture,
  kInvalidVertex,
  kTexture,
  kVertex,
};

constexpr uint32_t kTextureFetchConstantCount = 32;
constexpr uint32_t kVertexFetchConstantCount = 3 * kTextureFetchConstantCount;

union alignas(uint32_t) xe_gpu_vertex_fetch_t {
  struct {
    uint32_t dword_0;
    uint32_t dword_1;
  };
  struct {
    FetchConstantType type : 2;
    uint32_t address : 30;

    Endian endian : 2;
    uint32_t size : 24;
    uint32_t _pad_1_26 : 6;
  };
};
static_assert_size(xe_gpu_vertex_fetch_t, sizeof(uint32_t) * 2);

constexpr uint32_t kTextureSubresourceAlignmentBytesLog2 = 12;
constexpr uint32_t kTextureSubresourceAlignmentBytes = 1 << kTextureSubresourceAlignmentBytesLog2;

constexpr uint32_t kTexture1DMaxWidthLog2 = 24;
constexpr uint32_t kTexture1DMaxWidth = 1 << kTexture1DMaxWidthLog2;

constexpr uint32_t kTexture1DWideMaxRows = 128;
constexpr uint32_t kTexture2DCubeMaxWidthHeightLog2 = 13;
constexpr uint32_t kTexture2DCubeMaxWidthHeight = 1 << kTexture2DCubeMaxWidthHeightLog2;
constexpr uint32_t kTexture2DMaxStackDepthLog2 = 6;
constexpr uint32_t kTexture2DMaxStackDepth = 1 << kTexture2DMaxStackDepthLog2;
constexpr uint32_t kTexture3DMaxWidthHeightLog2 = 11;
constexpr uint32_t kTexture3DMaxWidthHeight = 1 << kTexture3DMaxWidthHeightLog2;
constexpr uint32_t kTexture3DMaxDepthLog2 = 10;
constexpr uint32_t kTexture3DMaxDepth = 1 << kTexture3DMaxDepthLog2;

constexpr uint32_t kTextureMaxMips =
    std::max(kTexture2DCubeMaxWidthHeightLog2, kTexture3DMaxWidthHeightLog2) + 1;

constexpr uint32_t kTextureTileWidthHeightLog2 = 5;
constexpr uint32_t kTextureTileWidthHeight = 1 << kTextureTileWidthHeightLog2;

constexpr uint32_t kTextureTileDepthLog2 = 2;
constexpr uint32_t kTextureTileDepth = 1 << kTextureTileDepthLog2;

constexpr uint32_t GetTextureTiledXBaseGranularityLog2(bool is_3d, uint32_t bytes_per_block_log2) {
  return 7 - std::min(UINT32_C(2), bytes_per_block_log2 + uint32_t(is_3d));
}
constexpr uint32_t GetTextureTiledYBaseGranularityLog2(bool is_3d, uint32_t bytes_per_block_log2) {
  return is_3d ? 5 : (7 - std::min(UINT32_C(2), bytes_per_block_log2));
}
constexpr uint32_t kTextureTiledZBaseGranularityLog2 = 3;
constexpr uint32_t kTextureTiledZBaseGranularity = 1 << kTextureTiledZBaseGranularityLog2;

constexpr uint32_t kTextureLinearRowAlignmentBytesLog2 = 8;
constexpr uint32_t kTextureLinearRowAlignmentBytes = 1 << kTextureLinearRowAlignmentBytesLog2;

union alignas(uint32_t) xe_gpu_texture_fetch_t {
  struct {
    uint32_t dword_0;
    uint32_t dword_1;
    uint32_t dword_2;
    uint32_t dword_3;
    uint32_t dword_4;
    uint32_t dword_5;
  };
  struct {
    FetchConstantType type : 2;

    TextureSign sign_x : 2;
    TextureSign sign_y : 2;
    TextureSign sign_z : 2;
    TextureSign sign_w : 2;
    ClampMode clamp_x : 3;
    ClampMode clamp_y : 3;
    ClampMode clamp_z : 3;
    uint32_t _pad_0_19 : 3;

    uint32_t pitch : 9;
    uint32_t tiled : 1;

    TextureFormat format : 6;
    Endian endianness : 2;
    uint32_t request_size : 2;
    uint32_t stacked : 1;
    uint32_t nearest_clamp_policy : 1;
    uint32_t base_address : 20;

    union {
      struct {
        uint32_t width : 24;
        uint32_t _pad_size_1d : 8;
      } size_1d;
      struct {
        uint32_t width : 13;
        uint32_t height : 13;

        uint32_t stack_depth : 6;
      } size_2d;
      struct {
        uint32_t width : 11;
        uint32_t height : 11;
        uint32_t depth : 10;
      } size_3d;
    };

    uint32_t num_format : 1;

    uint32_t swizzle : 12;
    int32_t exp_adjust : 6;
    TextureFilter mag_filter : 2;
    TextureFilter min_filter : 2;
    TextureFilter mip_filter : 2;
    AnisoFilter aniso_filter : 3;
    ArbitraryFilter arbitrary_filter : 3;
    uint32_t border_size : 1;

    uint32_t vol_mag_filter : 1;
    uint32_t vol_min_filter : 1;
    uint32_t mip_min_level : 4;
    uint32_t mip_max_level : 4;
    uint32_t mag_aniso_walk : 1;
    uint32_t min_aniso_walk : 1;

    int32_t lod_bias : 10;

    int32_t grad_exp_adjust_h : 5;
    int32_t grad_exp_adjust_v : 5;

    BorderColor border_color : 2;
    uint32_t force_bc_w_to_max : 1;

    uint32_t tri_clamp : 2;
    int32_t aniso_bias : 4;
    DataDimension dimension : 2;
    uint32_t packed_mips : 1;
    uint32_t mip_address : 20;
  };
};
static_assert_size(xe_gpu_texture_fetch_t, sizeof(uint32_t) * 6);

union alignas(uint32_t) xe_gpu_fetch_group_t {
  struct {
    uint32_t dword_0;
    uint32_t dword_1;
    uint32_t dword_2;
    uint32_t dword_3;
    uint32_t dword_4;
    uint32_t dword_5;
  };
  xe_gpu_texture_fetch_t texture_fetch;
  struct {
    xe_gpu_vertex_fetch_t vertex_fetch_0;
    xe_gpu_vertex_fetch_t vertex_fetch_1;
    xe_gpu_vertex_fetch_t vertex_fetch_2;
  };
  struct {
    uint32_t type_0 : 2;
    uint32_t data_0_a : 30;
    uint32_t data_0_b : 32;
    uint32_t type_1 : 2;
    uint32_t data_1_a : 30;
    uint32_t data_1_b : 32;
    uint32_t type_2 : 2;
    uint32_t data_2_a : 30;
    uint32_t data_2_b : 32;
  };
};
static_assert_size(xe_gpu_fetch_group_t, sizeof(uint32_t) * 6);

union alignas(uint32_t) xe_gpu_memexport_stream_t {
  struct {
    uint32_t dword_0;
    uint32_t dword_1;
    uint32_t dword_2;
    uint32_t dword_3;
  };
  struct {
    uint32_t base_address : 30;
    uint32_t const_0x1 : 2;

    uint32_t const_0x4b000000;

    Endian128 endianness : 3;
    uint32_t unused_0 : 5;
    ColorFormat format : 6;
    uint32_t unused_1 : 2;
    SurfaceNumberFormat num_format : 3;
    uint32_t red_blue_swap : 1;
    uint32_t const_0x4b0 : 12;

    uint32_t index_count : 23;
    uint32_t const_0x96 : 9;
  };
};
static_assert_size(xe_gpu_memexport_stream_t, sizeof(uint32_t) * 4);

struct alignas(uint32_t) xe_gpu_depth_sample_counts {
  le<uint32_t> Total_A;
  le<uint32_t> Total_B;
  le<uint32_t> ZFail_A;
  le<uint32_t> ZFail_B;
  le<uint32_t> ZPass_A;
  le<uint32_t> ZPass_B;
  le<uint32_t> StencilFail_A;
  le<uint32_t> StencilFail_B;
};
static_assert_size(xe_gpu_depth_sample_counts, sizeof(uint32_t) * 8);

enum Event {
  VS_DEALLOC = 0,
  PS_DEALLOC = 1,
  VS_DONE_TS = 2,
  PS_DONE_TS = 3,
  CACHE_FLUSH_TS = 4,
  CONTEXT_DONE = 5,
  CACHE_FLUSH = 6,
  VIZQUERY_START = 7,
  VIZQUERY_END = 8,
  SC_WAIT_WC = 9,
  MPASS_PS_CP_REFETCH = 10,
  MPASS_PS_RST_START = 11,
  MPASS_PS_INCR_START = 12,
  RST_PIX_CNT = 13,
  RST_VTX_CNT = 14,
  TILE_FLUSH = 15,
  CACHE_FLUSH_AND_INV_TS_EVENT = 20,
  ZPASS_DONE = 21,
  CACHE_FLUSH_AND_INV_EVENT = 22,
  PERFCOUNTER_START = 23,
  PERFCOUNTER_STOP = 24,
  SCREEN_EXT_INIT = 25,
  SCREEN_EXT_RPT = 26,
  VS_FETCH_DONE_TS = 27,
};

// clang-format off
enum Type3Opcode {
  PM4_ME_INIT               = 0x48,

  PM4_NOP                   = 0x10,

  PM4_INDIRECT_BUFFER       = 0x3f,
  PM4_INDIRECT_BUFFER_PFD   = 0x37,

  PM4_WAIT_FOR_IDLE         = 0x26,
  PM4_WAIT_REG_MEM          = 0x3c,
  PM4_WAIT_REG_EQ           = 0x52,
  PM4_WAIT_REG_GTE          = 0x53,
  PM4_WAIT_UNTIL_READ       = 0x5c,
  PM4_WAIT_IB_PFD_COMPLETE  = 0x5d,

  PM4_REG_RMW               = 0x21,
  PM4_REG_TO_MEM            = 0x3e,
  PM4_MEM_WRITE             = 0x3d,
  PM4_MEM_WRITE_CNTR        = 0x4f,
  PM4_COND_EXEC             = 0x44,
  PM4_COND_WRITE            = 0x45,

  PM4_EVENT_WRITE           = 0x46,
  PM4_EVENT_WRITE_SHD       = 0x58,
  PM4_EVENT_WRITE_CFL       = 0x59,
  PM4_EVENT_WRITE_EXT       = 0x5a,
  PM4_EVENT_WRITE_ZPD       = 0x5b,

  PM4_DRAW_INDX             = 0x22,
  PM4_DRAW_INDX_2           = 0x36,
  PM4_DRAW_INDX_BIN         = 0x34,
  PM4_DRAW_INDX_2_BIN       = 0x35,

  PM4_VIZ_QUERY             = 0x23,
  PM4_SET_STATE             = 0x25,
  PM4_SET_CONSTANT          = 0x2d,
  PM4_SET_CONSTANT2         = 0x55,
  PM4_SET_SHADER_CONSTANTS  = 0x56,
  PM4_LOAD_ALU_CONSTANT     = 0x2f,
  PM4_IM_LOAD               = 0x27,
  PM4_IM_LOAD_IMMEDIATE     = 0x2b,
  PM4_LOAD_CONSTANT_CONTEXT = 0x2e,
  PM4_INVALIDATE_STATE      = 0x3b,

  PM4_SET_SHADER_BASES      = 0x4A,
  PM4_SET_BIN_BASE_OFFSET   = 0x4B,
  PM4_SET_BIN_MASK          = 0x50,
  PM4_SET_BIN_SELECT        = 0x51,

  PM4_CONTEXT_UPDATE        = 0x5e,
  PM4_INTERRUPT             = 0x54,

  PM4_XE_SWAP               = 0x64,

  PM4_IM_STORE              = 0x2c,



  PM4_SET_BIN_MASK_LO       = 0x60,
  PM4_SET_BIN_MASK_HI       = 0x61,
  PM4_SET_BIN_SELECT_LO     = 0x62,
  PM4_SET_BIN_SELECT_HI     = 0x63,
};
// clang-format on

inline uint32_t MakePacketType0(uint16_t index, uint16_t count, bool one_reg = false) {
  assert(index <= 0x7FFF);
  assert(count >= 1 && count <= 0x4000);
  return (0u << 30) | (((count - 1) & 0x3FFF) << 16) | (index & 0x7FFF);
}

inline uint32_t MakePacketType1(uint16_t index_1, uint16_t index_2) {
  assert(index_1 <= 0x7FF);
  assert(index_2 <= 0x7FF);
  return (1u << 30) | ((index_2 & 0x7FF) << 11) | (index_1 & 0x7FF);
}

constexpr inline uint32_t MakePacketType2() {
  return (2u << 30);
}

inline uint32_t MakePacketType3(Type3Opcode opcode, uint16_t count, bool predicate = false) {
  assert(opcode <= 0x7F);
  assert(count >= 1 && count <= 0x4000);
  return (3u << 30) | (((count - 1) & 0x3FFF) << 16) | ((opcode & 0x7F) << 8) | (predicate ? 1 : 0);
}

}
}

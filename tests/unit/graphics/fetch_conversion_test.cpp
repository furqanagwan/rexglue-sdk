/**
 * @file        fetch_conversion_test.cpp
 * @brief       Packing of the fixed-format fetch conversion (RG-GDK-045)
 *
 * texture_util::GetIntegerScaleBits tells the translated fetch how to give the
 * guest its own result from a host sample: the integer range for num_format 1,
 * 16 fractional bits and the 4 to 7 bit point-sample conversion for num_format
 * 0, and the point sampled flag that snaps coordinates (xenia-canary #1072,
 * #1137, #1177, #1250).
 */

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/xenos.h>

namespace {

namespace xenos = rex::graphics::xenos;
using rex::graphics::texture_util::GetIntegerScaleBits;

constexpr uint32_t kNormalized = UINT32_C(1) << 24;
constexpr uint32_t kPointSampled = UINT32_C(1) << 26;

// X, Y, Z, W from components 0, 1, 2, 3.
constexpr uint32_t kIdentitySwizzle = 0 | (1 << 3) | (2 << 6) | (3 << 9);

constexpr uint32_t Component(uint32_t i, uint32_t width, xenos::TextureSign sign) {
  return ((uint32_t(sign) << 4) | (width ? width - 1 : 0)) << (i * 6);
}

uint8_t Signs(xenos::TextureSign x, xenos::TextureSign y, xenos::TextureSign z,
              xenos::TextureSign w) {
  return uint8_t(uint32_t(x) | (uint32_t(y) << 2) | (uint32_t(z) << 4) | (uint32_t(w) << 6));
}

xenos::xe_gpu_texture_fetch_t Fetch(xenos::TextureFormat format, uint32_t num_format, bool point,
                                    uint32_t swizzle = kIdentitySwizzle) {
  xenos::xe_gpu_texture_fetch_t fetch{};
  fetch.format = format;
  fetch.num_format = num_format;
  fetch.swizzle = swizzle;
  const auto filter = point ? xenos::TextureFilter::kPoint : xenos::TextureFilter::kLinear;
  fetch.mag_filter = filter;
  fetch.min_filter = filter;
  fetch.mip_filter = point ? xenos::TextureFilter::kPoint : xenos::TextureFilter::kLinear;
  fetch.aniso_filter = xenos::AnisoFilter::kDisabled;
  return fetch;
}

constexpr auto kU = xenos::TextureSign::kUnsigned;
constexpr auto kS = xenos::TextureSign::kSigned;
constexpr auto kGamma = xenos::TextureSign::kGamma;

}  // namespace

TEST_CASE("Integer num_format carries every component's width and sign", "[graphics][fetch]") {
  // 4_4_4_4 read as integers [0, 15]; linear filtering, so no point flag.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 1, false),
                            Signs(kU, kU, kU, kU)) ==
        (Component(0, 4, kU) | Component(1, 4, kU) | Component(2, 4, kU) | Component(3, 4, kU)));
  // 1_5_5_5 (components 5, 5, 5, 1) with a signed X.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_1_5_5_5, 1, false),
                            Signs(kS, kU, kU, kU)) ==
        (Component(0, 5, kS) | Component(1, 5, kU) | Component(2, 5, kU) | Component(3, 1, kU)));
}

TEST_CASE("Normalized fetches round to 16 bits, and point fetches of 4 to 7 bits carry the width",
          "[graphics][fetch]") {
  // Filtered 4_4_4_4: rounding only.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 0, false),
                            Signs(kU, kU, kU, kU)) == kNormalized);
  // Point sampled 4_4_4_4: the guest's n * (2^w + 1) / 2^(2w) needs the width.
  CHECK(
      GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 0, true), Signs(kU, kU, kU, kU)) ==
      (kPointSampled | kNormalized | Component(0, 4, kU) | Component(1, 4, kU) |
       Component(2, 4, kU) | Component(3, 4, kU)));
  // Point sampled 8_8_8_8: 8 bits is outside 4 to 7, so no widths.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 0, true),
                            Signs(kU, kU, kU, kU)) == (kPointSampled | kNormalized));
}

TEST_CASE("The swizzle picks each output's source component", "[graphics][fetch]") {
  // 8 has one component; Y, Z and W read past it and take the last stored
  // one. Constant 0 and 1 outputs carry nothing.
  const uint32_t swizzle = 1 | (2 << 3) | (xenos::XE_GPU_TEXTURE_SWIZZLE_0 << 6) | (5 << 9);
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8, 1, false, swizzle),
                            Signs(kU, kU, kU, kU)) == (Component(0, 8, kU) | Component(1, 8, kU)));
}

TEST_CASE("Gamma components and non-fixed formats are left alone", "[graphics][fetch]") {
  // Gamma with integer num_format: nothing for that component.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 1, false),
                            Signs(kGamma, kU, kU, kU)) ==
        (Component(1, 8, kU) | Component(2, 8, kU) | Component(3, 8, kU)));
  // Gamma with normalized num_format: the sign without a width.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 0, false),
                            Signs(kGamma, kU, kU, kU)) == (kNormalized | (uint32_t(kGamma) << 4)));
  // A float format is not sampled normalized; only the point flag remains.
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_16_FLOAT, 1, true),
                            Signs(kU, kU, kU, kU)) == kPointSampled);
}

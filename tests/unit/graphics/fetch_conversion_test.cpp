

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/pipeline/texture/util.h>
#include <rex/graphics/xenos.h>

namespace {

namespace xenos = rex::graphics::xenos;
using rex::graphics::texture_util::GetIntegerScaleBits;

constexpr uint32_t kNormalized = UINT32_C(1) << 24;
constexpr uint32_t kPointSampled = UINT32_C(1) << 26;

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

}

TEST_CASE("Integer num_format carries every component's width and sign", "[graphics][fetch]") {
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 1, false),
                            Signs(kU, kU, kU, kU)) ==
        (Component(0, 4, kU) | Component(1, 4, kU) | Component(2, 4, kU) | Component(3, 4, kU)));

  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_1_5_5_5, 1, false),
                            Signs(kS, kU, kU, kU)) ==
        (Component(0, 5, kS) | Component(1, 5, kU) | Component(2, 5, kU) | Component(3, 1, kU)));
}

TEST_CASE("Normalized fetches round to 16 bits, and point fetches of 4 to 7 bits carry the width",
          "[graphics][fetch]") {
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 0, false),
                            Signs(kU, kU, kU, kU)) == kNormalized);

  CHECK(
      GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_4_4_4_4, 0, true), Signs(kU, kU, kU, kU)) ==
      (kPointSampled | kNormalized | Component(0, 4, kU) | Component(1, 4, kU) |
       Component(2, 4, kU) | Component(3, 4, kU)));

  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 0, true),
                            Signs(kU, kU, kU, kU)) == (kPointSampled | kNormalized));
}

TEST_CASE("The swizzle picks each output's source component", "[graphics][fetch]") {
  const uint32_t swizzle = 1 | (2 << 3) | (xenos::XE_GPU_TEXTURE_SWIZZLE_0 << 6) | (5 << 9);
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8, 1, false, swizzle),
                            Signs(kU, kU, kU, kU)) == (Component(0, 8, kU) | Component(1, 8, kU)));
}

TEST_CASE("Gamma components and non-fixed formats are left alone", "[graphics][fetch]") {
  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 1, false),
                            Signs(kGamma, kU, kU, kU)) ==
        (Component(1, 8, kU) | Component(2, 8, kU) | Component(3, 8, kU)));

  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_8_8_8_8, 0, false),
                            Signs(kGamma, kU, kU, kU)) == (kNormalized | (uint32_t(kGamma) << 4)));

  CHECK(GetIntegerScaleBits(Fetch(xenos::TextureFormat::k_16_FLOAT, 1, true),
                            Signs(kU, kU, kU, kU)) == kPointSampled);
}

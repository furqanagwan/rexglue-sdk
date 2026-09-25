/**
 * @file        alu_fixture_test.cpp
 * @brief       Scalar approximation semantics of translated shaders (RG-GDK-012)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <bit>
#include <cfloat>
#include <cmath>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <rex/graphics/registers.h>
#include <rex/graphics/xenos.h>

#include "gpu_fixture.h"
#include "guest_draw.h"

namespace {

using namespace rex::graphics;  // NOLINT: XE_GPU_REG_* register indices.
namespace reg = rex::graphics::reg;
namespace xenos = rex::graphics::xenos;
using rex::testing::GpuFixture;
using namespace rex::testing::guest_draw;  // NOLINT

// Scalar opcodes (ucode::AluScalarOpcode).
enum class Op : uint32_t {
  kExp = 14,
  kLogc = 15,
  kLog = 16,
  kRcpc = 17,
  kRcpf = 18,
  kRcp = 19,
  kRsqc = 20,
  kRsqf = 21,
  kRsq = 22,
  kSqrt = 40,
};

const char* OpName(Op op) {
  switch (op) {
    case Op::kExp:
      return "exp";
    case Op::kLogc:
      return "logc";
    case Op::kLog:
      return "log";
    case Op::kRcpc:
      return "rcpc";
    case Op::kRcpf:
      return "rcpf";
    case Op::kRcp:
      return "rcp";
    case Op::kRsqc:
      return "rsqc";
    case Op::kRsqf:
      return "rsqf";
    case Op::kRsq:
      return "rsq";
    case Op::kSqrt:
      return "sqrt";
  }
  return "?";
}

// Scalar operation on r1.x exported to eM0.x, the vector operation writing
// nothing. For one-operand scalar operations the operand is src3's W, so the
// swizzle selects X there.
std::vector<uint32_t> ScalarExport(Op op) {
  constexpr uint32_t kSrc3SwizzleXAsW = 1 << 6;
  return {33u | (1u << 15) | (0x1u << 20) | (uint32_t(op) << 26), kSrc3SwizzleXAsW,
          1u | (1u << 8) | (1u << 16) | (kAluMax << 24) | (7u << 29)};
}

// vfetch r1 (the input in X); oPos = r1; eA from c2 by the vertex index; eM0.x
// = op(r1.x). One exported float per vertex.
std::vector<uint32_t> ScalarOpVertexShader(Op op) {
  std::vector<uint32_t> ucode;
  PackCf(ucode, Exec(3, 1, 1, false), Alloc(ucode::AllocType::kVsPosition));
  PackCf(ucode, Exec(4, 1, 0, false), Alloc(ucode::AllocType::kMemory));
  PackCf(ucode, Exec(5, 2, 0, true), Cf{0, 0});
  ucode.insert(ucode.end(), {0x00081000, 0x00260688, 0x00000004});
  auto pos = AluExport(62, kAluMax, 1, 1, 0, 0, true, true, false);
  ucode.insert(ucode.end(), pos.begin(), pos.end());
  auto address = AluExport(32, kAluMad, 0, 1, 2, kSwizzleXXXX, true, false, false);
  ucode.insert(ucode.end(), address.begin(), address.end());
  auto data = ScalarExport(op);
  ucode.insert(ucode.end(), data.begin(), data.end());
  return ucode;
}

float F(uint32_t bits) {
  return std::bit_cast<float>(bits);
}

// Inputs: signed zeros, infinities, a NaN, negatives, and finite values across
// the exponent range (no denormals - the host flushes them).
const std::vector<float> kInputs = {
    0.0f,  -0.0f,         INFINITY, -INFINITY, F(0x7FC00000), -1.0f,   -4.0f,    1.0f,    2.0f,
    0.5f,  3.0f,          10.0f,    0.1f,      1.0e-30f,      1.0e30f, 123.456f, -2.5f,   0.75f,
    -0.3f, F(0x3F812345), 7.0e-20f, FLT_MAX,   FLT_MIN,       1.5f,    100.0f,   -100.0f, 64.0f,
};

// Runs `op` on every input through a translated vertex shader and returns the
// exported results, or an empty vector if the draw didn't complete.
std::vector<float> RunScalarOp(GpuFixture& fixture, Op op) {
  uint32_t count = uint32_t(kInputs.size());
  // Triangle lists need a multiple of three vertices; pad with 1.0.
  uint32_t vertex_count = (count + 2) / 3 * 3;
  std::vector<uint32_t> vertices;
  for (uint32_t i = 0; i < vertex_count; ++i) {
    float input = i < count ? kInputs[i] : 1.0f;
    vertices.insert(vertices.end(),
                    {std::bit_cast<uint32_t>(input), 0, 0, std::bit_cast<uint32_t>(1.0f)});
  }
  uint32_t vertex_buffer = fixture.AllocPhysical(0x1000);
  fixture.WriteDwords(vertex_buffer, vertices);
  uint32_t results = fixture.AllocPhysical(0x1000);
  fixture.WriteDwords(results, std::vector<uint32_t>(vertex_count, 0xDEADBEEF));

  DrawOptions options;
  options.color_mask = 0;
  SetupDraw(fixture, {xenos::MsaaSamples::k1X, 64}, 32, 32, options);
  fixture.Submit(LoadShader(xenos::ShaderType::kVertex, ScalarOpVertexShader(op)));
  xenos::xe_gpu_vertex_fetch_t fetch = {};
  fetch.type = xenos::FetchConstantType::kVertex;
  fetch.address = vertex_buffer >> 2;
  fetch.endian = xenos::Endian::k8in32;
  fetch.size = vertex_count * 4;
  fixture.Submit(GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_FETCH_00_0,
                                          {fetch.dword_0, fetch.dword_1}));
  xenos::xe_gpu_memexport_stream_t stream = {};
  stream.base_address = results >> 2;
  stream.const_0x1 = 0x1;
  stream.const_0x4b000000 = 0x4B000000;
  stream.endianness = xenos::Endian128::k8in32;
  stream.format = xenos::ColorFormat::k_32_FLOAT;
  stream.num_format = xenos::SurfaceNumberFormat::kFloat;
  stream.const_0x4b0 = 0x4B0;
  stream.index_count = vertex_count;
  stream.const_0x96 = 0x96;
  fixture.Submit(
      GpuFixture::SetRegisters(XE_GPU_REG_SHADER_CONSTANT_000_X + 4,
                               {std::bit_cast<uint32_t>(0.0f), std::bit_cast<uint32_t>(1.0f), 0, 0,
                                stream.dword_0, stream.dword_1, stream.dword_2, stream.dword_3}));
  reg::VGT_DRAW_INITIATOR initiator = {};
  initiator.prim_type = xenos::PrimitiveType::kTriangleList;
  initiator.source_select = xenos::SourceSelect::kAutoIndex;
  initiator.num_indices = vertex_count;
  fixture.Submit({xenos::MakePacketType3(xenos::PM4_DRAW_INDX_2, 1), initiator.value});
  if (!fixture.Flush()) {
    return {};
  }
  std::vector<float> out;
  for (uint32_t i = 0; i < count; ++i) {
    out.push_back(F(fixture.ReadDword(results + i * 4)));
  }
  return out;
}

// The documented special cases, and the double-precision value for finite
// results. Clamped variants (C) turn infinite results into +-FLT_MAX, flushed
// ones (F) into signed zero; LOGC turns -Inf into -FLT_MAX.
double Reference(Op op, float input) {
  double x = input;
  double r = 0.0;
  switch (op) {
    case Op::kExp:
      r = std::exp2(x);
      break;
    case Op::kLog:
    case Op::kLogc:
      r = std::log2(x);
      break;
    case Op::kRcp:
    case Op::kRcpc:
    case Op::kRcpf:
      r = 1.0 / x;
      break;
    case Op::kRsq:
    case Op::kRsqc:
    case Op::kRsqf:
      r = 1.0 / std::sqrt(x);
      break;
    case Op::kSqrt:
      r = std::sqrt(x);
      break;
  }
  // Single precision range.
  if (std::isfinite(r) && std::abs(r) > double(FLT_MAX) * (1.0 + 1.0 / (1 << 22))) {
    r = std::copysign(INFINITY, r);
  }
  bool infinite = std::isinf(r);
  switch (op) {
    case Op::kLogc:
      if (r == -INFINITY) {
        r = -FLT_MAX;
      }
      break;
    case Op::kRcpc:
    case Op::kRsqc:
      if (infinite) {
        r = std::copysign(FLT_MAX, r);
      }
      break;
    case Op::kRcpf:
    case Op::kRsqf:
      if (infinite) {
        r = std::copysign(0.0, r);
      }
      break;
    default:
      break;
  }
  return r;
}

// Mismatch description, or empty if `result` meets the reference: bit-exact
// for special values, within 2^-20 relative (or 2^-20 absolute near zero) for
// finite ones, which covers the host's documented approximation error and the
// optional 21-bit reduction.
std::string Check(Op op, float input, float result) {
  double ref = Reference(op, input);
  if (std::isnan(ref)) {
    return std::isnan(result) ? "" : "expected NaN";
  }
  if (std::isinf(ref) || ref == 0.0 || std::abs(ref) == double(FLT_MAX)) {
    return std::bit_cast<uint32_t>(result) == std::bit_cast<uint32_t>(float(ref))
               ? ""
               : "expected exactly " + std::to_string(ref);
  }
  if (!std::isfinite(result)) {
    return "expected finite " + std::to_string(ref);
  }
  // A denormal result may be flushed to zero by the host float controls.
  if (std::abs(ref) < double(FLT_MIN) && result == 0.0f) {
    return "";
  }
  double error = std::abs(double(result) - ref);
  double tolerance = std::max(std::abs(ref) * std::ldexp(1.0, -20), std::ldexp(1.0, -20));
  return error <= tolerance ? "" : "expected " + std::to_string(ref);
}

}  // namespace

TEST_CASE("Scalar approximations follow the documented special cases and precision", "[gpu][alu]") {
  bool rounding = GENERATE(false, true);
  std::string error;
  auto fixture = GpuFixture::Create(
      &error, {{"async_shader_compilation", "false"},
               {"readback_memexport", "true"},
               {"readback_memexport_fast", "false"},
               {"gpu_scalar_approximation_rounding", rounding ? "true" : "false"}});
  if (!fixture) {
    SKIP("GPU fixture host unavailable: " << error);
  }
  INFO(fixture->Metadata());
  INFO("gpu_scalar_approximation_rounding " << rounding);
  for (Op op : {Op::kExp, Op::kLog, Op::kLogc, Op::kRcp, Op::kRcpc, Op::kRcpf, Op::kRsq, Op::kRsqc,
                Op::kRsqf, Op::kSqrt}) {
    std::vector<float> results = RunScalarOp(*fixture, op);
    REQUIRE(results.size() == kInputs.size());
    for (size_t i = 0; i < kInputs.size(); ++i) {
      std::string mismatch = Check(op, kInputs[i], results[i]);
      INFO(OpName(op) << "(" << kInputs[i] << " / 0x" << std::hex
                      << std::bit_cast<uint32_t>(kInputs[i]) << ") = " << std::dec << results[i]
                      << " / 0x" << std::hex << std::bit_cast<uint32_t>(results[i]) << std::dec
                      << ": " << mismatch);
      CHECK(mismatch.empty());
      if (rounding && std::isfinite(results[i]) && std::abs(results[i]) != FLT_MAX) {
        // The opt-in reduction leaves 21 mantissa bits. The clamped variants
        // turn infinity into exactly +-FLT_MAX after it.
        CHECK((std::bit_cast<uint32_t>(results[i]) & 3u) == 0u);
      }
    }
  }
}

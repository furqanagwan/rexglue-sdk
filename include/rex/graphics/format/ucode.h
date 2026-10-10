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

#include <cstdint>

#include <rex/assert.h>
#include <rex/graphics/xenos.h>
#include <rex/math.h>
#include <rex/platform.h>

/*
 * Copyright (c) 2012 Rob Clark <robdclark@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

namespace rex::graphics::ucode {

enum class ControlFlowOpcode : uint32_t {

  kNop = 0,

  kExec = 1,

  kExecEnd = 2,

  kCondExec = 3,

  kCondExecEnd = 4,

  kCondExecPred = 5,

  kCondExecPredEnd = 6,

  kLoopStart = 7,

  kLoopEnd = 8,

  kCondCall = 9,

  kReturn = 10,

  kCondJmp = 11,

  kAlloc = 12,

  kCondExecPredClean = 13,

  kCondExecPredCleanEnd = 14,

  kMarkVsFetchDone = 15,
};

constexpr bool IsControlFlowOpcodeExec(ControlFlowOpcode opcode) {
  return opcode == ControlFlowOpcode::kExec || opcode == ControlFlowOpcode::kExecEnd ||
         opcode == ControlFlowOpcode::kCondExec || opcode == ControlFlowOpcode::kCondExecEnd ||
         opcode == ControlFlowOpcode::kCondExecPred ||
         opcode == ControlFlowOpcode::kCondExecPredEnd ||
         opcode == ControlFlowOpcode::kCondExecPredClean ||
         opcode == ControlFlowOpcode::kCondExecPredCleanEnd;
}

constexpr bool DoesControlFlowOpcodeEndShader(ControlFlowOpcode opcode) {
  return opcode == ControlFlowOpcode::kExecEnd || opcode == ControlFlowOpcode::kCondExecEnd ||
         opcode == ControlFlowOpcode::kCondExecPredEnd ||
         opcode == ControlFlowOpcode::kCondExecPredCleanEnd;
}

constexpr bool DoesControlFlowCondExecHaveCleanPredicate(ControlFlowOpcode opcode) {
  return opcode == ControlFlowOpcode::kCondExecPredClean ||
         opcode == ControlFlowOpcode::kCondExecPredCleanEnd;
}

enum class AddressingMode : uint32_t {

  kRelative = 0,

  kAbsolute = 1,
};

enum class AllocType : uint32_t {

  kNone = 0,

  kVsPosition = 1,

  kVsInterpolators = 2,

  kPsColors = 2,

  kMemory = 3,
};

struct ControlFlowExecInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  uint32_t count() const { return count_; }

  uint32_t sequence() const { return sequence_; }
  bool is_predicate_clean() const { return is_predicate_clean_ == 1; }

  bool is_yield() const { return is_yield_ == 1; }

 private:
  uint32_t address_ : 12;
  uint32_t count_ : 3;
  uint32_t is_yield_ : 1;
  uint32_t sequence_ : 12;
  [[maybe_unused]] uint32_t vc_hi_ : 4;

  [[maybe_unused]] uint32_t vc_lo_ : 2;
  uint32_t : 7;

  uint32_t is_predicate_clean_ : 1;
  uint32_t : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowExecInstruction, sizeof(uint32_t) * 2);

struct ControlFlowCondExecInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  uint32_t count() const { return count_; }

  uint32_t sequence() const { return sequence_; }

  uint32_t bool_address() const { return bool_address_; }

  bool condition() const { return condition_ == 1; }

  bool is_yield() const { return is_yield_ == 1; }

 private:
  uint32_t address_ : 12;
  uint32_t count_ : 3;
  uint32_t is_yield_ : 1;
  uint32_t sequence_ : 12;
  [[maybe_unused]] uint32_t vc_hi_ : 4;

  [[maybe_unused]] uint32_t vc_lo_ : 2;
  uint32_t bool_address_ : 8;
  uint32_t condition_ : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowCondExecInstruction, sizeof(uint32_t) * 2);

struct ControlFlowCondExecPredInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  uint32_t count() const { return count_; }

  uint32_t sequence() const { return sequence_; }
  bool is_predicate_clean() const { return is_predicate_clean_ == 1; }

  bool condition() const { return condition_ == 1; }

  bool is_yield() const { return is_yield_ == 1; }

 private:
  uint32_t address_ : 12;
  uint32_t count_ : 3;
  uint32_t is_yield_ : 1;
  uint32_t sequence_ : 12;
  [[maybe_unused]] uint32_t vc_hi_ : 4;

  [[maybe_unused]] uint32_t vc_lo_ : 2;
  uint32_t : 7;
  uint32_t is_predicate_clean_ : 1;
  uint32_t condition_ : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowCondExecPredInstruction, sizeof(uint32_t) * 2);

struct ControlFlowLoopStartInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  bool is_repeat() const { return is_repeat_; }

  uint32_t loop_id() const { return loop_id_; }

 private:
  uint32_t address_ : 13;
  uint32_t is_repeat_ : 1;
  uint32_t : 2;
  uint32_t loop_id_ : 5;
  uint32_t : 11;

  uint32_t : 11;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowLoopStartInstruction, sizeof(uint32_t) * 2);

struct ControlFlowLoopEndInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  uint32_t loop_id() const { return loop_id_; }

  bool is_predicated_break() const { return is_predicated_break_; }

  bool condition() const { return condition_ == 1; }

 private:
  uint32_t address_ : 13;
  uint32_t : 3;
  uint32_t loop_id_ : 5;
  uint32_t is_predicated_break_ : 1;
  uint32_t : 10;

  uint32_t : 10;
  uint32_t condition_ : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowLoopEndInstruction, sizeof(uint32_t) * 2);

struct ControlFlowCondCallInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  bool is_unconditional() const { return is_unconditional_; }

  bool is_predicated() const { return is_predicated_; }

  uint32_t bool_address() const { return bool_address_; }

  bool condition() const { return condition_ == 1; }

 private:
  uint32_t address_ : 13;
  uint32_t is_unconditional_ : 1;
  uint32_t is_predicated_ : 1;
  uint32_t : 17;

  uint32_t : 2;
  uint32_t bool_address_ : 8;
  uint32_t condition_ : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowCondCallInstruction, sizeof(uint32_t) * 2);

struct ControlFlowReturnInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

 private:
  uint32_t : 32;

  uint32_t : 11;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowReturnInstruction, sizeof(uint32_t) * 2);

struct ControlFlowCondJmpInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }
  AddressingMode addressing_mode() const { return address_mode_; }

  uint32_t address() const { return address_; }

  bool is_unconditional() const { return is_unconditional_; }

  bool is_predicated() const { return is_predicated_; }

  uint32_t bool_address() const { return bool_address_; }

  bool condition() const { return condition_ == 1; }

 private:
  uint32_t address_ : 13;
  uint32_t is_unconditional_ : 1;
  uint32_t is_predicated_ : 1;
  uint32_t : 17;

  uint32_t : 1;
  [[maybe_unused]] uint32_t direction_ : 1;
  uint32_t bool_address_ : 8;
  uint32_t condition_ : 1;
  AddressingMode address_mode_ : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowCondJmpInstruction, sizeof(uint32_t) * 2);

struct ControlFlowAllocInstruction {
  ControlFlowOpcode opcode() const { return opcode_; }

  uint32_t size() const { return size_; }

  AllocType alloc_type() const { return alloc_type_; }

 private:
  uint32_t size_ : 3;
  uint32_t : 29;

  uint32_t : 8;
  uint32_t : 1;
  AllocType alloc_type_ : 2;
  uint32_t : 1;
  ControlFlowOpcode opcode_ : 4;
};
static_assert_size(ControlFlowAllocInstruction, sizeof(uint32_t) * 2);

union ControlFlowInstruction {
  ControlFlowOpcode opcode() const { return opcode_value; }

  ControlFlowExecInstruction exec;
  ControlFlowCondExecInstruction cond_exec;
  ControlFlowCondExecPredInstruction cond_exec_pred;
  ControlFlowLoopStartInstruction loop_start;
  ControlFlowLoopEndInstruction loop_end;
  ControlFlowCondCallInstruction cond_call;
  ControlFlowReturnInstruction ret;
  ControlFlowCondJmpInstruction cond_jmp;
  ControlFlowAllocInstruction alloc;

  struct {
    uint32_t dword_0;
    uint32_t dword_1;
  };
  struct {
    uint32_t unused_0 : 32;
    uint32_t unused_1 : 12;
    ControlFlowOpcode opcode_value : 4;
  };
};
static_assert_size(ControlFlowInstruction, sizeof(uint32_t) * 2);

inline void UnpackControlFlowInstructions(const uint32_t* dwords, ControlFlowInstruction* out_ab) {
  uint32_t dword_0 = dwords[0];
  uint32_t dword_1 = dwords[1];
  uint32_t dword_2 = dwords[2];
  out_ab[0].dword_0 = dword_0;
  out_ab[0].dword_1 = dword_1 & 0xFFFF;
  out_ab[1].dword_0 = (dword_1 >> 16) | (dword_2 << 16);
  out_ab[1].dword_1 = dword_2 >> 16;
}

enum class FetchOpcode : uint32_t {
  kVertexFetch = 0,

  kTextureFetch = 1,

  kGetTextureBorderColorFrac = 16,

  kGetTextureComputedLod = 17,

  kGetTextureGradients = 18,

  kGetTextureWeights = 19,

  kSetTextureLod = 24,

  kSetTextureGradientsHorz = 25,

  kSetTextureGradientsVert = 26,
};

enum class FetchDestinationSwizzle {

  kX = 0,
  kY = 1,
  kZ = 2,
  kW = 3,
  k0 = 4,
  k1 = 5,

  kKeep = 7,
};

constexpr FetchDestinationSwizzle GetFetchDestinationComponentSwizzle(uint32_t swizzle,
                                                                      uint32_t component) {
  return FetchDestinationSwizzle((swizzle >> (3 * component)) & 0b111);
}

struct alignas(uint32_t) VertexFetchInstruction {
  FetchOpcode opcode() const { return data_.opcode_value; }

  bool is_predicated() const { return data_.is_predicated; }

  bool predicate_condition() const { return data_.pred_condition == 1; }

  uint32_t fetch_constant_index() const { return data_.const_index * 3 + data_.const_index_sel; }

  uint32_t dest() const { return data_.dst_reg; }
  uint32_t dest_swizzle() const { return data_.dst_swiz; }
  bool is_dest_relative() const { return data_.dst_reg_am; }

  uint32_t src() const { return data_.src_reg; }
  uint32_t src_swizzle() const { return data_.src_swiz; }
  bool is_src_relative() const { return data_.src_reg_am; }

  uint32_t prefetch_count() const { return data_.prefetch_count; }
  bool is_mini_fetch() const { return data_.is_mini_fetch == 1; }

  xenos::VertexFormat data_format() const { return data_.format; }

  int exp_adjust() const { return data_.exp_adjust; }
  bool is_signed() const { return data_.fomat_comp_all == 1; }
  bool is_normalized() const { return data_.num_format_all == 0; }
  xenos::SignedRepeatingFractionMode signed_rf_mode() const { return data_.signed_rf_mode_all; }

  bool is_index_rounded() const { return data_.is_index_rounded == 1; }

  uint32_t stride() const { return data_.stride; }

  int32_t offset() const { return data_.offset; }

 private:
  struct Data {
    struct {
      FetchOpcode opcode_value : 5;
      uint32_t src_reg : 6;
      uint32_t src_reg_am : 1;
      uint32_t dst_reg : 6;
      uint32_t dst_reg_am : 1;
      uint32_t must_be_one : 1;
      uint32_t const_index : 5;
      uint32_t const_index_sel : 2;

      uint32_t prefetch_count : 3;

      uint32_t src_swiz : 2;
    };
    struct {
      uint32_t dst_swiz : 12;
      uint32_t fomat_comp_all : 1;
      uint32_t num_format_all : 1;
      xenos::SignedRepeatingFractionMode signed_rf_mode_all : 1;
      uint32_t is_index_rounded : 1;
      xenos::VertexFormat format : 6;
      uint32_t reserved2 : 2;
      int32_t exp_adjust : 6;
      uint32_t is_mini_fetch : 1;
      uint32_t is_predicated : 1;
    };
    struct {
      uint32_t stride : 8;
      int32_t offset : 23;
      uint32_t pred_condition : 1;
    };
  };
  Data data_;
};
static_assert_size(VertexFetchInstruction, sizeof(uint32_t) * 3);

struct alignas(uint32_t) TextureFetchInstruction {
  FetchOpcode opcode() const { return data_.opcode_value; }

  bool is_predicated() const { return data_.is_predicated; }

  bool predicate_condition() const { return data_.pred_condition == 1; }

  uint32_t fetch_constant_index() const { return data_.const_index; }

  uint32_t dest() const { return data_.dst_reg; }
  uint32_t dest_swizzle() const { return data_.dst_swiz; }
  bool is_dest_relative() const { return data_.dst_reg_am; }
  uint32_t src() const { return data_.src_reg; }
  uint32_t src_swizzle() const { return data_.src_swiz; }
  bool is_src_relative() const { return data_.src_reg_am; }

  xenos::FetchOpDimension dimension() const { return data_.dimension; }
  bool fetch_valid_only() const { return data_.fetch_valid_only == 1; }
  bool unnormalized_coordinates() const { return data_.tx_coord_denorm == 1; }
  bool has_mag_filter() const { return data_.mag_filter != xenos::TextureFilter::kUseFetchConst; }
  xenos::TextureFilter mag_filter() const { return data_.mag_filter; }
  bool has_min_filter() const { return data_.min_filter != xenos::TextureFilter::kUseFetchConst; }
  xenos::TextureFilter min_filter() const { return data_.min_filter; }
  bool has_mip_filter() const { return data_.mip_filter != xenos::TextureFilter::kUseFetchConst; }
  xenos::TextureFilter mip_filter() const { return data_.mip_filter; }
  bool has_aniso_filter() const { return data_.aniso_filter != xenos::AnisoFilter::kUseFetchConst; }
  xenos::AnisoFilter aniso_filter() const { return data_.aniso_filter; }
  bool has_vol_mag_filter() const {
    return data_.vol_mag_filter != xenos::TextureFilter::kUseFetchConst;
  }
  xenos::TextureFilter vol_mag_filter() const { return data_.vol_mag_filter; }
  bool has_vol_min_filter() const {
    return data_.vol_min_filter != xenos::TextureFilter::kUseFetchConst;
  }
  xenos::TextureFilter vol_min_filter() const { return data_.vol_min_filter; }
  bool use_computed_lod() const { return data_.use_comp_lod == 1; }
  bool use_register_lod() const { return data_.use_reg_lod == 1; }
  bool use_register_gradients() const { return data_.use_reg_gradients == 1; }
  xenos::SampleLocation sample_location() const { return data_.sample_location; }
  float lod_bias() const { return data_.lod_bias * (1.0f / 16.0f); }
  float offset_x() const { return data_.offset_x * 0.5f; }
  float offset_y() const { return data_.offset_y * 0.5f; }
  float offset_z() const { return data_.offset_z * 0.5f; }

 private:
  struct Data {
    struct {
      FetchOpcode opcode_value : 5;
      uint32_t src_reg : 6;
      uint32_t src_reg_am : 1;
      uint32_t dst_reg : 6;
      uint32_t dst_reg_am : 1;
      uint32_t fetch_valid_only : 1;
      uint32_t const_index : 5;
      uint32_t tx_coord_denorm : 1;

      uint32_t src_swiz : 6;
    };
    struct {
      uint32_t dst_swiz : 12;
      xenos::TextureFilter mag_filter : 2;
      xenos::TextureFilter min_filter : 2;
      xenos::TextureFilter mip_filter : 2;
      xenos::AnisoFilter aniso_filter : 3;
      xenos::ArbitraryFilter arbitrary_filter : 3;
      xenos::TextureFilter vol_mag_filter : 2;
      xenos::TextureFilter vol_min_filter : 2;
      uint32_t use_comp_lod : 1;
      uint32_t use_reg_lod : 1;
      uint32_t unk : 1;
      uint32_t is_predicated : 1;
    };
    struct {
      uint32_t use_reg_gradients : 1;
      xenos::SampleLocation sample_location : 1;
      int32_t lod_bias : 7;
      uint32_t unused : 5;
      xenos::FetchOpDimension dimension : 2;
      int32_t offset_x : 5;
      int32_t offset_y : 5;
      int32_t offset_z : 5;
      uint32_t pred_condition : 1;
    };
  };
  Data data_;
};
static_assert_size(TextureFetchInstruction, sizeof(uint32_t) * 3);

union alignas(uint32_t) FetchInstruction {
 public:
  FetchOpcode opcode() const { return data_.opcode_value; }

  bool is_predicated() const { return data_.is_predicated; }

  bool predicate_condition() const { return data_.pred_condition == 1; }

  uint32_t dest() const { return data_.dst_reg; }
  uint32_t dest_swizzle() const { return data_.dst_swiz; }
  bool is_dest_relative() const { return data_.dst_reg_am; }
  uint32_t src() const { return data_.src_reg; }
  bool is_src_relative() const { return data_.src_reg_am; }

  const VertexFetchInstruction& vertex_fetch() const { return vertex_fetch_; }

  const TextureFetchInstruction& texture_fetch() const { return texture_fetch_; }

 private:
  struct Data {
    struct {
      FetchOpcode opcode_value : 5;
      uint32_t src_reg : 6;
      uint32_t src_reg_am : 1;
      uint32_t dst_reg : 6;
      uint32_t dst_reg_am : 1;

      uint32_t : 1;

      uint32_t const_index : 5;

      uint32_t : 7;
    };
    struct {
      uint32_t dst_swiz : 12;

      uint32_t : 19;
      uint32_t is_predicated : 1;
    };
    struct {
      uint32_t : 31;
      uint32_t pred_condition : 1;
    };
  };
  Data data_;
  VertexFetchInstruction vertex_fetch_;
  TextureFetchInstruction texture_fetch_;
};
static_assert_size(FetchInstruction, sizeof(uint32_t) * 3);

enum AluOpChangedState {
  kAluOpChangedStateNone = 0,
  kAluOpChangedStateAddressRegister = 1 << 0,
  kAluOpChangedStatePredicate = 1 << 1,
  kAluOpChangedStatePixelKill = 1 << 2,
};

enum class AluScalarOpcode : uint32_t {

  kAdds = 0,

  kAddsPrev = 1,

  kMuls = 2,

  kMulsPrev = 3,

  kMulsPrev2 = 4,

  kMaxs = 5,

  kMins = 6,

  kSeqs = 7,

  kSgts = 8,

  kSges = 9,

  kSnes = 10,

  kFrcs = 11,

  kTruncs = 12,

  kFloors = 13,

  kExp = 14,

  kLogc = 15,

  kLog = 16,

  kRcpc = 17,

  kRcpf = 18,

  kRcp = 19,

  kRsqc = 20,

  kRsqf = 21,

  kRsq = 22,

  kMaxAs = 23,

  kMaxAsf = 24,

  kSubs = 25,

  kSubsPrev = 26,

  kSetpEq = 27,

  kSetpNe = 28,

  kSetpGt = 29,

  kSetpGe = 30,

  kSetpInv = 31,

  kSetpPop = 32,

  kSetpClr = 33,

  kSetpRstr = 34,

  kKillsEq = 35,

  kKillsGt = 36,

  kKillsGe = 37,

  kKillsNe = 38,

  kKillsOne = 39,

  kSqrt = 40,

  kMulsc0 = 42,

  kMulsc1 = 43,

  kAddsc0 = 44,

  kAddsc1 = 45,

  kSubsc0 = 46,

  kSubsc1 = 47,

  kSin = 48,

  kCos = 49,

  kRetainPrev = 50,
};

struct AluScalarOpcodeInfo {
  const char* name;

  uint32_t operand_count;

  bool single_operand_is_two_component;

  AluOpChangedState changed_state;
};

extern const AluScalarOpcodeInfo kAluScalarOpcodeInfos[64];

inline const AluScalarOpcodeInfo& GetAluScalarOpcodeInfo(AluScalarOpcode opcode) {
  assert_true(uint32_t(opcode) < rex::countof(kAluScalarOpcodeInfos));
  return kAluScalarOpcodeInfos[uint32_t(opcode)];
}

enum class AluVectorOpcode : uint32_t {

  kAdd = 0,

  kMul = 1,

  kMax = 2,

  kMin = 3,

  kSeq = 4,

  kSgt = 5,

  kSge = 6,

  kSne = 7,

  kFrc = 8,

  kTrunc = 9,

  kFloor = 10,

  kMad = 11,

  kCndEq = 12,

  kCndGe = 13,

  kCndGt = 14,

  kDp4 = 15,

  kDp3 = 16,

  kDp2Add = 17,

  kCube = 18,

  kMax4 = 19,

  kSetpEqPush = 20,

  kSetpNePush = 21,

  kSetpGtPush = 22,

  kSetpGePush = 23,

  kKillEq = 24,

  kKillGt = 25,

  kKillGe = 26,

  kKillNe = 27,

  kDst = 28,

  kMaxA = 29,
};

struct AluVectorOpcodeInfo {
  const char* name;
  uint32_t operand_components_used[3];
  AluOpChangedState changed_state;

  uint32_t GetOperandCount() const {
    if (!operand_components_used[2]) {
      if (!operand_components_used[1]) {
        if (!operand_components_used[0]) {
          return 0;
        }
        return 1;
      }
      return 2;
    }
    return 3;
  }

  uint32_t ScalarSecondSourceComponent() const { return GetOperandCount() == 3 ? 2 : 0; }
};

extern const AluVectorOpcodeInfo kAluVectorOpcodeInfos[32];

inline const AluVectorOpcodeInfo& GetAluVectorOpcodeInfo(AluVectorOpcode opcode) {
  assert_true(uint32_t(opcode) < rex::countof(kAluVectorOpcodeInfos));
  return kAluVectorOpcodeInfos[uint32_t(opcode)];
}

inline uint32_t GetAluVectorOpNeededSourceComponents(AluVectorOpcode vector_opcode,
                                                     uint32_t src_index,
                                                     uint32_t used_result_components) {
  assert_not_zero(src_index);
  assert_zero(used_result_components & ~uint32_t(0b1111));
  uint32_t components = used_result_components;
  switch (vector_opcode) {
    case AluVectorOpcode::kDp4:
    case AluVectorOpcode::kMax4:
      components = used_result_components ? 0b1111 : 0;
      break;
    case AluVectorOpcode::kDp3:
      components = used_result_components ? 0b0111 : 0;
      break;
    case AluVectorOpcode::kDp2Add:
      components = used_result_components ? (src_index == 3 ? 0b0001 : 0b0011) : 0;
      break;
    case AluVectorOpcode::kCube:
      components = used_result_components ? 0b1111 : 0;
      break;
    case AluVectorOpcode::kSetpEqPush:
    case AluVectorOpcode::kSetpNePush:
    case AluVectorOpcode::kSetpGtPush:
    case AluVectorOpcode::kSetpGePush:
      components = used_result_components ? 0b1001 : 0b1000;
      break;
    case AluVectorOpcode::kKillEq:
    case AluVectorOpcode::kKillGt:
    case AluVectorOpcode::kKillGe:
    case AluVectorOpcode::kKillNe:
      components = 0b1111;
      break;

    case AluVectorOpcode::kMaxA:
      if (src_index == 1) {
        components |= 0b1000;
      }
      break;
    default:
      break;
  }
  return components & GetAluVectorOpcodeInfo(vector_opcode).operand_components_used[src_index - 1];
}

constexpr uint32_t kMaxMemExportElementCount = 5;

enum class ExportRegister : uint32_t {
  kVSInterpolator0 = 0,
  kVSInterpolator1,
  kVSInterpolator2,
  kVSInterpolator3,
  kVSInterpolator4,
  kVSInterpolator5,
  kVSInterpolator6,
  kVSInterpolator7,
  kVSInterpolator8,
  kVSInterpolator9,
  kVSInterpolator10,
  kVSInterpolator11,
  kVSInterpolator12,
  kVSInterpolator13,
  kVSInterpolator14,
  kVSInterpolator15,

  kVSPosition = 62,

  kVSPointSizeEdgeFlagKillVertex = 63,

  kPSColor0 = 0,
  kPSColor1,
  kPSColor2,
  kPSColor3,

  kPSDepth = 61,

  kExportAddress = 32,

  kExportData0 = 33,
  kExportData1,
  kExportData2,
  kExportData3,
  kExportData4,
};

struct alignas(uint32_t) AluInstruction {
  bool is_export() const { return data_.export_data == 1; }

  bool is_predicated() const { return data_.is_predicated; }

  bool predicate_condition() const { return data_.pred_condition == 1; }

  bool abs_constants() const { return data_.abs_constants == 1; }
  bool is_const_0_addressed() const { return data_.const_0_rel_abs == 1; }
  bool is_const_1_addressed() const { return data_.const_1_rel_abs == 1; }
  bool is_const_address_register_relative() const {
    return data_.const_address_register_relative == 1;
  }

  AluVectorOpcode vector_opcode() const { return data_.vector_opc; }
  uint32_t vector_write_mask() const { return data_.vector_write_mask; }
  uint32_t vector_dest() const { return data_.vector_dest; }
  bool is_vector_dest_relative() const { return data_.vector_dest_rel == 1; }
  bool vector_clamp() const { return data_.vector_clamp == 1; }

  AluScalarOpcode scalar_opcode() const { return data_.scalar_opc; }
  uint32_t scalar_write_mask() const { return data_.scalar_write_mask; }
  uint32_t scalar_dest() const { return data_.scalar_dest; }
  bool is_scalar_dest_relative() const { return data_.scalar_dest_rel == 1; }
  bool scalar_clamp() const { return data_.scalar_clamp == 1; }

  static constexpr uint32_t src_temp_reg(uint32_t src_reg) { return src_reg & 0x3F; }
  static constexpr bool is_src_temp_relative(uint32_t src_reg) { return (src_reg & 0x40) != 0; }
  static constexpr bool is_src_temp_value_absolute(uint32_t src_reg) {
    return (src_reg & 0x80) != 0;
  }

  uint32_t src_reg(size_t i) const {
    switch (i) {
      case 1:
        return data_.src1_reg;
      case 2:
        return data_.src2_reg;
      case 3:
        return data_.src3_reg;
      default:
        assert_unhandled_case(i);
        return 0;
    }
  }
  bool src_is_temp(size_t i) const {
    switch (i) {
      case 1:
        return bool(data_.src1_sel);
      case 2:
        return bool(data_.src2_sel);
      case 3:
        return bool(data_.src3_sel);
      default:
        assert_unhandled_case(i);
        return 0;
    }
  }

  bool src_const_is_addressed(size_t i) const {
    switch (i) {
      case 1:
        return bool(data_.const_0_rel_abs);
      case 2:
        return bool(src_is_temp(1) ? data_.const_0_rel_abs : data_.const_1_rel_abs);
      case 3:
        return bool((src_is_temp(1) && src_is_temp(2)) ? data_.const_0_rel_abs
                                                       : data_.const_1_rel_abs);
      default:
        assert_unhandled_case(i);
        return false;
    }
  }
  uint32_t src_swizzle(size_t i) const {
    switch (i) {
      case 1:
        return data_.src1_swiz;
      case 2:
        return data_.src2_swiz;
      case 3:
        return data_.src3_swiz;
      default:
        assert_unhandled_case(i);
        return 0;
    }
  }
  bool src_negate(size_t i) const {
    switch (i) {
      case 1:
        return data_.src1_reg_negate == 1;
      case 2:
        return data_.src2_reg_negate == 1;
      case 3:
        return data_.src3_reg_negate == 1;
      default:
        assert_unhandled_case(i);
        return 0;
    }
  }

  uint32_t scalar_const_reg_op_src_temp_reg() const {
    return (uint32_t(data_.scalar_opc) & 1) | (data_.src3_sel << 1) | (data_.src3_swiz & 0x3C);
  }

  static constexpr uint32_t GetSwizzledComponentIndex(uint32_t swizzle, uint32_t component_index) {
    return ((swizzle >> (2 * component_index)) + component_index) & 3;
  }

  uint32_t GetVectorOpResultWriteMask() const {
    uint32_t mask = vector_write_mask();
    if (is_export()) {
      mask &= ~scalar_write_mask();
    }
    return mask;
  }
  uint32_t GetScalarOpResultWriteMask() const {
    uint32_t mask = scalar_write_mask();
    if (is_export()) {
      mask &= ~vector_write_mask();
    }
    return mask;
  }
  uint32_t GetConstant0WriteMask() const {
    if (!is_export() || !is_scalar_dest_relative()) {
      return 0b0000;
    }
    return 0b1111 & ~(vector_write_mask() | scalar_write_mask());
  }
  uint32_t GetConstant1WriteMask() const {
    if (!is_export()) {
      return 0b0000;
    }
    return vector_write_mask() & scalar_write_mask();
  }

 private:
  struct Data {
    struct {
      uint32_t vector_dest : 6;
      uint32_t vector_dest_rel : 1;
      uint32_t abs_constants : 1;
      uint32_t scalar_dest : 6;
      uint32_t scalar_dest_rel : 1;

      uint32_t export_data : 1;
      uint32_t vector_write_mask : 4;
      uint32_t scalar_write_mask : 4;
      uint32_t vector_clamp : 1;
      uint32_t scalar_clamp : 1;
      AluScalarOpcode scalar_opc : 6;
    };
    struct {
      uint32_t src3_swiz : 8;
      uint32_t src2_swiz : 8;
      uint32_t src1_swiz : 8;
      uint32_t src3_reg_negate : 1;
      uint32_t src2_reg_negate : 1;
      uint32_t src1_reg_negate : 1;
      uint32_t pred_condition : 1;
      uint32_t is_predicated : 1;

      uint32_t const_address_register_relative : 1;
      uint32_t const_1_rel_abs : 1;
      uint32_t const_0_rel_abs : 1;
    };
    struct {
      uint32_t src3_reg : 8;
      uint32_t src2_reg : 8;
      uint32_t src1_reg : 8;
      AluVectorOpcode vector_opc : 5;
      uint32_t src3_sel : 1;
      uint32_t src2_sel : 1;
      uint32_t src1_sel : 1;
    };
  };
  Data data_;
};
static_assert_size(AluInstruction, sizeof(uint32_t) * 3);

}

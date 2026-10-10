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

#include <algorithm>
#include <cmath>
#include <memory>
#include <sstream>
#include <fmt/format.h>
#include <rex/assert.h>
#include <rex/cvar.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/pipeline/render_target/cache.h>
#include <rex/graphics/pipeline/shader/dxbc_translator.h>
#include <rex/math.h>
#include <rex/string.h>

namespace rex::graphics {

using namespace ucode;

void DxbcShaderTranslator::ProcessVertexFetchInstruction(
    const ParsedVertexFetchInstruction& instr) {
  if (emit_source_map_) {
    instruction_disassembly_buffer_.Reset();
    instr.Disassemble(&instruction_disassembly_buffer_);
  }
  UpdateInstructionPredicationAndEmitDisassembly(instr.is_predicated, instr.predicate_condition);

  uint32_t used_result_components = instr.result.GetUsedResultComponents();
  uint32_t needed_words =
      xenos::GetVertexFormatNeededWords(instr.attributes.data_format, used_result_components);

  if (!needed_words && instr.is_mini_fetch) {
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }

  if (cbuffer_index_fetch_constants_ == kBindingIndexUnallocated) {
    cbuffer_index_fetch_constants_ = cbuffer_count_++;
  }
  dxbc::Src fetch_constant_src(
      dxbc::Src::CB(cbuffer_index_fetch_constants_, uint32_t(CbufferRegister::kFetchConstants),
                    instr.operands[1].storage_index >> 1,
                    (instr.operands[1].storage_index & 1) ? 0b10101110 : 0b00000100));

  dxbc::Src address_src(dxbc::Src::R(system_temp_grad_v_vfetch_address_, dxbc::Src::kWWWW));
  if (!instr.is_mini_fetch) {
    dxbc::Dest address_dest(dxbc::Dest::R(system_temp_grad_v_vfetch_address_, 0b1000));
    if (instr.attributes.stride) {
      {
        bool index_operand_temp_pushed = false;
        dxbc::Src index_operand(LoadOperand(instr.operands[0], 0b0001, index_operand_temp_pushed)
                                    .SelectFromSwizzled(0));
        if (instr.attributes.is_index_rounded) {
          a_.OpAdd(address_dest, index_operand, dxbc::Src::LF(0.5f));
          a_.OpRoundNI(address_dest, address_src);
        } else {
          a_.OpRoundNI(address_dest, index_operand);
        }
        if (index_operand_temp_pushed) {
          PopSystemTemp();
        }
      }
      a_.OpFToI(address_dest, address_src);

      a_.OpAnd(dxbc::Dest::R(system_temp_result_, 0b1000), fetch_constant_src.SelectFromSwizzled(0),
               dxbc::Src::LU(~uint32_t(3)));

      a_.OpIMAd(address_dest, address_src,
                dxbc::Src::LU(instr.attributes.stride * sizeof(uint32_t)),
                dxbc::Src::R(system_temp_result_, dxbc::Src::kWWWW));
    } else {
      a_.OpAnd(address_dest, fetch_constant_src.SelectFromSwizzled(0), dxbc::Src::LU(~uint32_t(3)));
    }
  }

  if (!needed_words) {
    StoreResult(instr.result, dxbc::Src::LF(0.0f));
    return;
  }

  dxbc::Dest address_temp_dest(dxbc::Dest::R(system_temp_result_, 0b1000));
  dxbc::Src address_temp_src(dxbc::Src::R(system_temp_result_, dxbc::Src::kWWWW));

  uint32_t first_word_index;
  rex::bit_scan_forward(needed_words, &first_word_index);
  int32_t first_word_buffer_offset = instr.attributes.offset + int32_t(first_word_index);
  if (first_word_buffer_offset) {
    a_.OpIAdd(address_temp_dest, address_src,
              dxbc::Src::LI(first_word_buffer_offset * sizeof(uint32_t)));
    address_src = address_temp_src;
  }

  a_.OpAnd(dxbc::Dest::R(system_temp_result_, 0b0001), LoadFlagsSystemConstant(),
           dxbc::Src::LU(kSysFlag_SharedMemoryIsUAV));
  a_.OpIf(false, dxbc::Src::R(system_temp_result_, dxbc::Src::kXXXX));
  if (srv_index_shared_memory_ == kBindingIndexUnallocated) {
    srv_index_shared_memory_ = srv_count_++;
  }
  if (uav_index_shared_memory_ == kBindingIndexUnallocated) {
    uav_index_shared_memory_ = uav_count_++;
  }
  for (uint32_t i = 0; i < 2; ++i) {
    if (i) {
      a_.OpElse();
    }
    dxbc::Src shared_memory_src(
        i ? dxbc::Src::U(uav_index_shared_memory_, uint32_t(UAVRegister::kSharedMemory))
          : dxbc::Src::T(srv_index_shared_memory_, uint32_t(SRVMainRegister::kSharedMemory)));
    uint32_t needed_words_remaining = needed_words;
    uint32_t word_index_previous = first_word_index;
    while (needed_words_remaining) {
      uint32_t word_index;
      rex::bit_scan_forward(needed_words_remaining, &word_index);
      uint32_t word_count;
      rex::bit_scan_forward(~(needed_words_remaining >> word_index), &word_count);
      needed_words_remaining &= ~((uint32_t(1) << (word_index + word_count)) - uint32_t(1));
      if (word_index != word_index_previous) {
        a_.OpIAdd(address_temp_dest, address_src,
                  dxbc::Src::LU((word_index - word_index_previous) * sizeof(uint32_t)));
        address_src = address_temp_src;
        word_index_previous = word_index;
      }

      dxbc::Dest words_result_dest(
          dxbc::Dest::R(system_temp_result_, ((1 << word_count) - 1) << word_index));
      if (!word_index || word_count == 1) {
        a_.OpLdRaw(words_result_dest, address_src, shared_memory_src);
      } else {
        uint32_t load_temp = PushSystemTemp();
        a_.OpLdRaw(dxbc::Dest::R(load_temp, (1 << word_count) - 1), address_src, shared_memory_src);

        a_.OpMov(words_result_dest,
                 dxbc::Src::R(load_temp, (dxbc::Src::kXYZW & ((1 << (word_count * 2)) - 1))
                                             << (word_index * 2)));

        PopSystemTemp();
      }
    }
  }
  a_.OpEndIf();

  dxbc::Src result_src(dxbc::Src::R(system_temp_result_));

  {
    uint32_t swap_temp = PushSystemTemp();

    uint32_t endian_temp, endian_temp_component;
    if (needed_words == 0b1111) {
      endian_temp = PushSystemTemp();
      endian_temp_component = 0;
    } else {
      endian_temp = swap_temp;
      rex::bit_scan_forward(~needed_words, &endian_temp_component);
    }
    a_.OpAnd(dxbc::Dest::R(endian_temp, 1 << endian_temp_component),
             fetch_constant_src.SelectFromSwizzled(1), dxbc::Src::LU(0b11));
    dxbc::Src endian_src(dxbc::Src::R(endian_temp).Select(endian_temp_component));

    dxbc::Dest swap_temp_dest(dxbc::Dest::R(swap_temp, needed_words));
    dxbc::Src swap_temp_src(dxbc::Src::R(swap_temp));
    dxbc::Dest swap_result_dest(dxbc::Dest::R(system_temp_result_, needed_words));

    a_.OpSwitch(endian_src);
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian128::k8in16)));
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian128::k8in32)));

    a_.OpAnd(swap_temp_dest, result_src, dxbc::Src::LU(0x00FF00FF));

    a_.OpUShR(swap_result_dest, result_src, dxbc::Src::LU(8));

    a_.OpAnd(swap_result_dest, result_src, dxbc::Src::LU(0x00FF00FF));

    a_.OpUMAd(swap_result_dest, swap_temp_src, dxbc::Src::LU(256), result_src);
    a_.OpBreak();
    a_.OpEndSwitch();

    a_.OpSwitch(endian_src);
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian128::k8in32)));
    a_.OpCase(dxbc::Src::LU(uint32_t(xenos::Endian128::k16in32)));

    a_.OpUShR(swap_temp_dest, result_src, dxbc::Src::LU(16));

    a_.OpBFI(swap_result_dest, dxbc::Src::LU(16), dxbc::Src::LU(16), result_src, swap_temp_src);
    a_.OpBreak();
    a_.OpEndSwitch();

    PopSystemTemp((endian_temp != swap_temp) ? 2 : 1);
  }

  uint32_t used_format_components =
      used_result_components &
      ((1 << xenos::GetVertexFormatComponentCount(instr.attributes.data_format)) - 1);
  dxbc::Dest result_unpacked_dest(dxbc::Dest::R(system_temp_result_, used_format_components));

  assert_not_zero(used_format_components);
  uint32_t packed_widths[4] = {}, packed_offsets[4] = {};
  uint32_t packed_swizzle = dxbc::Src::kXXXX;
  switch (instr.attributes.data_format) {
    case xenos::VertexFormat::k_8_8_8_8:
      packed_widths[0] = packed_widths[1] = packed_widths[2] = packed_widths[3] = 8;
      packed_offsets[1] = 8;
      packed_offsets[2] = 16;
      packed_offsets[3] = 24;
      break;
    case xenos::VertexFormat::k_2_10_10_10:
      packed_widths[0] = packed_widths[1] = packed_widths[2] = 10;
      packed_widths[3] = 2;
      packed_offsets[1] = 10;
      packed_offsets[2] = 20;
      packed_offsets[3] = 30;
      break;
    case xenos::VertexFormat::k_10_11_11:
      packed_widths[0] = packed_widths[1] = 11;
      packed_widths[2] = 10;
      packed_offsets[1] = 11;
      packed_offsets[2] = 22;
      break;
    case xenos::VertexFormat::k_11_11_10:
      packed_widths[0] = 10;
      packed_widths[1] = packed_widths[2] = 11;
      packed_offsets[1] = 10;
      packed_offsets[2] = 21;
      break;
    case xenos::VertexFormat::k_16_16:
      packed_widths[0] = packed_widths[1] = 16;
      packed_offsets[1] = 16;
      break;
    case xenos::VertexFormat::k_16_16_16_16:
      packed_widths[0] = packed_widths[1] = packed_widths[2] = packed_widths[3] = 16;
      packed_offsets[1] = packed_offsets[3] = 16;
      packed_swizzle = 0b01010000;
      break;
    default:

      break;
  }
  if (packed_widths[0]) {
    if (instr.attributes.is_signed) {
      a_.OpIBFE(result_unpacked_dest, dxbc::Src::LP(packed_widths), dxbc::Src::LP(packed_offsets),
                dxbc::Src::R(system_temp_result_, packed_swizzle));
      a_.OpIToF(result_unpacked_dest, result_src);
      if (!instr.attributes.is_integer) {
        float packed_scales[4] = {};
        switch (instr.attributes.signed_rf_mode) {
          case xenos::SignedRepeatingFractionMode::kZeroClampMinusOne: {
            uint32_t packed_scales_mask = 0b0000;
            for (uint32_t i = 0; i < 4; ++i) {
              if (!(used_format_components & (1 << i))) {
                continue;
              }
              if (packed_widths[i] > 2) {
                packed_scales[i] = 1.0f / float((uint32_t(1) << (packed_widths[i] - 1)) - 1);
                packed_scales_mask |= 1 << i;
              }
            }
            if (packed_scales_mask) {
              a_.OpMul(dxbc::Dest::R(system_temp_result_, packed_scales_mask), result_src,
                       dxbc::Src::LP(packed_scales));
            }

            a_.OpMax(result_unpacked_dest, result_src, dxbc::Src::LF(-1.0f));
          } break;
          case xenos::SignedRepeatingFractionMode::kNoZero: {
            float packed_zeros[4] = {};
            for (uint32_t i = 0; i < 4; ++i) {
              if (!(used_format_components & (1 << i))) {
                continue;
              }
              assert_not_zero(packed_widths[i]);
              packed_zeros[i] = 1.0f / float((uint32_t(1) << packed_widths[i]) - 1);
              packed_scales[i] = 2.0f * packed_zeros[i];
            }
            a_.OpMAd(result_unpacked_dest, result_src, dxbc::Src::LP(packed_scales),
                     dxbc::Src::LP(packed_zeros));
          } break;
          default:
            assert_unhandled_case(instr.attributes.signed_rf_mode);
        }
      }
    } else {
      a_.OpUBFE(result_unpacked_dest, dxbc::Src::LP(packed_widths), dxbc::Src::LP(packed_offsets),
                dxbc::Src::R(system_temp_result_, packed_swizzle));
      a_.OpUToF(result_unpacked_dest, result_src);
      if (!instr.attributes.is_integer) {
        float packed_scales[4] = {};
        uint32_t packed_scales_mask = 0b0000;
        for (uint32_t i = 0; i < 4; ++i) {
          if (!(used_format_components & (1 << i))) {
            continue;
          }
          if (packed_widths[i] > 1) {
            packed_scales[i] = 1.0f / float((uint32_t(1) << packed_widths[i]) - 1);
            packed_scales_mask |= 1 << i;
          }
        }
        if (packed_scales_mask) {
          a_.OpMul(dxbc::Dest::R(system_temp_result_, packed_scales_mask), result_src,
                   dxbc::Src::LP(packed_scales));
        }
      }
    }
  } else {
    switch (instr.attributes.data_format) {
      case xenos::VertexFormat::k_16_16_FLOAT:
      case xenos::VertexFormat::k_16_16_16_16_FLOAT:

        a_.OpUBFE(result_unpacked_dest, dxbc::Src::LU(16), dxbc::Src::LU(0, 16, 0, 16),
                  dxbc::Src::R(system_temp_result_, 0b01010000));
        a_.OpF16ToF32(result_unpacked_dest, result_src);
        break;
      case xenos::VertexFormat::k_32:
      case xenos::VertexFormat::k_32_32:
      case xenos::VertexFormat::k_32_32_32_32:
        if (instr.attributes.is_signed) {
          a_.OpIToF(result_unpacked_dest, result_src);
        } else {
          a_.OpUToF(result_unpacked_dest, result_src);
        }
        if (!instr.attributes.is_integer) {
          if (instr.attributes.is_signed) {
            switch (instr.attributes.signed_rf_mode) {
              case xenos::SignedRepeatingFractionMode::kZeroClampMinusOne:
                a_.OpMul(result_unpacked_dest, result_src, dxbc::Src::LF(1.0f / 2147483647.0f));

                break;
              case xenos::SignedRepeatingFractionMode::kNoZero:
                a_.OpMAd(result_unpacked_dest, result_src, dxbc::Src::LF(1.0f / 2147483647.5f),
                         dxbc::Src::LF(0.5f / 2147483647.5f));
                break;
              default:
                assert_unhandled_case(instr.attributes.signed_rf_mode);
            }
          } else {
            a_.OpMul(result_unpacked_dest, result_src, dxbc::Src::LF(1.0f / 4294967295.0f));
          }
        }
        break;
      case xenos::VertexFormat::k_32_FLOAT:
      case xenos::VertexFormat::k_32_32_FLOAT:
      case xenos::VertexFormat::k_32_32_32_32_FLOAT:
      case xenos::VertexFormat::k_32_32_32_FLOAT:

        break;
      default:

        assert_not_zero(packed_widths[0]);
        break;
    }
  }

  if (instr.attributes.exp_adjust) {
    a_.OpMul(result_unpacked_dest, result_src,
             dxbc::Src::LF(std::ldexp(1.0f, instr.attributes.exp_adjust)));
  }

  uint32_t used_missing_components = used_result_components & ~used_format_components;
  if (used_missing_components) {
    a_.OpMov(dxbc::Dest::R(system_temp_result_, used_missing_components), dxbc::Src::LF(0.0f));
  }

  StoreResult(instr.result, dxbc::Src::R(system_temp_result_));
}

}

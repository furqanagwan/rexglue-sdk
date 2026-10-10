/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2021 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

#include <rex/assert.h>
#include <rex/graphics/format/dxbc.h>

namespace rex::graphics::dxbc {

class Assembler {
 public:
  Assembler(std::vector<uint32_t>& code, Statistics& stat) : code_(code), stat_(stat) {}

  void OpAdd(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kAdd, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpAnd(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kAnd, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpBreak() {
    code_.push_back(OpcodeToken(Opcode::kBreak, 0));
    ++stat_.instruction_count;
  }
  void OpCall(const Src& label) {
    EmitFlowOp(Opcode::kCall, label);
    ++stat_.static_flow_control_count;
  }
  void OpCallC(bool test, const Src& src, const Src& label) {
    EmitFlowOp(Opcode::kCallC, src, label, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpCase(const Src& src) {
    EmitFlowOp(Opcode::kCase, src);
    ++stat_.static_flow_control_count;
  }
  void OpContinue() {
    code_.push_back(OpcodeToken(Opcode::kContinue, 0));
    ++stat_.instruction_count;
  }
  void OpDefault() {
    code_.push_back(OpcodeToken(Opcode::kDefault, 0));
    ++stat_.instruction_count;
    ++stat_.static_flow_control_count;
  }
  void OpDiscard(bool test, const Src& src) { EmitFlowOp(Opcode::kDiscard, src, test); }
  void OpDiv(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kDiv, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDP2(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b0011) + src1.GetLength(0b0011);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP2, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b0011);
    src1.Write(code_, false, 0b0011);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpDP3(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b0111) + src1.GetLength(0b0111);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP3, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b0111);
    src1.Write(code_, false, 0b0111);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpDP4(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t operands_length = dest.GetLength() + src0.GetLength(0b1111) + src1.GetLength(0b1111);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDP4, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, false, 0b1111);
    src1.Write(code_, false, 0b1111);
    ++stat_.instruction_count;
    ++stat_.float_instruction_count;
  }
  void OpElse() {
    code_.push_back(OpcodeToken(Opcode::kElse, 0));
    ++stat_.instruction_count;
  }
  void OpEndIf() {
    code_.push_back(OpcodeToken(Opcode::kEndIf, 0));
    ++stat_.instruction_count;
  }
  void OpEndLoop() {
    code_.push_back(OpcodeToken(Opcode::kEndLoop, 0));
    ++stat_.instruction_count;
  }
  void OpEndSwitch() {
    code_.push_back(OpcodeToken(Opcode::kEndSwitch, 0));
    ++stat_.instruction_count;
  }
  void OpEq(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kEq, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpExp(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kExp, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpFrc(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kFrc, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpFToI(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFToI, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpFToU(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFToU, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kGE, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpIAdd(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIAdd, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIf(bool test, const Src& src) {
    EmitFlowOp(Opcode::kIf, src, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpIEq(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIEq, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIGE, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpILT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kILT, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add) {
    EmitAluOp(Opcode::kIMAd, 0b111, dest, mul0, mul1, add);
    ++stat_.int_instruction_count;
  }
  void OpIMax(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMax, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMin(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMin, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIMul(const Dest& dest_hi, const Dest& dest_lo, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kIMul, 0b11, dest_hi, dest_lo, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpINE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kINE, 0b11, dest, src0, src1);
    ++stat_.int_instruction_count;
  }
  void OpIShL(const Dest& dest, const Src& value, const Src& shift) {
    EmitAluOp(Opcode::kIShL, 0b11, dest, value, shift);
    ++stat_.int_instruction_count;
  }
  void OpIToF(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kIToF, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpLabel(const Src& label) {
    uint32_t operands_length = label.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLabel, operands_length));
    label.Write(code_, true, 0b0000);
  }
  void OpLd(const Dest& dest, const Src& address, uint32_t address_mask, const Src& resource,
            int32_t aoffimmi_u = 0, int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               resource.GetLength(dest_write_mask, true);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLd, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask, true);
    resource.Write(code_, false, dest_write_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpLdMS(const Dest& dest, const Src& address, uint32_t address_mask, const Src& resource,
              const Src& sample_index, int32_t aoffimmi_u = 0, int32_t aoffimmi_v = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, 0);
    }
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               resource.GetLength(dest_write_mask, true) +
                               sample_index.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdMS, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask, true);
    resource.Write(code_, false, dest_write_mask, true);
    sample_index.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpLog(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kLog, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpLoop() {
    code_.push_back(OpcodeToken(Opcode::kLoop, 0));
    ++stat_.instruction_count;
    ++stat_.dynamic_flow_control_count;
  }
  void OpLT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kLT, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add,
             bool saturate = false) {
    EmitAluOp(Opcode::kMAd, 0b000, dest, mul0, mul1, add, saturate);
    ++stat_.float_instruction_count;
  }
  void OpMin(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMin, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpMax(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMax, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }

  void* OpCustomData(CustomDataClass custom_data_class, uint32_t length_bytes) {
    uint32_t length_bytes_aligned = rex::align(length_bytes, uint32_t(sizeof(uint32_t)));
    uint32_t total_length_dwords = length_bytes_aligned / sizeof(uint32_t) + 2;
    size_t offset_dwords = code_.size();
    code_.resize(offset_dwords + total_length_dwords);
    uint32_t* data = code_.data() + offset_dwords;

    *(data++) = uint32_t(Opcode::kCustomData) | (uint32_t(custom_data_class) << 11);
    *(data++) = total_length_dwords;

    std::memset(reinterpret_cast<uint8_t*>(data) + length_bytes, dxbc::kAlignmentPadding,
                length_bytes_aligned - length_bytes);
    return data;
  }
  void OpMov(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kMov, 0b0, dest, src, saturate);
    if (dest.type_ == OperandType::kIndexableTemp || src.type_ == OperandType::kIndexableTemp) {
      ++stat_.array_instruction_count;
    } else {
      ++stat_.mov_instruction_count;
    }
  }
  void OpMovC(const Dest& dest, const Src& test, const Src& src_nz, const Src& src_z,
              bool saturate = false) {
    EmitAluOp(Opcode::kMovC, 0b001, dest, test, src_nz, src_z, saturate);
    ++stat_.movc_instruction_count;
  }
  void OpMul(const Dest& dest, const Src& src0, const Src& src1, bool saturate = false) {
    EmitAluOp(Opcode::kMul, 0b00, dest, src0, src1, saturate);
    ++stat_.float_instruction_count;
  }
  void OpNE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kNE, 0b00, dest, src0, src1);
    ++stat_.float_instruction_count;
  }
  void OpNot(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kNot, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpOr(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kOr, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpRet() {
    code_.push_back(OpcodeToken(Opcode::kRet, 0));
    ++stat_.instruction_count;
    ++stat_.static_flow_control_count;
  }
  void OpRetC(bool test, const Src& src) {
    EmitFlowOp(Opcode::kRetC, src, test);
    ++stat_.dynamic_flow_control_count;
  }
  void OpRoundNE(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundNE, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundNI(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundNI, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundPI(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundPI, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRoundZ(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRoundZ, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRSq(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRSq, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpSampleL(const Dest& dest, const Src& address, uint32_t address_components,
                 const Src& resource, const Src& sampler, const Src& lod, int32_t aoffimmi_u = 0,
                 int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask, true) +
                               sampler.GetLength(0b0000) + lod.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kSampleL, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask, true);
    sampler.Write(code_, false, 0b0000);
    lod.Write(code_, false, 0b0000);
    ++stat_.instruction_count;
    ++stat_.texture_normal_instructions;
  }
  void OpSampleD(const Dest& dest, const Src& address, uint32_t address_components,
                 const Src& resource, const Src& sampler, const Src& x_derivatives,
                 const Src& y_derivatives, uint32_t derivatives_components, int32_t aoffimmi_u = 0,
                 int32_t aoffimmi_v = 0, int32_t aoffimmi_w = 0) {
    assert_true(derivatives_components <= address_components);
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t sample_controls = 0;
    if (aoffimmi_u || aoffimmi_v || aoffimmi_w) {
      sample_controls = SampleControlsExtendedOpcodeToken(aoffimmi_u, aoffimmi_v, aoffimmi_w);
    }
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t derivatives_mask = (1 << derivatives_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask, true) +
                               sampler.GetLength(0b0000) +
                               x_derivatives.GetLength(derivatives_mask, address_components > 1) +
                               y_derivatives.GetLength(derivatives_mask, address_components > 1);
    code_.reserve(code_.size() + 1 + (sample_controls ? 1 : 0) + operands_length);
    code_.push_back(OpcodeToken(Opcode::kSampleD, operands_length, false, sample_controls ? 1 : 0));
    if (sample_controls) {
      code_.push_back(sample_controls);
    }
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask, true);
    sampler.Write(code_, false, 0b0000);
    x_derivatives.Write(code_, false, derivatives_mask, address_components > 1);
    y_derivatives.Write(code_, false, derivatives_mask, address_components > 1);
    ++stat_.instruction_count;
    ++stat_.texture_gradient_instructions;
  }
  void OpSqRt(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kSqRt, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpSwitch(const Src& src) {
    EmitFlowOp(Opcode::kSwitch, src);
    ++stat_.dynamic_flow_control_count;
  }
  void OpSinCos(const Dest& dest_sin, const Dest& dest_cos, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kSinCos, 0b0, dest_sin, dest_cos, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpUDiv(const Dest& dest_quotient, const Dest& dest_remainder, const Src& src0,
              const Src& src1) {
    EmitAluOp(Opcode::kUDiv, 0b11, dest_quotient, dest_remainder, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpULT(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kULT, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUGE(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUGE, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMul(const Dest& dest_hi, const Dest& dest_lo, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMul, 0b11, dest_hi, dest_lo, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMAd(const Dest& dest, const Src& mul0, const Src& mul1, const Src& add) {
    EmitAluOp(Opcode::kUMAd, 0b111, dest, mul0, mul1, add);
    ++stat_.uint_instruction_count;
  }
  void OpUMax(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMax, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUMin(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kUMin, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpUShR(const Dest& dest, const Src& value, const Src& shift) {
    EmitAluOp(Opcode::kUShR, 0b11, dest, value, shift);
    ++stat_.uint_instruction_count;
  }
  void OpUToF(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kUToF, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpXOr(const Dest& dest, const Src& src0, const Src& src1) {
    EmitAluOp(Opcode::kXOr, 0b11, dest, src0, src1);
    ++stat_.uint_instruction_count;
  }
  void OpDclResource(ResourceDimension dimension, uint32_t return_type_token, const Src& operand,
                     uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclResource, 2 + operands_length) |
                    (uint32_t(dimension) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(return_type_token);
    code_.push_back(space);
  }

  void OpDclConstantBuffer(
      const Src& operand, uint32_t size_vectors,
      ConstantBufferAccessPattern access_pattern = ConstantBufferAccessPattern::kImmediateIndexed,
      uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclConstantBuffer, 2 + operands_length) |
                    (uint32_t(access_pattern) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(size_vectors);
    code_.push_back(space);
  }
  void OpDclSampler(const Src& operand, SamplerMode mode = SamplerMode::kDefault,
                    uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclSampler, 1 + operands_length) | (uint32_t(mode) << 11));
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(space);
  }

  void OpDclOutputTopology(PrimitiveTopology output_topology) {
    code_.push_back(OpcodeToken(Opcode::kDclOutputTopology, 0) | (uint32_t(output_topology) << 11));
    stat_.gs_output_topology = output_topology;
  }

  void OpDclInputPrimitive(Primitive input_primitive) {
    code_.push_back(OpcodeToken(Opcode::kDclInputPrimitive, 0) | (uint32_t(input_primitive) << 11));
    stat_.input_primitive = input_primitive;
  }

  size_t OpDclMaxOutputVertexCount(uint32_t count) {
    code_.reserve(code_.size() + 2);
    code_.push_back(OpcodeToken(Opcode::kDclMaxOutputVertexCount, 1));
    code_.push_back(count);
    stat_.gs_max_output_vertex_count = count;
    return code_.size() - 1;
  }
  void OpDclInput(const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInput, operands_length));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclInputSGV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputSGV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputSIV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputSIV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputPS(InterpolationMode interpolation_mode, const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputPS, operands_length) |
                    (uint32_t(interpolation_mode) << 11));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclInputPSSGV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);

    code_.push_back(OpcodeToken(Opcode::kDclInputPSSGV, 1 + operands_length) |
                    (uint32_t(InterpolationMode::kConstant) << 11));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclInputPSSIV(InterpolationMode interpolation_mode, const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclInputPSSIV, 1 + operands_length) |
                    (uint32_t(interpolation_mode) << 11));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }
  void OpDclOutput(const Dest& operand) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclOutput, operands_length));
    operand.Write(code_, true);
    ++stat_.dcl_count;
  }
  void OpDclOutputSIV(const Dest& operand, Name name) {
    uint32_t operands_length = operand.GetLength();
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclOutputSIV, 1 + operands_length));
    operand.Write(code_, true);
    code_.push_back(uint32_t(name));
    ++stat_.dcl_count;
  }

  size_t OpDclTemps(uint32_t count) {
    code_.reserve(code_.size() + 2);
    code_.push_back(OpcodeToken(Opcode::kDclTemps, 1));
    code_.push_back(count);
    stat_.temp_register_count = count;
    return code_.size() - 1;
  }
  void OpDclIndexableTemp(uint32_t index, uint32_t count, uint32_t component_count) {
    code_.reserve(code_.size() + 4);
    code_.push_back(OpcodeToken(Opcode::kDclIndexableTemp, 3));
    code_.push_back(index);
    code_.push_back(count);
    code_.push_back(component_count);
    stat_.temp_array_count += count;
  }

  void OpDclGlobalFlags(uint32_t flags) {
    code_.push_back(OpcodeToken(Opcode::kDclGlobalFlags, 0) | flags);
  }
  void OpLOD(const Dest& dest, const Src& address, uint32_t address_components, const Src& resource,
             const Src& sampler) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask) +
                               resource.GetLength(dest_write_mask) + sampler.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLOD, operands_length));
    dest.Write(code_);
    address.Write(code_, false, address_mask);
    resource.Write(code_, false, dest_write_mask);
    sampler.Write(code_, false, 0b0000);
    ++stat_.instruction_count;
    ++stat_.lod_instructions;
  }
  void OpEmitStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEmitStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;
    ++stat_.emit_instruction_count;
  }
  void OpCutStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kCutStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;
    ++stat_.cut_instruction_count;
  }

  void OpEmitThenCutStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEmitThenCutStream, operands_length));
    stream.Write(code_);
    ++stat_.instruction_count;

    ++stat_.emit_instruction_count;
    ++stat_.cut_instruction_count;
  }
  void OpDerivRTXCoarse(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTXCoarse, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTXFine(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTXFine, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTYCoarse(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTYCoarse, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpDerivRTYFine(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kDerivRTYFine, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpRcp(const Dest& dest, const Src& src, bool saturate = false) {
    EmitAluOp(Opcode::kRcp, 0b0, dest, src, saturate);
    ++stat_.float_instruction_count;
  }
  void OpF32ToF16(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kF32ToF16, 0b0, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpF16ToF32(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kF16ToF32, 0b1, dest, src);
    ++stat_.conversion_instruction_count;
  }
  void OpCountBits(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kCountBits, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpFirstBitHi(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFirstBitHi, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpFirstBitLo(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kFirstBitLo, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpUBFE(const Dest& dest, const Src& width, const Src& offset, const Src& src) {
    EmitAluOp(Opcode::kUBFE, 0b111, dest, width, offset, src);
    ++stat_.uint_instruction_count;
  }
  void OpIBFE(const Dest& dest, const Src& width, const Src& offset, const Src& src) {
    EmitAluOp(Opcode::kIBFE, 0b111, dest, width, offset, src);
    ++stat_.int_instruction_count;
  }
  void OpBFI(const Dest& dest, const Src& width, const Src& offset, const Src& from,
             const Src& to) {
    EmitAluOp(Opcode::kBFI, 0b1111, dest, width, offset, from, to);
    ++stat_.uint_instruction_count;
  }
  void OpBFRev(const Dest& dest, const Src& src) {
    EmitAluOp(Opcode::kBFRev, 0b1, dest, src);
    ++stat_.uint_instruction_count;
  }
  void OpDclStream(const Dest& stream) {
    uint32_t operands_length = stream.GetLength();
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclStream, operands_length));
    stream.Write(code_, true);
  }
  void OpDclInputControlPointCount(uint32_t count) {
    code_.push_back(OpcodeToken(Opcode::kDclInputControlPointCount, 0) | (count << 11));
    stat_.c_control_points = count;
  }
  void OpDclTessDomain(TessellatorDomain domain) {
    code_.push_back(OpcodeToken(Opcode::kDclTessDomain, 0) | (uint32_t(domain) << 11));
    stat_.tessellator_domain = domain;
  }
  void OpDclThreadGroup(uint32_t x, uint32_t y, uint32_t z) {
    code_.reserve(code_.size() + 4);
    code_.push_back(OpcodeToken(Opcode::kDclThreadGroup, 3));
    code_.push_back(x);
    code_.push_back(y);
    code_.push_back(z);
  }

  void OpDclUnorderedAccessViewTyped(ResourceDimension dimension, uint32_t flags,
                                     uint32_t return_type_token, const Src& operand,
                                     uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 3 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclUnorderedAccessViewTyped, 2 + operands_length) |
                    (uint32_t(dimension) << 11) | flags);
    operand.Write(code_, false, 0b1111, false, true);
    code_.push_back(return_type_token);
    code_.push_back(space);
  }

  void OpDclUnorderedAccessViewRaw(uint32_t flags, const Src& operand, uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclUnorderedAccessViewRaw, 1 + operands_length) | flags);
    operand.Write(code_, true, 0b1111, false, true);
    code_.push_back(space);
  }
  void OpDclResourceRaw(const Src& operand, uint32_t space = 0) {
    uint32_t operands_length = operand.GetLength(0b1111, false);
    code_.reserve(code_.size() + 2 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kDclResourceRaw, 1 + operands_length));
    operand.Write(code_, true, 0b1111, false, true);
    code_.push_back(space);
  }
  void OpLdUAVTyped(const Dest& dest, const Src& address, uint32_t address_components,
                    const Src& uav) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length = dest.GetLength() + address.GetLength(address_mask, true) +
                               uav.GetLength(dest_write_mask, true);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdUAVTyped, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask, true);
    uav.Write(code_, false, dest_write_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpStoreUAVTyped(const Dest& dest, const Src& address, uint32_t address_components,
                       const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();

    assert_true(dest_write_mask == 0b1111);
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length =
        dest.GetLength() + address.GetLength(address_mask, true) + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kStoreUAVTyped, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask, true);
    value.Write(code_, false, dest_write_mask);
    ++stat_.instruction_count;
    ++stat_.c_texture_store_instructions;
  }
  void OpLdRaw(const Dest& dest, const Src& byte_offset, const Src& src) {
    uint32_t dest_write_mask = dest.GetMask();
    assert_true(dest_write_mask == 0b0001 || dest_write_mask == 0b0010 ||
                dest_write_mask == 0b0100 || dest_write_mask == 0b1000 ||
                dest_write_mask == 0b0011 || dest_write_mask == 0b0111 ||
                dest_write_mask == 0b1111);
    uint32_t component_count = rex::bit_count(dest_write_mask);
    assert_true((src.swizzle_ & ((1 << (component_count * 2)) - 1)) ==
                (Src::kXYZW & ((1 << (component_count * 2)) - 1)));
    uint32_t src_mask = (1 << component_count) - 1;
    uint32_t operands_length =
        dest.GetLength() + byte_offset.GetLength(0b0000) + src.GetLength(src_mask, true);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kLdRaw, operands_length));
    dest.Write(code_);
    byte_offset.Write(code_, true, 0b0000);
    src.Write(code_, true, src_mask, true);
    ++stat_.instruction_count;
    ++stat_.texture_load_instructions;
  }
  void OpStoreRaw(const Dest& dest, const Src& byte_offset, const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();
    assert_true(dest_write_mask == 0b0001 || dest_write_mask == 0b0011 ||
                dest_write_mask == 0b0111 || dest_write_mask == 0b1111);
    uint32_t operands_length =
        dest.GetLength() + byte_offset.GetLength(0b0000) + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kStoreRaw, operands_length));
    dest.Write(code_);
    byte_offset.Write(code_, true, 0b0000);
    value.Write(code_, true, dest_write_mask);
    ++stat_.instruction_count;
    ++stat_.c_texture_store_instructions;
  }
  void OpAtomicAnd(const Dest& dest, const Src& address, uint32_t address_components,
                   const Src& value) {
    EmitAtomicOp(Opcode::kAtomicAnd, dest, address, address_components, value);
  }
  void OpAtomicOr(const Dest& dest, const Src& address, uint32_t address_components,
                  const Src& value) {
    EmitAtomicOp(Opcode::kAtomicOr, dest, address, address_components, value);
  }
  void OpAtomicIAdd(const Dest& dest, const Src& address, uint32_t address_components,
                    const Src& value) {
    EmitAtomicOp(Opcode::kAtomicIAdd, dest, address, address_components, value);
  }
  void OpEvalSampleIndex(const Dest& dest, const Src& value, const Src& sample_index) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length =
        dest.GetLength() + value.GetLength(dest_write_mask) + sample_index.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEvalSampleIndex, operands_length));
    dest.Write(code_);
    value.Write(code_, false, dest_write_mask);
    sample_index.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void OpEvalCentroid(const Dest& dest, const Src& value) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + value.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(Opcode::kEvalCentroid, operands_length));
    dest.Write(code_);
    value.Write(code_, false, dest_write_mask);
    ++stat_.instruction_count;
  }

 private:
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src,
                 bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length =
        dest.GetLength() + src0.GetLength(dest_write_mask) + src1.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, const Src& src2, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src0.GetLength(dest_write_mask) +
                               src1.GetLength(dest_write_mask) + src2.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    src2.Write(code_, (src_are_integer & 0b100) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest, const Src& src0,
                 const Src& src1, const Src& src2, const Src& src3, bool saturate = false) {
    uint32_t dest_write_mask = dest.GetMask();
    uint32_t operands_length = dest.GetLength() + src0.GetLength(dest_write_mask) +
                               src1.GetLength(dest_write_mask) + src2.GetLength(dest_write_mask) +
                               src3.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    src2.Write(code_, (src_are_integer & 0b100) != 0, dest_write_mask);
    src3.Write(code_, (src_are_integer & 0b1000) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest0, const Dest& dest1,
                 const Src& src, bool saturate = false) {
    uint32_t dest_write_mask = dest0.GetMask() | dest1.GetMask();
    uint32_t operands_length =
        dest0.GetLength() + dest1.GetLength() + src.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest0.Write(code_);
    dest1.Write(code_);
    src.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitAluOp(Opcode opcode, uint32_t src_are_integer, const Dest& dest0, const Dest& dest1,
                 const Src& src0, const Src& src1, bool saturate = false) {
    uint32_t dest_write_mask = dest0.GetMask() | dest1.GetMask();
    uint32_t operands_length = dest0.GetLength() + dest1.GetLength() +
                               src0.GetLength(dest_write_mask) + src1.GetLength(dest_write_mask);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length, saturate));
    dest0.Write(code_);
    dest1.Write(code_);
    src0.Write(code_, (src_are_integer & 0b1) != 0, dest_write_mask);
    src1.Write(code_, (src_are_integer & 0b10) != 0, dest_write_mask);
    ++stat_.instruction_count;
  }
  void EmitFlowOp(Opcode opcode, const Src& src, bool test = false) {
    uint32_t operands_length = src.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length) | (test ? (1 << 18) : 0));
    src.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void EmitFlowOp(Opcode opcode, const Src& src0, const Src& src1, bool test = false) {
    uint32_t operands_length = src0.GetLength(0b0000) + src1.GetLength(0b0000);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length) | (test ? (1 << 18) : 0));
    src0.Write(code_, true, 0b0000);
    src1.Write(code_, true, 0b0000);
    ++stat_.instruction_count;
  }
  void EmitAtomicOp(Opcode opcode, const Dest& dest, const Src& address,
                    uint32_t address_components, const Src& value) {
    assert_zero(dest.GetMask());
    uint32_t address_mask = (1 << address_components) - 1;
    uint32_t operands_length =
        dest.GetLength() + address.GetLength(address_mask) + value.GetLength(0b0001);
    code_.reserve(code_.size() + 1 + operands_length);
    code_.push_back(OpcodeToken(opcode, operands_length));
    dest.Write(code_);
    address.Write(code_, true, address_mask);
    value.Write(code_, true, 0b0001);
    ++stat_.instruction_count;
    ++stat_.c_interlocked_instructions;
  }

  std::vector<uint32_t>& code_;
  Statistics& stat_;
};

}

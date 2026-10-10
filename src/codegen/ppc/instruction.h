/**
 * @file        arch/ppc/instruction.h
 * @brief       PowerPC instruction representation and decoding
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include "opcode.h"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <rex/types.h>

namespace rex::codegen::ppc {

struct Instruction {
  uint32_t address = 0;
  rex::be<uint32_t> code{0};
  Opcode opcode = Opcode::kUnknown;
  InstrFormat format = InstrFormat::kUnknown;

  struct FormatI {
    uint32_t LI : 24;
    uint32_t AA : 1;
    uint32_t LK : 1;
    uint32_t _pad : 6;

    int32_t offset() const {
      int32_t val = (int32_t)(LI << 8) >> 6;
      return val;
    }
  };

  struct FormatB {
    uint32_t BD : 14;
    uint32_t AA : 1;
    uint32_t LK : 1;
    uint32_t BI : 5;
    uint32_t BO : 5;
    uint32_t _pad : 6;

    int32_t offset() const {
      int32_t val = (int32_t)(BD << 18) >> 16;
      return val;
    }
  };

  struct FormatD {
    uint32_t d : 16;
    uint32_t RA : 5;
    uint32_t RT : 5;
    uint32_t _pad : 6;

    int32_t SIMM() const { return (int32_t)((int16_t)d); }

    uint32_t UIMM() const { return (uint32_t)d; }

    uint32_t RS() const { return RT; }
  };

  struct FormatDS {
    uint32_t XO : 2;
    uint32_t DS : 14;
    uint32_t RA : 5;
    uint32_t RT : 5;
    uint32_t _pad : 6;

    int32_t displacement() const { return (int32_t)((int16_t)(DS << 2)); }

    uint32_t RS() const { return RT; }
  };

  struct FormatX {
    uint32_t Rc : 1;
    uint32_t XO : 10;
    uint32_t RB : 5;
    uint32_t RA : 5;
    uint32_t RT : 5;
    uint32_t _pad : 6;

    uint32_t RS() const { return RT; }
  };

  struct FormatXL {
    uint32_t LK : 1;
    uint32_t XO : 10;
    uint32_t _unused : 5;
    uint32_t BI : 5;
    uint32_t BO : 5;
    uint32_t _pad : 6;
  };

  struct FormatXFX {
    uint32_t _unused : 1;
    uint32_t XO : 10;
    uint32_t SPR : 10;
    uint32_t RT : 5;
    uint32_t _pad : 6;

    uint32_t spr_num() const {
      uint32_t lower = (SPR >> 5) & 0x1F;
      uint32_t upper = SPR & 0x1F;
      return (upper << 5) | lower;
    }

    uint32_t RS() const { return RT; }
  };

  struct FormatXO {
    uint32_t Rc : 1;
    uint32_t XO : 9;
    uint32_t OE : 1;
    uint32_t RB : 5;
    uint32_t RA : 5;
    uint32_t RT : 5;
    uint32_t _pad : 6;
  };

  struct FormatM {
    uint32_t Rc : 1;
    uint32_t ME : 5;
    uint32_t MB : 5;
    uint32_t SH : 5;
    uint32_t RA : 5;
    uint32_t RS : 5;
    uint32_t _pad : 6;

    uint32_t RB() const { return SH; }
  };

  struct FormatMD {
    uint32_t Rc : 1;
    uint32_t XO : 3;
    uint32_t mb : 6;
    uint32_t sh : 6;
    uint32_t RA : 5;
    uint32_t RS : 5;
    uint32_t _pad : 6;
  };

  struct FormatA {
    uint32_t Rc : 1;
    uint32_t XO : 5;
    uint32_t FRC : 5;
    uint32_t FRB : 5;
    uint32_t FRA : 5;
    uint32_t FRT : 5;
    uint32_t _pad : 6;
  };

  struct FormatVA {
    uint32_t XO : 6;
    uint32_t VRC : 5;
    uint32_t VRB : 5;
    uint32_t VRA : 5;
    uint32_t VRT : 5;
    uint32_t _pad : 6;

    uint32_t VD() const { return VRT; }
  };

  struct FormatVX {
    uint32_t XO : 11;
    uint32_t VRB : 5;
    uint32_t VRA : 5;
    uint32_t VRT : 5;
    uint32_t _pad : 6;

    uint32_t UIMM() const { return VRA; }
    int32_t SIMM() const { return (int32_t)((int8_t)(VRA << 3) >> 3); }
    uint32_t VD() const { return VRT; }
  };

  struct FormatVXR {
    uint32_t XO : 10;
    uint32_t Rc : 1;
    uint32_t VRB : 5;
    uint32_t VRA : 5;
    uint32_t VRT : 5;
    uint32_t _pad : 6;

    uint32_t VD() const { return VRT; }
  };

  struct FormatVMX128 {
    uint32_t XO : 6;
    uint32_t VRC : 5;
    uint32_t VRB : 5;
    uint32_t VRA : 5;
    uint32_t VRT : 5;
    uint32_t _pad : 6;

    uint32_t VD() const { return VRT; }
  };

  union {
    FormatI I;
    FormatB B;
    FormatD D;
    FormatDS DS;
    FormatX X;
    FormatXL XL;
    FormatXFX XFX;
    FormatXO XO;
    FormatM M;
    FormatMD MD;
    FormatA A;
    FormatVA VA;
    FormatVX VX;
    FormatVXR VXR;
    FormatVMX128 VMX128;
    uint32_t raw;
  };

  static int32_t get_i_offset(uint32_t instr) {
    return static_cast<int32_t>(((instr & 0x3FFFFFC) ^ 0x2000000) - 0x2000000);
  }

  static int32_t get_b_offset(uint32_t instr) {
    return static_cast<int32_t>(((instr & 0xFFFC) ^ 0x8000) - 0x8000);
  }

  std::optional<uint32_t> branch_target;

  bool is_branch() const;

  bool is_call() const;

  bool is_return() const;

  bool is_indirect_branch() const;

  bool is_record_form() const;

  bool is_conditional() const;

  std::vector<uint8_t> get_register_reads() const;

  std::vector<uint8_t> get_register_writes() const;

  std::string to_string() const;

  struct Semantics {
    std::vector<uint8_t> reads_gpr;
    std::vector<uint8_t> writes_gpr;
    bool reads_memory = false;
    bool writes_memory = false;
    bool reads_lr = false;
    bool writes_lr = false;
    bool reads_ctr = false;
    bool writes_ctr = false;
    bool reads_cr = false;
    bool writes_cr = false;
    bool is_branch = false;
    bool is_call = false;
    bool is_return = false;
  };

  Semantics get_semantics() const;
};

Instruction decode_instruction(uint32_t address, uint32_t code);

class InstructionString {
 public:
  static std::string disassemble(const Instruction& instr);

 private:
  static std::string format_register(u8 reg);
  static std::string format_immediate(i32 imm);
  static std::string format_address(guest_addr_t addr);
  static std::string format_offset(i32 offset, u8 base_reg);

  static std::string format_branch(const Instruction& instr);
  static std::string format_load_store(const Instruction& instr);
  static std::string format_immediate_alu(const Instruction& instr);
  static std::string format_register_alu(const Instruction& instr);
  static std::string format_compare(const Instruction& instr);
  static std::string format_spr(const Instruction& instr);
  static std::string format_rotate(const Instruction& instr);
  static std::string format_float(const Instruction& instr);
  static std::string format_vector(const Instruction& instr);
};

}

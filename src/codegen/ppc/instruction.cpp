/**
 * @file        arch/ppc/instruction.cpp
 * @brief       PowerPC instruction implementation
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "instruction.h"
#include "opcode.h"

#include <rex/types.h>

namespace rex::codegen::ppc {

constexpr u32 SPR_LR = 8;
constexpr u32 SPR_CTR = 9;

bool Instruction::is_branch() const {
  const auto& info = get_opcode_info(opcode);
  return info.group == OpcodeGroup::kBranch;
}

bool Instruction::is_call() const {
  switch (opcode) {
    case Opcode::bl:
    case Opcode::bla:
      return true;
    case Opcode::bcl:
    case Opcode::bcla:
    case Opcode::bclrl:
    case Opcode::bcctrl:
      return true;
    default:
      return false;
  }
}

bool Instruction::is_return() const {
  if (opcode == Opcode::bclr) {
    return (raw == 0x4E800020);
  }
  return false;
}

bool Instruction::is_indirect_branch() const {
  return opcode == Opcode::bclr || opcode == Opcode::bcctr;
}

bool Instruction::is_record_form() const {
  switch (format) {
    case InstrFormat::kX:
      return X.Rc != 0;
    case InstrFormat::kXO:
      return XO.Rc != 0;
    case InstrFormat::kM:
      return M.Rc != 0;
    case InstrFormat::kMD:
      return MD.Rc != 0;
    case InstrFormat::kA:
      return A.Rc != 0;
    case InstrFormat::kVXR:
      return VXR.Rc != 0;
    default:
      return false;
  }
}

bool Instruction::is_conditional() const {
  switch (opcode) {
    case Opcode::bc:
    case Opcode::bca:
    case Opcode::bcl:
    case Opcode::bcla:
      return true;
    case Opcode::bclr:
    case Opcode::bclrl:
    case Opcode::bcctr:
    case Opcode::bcctrl:

      return XL.BO != 20;
    default:
      return false;
  }
}

std::vector<u8> Instruction::get_register_reads() const {
  std::vector<u8> regs;

  switch (format) {
    case InstrFormat::kD:
      if (D.RA != 0)
        regs.push_back((u8)D.RA);
      break;
    case InstrFormat::kX:
      if (X.RA != 0)
        regs.push_back((u8)X.RA);
      if (X.RB != 0)
        regs.push_back((u8)X.RB);
      break;
    case InstrFormat::kXO:
      if (XO.RA != 0)
        regs.push_back((u8)XO.RA);
      if (XO.RB != 0)
        regs.push_back((u8)XO.RB);
      break;
    case InstrFormat::kM:
      regs.push_back((u8)M.RS);
      break;
    default:
      break;
  }

  return regs;
}

std::vector<u8> Instruction::get_register_writes() const {
  std::vector<u8> regs;

  switch (format) {
    case InstrFormat::kD:
      regs.push_back((u8)D.RT);
      break;
    case InstrFormat::kX:
      regs.push_back((u8)X.RT);
      break;
    case InstrFormat::kXO:
      regs.push_back((u8)XO.RT);
      break;
    case InstrFormat::kM:
      regs.push_back((u8)M.RA);
      break;
    default:
      break;
  }

  return regs;
}

Instruction::Semantics Instruction::get_semantics() const {
  Semantics sem;

  sem.reads_gpr = get_register_reads();
  sem.writes_gpr = get_register_writes();
  sem.is_branch = is_branch();
  sem.is_call = is_call();
  sem.is_return = is_return();

  const auto& info = get_opcode_info(opcode);
  if (info.group == OpcodeGroup::kMemory) {
    switch (opcode) {
      case Opcode::lbz:
      case Opcode::lbzu:
      case Opcode::lhz:
      case Opcode::lhzu:
      case Opcode::lwz:
      case Opcode::lwzu:
      case Opcode::ld:
      case Opcode::ldu:
        sem.reads_memory = true;
        break;
      case Opcode::stb:
      case Opcode::stbu:
      case Opcode::sth:
      case Opcode::sthu:
      case Opcode::stw:
      case Opcode::stwu:
      case Opcode::std:
      case Opcode::stdu:
        sem.writes_memory = true;
        break;
      default:
        break;
    }
  }

  if (opcode == Opcode::mfspr) {
    u32 spr = XFX.spr_num();
    if (spr == SPR_LR)
      sem.reads_lr = true;
    else if (spr == SPR_CTR)
      sem.reads_ctr = true;
  } else if (opcode == Opcode::mtspr) {
    u32 spr = XFX.spr_num();
    if (spr == SPR_LR)
      sem.writes_lr = true;
    else if (spr == SPR_CTR)
      sem.writes_ctr = true;
  }

  if (opcode == Opcode::mflr)
    sem.reads_lr = true;
  if (opcode == Opcode::mtlr)
    sem.writes_lr = true;
  if (opcode == Opcode::mfctr)
    sem.reads_ctr = true;
  if (opcode == Opcode::mtctr)
    sem.writes_ctr = true;

  if (opcode == Opcode::bclr || opcode == Opcode::bclrl) {
    sem.reads_lr = true;
  }
  if (opcode == Opcode::bcctr || opcode == Opcode::bcctrl) {
    sem.reads_ctr = true;
  }

  if (opcode == Opcode::cmp || opcode == Opcode::cmpi || opcode == Opcode::cmpl ||
      opcode == Opcode::cmpli) {
    sem.writes_cr = true;
  }

  return sem;
}

Instruction decode_instruction(guest_addr_t address, u32 code) {
  Instruction instr;
  instr.address = address;
  instr.code = code;
  instr.raw = code;

  instr.opcode = lookup_opcode(code);

  const auto& info = get_opcode_info(instr.opcode);
  instr.format = info.format;

  if (instr.is_branch()) {
    switch (instr.format) {
      case InstrFormat::kI: {
        i32 offset = Instruction::get_i_offset(code);
        bool aa = (code >> 1) & 1;
        if (aa) {
          instr.branch_target = static_cast<guest_addr_t>(offset & 0xFFFFFFFF);
        } else {
          instr.branch_target = address + offset;
        }
        break;
      }

      case InstrFormat::kB: {
        i32 offset = Instruction::get_b_offset(code);
        bool aa = (code >> 1) & 1;
        if (aa) {
          instr.branch_target = static_cast<guest_addr_t>(offset & 0xFFFF);
        } else {
          instr.branch_target = address + offset;
        }
        break;
      }

      case InstrFormat::kXL: {
        instr.branch_target = std::nullopt;
        break;
      }

      default:
        instr.branch_target = std::nullopt;
        break;
    }
  }

  if (code == 0x4E800020) {
    instr.opcode = Opcode::bclr;
  }

  if (code == 0x4E800420) {
    instr.opcode = Opcode::bcctr;
  }

  if (code == 0x60000000) {
    instr.opcode = Opcode::nop;
  }

  if (instr.opcode == Opcode::addi && instr.D.RA == 0) {
    instr.opcode = Opcode::li;
  }

  if (instr.opcode == Opcode::addis && instr.D.RA == 0) {
    instr.opcode = Opcode::lis;
  }

  if (instr.opcode == Opcode::or_ && instr.X.RT == instr.X.RB) {
    instr.opcode = Opcode::mr;
  }

  if (instr.opcode == Opcode::mfspr && instr.XFX.spr_num() == SPR_LR) {
    instr.opcode = Opcode::mflr;
  }

  if (instr.opcode == Opcode::mtspr && instr.XFX.spr_num() == SPR_LR) {
    instr.opcode = Opcode::mtlr;
  }

  if (instr.opcode == Opcode::mfspr && instr.XFX.spr_num() == SPR_CTR) {
    instr.opcode = Opcode::mfctr;
  }

  if (instr.opcode == Opcode::mtspr && instr.XFX.spr_num() == SPR_CTR) {
    instr.opcode = Opcode::mtctr;
  }

  return instr;
}

std::string Instruction::to_string() const {
  const auto& info = get_opcode_info(opcode);
  return std::string(info.name);
}
}

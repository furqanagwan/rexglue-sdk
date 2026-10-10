/**
 * @file        arch/ppc/opcode.h
 * @brief       PowerPC opcode definitions for Xbox 360
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>

namespace rex::codegen::ppc {

enum class InstrFormat : uint8_t {
  kUnknown = 0,
  kI,
  kB,
  kD,
  kDS,
  kX,
  kXL,
  kXFX,
  kXO,
  kM,
  kMD,
  kA,
  kVXR,
};

enum class Opcode : uint16_t {
  kUnknown = 0,

  b,
  ba,
  bl,
  bla,
  bc,
  bca,
  bcl,
  bcla,
  bclr,
  bclrl,
  bcctr,
  bcctrl,

  lbz,
  lbzu,
  lbzx,
  lhz,
  lhzu,
  lhzx,
  lha,
  lhax,
  lwz,
  lwzu,
  lwzx,
  ld,
  ldu,
  ldx,

  stb,
  stbu,
  stbx,
  sth,
  sthu,
  sthx,
  stw,
  stwu,
  stwx,
  std,
  stdu,
  stdx,

  add,
  addi,
  addis,
  addic,
  addic_,
  subf,
  subfic,
  neg,
  ori,
  oris,
  xori,
  xoris,
  andi_,
  andis_,
  mulli,

  mullw,
  mulhw,
  mulhwu,
  divw,
  divwu,

  and_,
  or_,
  xor_,
  nand,
  nor,
  andc,
  orc,
  eqv,

  slw,
  srw,
  sraw,
  srawi,
  rlwinm,
  rlwnm,
  cntlzw,

  extsb,
  extsh,

  cmp,
  cmpi,
  cmpl,
  cmpli,

  mfspr,
  mtspr,
  mfcr,
  mtcr,

  mflr,
  mtlr,
  mfctr,
  mtctr,

  sync,
  isync,

  sc,

  tw,
  twi,

  mr,

  nop,

  li,
  lis,

  lfs,
  lfsu,
  lfsx,
  lfd,
  lfdu,
  lfdx,
  stfs,
  stfsu,
  stfsx,
  stfd,
  stfdu,
  stfdx,

  fadd,
  fadds,
  fsub,
  fsubs,
  fmul,
  fmuls,
  fdiv,
  fdivs,
  fsqrt,
  fsqrts,
  fre,
  fres,
  frsqrte,
  frsqrtes,

  fmadd,
  fmadds,
  fmsub,
  fmsubs,
  fnmadd,
  fnmadds,
  fnmsub,
  fnmsubs,

  frsp,
  fctiw,
  fctiwz,
  fcfid,
  fctid,
  fctidz,

  fmr,
  fabs,
  fnabs,
  fneg,
  fsel,

  fcmpu,
  fcmpo,

  mffs,
  mtfsf,
  mtfsfi,
  mtfsb0,
  mtfsb1,

  lvx,
  lvxl,
  stvx,
  stvxl,
  lvlx,
  lvrx,
  stvlx,
  stvrx,
  lvsl,
  lvsr,

  lvx128,
  stvx128,
  lvlx128,
  lvrx128,
  stvlx128,
  stvrx128,
  lvlxl128,
  lvrxl128,
  stvlxl128,
  stvrxl128,
  lvsl128,
  lvsr128,
  lvewx128,
  lvxl128,
  stvewx128,
  stvxl128,
  vsldoi128,

  vaddfp,
  vsubfp,
  vmaddfp,
  vnmsubfp,
  vmulfp128,
  vrsqrtefp,
  vrefp,
  vlogfp,
  vexptefp,
  vmaxfp,
  vminfp,

  vaddfp128,
  vsubfp128,
  vmaddfp128,
  vmaddcfp128,
  vnmsubfp128,
  vmaxfp128,
  vminfp128,
  vrefp128,
  vrsqrtefp128,
  vexptefp128,
  vlogefp128,

  vdot3fp128,
  vdot4fp128,
  vmsum3fp128,
  vmsum4fp128,

  vaddubm,
  vadduhm,
  vadduwm,
  vsububm,
  vsubuhm,
  vsubuwm,
  vmuloub,
  vmulouh,
  vmulouw,
  vmuleub,
  vmuleuh,
  vmuleuw,
  vavgub,
  vavguh,
  vavguw,

  vand,
  vandc,
  vor,
  vorc,
  vxor,
  vnor,
  vsel,

  vand128,
  vandc128,
  vor128,
  vxor128,
  vnor128,
  vsel128,
  vslo128,
  vsro128,

  vcmpeqfp,
  vcmpgefp,
  vcmpgtfp,
  vcmpbfp,
  vcmpeqfp_,
  vcmpgefp_,
  vcmpgtfp_,

  vcmpequb,
  vcmpequh,
  vcmpequw,
  vcmpgtub,
  vcmpgtuh,
  vcmpgtuw,
  vcmpgtsb,
  vcmpgtsh,
  vcmpgtsw,

  vcmpeqfp128,
  vcmpgefp128,
  vcmpgtfp128,
  vcmpbfp128,
  vcmpequw128,

  vperm,
  vperm128,
  vmrghb,
  vmrghh,
  vmrghw,
  vmrglb,
  vmrglh,
  vmrglw,

  vmrghw128,
  vmrglw128,
  vpermwi128,

  vpkuhum,
  vpkuwum,
  vpkuhus,
  vpkuwus,
  vpkshus,
  vpkswus,
  vpkshss,
  vpkswss,
  vupkhsb,
  vupkhsh,
  vupklsb,
  vupklsh,

  vpkshss128,
  vpkshus128,
  vpkswss128,
  vpkswus128,
  vpkuhum128,
  vpkuhus128,
  vpkuwum128,
  vpkuwus128,
  vupkhsb128,
  vupklsb128,

  vspltb,
  vsplth,
  vspltw,
  vspltisb,
  vspltish,
  vspltisw,

  vspltw128,
  vspltisw128,

  vslb,
  vslh,
  vslw,
  vsrb,
  vsrh,
  vsrw,
  vsrab,
  vsrah,
  vsraw,
  vrlb,
  vrlh,
  vrlw,
  vsl,
  vsr,
  vslo,
  vsro,

  vcfux,
  vcfsx,
  vctuxs,
  vctsxs,
  vrfin,
  vrfiz,
  vrfip,
  vrfim,

  vcfpsxws128,
  vcfpuxws128,
  vcsxwfp128,
  vcuxwfp128,
  vrfim128,
  vrfin128,
  vrfip128,
  vrfiz128,

  vmrgow128,
  vmrgew128,
  vrlw128,
  vslw128,
  vsrw128,
  vsraw128,
  vupkd3d128,
  vpkd3d128,
  vrlimi128,

  mfvscr,
  mtvscr,
};

enum class OpcodeGroup : uint8_t {
  kGeneral,
  kBranch,
  kMemory,
  kSpecial,
  kSync,
  kSystem,
  kFloat,
  kVector,
};

inline bool is_branch_instruction(Opcode op) {
  switch (op) {
    case Opcode::b:
    case Opcode::ba:
    case Opcode::bl:
    case Opcode::bla:
    case Opcode::bc:
    case Opcode::bca:
    case Opcode::bcl:
    case Opcode::bcla:
    case Opcode::bclr:
    case Opcode::bclrl:
    case Opcode::bcctr:
    case Opcode::bcctrl:
      return true;
    default:
      return false;
  }
}

inline bool is_unconditional_branch(Opcode op) {
  switch (op) {
    case Opcode::b:
    case Opcode::ba:
    case Opcode::bl:
    case Opcode::bla:
      return true;
    default:
      return false;
  }
}

inline bool is_terminator_instruction(Opcode op) {
  switch (op) {
    case Opcode::b:
    case Opcode::ba:
    case Opcode::bl:
    case Opcode::bla:
    case Opcode::bc:
    case Opcode::bca:
    case Opcode::bcl:
    case Opcode::bcla:
    case Opcode::bclr:
    case Opcode::bclrl:
    case Opcode::bcctr:
    case Opcode::bcctrl:
    case Opcode::sc:
    case Opcode::tw:
    case Opcode::twi:
      return true;
    default:
      return false;
  }
}

struct OpcodeInfo {
  Opcode opcode;
  InstrFormat format;
  OpcodeGroup group;
  const char* name;
  uint32_t primary_opcode;
  uint32_t extended_opcode;
  bool has_extended;
};

Opcode lookup_opcode(uint32_t code);

const OpcodeInfo& get_opcode_info(Opcode opcode);

}

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

#include <rex/exception_handler.h>

namespace rex::arch {

// Copyright 2015, VIXL authors

//   * Redistributions of source code must retain the above copyright notice,

//   * Redistributions in binary form must reproduce the above copyright notice,

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS CONTRIBUTORS "AS IS" AND

// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE

bool IsArm64LoadPrefetchStore(uint32_t instruction, bool& is_store_out) {
  if ((instruction & kArm64LoadLiteralFMask) == kArm64LoadLiteralFixed) {
    return true;
  }
  if ((instruction & kArm64LoadStoreAnyFMask) != kArm64LoadStoreAnyFixed) {
    return false;
  }
  if ((instruction & kArm64LoadStorePairAnyFMask) == kArm64LoadStorePairAnyFixed) {
    is_store_out = !(instruction & kArm64LoadStorePairLoadBit);
    return true;
  }
  switch (Arm64LoadStoreOp(instruction & kArm64LoadStoreMask)) {
    case Arm64LoadStoreOp::kLDRB_w:
    case Arm64LoadStoreOp::kLDRH_w:
    case Arm64LoadStoreOp::kLDR_w:
    case Arm64LoadStoreOp::kLDR_x:
    case Arm64LoadStoreOp::kLDRSB_x:
    case Arm64LoadStoreOp::kLDRSH_x:
    case Arm64LoadStoreOp::kLDRSW_x:
    case Arm64LoadStoreOp::kLDRSB_w:
    case Arm64LoadStoreOp::kLDRSH_w:
    case Arm64LoadStoreOp::kLDR_b:
    case Arm64LoadStoreOp::kLDR_h:
    case Arm64LoadStoreOp::kLDR_s:
    case Arm64LoadStoreOp::kLDR_d:
    case Arm64LoadStoreOp::kLDR_q:
    case Arm64LoadStoreOp::kPRFM:
      is_store_out = false;
      return true;
    case Arm64LoadStoreOp::kSTRB_w:
    case Arm64LoadStoreOp::kSTRH_w:
    case Arm64LoadStoreOp::kSTR_w:
    case Arm64LoadStoreOp::kSTR_x:
    case Arm64LoadStoreOp::kSTR_b:
    case Arm64LoadStoreOp::kSTR_h:
    case Arm64LoadStoreOp::kSTR_s:
    case Arm64LoadStoreOp::kSTR_d:
    case Arm64LoadStoreOp::kSTR_q:
      is_store_out = true;
      return true;
    default:
      return false;
  }
}

}

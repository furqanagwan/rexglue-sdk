// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
#pragma once

#include <cstdint>
#include <vector>

namespace rex::codegen {
class BinaryView;
struct RecompilerConfig;

struct CrtJumpCandidates {
  std::vector<uint32_t> setjmp;
  std::vector<uint32_t> longjmp;
  bool uniquePair() const { return setjmp.size() == 1 && longjmp.size() == 1; }
};

CrtJumpCandidates ScanCrtJumps(const BinaryView& binary);

bool ApplyCrtJumpCandidates(const CrtJumpCandidates& candidates, RecompilerConfig& config);
}

/**
 * @file        codegen/phase_merge.cpp
 * @brief       Merge phase: resolve jumps and seal functions
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "codegen_flags.h"

#include <algorithm>

#include <rex/codegen/phases.h>
#include "phase_helpers.h"

#include <rex/logging.h>

#include "codegen_logging.h"
#include <rex/memory/utils.h>

using rex::memory::load_and_swap;

namespace rex::codegen {

namespace {

size_t registerTailBranchesIntoBodies(CodegenContext& ctx) {
  auto& graph = ctx.graph;
  std::vector<uint32_t> targets;
  for (const auto* node : graph.getPendingFunctions()) {
    for (const auto& jump : node->unresolvedJumps()) {
      if (jump.isCall || jump.isConditional || (jump.target & 3) ||
          graph.isEntryPoint(jump.target)) {
        continue;
      }

      const auto* source = ctx.binary().findSection(jump.site);
      if (!source || !source->executable || source->end() - jump.site < 4 ||
          (load_and_swap<uint32_t>(source->translate(jump.site)) & 0xFC000001u) != 0x48000000u) {
        continue;
      }
      const FunctionNode* host = graph.getFunctionContaining(jump.target);
      if (!host || host == node ||
          !std::any_of(host->blocks().begin(), host->blocks().end(), [&](const Block& block) {
            return block.contains(jump.target) && block.end() - jump.target >= 8;
          })) {
        continue;
      }
      const auto* section = ctx.binary().findSection(jump.target);
      if (!section || !section->executable || section->end() - jump.target < 8) {
        continue;
      }
      const auto* code = section->translate(jump.target);

      if ((load_and_swap<uint32_t>(code) & 0xFFFF0000u) != 0x38600000u ||
          load_and_swap<uint32_t>(code + 4) != 0x4E800020u) {
        continue;
      }
      targets.push_back(jump.target);
    }
  }
  size_t added = 0;
  for (uint32_t target : targets) {
    if (graph.isEntryPoint(target)) {
      continue;
    }
    graph.addFunction(target, 4, FunctionAuthority::DISCOVERED, true);
    REXCODEGEN_TRACE("Merge: 0x{:08X} is branched to from another function, registered", target);
    added++;
  }
  if (added) {
    discoverPendingFunctions(ctx, buildKnownFunctions(graph));
  }
  return added;
}

void mergeAndSeal(CodegenContext& ctx) {
  REXCODEGEN_TRACE("Analyze: resolving jumps and sealing functions...");

  auto& graph = ctx.graph;
  auto& binary = ctx.binary();

  graph.setMemoryReader([&binary](uint32_t addr) -> std::optional<uint32_t> {
    auto* section = binary.findSection(addr);
    if (!section || !section->data) {
      return std::nullopt;
    }
    uint32_t offset = addr - section->baseAddress;
    if (offset + 4 > section->size) {
      return std::nullopt;
    }
    return load_and_swap<uint32_t>(section->data + offset);
  });

  size_t iteration = 0;
  size_t totalResolved = 0;
  const size_t maxResolveIterations = REXCVAR_GET(max_resolve_iterations);

  while (iteration < maxResolveIterations) {
    iteration++;
    size_t changesThisIteration = 0;

    std::vector<uint32_t> pendingAddrs;
    for (const auto* node : graph.getPendingFunctions()) {
      pendingAddrs.push_back(node->base());
    }

    for (uint32_t funcAddr : pendingAddrs) {
      size_t resolved = graph.tryResolveFunction(funcAddr);
      changesThisIteration += resolved;
      totalResolved += resolved;
    }

    if (changesThisIteration == 0) {
      if (registerTailBranchesIntoBodies(ctx) == 0) {
        break;
      }
    }
  }

  size_t sharedRegs = graph.markFuncletRegisterSharing();
  if (sharedRegs > 0) {
    REXCODEGEN_DEBUG("Analyze: {} functions share registers with an SEH funclet", sharedRegs);
  }

  size_t totalSealed = graph.sealAllReady();
  size_t stillPending = graph.pendingCount();

  REXCODEGEN_TRACE("Analyze: {} iterations, resolved={}, sealed={}/{}", iteration, totalResolved,
                   totalSealed, graph.functionCount());

  if (stillPending > 0) {
    REXCODEGEN_DEBUG("Analyze: {} functions still PENDING with unresolved jumps", stillPending);
  }
}

}

namespace phases {

VoidResult Merge(CodegenContext& ctx, ProgressReporter* reporter) {
  (void)reporter;
  mergeAndSeal(ctx);
  return Ok();
}

}

}

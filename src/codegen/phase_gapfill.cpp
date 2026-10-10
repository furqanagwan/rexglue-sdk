/**
 * @file        codegen/phase_gapfill.cpp
 * @brief       GapFill phase: find uncovered code regions and register them as functions
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include "ppc/instruction.h"

#include <algorithm>
#include <optional>
#include <unordered_set>
#include <vector>

#include <rex/codegen/phases.h>
#include "codegen_flags.h"
#include "phase_helpers.h"

#include <rex/logging.h>

#include "codegen_logging.h"
#include <rex/memory/utils.h>

#include <ppc.h>

using rex::codegen::ppc::decode_instruction;
using rex::codegen::ppc::Opcode;
using rex::memory::load_and_swap;

namespace rex::codegen {

namespace {

std::vector<CodeRegion> splitRegionOnTerminators(
    const CodeRegion& region, const BinaryView& binary,
    const std::unordered_set<uint32_t>& knownCallables) {
  std::vector<CodeRegion> segments;
  uint32_t segmentStart = region.start;

  for (uint32_t addr = region.start; addr < region.end; addr += 4) {
    const uint8_t* data = binary.translate(addr);
    if (!data)
      break;

    uint32_t raw = load_and_swap<uint32_t>(data);
    auto decoded = decode_instruction(addr, raw);
    bool shouldSplit = false;
    const char* reason = nullptr;

    if (decoded.is_return()) {
      shouldSplit = true;
      reason = "blr";
    } else if (decoded.opcode == Opcode::b && decoded.branch_target.has_value()) {
      uint32_t target = decoded.branch_target.value();

      if (target != segmentStart && knownCallables.contains(target)) {
        shouldSplit = true;
        reason = "tail call";
      }
    }

    if (shouldSplit) {
      uint32_t segmentEnd = addr + 4;
      if (segmentEnd > segmentStart) {
        segments.push_back({segmentStart, segmentEnd});
        REXCODEGEN_TRACE("GapFill: split segment 0x{:08X}-0x{:08X} ({} at 0x{:08X})", segmentStart,
                         segmentEnd, reason, addr);
      }
      segmentStart = segmentEnd;
    }
  }

  if (segmentStart < region.end) {
    segments.push_back({segmentStart, region.end});
  }

  return segments;
}

bool looksLikeExceptionData(const BinaryView& binary, const FunctionGraph& graph, uint32_t addr) {
  const auto* section = binary.findSection(addr);
  if (!section || section->end() - addr < 8)
    return false;
  const uint8_t* data = binary.translate(addr);
  if (!data)
    return false;

  uint32_t firstDword = load_and_swap<uint32_t>(data);
  uint32_t secondDword = load_and_swap<uint32_t>(data + 4);

  if (!graph.isEntryPoint(firstDword)) {
    return false;
  }

  auto* rdataSection = binary.findSectionByName(".rdata");
  if (!rdataSection)
    return false;

  uint32_t rdataStart = rdataSection->baseAddress;
  uint32_t rdataEnd = rdataStart + rdataSection->size;

  if (secondDword >= rdataStart && secondDword < rdataEnd) {
    REXCODEGEN_TRACE(
        "GapFill: 0x{:08X} looks like exception data (handler=0x{:08X}, scope=0x{:08X}), skipping",
        addr, firstDword, secondDword);
    return true;
  }

  return false;
}

bool registerGapSegment(CodegenContext& ctx, const CodeRegion& segment) {
  auto& graph = ctx.graph;
  if (graph.isEntryPoint(segment.start))
    return false;
  if (graph.getFunctionContaining(segment.start))
    return false;
  if (looksLikeExceptionData(ctx.binary(), graph, segment.start))
    return false;
  uint32_t segmentSize = segment.size();
  graph.addFunction(segment.start, segmentSize, FunctionAuthority::GAP_FILL, false);
  REXCODEGEN_TRACE("GapFill: registered sub_{:08X} (0x{:08X}-0x{:08X}, {} bytes)", segment.start,
                   segment.start, segment.end, segmentSize);
  return true;
}

std::vector<CodeRegion> gapFillCodeRegions(CodegenContext& ctx) {
  REXCODEGEN_TRACE("Analyze: checking for uncovered code regions...");

  auto& graph = ctx.graph;
  auto& binary = ctx.binary();
  auto& scan = ctx.scan;

  std::unordered_set<uint32_t> knownCallables;
  for (const auto& [addr, node] : graph.functions()) {
    knownCallables.insert(addr);
  }

  size_t gapsFound = 0;
  size_t segmentsCreated = 0;
  std::vector<CodeRegion> entrySegments;

  for (const auto& region : scan.codeRegions) {
    auto segments = splitRegionOnTerminators(region, binary, knownCallables);

    for (const auto& segment : segments) {
      if (graph.isEntryPoint(segment.start) || graph.getFunctionContaining(segment.start)) {
        entrySegments.push_back(segment);
      } else if (registerGapSegment(ctx, segment)) {
        segmentsCreated++;
      }
    }

    gapsFound++;
  }

  if (segmentsCreated > 0) {
    REXCODEGEN_TRACE("Analyze: registered {} gap functions from {} regions", segmentsCreated,
                     gapsFound);
  } else {
    REXCODEGEN_TRACE("Analyze: no uncovered regions found");
  }
  return entrySegments;
}

uint32_t claimedPrefixEnd(const FunctionGraph& graph, const CodeRegion& segment,
                          std::vector<const FunctionNode*>& owners) {
  uint32_t cursor = segment.start;
  while (cursor < segment.end) {
    const FunctionNode* node = graph.getFunction(cursor);
    if (!node) {
      node = graph.getFunctionContaining(cursor);
    }
    if (!node || !node->isDiscovered() || node->blocks().empty()) {
      break;
    }

    uint32_t bodyEnd = cursor;
    for (const auto& block : node->blocks()) {
      if (block.base < segment.end) {
        bodyEnd = std::max(bodyEnd, block.end());
      }
    }
    if (node->authority() == FunctionAuthority::PDATA ||
        node->authority() == FunctionAuthority::CONFIG) {
      bodyEnd = std::max(bodyEnd, node->end());
    }
    if (bodyEnd <= cursor) {
      break;
    }
    owners.push_back(node);
    cursor = bodyEnd;
  }
  return cursor;
}

std::unordered_set<uint32_t> dataCodePointers(const BinaryView& binary) {
  std::unordered_set<uint32_t> pointers;
  for (const auto& section : binary.sections()) {
    if (section.executable || !section.data) {
      continue;
    }
    for (uint32_t offset = 0; offset + 4 <= section.size; offset += 4) {
      const uint32_t value = load_and_swap<uint32_t>(section.data + offset);
      if ((value & 3) == 0 && binary.isExecutable(value)) {
        pointers.insert(value);
      }
    }
  }
  return pointers;
}

size_t gapFillLeftovers(CodegenContext& ctx, const std::vector<CodeRegion>& entrySegments) {
  auto& graph = ctx.graph;
  auto& binary = ctx.binary();

  std::unordered_set<uint32_t> knownCallables;
  std::vector<CodeRegion> segments = entrySegments;
  for (const auto& [addr, node] : graph.functions()) {
    knownCallables.insert(addr);
    if (node->authority() == FunctionAuthority::GAP_FILL) {
      segments.push_back({node->base(), node->end()});
    }
  }

  std::vector<CodeRegion> leftovers;
  for (const auto& segment : segments) {
    std::vector<const FunctionNode*> owners;
    const uint32_t leftoverStart = claimedPrefixEnd(graph, segment, owners);
    if (owners.empty() || leftoverStart >= segment.end) {
      continue;
    }
    bool branchesIntoLeftover = false;
    for (const auto* owner : owners) {
      for (const auto& jump : owner->unresolvedJumps()) {
        if (jump.target >= leftoverStart && jump.target < segment.end) {
          branchesIntoLeftover = true;
          break;
        }
      }
    }
    if (branchesIntoLeftover) {
      continue;
    }
    const uint8_t* first = binary.translate(leftoverStart);
    if (!first || load_and_swap<uint32_t>(first) == 0) {
      continue;
    }
    leftovers.push_back({leftoverStart, segment.end});
  }

  size_t registered = 0;
  std::optional<std::unordered_set<uint32_t>> pointers;
  for (const auto& leftover : leftovers) {
    for (const auto& segment : splitRegionOnTerminators(leftover, binary, knownCallables)) {
      if (segment.size() == 4) {
        const auto* data = binary.translate(segment.start);
        if (data && decode_instruction(segment.start, load_and_swap<uint32_t>(data)).is_return()) {
          if (!pointers) {
            pointers = dataCodePointers(binary);
          }
          if (!pointers->contains(segment.start))
            continue;
        }
      }
      if (registerGapSegment(ctx, segment)) {
        REXCODEGEN_TRACE("GapFill: leftover from 0x{:08X} gives sub_{:08X}", leftover.start,
                         segment.start);
        registered++;
      }
    }
  }
  return registered;
}

void cleanupAbsorbedGapFills(CodegenContext& ctx) {
  auto& graph = ctx.graph;
  std::vector<uint32_t> toRemove;

  for (const auto& [addr, node] : graph.functions()) {
    if (node->authority() != FunctionAuthority::GAP_FILL)
      continue;

    for (const auto& [otherAddr, otherNode] : graph.functions()) {
      if (otherAddr == addr)
        continue;
      if (!otherNode->containsAddress(addr))
        continue;

      if (otherNode->authority() != FunctionAuthority::GAP_FILL) {
        toRemove.push_back(addr);
        break;
      } else if (otherAddr < addr) {
        toRemove.push_back(addr);
        break;
      }
    }
  }

  for (uint32_t addr : toRemove) {
    graph.removeFunction(addr);
  }

  if (!toRemove.empty()) {
    REXCODEGEN_TRACE("Analyze: removed {} absorbed GAP_FILL functions", toRemove.size());
  }
}

}

namespace phases {

VoidResult GapFill(CodegenContext& ctx, ProgressReporter* reporter) {
  (void)reporter;
  const std::vector<CodeRegion> entrySegments = gapFillCodeRegions(ctx);

  auto known = buildKnownFunctions(ctx.graph, true);
  size_t discovered = discoverPendingFunctions(ctx, known);
  REXCODEGEN_TRACE("Analyze: discovered blocks for {} gap-filled functions", discovered);

  size_t leftoverFunctions = 0;
  for (uint32_t pass = 0; pass < REXCVAR_GET(max_discovery_iterations); ++pass) {
    size_t registered = gapFillLeftovers(ctx, entrySegments);
    if (!registered) {
      break;
    }
    leftoverFunctions += registered;
    known = buildKnownFunctions(ctx.graph, true);
    discoverPendingFunctions(ctx, known);
  }
  REXCODEGEN_DEBUG("GapFill: {} functions registered in gap segment leftovers", leftoverFunctions);

  cleanupAbsorbedGapFills(ctx);

  return Ok();
}

}

}

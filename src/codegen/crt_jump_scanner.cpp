// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
#include <rex/codegen/crt_jump_scanner.h>

#include <array>
#include <algorithm>
#include <span>

#include <rex/codegen/binary_view.h>
#include <rex/codegen/config.h>
#include <rex/memory/utils.h>

namespace rex::codegen {
namespace {
using rex::memory::load_and_swap;

struct Word {
  uint32_t value;
  uint32_t mask = 0xFFFFFFFFu;
};

constexpr auto SetjmpPattern() {
  std::array<Word, 179> words{};
  size_t n = 0;
  words[n++] = {0x3C800000, 0xFFFF0000};
  words[n++] = {0x80040000, 0xFFFF0000};
  for (uint32_t op : {0x2C000000u, 0x7C0903A6u, 0x4C820420u, 0x7C0802A6u, 0x7C800026u})
    words[n++] = {op};
  for (uint32_t i = 0; i < 18; ++i)
    words[n++] = {0xD9C30000 + i * 0x200008};
  for (uint32_t i = 0; i < 19; ++i)
    words[n++] = {0xF9A30098 + i * 0x200008};
  for (uint32_t i = 0; i < 64; ++i) {
    words[n++] = {0x38A00140 + 16 * i};
    words[n++] = {0x10051D0B | ((i & 31) << 21) | ((i >> 5) << 2)};
  }
  for (uint32_t op :
       {0x90030134u, 0x90830130u, 0xF8230090u, 0x38000000u, 0x90030138u, 0x38600000u, 0x4E800020u})
    words[n++] = {op};
  return words;
}

constexpr auto LongjmpPattern() {
  std::array<Word, 197> words{};
  size_t n = 0;
  for (uint32_t op :
       {0x7C0802A6u, 0x9421FFB0u, 0x90010008u, 0x7C862378u, 0x2C040000u, 0x80030138u, 0x2C800000u,
        0x7C671B78u, 0x38A00000u, 0x40820008u, 0x38C00001u, 0x408602C0u, 0x80670134u, 0x80870090u})
    words[n++] = {op};
  words[n++] = {0x48000001, 0xFC000003};
  for (uint32_t i = 0; i < 18; ++i)
    words[n++] = {0xC9C70000 + i * 0x200008};
  for (uint32_t i = 0; i < 19; ++i)
    words[n++] = {0xE9A70098 + i * 0x200008};
  for (uint32_t i = 0; i < 64; ++i) {
    words[n++] = {0x38600140 + 16 * i};
    words[n++] = {0x100338CB | ((i & 31) << 21) | ((i >> 5) << 2)};
  }
  for (uint32_t op : {0x80A70134u, 0x80870130u, 0x7CA803A6u, 0xE8270090u, 0x7C8FF120u, 0x7CC33378u,
                      0x4E800020u, 0x80670004u, 0x80870000u})
    words[n++] = {op};
  words[n++] = {0x48000001, 0xFC000003};
  words[n++] = {0x80670000};
  words[n++] = {0x80870004};
  words[n++] = {0x48000001, 0xFC000003};
  for (uint32_t op : {0x80010008u, 0x7C0803A6u, 0x38210050u, 0x4E800020u})
    words[n++] = {op};
  return words;
}

bool Matches(const uint8_t* data, std::span<const Word> pattern) {
  for (size_t i = 0; i < pattern.size(); ++i) {
    if ((load_and_swap<uint32_t>(data + i * 4) & pattern[i].mask) != pattern[i].value)
      return false;
  }
  return true;
}

uint32_t BranchTarget(const uint8_t* data, uint32_t address, uint32_t index) {
  uint32_t disp = load_and_swap<uint32_t>(data + index * 4) & 0x03FFFFFC;
  if (disp & 0x02000000)
    disp |= 0xFC000000;
  return address + index * 4 + disp;
}
}

CrtJumpCandidates ScanCrtJumps(const BinaryView& binary) {
  static constexpr auto save = SetjmpPattern();
  static constexpr auto restore = LongjmpPattern();
  CrtJumpCandidates result;
  for (const auto& section : binary.sections()) {
    if (!section.executable || !section.data)
      continue;

    for (uint64_t offset = (4 - (section.baseAddress & 3)) & 3;
         offset + save.size() * 4 <= section.size; offset += 4) {
      uint64_t address64 = uint64_t(section.baseAddress) + offset;
      if (address64 + save.size() * 4 > uint64_t(UINT32_MAX) + 1)
        break;
      auto address = static_cast<uint32_t>(address64);
      if (binary.isInImportExportRange(address))
        continue;
      const auto* data = section.data + offset;
      if (Matches(data, save)) {
        uint32_t hook =
            (load_and_swap<uint32_t>(data) << 16) + int16_t(load_and_swap<uint32_t>(data + 4));
        const auto* hookSection = binary.findSection(hook);
        if (!(hook & 3) && hookSection &&
            uint64_t(hook) + 4 <= uint64_t(hookSection->baseAddress) + hookSection->size)
          result.setjmp.push_back(address);
      }
      if (offset + restore.size() * 4 > section.size ||
          address64 + restore.size() * 4 > uint64_t(UINT32_MAX) + 1 || !Matches(data, restore))
        continue;
      uint32_t normal = BranchTarget(data, address, 14);
      uint32_t alternate = BranchTarget(data, address, 192);

      bool unwindImport = std::ranges::any_of(binary.importSymbols(), [&](const auto& symbol) {
        return symbol.address == alternate && symbol.name == "xboxkrnl@327";
      });
      if (normal == BranchTarget(data, address, 189) && binary.isExecutable(normal) &&
          binary.isExecutable(alternate) && !binary.isInImportExportRange(normal) && unwindImport)
        result.longjmp.push_back(address);
    }
  }
  return result;
}

bool ApplyCrtJumpCandidates(const CrtJumpCandidates& candidates, RecompilerConfig& config) {
  if (!candidates.uniquePair() ||
      (config.setJmpAddress && config.setJmpAddress != candidates.setjmp.front()) ||
      (config.longJmpAddress && config.longJmpAddress != candidates.longjmp.front()))
    return false;
  config.setJmpAddress = candidates.setjmp.front();
  config.longJmpAddress = candidates.longjmp.front();
  return true;
}
}

/**
 * @file        rexcodegen/vtable_scanner.cpp
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/codegen/vtable_scanner.h>
#include <rex/logging.h>

#include "codegen_logging.h"
#include <rex/memory/utils.h>
#include <rex/types.h>

using rex::memory::load_and_swap;

namespace rex::codegen {

VTableScanner::VTableScanner(const BinaryView& binary) : binary_(binary) {}

std::vector<VTableInfo> VTableScanner::scan() {
  std::vector<VTableInfo> vtables;

  auto cols = findCompleteObjectLocators();
  REXCODEGEN_DEBUG("VTableScanner: found {} Complete Object Locators", cols.size());

  for (uint32_t colAddr : cols) {
    auto vtableAddr = findVTableForCOL(colAddr);
    if (!vtableAddr) {
      REXCODEGEN_TRACE("VTableScanner: COL at 0x{:08X} has no referencing vtable", colAddr);
      continue;
    }

    VTableInfo info;
    info.vtableAddress = *vtableAddr;
    info.colAddress = colAddr;
    info.className = extractClassName(colAddr);
    info.slots = readVTableSlots(*vtableAddr);

    if (info.slots.empty()) {
      REXCODEGEN_TRACE("VTableScanner: vtable at 0x{:08X} has no valid slots", *vtableAddr);
      continue;
    }

    REXCODEGEN_DEBUG("VTableScanner: vtable at 0x{:08X} ({}) has {} slots", info.vtableAddress,
                     info.className, info.slots.size());

    vtables.push_back(std::move(info));
  }

  return vtables;
}

std::vector<uint32_t> VTableScanner::findCompleteObjectLocators() {
  std::vector<uint32_t> cols;

  const auto* rdata = binary_.findSectionByName(".rdata");
  if (!rdata || !rdata->data) {
    REXCODEGEN_WARN("VTableScanner: .rdata section not found");
    return cols;
  }

  const uint8_t* data = rdata->data;
  uint32_t base = rdata->baseAddress;
  size_t size = rdata->size;

  if (size < sizeof(RTTICompleteObjectLocator)) {
    return cols;
  }

  for (size_t offset = 0; offset + sizeof(RTTICompleteObjectLocator) <= size; offset += 4) {
    auto* col = reinterpret_cast<const RTTICompleteObjectLocator*>(data + offset);

    uint32_t signature = load_and_swap<uint32_t>(&col->signature);
    uint32_t typeDescPtr = load_and_swap<uint32_t>(&col->pTypeDescriptor);

    if (signature != 0) {
      continue;
    }

    const auto* typeDescSection = binary_.findSection(typeDescPtr);
    if (!typeDescSection || !typeDescSection->data) {
      continue;
    }

    std::string typeName = readString(typeDescPtr + 8, 64);
    if (typeName.find(".?AV") != 0 && typeName.find(".?AU") != 0) {
      continue;
    }

    uint32_t colAddr = base + static_cast<uint32_t>(offset);
    cols.push_back(colAddr);

    REXCODEGEN_TRACE("VTableScanner: found COL at 0x{:08X} -> {}", colAddr, typeName);
  }

  return cols;
}

std::optional<uint32_t> VTableScanner::findVTableForCOL(uint32_t colAddr) {
  const auto* rdata = binary_.findSectionByName(".rdata");
  if (!rdata || !rdata->data) {
    return std::nullopt;
  }

  const uint8_t* data = rdata->data;
  uint32_t base = rdata->baseAddress;
  size_t size = rdata->size;

  for (size_t offset = 0; offset + 4 <= size; offset += 4) {
    uint32_t value = load_and_swap<uint32_t>(data + offset);

    if (value == colAddr) {
      uint32_t vtableAddr = base + static_cast<uint32_t>(offset) + 4;
      return vtableAddr;
    }
  }

  return std::nullopt;
}

std::vector<uint32_t> VTableScanner::readVTableSlots(uint32_t vtableStart) {
  std::vector<uint32_t> slots;

  uint32_t slotAddr = vtableStart;

  while (true) {
    auto funcAddr = readDword(slotAddr);
    if (!funcAddr) {
      break;
    }

    uint32_t addr = *funcAddr;

    if (addr == 0) {
      break;
    }

    if (!isExecutableAddress(addr)) {
      break;
    }

    if (addr & 0x3) {
      break;
    }

    slots.push_back(addr);
    slotAddr += 4;
  }

  return slots;
}

std::string VTableScanner::extractClassName(uint32_t colAddr) {
  auto typeDescPtr = readDword(colAddr + 12);
  if (!typeDescPtr) {
    return "";
  }

  std::string mangled = readString(*typeDescPtr + 8, 256);

  if (mangled.size() > 4 && (mangled.substr(0, 4) == ".?AV" || mangled.substr(0, 4) == ".?AU")) {
    size_t end = mangled.find("@@");
    if (end != std::string::npos) {
      return mangled.substr(4, end - 4);
    }
  }

  return mangled;
}

bool VTableScanner::isExecutableAddress(uint32_t addr) const {
  return binary_.isExecutable(addr);
}

std::optional<uint32_t> VTableScanner::readDword(uint32_t addr) const {
  const auto* section = binary_.findSection(addr);
  if (!section || !section->data) {
    return std::nullopt;
  }

  uint32_t offset = addr - section->baseAddress;
  if (offset + 4 > section->size) {
    return std::nullopt;
  }

  return load_and_swap<uint32_t>(section->data + offset);
}

std::string VTableScanner::readString(uint32_t addr, size_t maxLen) const {
  const auto* section = binary_.findSection(addr);
  if (!section || !section->data) {
    return "";
  }

  uint32_t offset = addr - section->baseAddress;
  size_t available = section->size - offset;
  size_t len = std::min(maxLen, available);

  const char* str = reinterpret_cast<const char*>(section->data + offset);
  size_t actualLen = strnlen(str, len);

  return std::string(str, actualLen);
}

}

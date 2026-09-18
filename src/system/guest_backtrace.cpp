/**
 * @file        system/guest_backtrace.cpp
 * @brief       Return addresses of the guest functions on the calling thread
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include <rex/ppc/backtrace.h>

#include <cstring>

#include <rex/system/thread_state.h>
#include <rex/system/xmemory.h>

namespace rex::ppc {
namespace {

// The PowerPC frame the recompiler emits, as __savegprlr_N builds it: on entry
// r1 is the caller's stack pointer S, the helper stores the return address at
// S + 8, and the prologue's stwu leaves the back chain to S at the new r1. So
// walking one frame is: follow the back chain to S, then read S + 8.
constexpr uint32_t kBackChainOffset = 0;
constexpr uint32_t kReturnAddressOffset = 8;

bool ReadGuestWord(rex::memory::Memory* memory, uint32_t address, uint32_t* out) {
  if (address < 0x1000 || (address & 3) != 0) {
    return false;
  }
  auto* heap = const_cast<rex::memory::BaseHeap*>(memory->LookupHeap(address));
  if (!heap) {
    return false;
  }
  // A frame chain can run off the end of a committed region, and reading a word
  // that is not there faults the guest thread rather than this walk, so ask
  // before reading rather than after.
  uint32_t protect = 0;
  if (!heap->QueryProtect(address, &protect) ||
      !(protect & rex::memory::kMemoryProtectRead)) {
    return false;
  }
  uint32_t big_endian = 0;
  std::memcpy(&big_endian, memory->TranslateVirtual<const uint8_t*>(address), sizeof(big_endian));
  *out = __builtin_bswap32(big_endian);
  return true;
}

// Guest code lives in the module's virtual range; anything outside it is a
// stack word that happened to sit where a return address goes.
bool PlausibleCode(uint32_t address) {
  return address >= 0x82000000 && address < 0x90000000 && (address & 3) == 0;
}

}  // namespace

size_t CaptureGuestBacktrace(uint32_t* frames, size_t max_frames) {
  if (!frames || max_frames == 0) {
    return 0;
  }
  auto* thread_state = rex::runtime::ThreadState::Get();
  if (!thread_state) {
    return 0;
  }
  auto* context = thread_state->context();
  auto* memory = thread_state->memory();
  if (!context || !memory) {
    return 0;
  }

  size_t count = 0;
  // A leaf function never stores its return address, so link register first.
  const uint32_t link = static_cast<uint32_t>(context->lr);
  if (PlausibleCode(link)) {
    frames[count++] = link;
  }

  uint32_t stack_pointer = context->r1.u32;
  while (count < max_frames) {
    uint32_t caller_stack_pointer = 0;
    if (!ReadGuestWord(memory, stack_pointer + kBackChainOffset, &caller_stack_pointer)) {
      break;
    }
    // The chain grows upwards and ends at zero; anything else is not a frame.
    if (caller_stack_pointer <= stack_pointer) {
      break;
    }
    uint32_t return_address = 0;
    if (!ReadGuestWord(memory, caller_stack_pointer + kReturnAddressOffset, &return_address)) {
      break;
    }
    if (PlausibleCode(return_address) && (count == 0 || frames[count - 1] != return_address)) {
      frames[count++] = return_address;
    }
    stack_pointer = caller_stack_pointer;
  }
  return count;
}

}  // namespace rex::ppc

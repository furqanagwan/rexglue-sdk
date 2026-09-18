/**
 * @file        graphics/util/submitter_trace.h
 * @brief       The guest code that wrote each command buffer packet
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#pragma once

#include <array>
#include <climits>
#include <cstdint>
#include <mutex>
#include <vector>

#include <rex/ppc/backtrace.h>

namespace rex::memory {
class Memory;
}  // namespace rex::memory

namespace rex::graphics {

// Which guest function submitted a draw.
//
// The command processor runs behind the game: by the time it executes a draw
// packet, the guest thread that wrote that packet has moved on, so there is no
// call stack to ask. What there is, is the moment the packet was written.
//
// So the buffers the guest builds commands in are write-watched while a trace
// is running. The first write to each page after the watch is armed faults on
// the guest thread, where the stack still says which engine code is submitting,
// and that stack is kept against the page. A draw packet then carries the stack
// of whichever sample covers it.
//
// That makes the resolution a page: a sample is the code that first wrote into
// that page this frame, not necessarily the code that wrote this exact packet.
// It is enough for what this is for - finding which function submits a shader
// program's draws, across a frame's worth of samples - and it costs one page
// fault per page per frame, only while tracing.
class SubmitterTrace {
 public:
  struct Sample {
    uint32_t page_address = 0;  // Guest physical address of the page's start.
    uint32_t frames = 0;        // How many of the backtrace are filled in.
    std::array<uint32_t, rex::ppc::kMaxGuestBacktrace> backtrace{};
  };

  // Starts and stops watching. Safe to call repeatedly with the same state.
  void SetEnabled(bool enabled, rex::memory::Memory* memory);
  bool enabled() const { return enabled_; }

  // A buffer the guest builds commands in. Indirect buffers are only learnt by
  // executing them, and a game cycles through a pool of them, so what is
  // watched is the span the ones seen so far cover: a buffer used once would
  // otherwise be written before it was ever known, which is most of them.
  void NoteCommandBuffer(uint32_t physical_address, uint32_t length);

  // Re-arms every known buffer. Called once per frame: a page only faults on
  // its first write, so without this a buffer is sampled once and never again.
  void RearmForFrame();

  // The stack of the sample covering this packet, or nullptr.
  const Sample* Lookup(uint32_t physical_address) const;

 private:
  static std::pair<uint32_t, uint32_t> InvalidationThunk(void* context, uint32_t physical_address,
                                                         uint32_t length, bool exact_range);
  void OnGuestWrite(uint32_t physical_address, uint32_t length);

  // Past this the span is treated as a stray address rather than a pool, and
  // left as it was: watching tens of megabytes would fault on everything the
  // game touches, not on its command buffers.
  static constexpr uint32_t kMaxSpan = 32u * 1024 * 1024;

  bool enabled_ = false;
  rex::memory::Memory* memory_ = nullptr;
  void* invalidation_handle_ = nullptr;

  mutable std::mutex mutex_;
  uint64_t samples_taken_ = 0;
  // The watched span, empty while span_last_ is below span_first_, which is
  // what these two start as.
  uint32_t span_first_ = UINT32_MAX;
  uint32_t span_last_ = 0;
  uint32_t buffers_seen_ = 0;
  // Two frames of samples, each sorted by page_address. The command processor
  // runs behind the guest, so a draw it executes now sits in a page the guest
  // wrote a frame or more ago; keeping the frame before the current one is what
  // makes those draws findable. A page re-sampled this frame shadows its older
  // entry, so a reused buffer reports whoever wrote it last.
  std::vector<Sample> samples_;
  std::vector<Sample> previous_samples_;
};

}  // namespace rex::graphics

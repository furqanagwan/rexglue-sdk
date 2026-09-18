/**
 * @file        graphics/util/submitter_trace.cpp
 * @brief       The guest code that wrote each command buffer packet
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */
#include "submitter_trace.h"

#include <algorithm>
#include <functional>
#include <utility>

#include <rex/logging.h>
#include <rex/system/xmemory.h>

namespace rex::graphics {
namespace {

// Samples are per page, and a frame of a busy scene writes a few hundred pages
// of commands. Past this the oldest go, which only loses the buffers the guest
// stopped writing to.
constexpr size_t kMaxSamples = 4096;

constexpr uint32_t kPageSize = 4096;

// The command processor holds the addresses the guest put in its registers,
// which carry the segment bits above physical memory; the invalidation callback
// reports addresses into physical memory itself. Everything here is stored and
// looked up in the latter, so the two meet.
constexpr uint32_t kPhysicalAddressMask = 0x1FFFFFFF;

uint32_t Physical(uint32_t address) {
  return address & kPhysicalAddressMask;
}

uint32_t PageOf(uint32_t address) {
  return address & ~(kPageSize - 1);
}

}  // namespace

void SubmitterTrace::SetEnabled(bool enabled, rex::memory::Memory* memory) {
  if (enabled == enabled_) {
    return;
  }
  if (enabled) {
    if (!memory) {
      return;
    }
    memory_ = memory;
    invalidation_handle_ =
        memory_->RegisterPhysicalMemoryInvalidationCallback(InvalidationThunk, this);
    enabled_ = true;
    REXGPU_INFO("gpu_trace: watching command buffer writes for their submitters");
  } else {
    enabled_ = false;
    REXGPU_INFO("gpu_trace: {} submitter sample(s) over {} KB holding {} command buffer(s)",
                samples_taken_,
                span_last_ >= span_first_ ? (span_last_ - span_first_ + kPageSize) / 1024 : 0,
                buffers_seen_);
    samples_taken_ = 0;
    if (memory_ && invalidation_handle_) {
      memory_->UnregisterPhysicalMemoryInvalidationCallback(invalidation_handle_);
    }
    invalidation_handle_ = nullptr;
    std::lock_guard<std::mutex> lock(mutex_);
    span_first_ = UINT32_MAX;
    span_last_ = 0;
    buffers_seen_ = 0;
    samples_.clear();
    previous_samples_.clear();
  }
}

void SubmitterTrace::NoteCommandBuffer(uint32_t physical_address, uint32_t length) {
  if (!enabled_ || !length) {
    return;
  }
  const uint32_t first = PageOf(Physical(physical_address));
  const uint32_t last = PageOf(Physical(physical_address) + length - 1);
  std::lock_guard<std::mutex> lock(mutex_);
  const uint32_t grown_first = span_last_ < span_first_ ? first : std::min(span_first_, first);
  const uint32_t grown_last = span_last_ < span_first_ ? last : std::max(span_last_, last);
  if (grown_last - grown_first > kMaxSpan) {
    return;
  }
  if (grown_first != span_first_ || grown_last != span_last_) {
    span_first_ = grown_first;
    span_last_ = grown_last;
  }
  ++buffers_seen_;
}

void SubmitterTrace::RearmForFrame() {
  if (!enabled_ || !memory_) {
    return;
  }
  uint32_t first = 0;
  uint32_t last = 0;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    first = span_first_;
    last = span_last_;
    previous_samples_ = std::move(samples_);
    samples_.clear();
  }
  if (last < first) {
    return;
  }
  memory_->EnablePhysicalMemoryAccessCallbacks(first, last - first + kPageSize, true, false);
}

/*static*/ std::pair<uint32_t, uint32_t> SubmitterTrace::InvalidationThunk(
    void* context, uint32_t physical_address, uint32_t length, bool exact_range) {
  (void)exact_range;
  reinterpret_cast<SubmitterTrace*>(context)->OnGuestWrite(physical_address, length);
  // Nothing here needs a page to stay watched, and saying so lets whoever else
  // is watching this range decide how much to unwatch.
  return {0, UINT32_MAX};
}

void SubmitterTrace::OnGuestWrite(uint32_t physical_address, uint32_t length) {
  if (!enabled_) {
    return;
  }
  // This runs on the guest thread inside its access violation, so the stack
  // below it is the code that is writing the commands.
  Sample sample;
  physical_address = Physical(physical_address);
  sample.page_address = PageOf(physical_address);
  sample.frames = static_cast<uint32_t>(
      rex::ppc::CaptureGuestBacktrace(sample.backtrace.data(), sample.backtrace.size()));
  if (!sample.frames) {
    return;
  }

  std::lock_guard<std::mutex> lock(mutex_);
  // Only the span the command buffers live in; the rest of physical memory
  // faults for its own reasons.
  const bool known =
      span_last_ >= span_first_ && physical_address >= span_first_ && physical_address <= span_last_;
  if (!known) {
    return;
  }
  if (samples_.size() >= kMaxSamples) {
    return;
  }
  const uint32_t last_page = PageOf(physical_address + (length ? length - 1 : 0));
  for (uint32_t page = sample.page_address; page <= last_page; page += kPageSize) {
    Sample page_sample = sample;
    page_sample.page_address = page;
    const auto at = std::lower_bound(
        samples_.begin(), samples_.end(), page,
        [](const Sample& entry, uint32_t value) { return entry.page_address < value; });
    if (at != samples_.end() && at->page_address == page) {
      continue;  // The first writer of a page is the one worth keeping.
    }
    samples_.insert(at, page_sample);
    ++samples_taken_;
    if (page == last_page) {
      break;
    }
  }
}

const SubmitterTrace::Sample* SubmitterTrace::Lookup(uint32_t physical_address) const {
  if (!enabled_) {
    return nullptr;
  }
  std::lock_guard<std::mutex> lock(mutex_);
  const uint32_t page = PageOf(Physical(physical_address));
  for (const std::vector<Sample>& generation : {std::cref(samples_), std::cref(previous_samples_)}) {
    const auto at = std::lower_bound(
        generation.begin(), generation.end(), page,
        [](const Sample& entry, uint32_t value) { return entry.page_address < value; });
    if (at != generation.end() && at->page_address == page) {
      return &*at;
    }
  }
  return nullptr;
}

}  // namespace rex::graphics

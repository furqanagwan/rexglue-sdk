/**
 * @file        debug_markers.h
 * @brief       PIX-format GPU debug markers, balanced across submissions (RG-GDK-028)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string_view>
#include <utility>

namespace rex::graphics {

// PIX event blobs for ID3D12GraphicsCommandList and ID3D12CommandQueue
// BeginEvent/SetMarker, encoded as WinPixEventRuntime's pix3.h does for GPU
// markers (PIX_USE_GPU_MARKERS_V2, microsoft/PixEvents b0caa73, MIT:
// PIXEventsCommon.h, PIXEvents.h, pix3_win.h). The GPU blob is written by the
// header alone, so it needs neither pix3.h nor WinPixEventRuntime.dll. EndEvent
// takes no blob.
//
// Layout, in 64-bit words: the event info, the color, the context (the
// command list or queue) and the label, eight ANSI characters per word, low
// byte first, zero-terminated.
namespace pix {

// WINPIX_EVENT_PIX3BLOB_V2: the metadata argument of BeginEvent/SetMarker.
constexpr uint32_t kBlobV2Metadata = 6345127;

enum class EventType : uint64_t {
  kBeginEvent = 0x01,
  kSetMarker = 0x02,
};

// Event info word fields.
constexpr uint64_t kSizeMask = 0x7F;     // Bits 0-6, event size in words.
constexpr uint32_t kTypeShift = 7;       // Bits 7-11.
constexpr uint32_t kMetadataShift = 12;  // Bits 12-19.
// Metadata bits.
constexpr uint64_t kMetadataOnContext = 0x1;
constexpr uint64_t kMetadataStringIsAnsi = 0x2;
constexpr uint64_t kMetadataHasColor = 0xF0;

// An opaque 0xAARRGGBB color, as PIX_COLOR makes it.
constexpr uint64_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return 0xFF000000u | (uint64_t(r) << 16) | (uint64_t(g) << 8) | b;
}

// Words for a label of at most kMaxLabelLength characters.
constexpr size_t kMaxLabelLength = 255;
constexpr size_t kMaxEventWords = 3 + (kMaxLabelLength + 1 + 7) / 8;

// Writes the blob of a begin event or a marker to `words`; returns its size
// in bytes. A longer label is cut to kMaxLabelLength characters.
inline uint32_t EncodeEvent(uint64_t (&words)[kMaxEventWords], EventType type, uint64_t color,
                            const void* context, std::string_view label) {
  label = label.substr(0, std::min(label.find('\0'), kMaxLabelLength));
  size_t label_words = label.size() / 8 + 1;  // With the terminator.
  size_t size = 3 + label_words;
  std::memset(words, 0, sizeof(words));
  words[0] = (uint64_t(size) & kSizeMask) | (uint64_t(type) << kTypeShift) |
             ((kMetadataOnContext | kMetadataStringIsAnsi | kMetadataHasColor) << kMetadataShift);
  words[1] = color;
  words[2] = uint64_t(reinterpret_cast<uintptr_t>(context));
  // Little-endian words: characters in order, low byte first.
  std::memcpy(&words[3], label.data(), label.size());
  return uint32_t(size * sizeof(uint64_t));
}

}  // namespace pix

// Tracks the open debug marker regions of the command list being recorded.
//
// PIX and the D3D12 debug layer expect every BeginEvent in a command list to
// be ended in the same command list, but a region opened for a draw or a swap
// can outlive the submission: the command processor may end the submission in
// the middle of the region (the swap submits before presenting, and a fence
// wait can submit early). CloseAll ends the open regions with the command
// list, and End then ignores regions whose command list is already closed, so
// they are never ended twice or in the wrong command list.
class DebugMarkerRegions {
 public:
  // Opens a region; pass the returned token to End.
  uint64_t Begin() {
    ++depth_;
    return generation_;
  }

  // Returns whether the region's EndEvent has to be recorded: false if the
  // command list it was opened in has been closed by CloseAll.
  bool End(uint64_t token) {
    if (token != generation_ || !depth_) {
      return false;
    }
    --depth_;
    return true;
  }

  // Closes the command list: returns how many EndEvents to record for regions
  // still open, and detaches those regions from their End calls.
  uint32_t CloseAll() {
    ++generation_;
    return std::exchange(depth_, 0);
  }

  uint32_t depth() const { return depth_; }

 private:
  uint64_t generation_ = 0;
  uint32_t depth_ = 0;
};

}  // namespace rex::graphics

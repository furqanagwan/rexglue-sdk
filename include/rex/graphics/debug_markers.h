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

namespace pix {

constexpr uint32_t kBlobV2Metadata = 6345127;

enum class EventType : uint64_t {
  kBeginEvent = 0x01,
  kSetMarker = 0x02,
};

constexpr uint64_t kSizeMask = 0x7F;
constexpr uint32_t kTypeShift = 7;
constexpr uint32_t kMetadataShift = 12;

constexpr uint64_t kMetadataOnContext = 0x1;
constexpr uint64_t kMetadataStringIsAnsi = 0x2;
constexpr uint64_t kMetadataHasColor = 0xF0;

constexpr uint64_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return 0xFF000000u | (uint64_t(r) << 16) | (uint64_t(g) << 8) | b;
}

constexpr size_t kMaxLabelLength = 255;
constexpr size_t kMaxEventWords = 3 + (kMaxLabelLength + 1 + 7) / 8;

inline uint32_t EncodeEvent(uint64_t (&words)[kMaxEventWords], EventType type, uint64_t color,
                            const void* context, std::string_view label) {
  label = label.substr(0, std::min(label.find('\0'), kMaxLabelLength));
  size_t label_words = label.size() / 8 + 1;
  size_t size = 3 + label_words;
  std::memset(words, 0, sizeof(words));
  words[0] = (uint64_t(size) & kSizeMask) | (uint64_t(type) << kTypeShift) |
             ((kMetadataOnContext | kMetadataStringIsAnsi | kMetadataHasColor) << kMetadataShift);
  words[1] = color;
  words[2] = uint64_t(reinterpret_cast<uintptr_t>(context));

  std::memcpy(&words[3], label.data(), label.size());
  return uint32_t(size * sizeof(uint64_t));
}

}

class DebugMarkerRegions {
 public:
  uint64_t Begin() {
    ++depth_;
    return generation_;
  }

  bool End(uint64_t token) {
    if (token != generation_ || !depth_) {
      return false;
    }
    --depth_;
    return true;
  }

  uint32_t CloseAll() {
    ++generation_;
    return std::exchange(depth_, 0);
  }

  uint32_t depth() const { return depth_; }

 private:
  uint64_t generation_ = 0;
  uint32_t depth_ = 0;
};

}

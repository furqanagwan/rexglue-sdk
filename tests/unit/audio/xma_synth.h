/**
 * @file        tests/unit/audio/xma_synth.h
 * @brief       Synthesized XMA streams: silent WMA Pro frames FFmpeg's xmaframes accepts
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#pragma once

#include <cstdint>
#include <vector>

#include <catch2/catch_test_macros.hpp>

namespace xma_synth {

constexpr uint32_t kPacketBytes = 2048;
constexpr uint32_t kPacketBits = kPacketBytes * 8;
constexpr uint32_t kHeaderBits = 32;
constexpr uint32_t kDataBits = kPacketBits - kHeaderBits;

using Bits = std::vector<bool>;

inline void Append(Bits& bits, uint64_t value, uint32_t count) {
  while (count--) {
    bits.push_back((value >> count) & 1);
  }
}

inline Bits SilentFrame(uint32_t size_bits, bool stereo, bool more_frames,
                        bool reserved_bit = false) {
  const uint32_t fixed_bits = stereo ? 57 : 52;
  REQUIRE(size_bits > fixed_bits);
  const uint32_t fill = size_bits - fixed_bits;
  Bits bits;
  Append(bits, size_bits, 15);
  Append(bits, 0b10, 2);
  if (stereo) {
    Append(bits, 0, 1);
  }
  Append(bits, 0, 8);
  Append(bits, 0, 1);
  Append(bits, 1, 1);
  Append(bits, 0, 2);
  Append(bits, 15, 4);
  Append(bits, fill - 1, 15);
  Append(bits, 0, fill);
  Append(bits, reserved_bit, 1);
  if (stereo) {
    Append(bits, 0, 1);
    Append(bits, 0b10, 2);
  }
  Append(bits, 0, stereo ? 2 : 1);
  Append(bits, 0, 1);
  Append(bits, more_frames, 1);
  REQUIRE(bits.size() == size_bits);
  return bits;
}

struct Stream {
  std::vector<uint8_t> bytes;
  std::vector<uint32_t> frame_offsets;
};

inline void SetBit(std::vector<uint8_t>& bytes, uint32_t bit) {
  bytes[bit / 8] |= uint8_t(0x80 >> (bit % 8));
}

inline void WritePacketHeader(uint8_t* packet, uint32_t frame_count, uint32_t first_frame_bit,
                              bool xma2, uint8_t skip) {
  const uint32_t offset = first_frame_bit ? first_frame_bit - kHeaderBits : 0x7FFF;
  packet[0] = uint8_t(frame_count << 2 | ((offset >> 13) & 0x3));
  packet[1] = uint8_t(offset >> 5);
  packet[2] = uint8_t((offset & 0x1F) << 3 | (xma2 ? 1 : 0));
  packet[3] = skip;
}

inline Stream BuildStream(const std::vector<Bits>& frames, uint32_t packet_count,
                          bool xma2 = true) {
  Stream stream;
  stream.bytes.assign(size_t(packet_count) * kPacketBytes, 0);
  std::vector<uint32_t> first_frame(packet_count, 0);
  std::vector<uint32_t> frame_count(packet_count, 0);
  uint32_t data_bit = 0;
  for (const Bits& frame : frames) {
    const uint32_t start_packet = data_bit / kDataBits;
    const uint32_t start = start_packet * kPacketBits + kHeaderBits + data_bit % kDataBits;
    stream.frame_offsets.push_back(start);
    if (!frame_count[start_packet]++) {
      first_frame[start_packet] = start % kPacketBits;
    }
    for (bool bit : frame) {
      REQUIRE(data_bit / kDataBits < packet_count);
      if (bit) {
        SetBit(stream.bytes,
               (data_bit / kDataBits) * kPacketBits + kHeaderBits + data_bit % kDataBits);
      }
      ++data_bit;
    }
  }
  for (uint32_t p = 0; p < packet_count; ++p) {
    WritePacketHeader(stream.bytes.data() + p * kPacketBytes, frame_count[p], first_frame[p], xma2,
                      0);
  }
  return stream;
}

inline std::vector<Bits> SilentFrames(const std::vector<uint32_t>& sizes, bool stereo = false) {
  std::vector<Bits> frames;
  for (size_t i = 0; i < sizes.size(); ++i) {
    frames.push_back(SilentFrame(sizes[i], stereo, i + 1 < sizes.size()));
  }
  return frames;
}

}

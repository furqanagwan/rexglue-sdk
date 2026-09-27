/**
 * @file        xma_context_test.cpp
 * @brief       XMA packet/loop accounting through the real decoder (RG-GDK-018)
 *
 * Streams are synthesized: silent WMA Pro frames (no coefficients, sized with
 * subframe fill bits) laid end to end through 2048-byte XMA packets. FFmpeg's
 * xmaframes decoder accepts them, so Work() runs its real decode, realignment,
 * loop and consume paths without any title data.
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <cstring>
#include <future>
#include <thread>
#include <vector>

#include <rex/audio/xma/context.h>
#include <rex/audio/xma/helpers.h>
#include <rex/system/xmemory.h>

#include "test_memory.h"

using rex::audio::kPacketInfo;
using rex::audio::XMA_CONTEXT_DATA;
using rex::audio::XmaContext;
using rex::testing::GetTestMemory;

namespace {

constexpr uint32_t kPacketBytes = XmaContext::kBytesPerPacket;
constexpr uint32_t kPacketBits = XmaContext::kBitsPerPacket;
constexpr uint32_t kHeaderBits = XmaContext::kBitsPerPacketHeader;
constexpr uint32_t kDataBits = kPacketBits - kHeaderBits;
constexpr uint32_t kOutputBlocks = 31;
constexpr uint32_t kBlocksPerMonoFrame = 4;

using Bits = std::vector<bool>;

void Append(Bits& bits, uint64_t value, uint32_t count) {
  while (count--) {
    bits.push_back((value >> count) & 1);
  }
}

// A WMA Pro frame as FFmpeg's xmaframes decoder parses it (flags 0x10d6):
// length prefix, one full-length subframe per channel, no coefficients, so it
// decodes to silence. Subframe fill bits pad it to size_bits. reserved_bit set
// makes FFmpeg reject it.
Bits SilentFrame(uint32_t size_bits, bool stereo, bool more_frames, bool reserved_bit = false) {
  const uint32_t fixed_bits = stereo ? 57 : 52;
  REQUIRE(size_bits > fixed_bits);
  const uint32_t fill = size_bits - fixed_bits;
  Bits bits;
  Append(bits, size_bits, 15);  // frame length
  Append(bits, 0b10, 2);        // tile header: fixed layout, one 512-sample subframe
  if (stereo) {
    Append(bits, 0, 1);  // no postproc transform
  }
  Append(bits, 0, 8);   // drc gain
  Append(bits, 0, 1);   // no start/end skip
  Append(bits, 1, 1);   // subframe extended header: fill bits follow
  Append(bits, 0, 2);   //   explicit fill length
  Append(bits, 15, 4);  //   15-bit length field
  Append(bits, fill - 1, 15);
  Append(bits, 0, fill);
  Append(bits, reserved_bit, 1);
  if (stereo) {
    Append(bits, 0, 1);     // channel transform present bit
    Append(bits, 0b10, 2);  // pair: no transform
  }
  Append(bits, 0, stereo ? 2 : 1);  // no coefficients per channel
  Append(bits, 0, 1);               // the bit before the trailer
  Append(bits, more_frames, 1);     // trailer
  REQUIRE(bits.size() == size_bits);
  return bits;
}

struct Stream {
  std::vector<uint8_t> bytes;
  std::vector<uint32_t> frame_offsets;  // absolute bit offsets in the buffer
};

void SetBit(std::vector<uint8_t>& bytes, uint32_t bit) {
  bytes[bit / 8] |= uint8_t(0x80 >> (bit % 8));
}

void WritePacketHeader(uint8_t* packet, uint32_t frame_count, uint32_t first_frame_bit, bool xma2,
                       uint8_t skip) {
  // first_frame_bit 0 marks a packet in which no frame starts.
  const uint32_t offset = first_frame_bit ? first_frame_bit - kHeaderBits : 0x7FFF;
  packet[0] = uint8_t(frame_count << 2 | ((offset >> 13) & 0x3));
  packet[1] = uint8_t(offset >> 5);
  packet[2] = uint8_t((offset & 0x1F) << 3 | (xma2 ? 1 : 0));
  packet[3] = skip;
}

// Lays frames end to end through the data area of packet_count packets.
Stream BuildStream(const std::vector<Bits>& frames, uint32_t packet_count, bool xma2 = true) {
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

std::vector<Bits> SilentFrames(const std::vector<uint32_t>& sizes, bool stereo = false) {
  std::vector<Bits> frames;
  for (size_t i = 0; i < sizes.size(); ++i) {
    frames.push_back(SilentFrame(sizes[i], stereo, i + 1 < sizes.size()));
  }
  return frames;
}

// One XMA context over guest memory, with the stream in input buffer 0.
struct Harness {
  explicit Harness(const Stream& stream) : memory(GetTestMemory()) {
    using rex::memory::kSystemHeapPhysical;
    context_ptr = memory.SystemHeapAlloc(sizeof(XMA_CONTEXT_DATA), 256, kSystemHeapPhysical);
    input_ptr = memory.SystemHeapAlloc(uint32_t(stream.bytes.size()), 4096, kSystemHeapPhysical);
    output_ptr = memory.SystemHeapAlloc(kOutputBlocks * 256, 256, kSystemHeapPhysical);
    REQUIRE(context_ptr);
    REQUIRE(input_ptr);
    REQUIRE(output_ptr);
    std::memcpy(memory.TranslateVirtual(input_ptr), stream.bytes.data(), stream.bytes.size());
    std::memset(memory.TranslateVirtual(context_ptr), 0, sizeof(XMA_CONTEXT_DATA));
    REQUIRE(context.Setup(0, &memory, context_ptr) == 0);
    context.set_is_allocated(true);

    XMA_CONTEXT_DATA data(memory.TranslateVirtual(context_ptr));
    data.input_buffer_0_packet_count = uint32_t(stream.bytes.size() / kPacketBytes);
    data.input_buffer_0_valid = 1;
    data.input_buffer_0_ptr = memory.GetPhysicalAddress(input_ptr);
    data.output_buffer_ptr = memory.GetPhysicalAddress(output_ptr);
    data.output_buffer_block_count = kOutputBlocks;
    data.output_buffer_valid = 1;
    data.subframe_decode_count = 1;
    data.sample_rate = 3;
    data.input_buffer_read_offset = kHeaderBits;
    Store(data);
  }
  ~Harness() {
    memory.SystemHeapFree(output_ptr);
    memory.SystemHeapFree(input_ptr);
    memory.SystemHeapFree(context_ptr);
  }

  XMA_CONTEXT_DATA Load() { return XMA_CONTEXT_DATA(memory.TranslateVirtual(context_ptr)); }
  void Store(XMA_CONTEXT_DATA& data) { data.Store(memory.TranslateVirtual(context_ptr)); }

  // Kicks the context once, as XMAEnableContext does.
  XMA_CONTEXT_DATA Kick() {
    context.Enable();
    REQUIRE(context.Work());
    return Load();
  }

  rex::memory::Memory& memory;
  uint32_t context_ptr = 0;
  uint32_t input_ptr = 0;
  uint32_t output_ptr = 0;
  XmaContext context;
};

// Blocks written by one kick that started with an empty ring at offset 0.
uint32_t BlocksWritten(const XMA_CONTEXT_DATA& data) {
  return data.output_buffer_write_offset;
}

}  // namespace

// --- Packet walking (pure) ---------------------------------------------------

TEST_CASE("XMA packet walk counts a frame whose header crosses the packet end", "[audio][xma]") {
  // Six frames leave 10 bits in the packet: the seventh frame's 15-bit header
  // runs into the next packet (xenia-edge adf56b76c).
  for (bool xma2 : {false, true}) {
    INFO("xma2 packet header " << xma2);
    auto frames = SilentFrames({2724, 2724, 2724, 2724, 2724, 2722, 2000, 2000});
    Stream stream = BuildStream(frames, 2, xma2);
    const uint8_t* packet = stream.bytes.data();
    REQUIRE(stream.frame_offsets[6] == kPacketBits - 10);

    kPacketInfo sixth = XmaContext::GetPacketInfo(packet, stream.frame_offsets[5]);
    CHECK(sixth.frame_count_ == 7);
    CHECK(sixth.current_frame_ == 5);
    CHECK_FALSE(sixth.isLastFrameInPacket());

    kPacketInfo split = XmaContext::GetPacketInfo(packet, stream.frame_offsets[6]);
    CHECK(split.current_frame_ == 6);
    CHECK(split.current_frame_size_ == 0);  // routes to the split-header path
    CHECK(split.isLastFrameInPacket());
  }
}

TEST_CASE("XMA packet walk resolves an offset to the next frame boundary", "[audio][xma]") {
  auto frames = SilentFrames({1000, 1000, 1000});
  Stream stream = BuildStream(frames, 1);
  const uint8_t* packet = stream.bytes.data();
  const uint32_t second = stream.frame_offsets[1];

  kPacketInfo exact = XmaContext::GetPacketInfo(packet, second);
  CHECK(exact.current_frame_offset_ == second);
  CHECK(exact.current_frame_ == 1);
  CHECK(exact.current_frame_size_ == 1000);

  // loop_start one bit short of the frame (xenia-edge 5dd1cdbbf).
  kPacketInfo early = XmaContext::GetPacketInfo(packet, second - 1);
  CHECK(early.current_frame_offset_ == second);
  CHECK(early.current_frame_size_ == 0);

  // Past the last frame there is nothing to resolve to.
  kPacketInfo past = XmaContext::GetPacketInfo(packet, stream.frame_offsets[2] + 1);
  CHECK(past.current_frame_offset_ == stream.frame_offsets[2] + 1);
}

TEST_CASE("XMA next-packet search follows the sub-stream skip chain", "[audio][xma]") {
  // Two interleaved sub-streams: A in packets 0, 1, 3; B in packet 2. Packet 1
  // only continues a frame of A and skips one packet to A's next packet
  // (xenia-edge 9d8210b32).
  std::vector<uint8_t> buffer(4 * kPacketBytes, 0);
  uint8_t* p = buffer.data();
  WritePacketHeader(p + 0 * kPacketBytes, 1, kHeaderBits, true, 1);
  WritePacketHeader(p + 1 * kPacketBytes, 0, 0, true, 1);
  WritePacketHeader(p + 2 * kPacketBytes, 1, 100, true, 1);
  WritePacketHeader(p + 3 * kPacketBytes, 1, 200, true, 1);

  CHECK(XmaContext::GetNextPacketReadOffset(p, 1, 4) == 3 * kPacketBits + 200);
  CHECK(XmaContext::GetNextPacketReadOffset(p, 2, 4) == 2 * kPacketBits + 100);

  // A frameless packet marked 0xFF ends the chain.
  WritePacketHeader(p + 1 * kPacketBytes, 0, 0, true, 0xFF);
  CHECK(XmaContext::GetNextPacketReadOffset(p, 1, 4) == kHeaderBits);
  // Running off the buffer does too.
  WritePacketHeader(p + 1 * kPacketBytes, 0, 0, true, 5);
  CHECK(XmaContext::GetNextPacketReadOffset(p, 1, 4) == kHeaderBits);
}

// --- Work() through FFmpeg ---------------------------------------------------

TEST_CASE("XMA synthetic silent frames decode through FFmpeg", "[audio][xma]") {
  auto frames = SilentFrames({1000, 1000, 1000});
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Kick();
  CHECK(h.context.decode_failure_count() == 0);
  // The first frame primes the start-padding realignment; each later frame
  // releases the previous one.
  CHECK(BlocksWritten(data) == 2 * kBlocksPerMonoFrame);
  CHECK_FALSE(data.input_buffer_0_valid);
  const uint8_t* output = h.memory.TranslatePhysical(data.output_buffer_ptr);
  for (uint32_t i = 0; i < BlocksWritten(data) * 256; ++i) {
    REQUIRE(output[i] == 0);
  }
}

TEST_CASE("XMA work drains the current frame after the input runs out", "[audio][xma]") {
  // subframe_decode_count 1 hands over one block per pass, so the pass that
  // exhausts the input leaves three blocks of the last frame
  // (xenia-edge 052365bc0).
  auto frames = SilentFrames({1000, 1000, 1000, 1000, 1000, 1000});
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Kick();
  CHECK(h.context.decode_failure_count() == 0);
  CHECK(BlocksWritten(data) == 5 * kBlocksPerMonoFrame);
  CHECK_FALSE(data.IsAnyInputBufferValid());
}

TEST_CASE("XMA split frame headers decode every frame for XMA1 and XMA2 packets", "[audio][xma]") {
  for (bool xma2 : {false, true}) {
    INFO("xma2 packet header " << xma2);
    auto frames = SilentFrames({2724, 2724, 2724, 2724, 2724, 2722, 2000, 2000});
    Harness h(BuildStream(frames, 2, xma2));
    XMA_CONTEXT_DATA data = h.Kick();
    CHECK(h.context.decode_failure_count() == 0);
    // Eight frames decoded, seven released; dropping the split frame costs one.
    CHECK(BlocksWritten(data) == 7 * kBlocksPerMonoFrame);
  }
}

TEST_CASE("XMA loop_start one bit before a frame loops like an exact loop_start", "[audio][xma]") {
  auto run = [](int32_t loop_start_adjust) {
    auto frames = SilentFrames({1000, 1000, 1000, 1000});
    Stream stream = BuildStream(frames, 1);
    Harness h(stream);
    XMA_CONTEXT_DATA data = h.Load();
    data.loop_count = 1;
    data.loop_start = stream.frame_offsets[1] + loop_start_adjust;
    data.loop_end = stream.frame_offsets[3];
    data.loop_subframe_end = 3;
    h.Store(data);
    data = h.Kick();
    CHECK(h.context.decode_failure_count() == 0);
    CHECK(data.loop_count == 0);
    return BlocksWritten(data);
  };
  // Frames 1-4, back to 2, then 2-4: seven decodes, six frames released.
  const uint32_t exact = run(0);
  CHECK(exact == 6 * kBlocksPerMonoFrame);
  CHECK(run(-1) == exact);
}

TEST_CASE("XMA output ring wraps at the block count", "[audio][xma]") {
  auto frames = SilentFrames({1000, 1000, 1000, 1000, 1000, 1000});
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Load();
  data.output_buffer_read_offset = 20;
  data.output_buffer_write_offset = 20;
  h.Store(data);
  data = h.Kick();
  CHECK(data.output_buffer_write_offset == (20 + 5 * kBlocksPerMonoFrame) % kOutputBlocks);
  CHECK(data.output_buffer_read_offset == 20);
}

TEST_CASE("XMA stereo frames release eight blocks each", "[audio][xma]") {
  auto frames = SilentFrames({1500, 1500, 1500}, /*stereo=*/true);
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Load();
  data.is_stereo = 1;
  data.subframe_decode_count = 2;
  h.Store(data);
  data = h.Kick();
  CHECK(h.context.decode_failure_count() == 0);
  CHECK(BlocksWritten(data) == 2 * 2 * kBlocksPerMonoFrame);
}

TEST_CASE("XMA decode failures are counted and not filled with silence", "[audio][xma]") {
  std::vector<Bits> frames = SilentFrames({1000, 1000, 1000, 1000, 1000});
  frames[1] = SilentFrame(1000, false, true, /*reserved_bit=*/true);
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Kick();
  CHECK(h.context.decode_failure_count() == 1);
  // Frame 2 fails and breaks the realignment, so frame 1 is never released and
  // frame 3 primes again: only frames 3 and 4 come out.
  CHECK(BlocksWritten(data) == 2 * kBlocksPerMonoFrame);
  CHECK(data.error_status == 0);
}

TEST_CASE("XMA work returns when a looping frame keeps failing", "[audio][xma]") {
  // An infinite loop over one undecodable frame used to spin in Work() with
  // the context lock held (xenia-edge ade7e610b). On regression this reports
  // the timeout, then the CTest timeout ends the still-spinning process.
  std::vector<Bits> frames = {SilentFrame(1000, false, false, /*reserved_bit=*/true)};
  Stream stream = BuildStream(frames, 1);
  Harness h(stream);
  XMA_CONTEXT_DATA data = h.Load();
  data.loop_count = 255;
  data.loop_start = stream.frame_offsets[0];
  data.loop_end = stream.frame_offsets[0];
  h.Store(data);

  h.context.Enable();
  auto work = std::async(std::launch::async, [&] { return h.context.Work(); });
  REQUIRE(work.wait_for(std::chrono::seconds(10)) == std::future_status::ready);
  CHECK(work.get());
  CHECK(h.context.decode_failure_count() >= 1);
  CHECK(BlocksWritten(h.Load()) == 0);
}

TEST_CASE("XMA single-frame loop keeps producing audio", "[audio][xma]") {
  auto frames = SilentFrames({1000});
  Stream stream = BuildStream(frames, 1);
  Harness h(stream);
  XMA_CONTEXT_DATA data = h.Load();
  data.loop_count = 255;
  data.loop_start = stream.frame_offsets[0];
  data.loop_end = stream.frame_offsets[0];
  data.loop_subframe_end = 3;
  h.Store(data);
  data = h.Kick();
  CHECK(h.context.decode_failure_count() == 0);
  // The loop fills all 31 blocks: the write offset comes round to the read
  // offset and the full buffer is handed back as invalid.
  CHECK(data.output_buffer_write_offset == data.output_buffer_read_offset);
  CHECK_FALSE(data.output_buffer_valid);
  CHECK(data.input_buffer_0_valid);
  CHECK(data.loop_count == 255);
}

TEST_CASE("XMA output stays valid when a kick releases nothing", "[audio][xma]") {
  // One frame only primes the realignment: nothing is written, which is not a
  // full buffer (xenia-canary 09dbe2cd3).
  auto frames = SilentFrames({1000});
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Kick();
  CHECK(BlocksWritten(data) == 0);
  CHECK_FALSE(data.input_buffer_0_valid);
  CHECK(data.output_buffer_valid);
}

TEST_CASE("XMA kick starved of input resets write to read", "[audio][xma]") {
  // NFS Carbon and Most Wanted watch for write == read (xenia-canary 09dbe2cd3).
  auto frames = SilentFrames({1000, 1000});
  Harness h(BuildStream(frames, 1));
  XMA_CONTEXT_DATA data = h.Load();
  data.input_buffer_0_valid = 0;
  data.output_buffer_read_offset = 5;
  data.output_buffer_write_offset = 12;
  h.Store(data);
  data = h.Kick();
  CHECK(data.output_buffer_write_offset == 5);
  CHECK_FALSE(data.output_buffer_valid);
}

TEST_CASE("XMA consume-only kick drains the frame left by a full buffer", "[audio][xma]") {
  auto frames = SilentFrames({1000});
  Stream stream = BuildStream(frames, 1);
  Harness h(stream);
  XMA_CONTEXT_DATA data = h.Load();
  data.loop_count = 255;
  data.loop_start = stream.frame_offsets[0];
  data.loop_end = stream.frame_offsets[0];
  data.loop_subframe_end = 3;
  h.Store(data);
  data = h.Kick();
  // 31 blocks: seven frames and three blocks of the eighth.
  REQUIRE_FALSE(data.output_buffer_valid);

  // The title reads everything, hands the buffer back and stops feeding input.
  data.output_buffer_valid = 1;
  data.input_buffer_0_packet_count = 0;
  data.input_buffer_0_valid = 0;
  h.Store(data);
  data = h.Kick();
  CHECK(data.output_buffer_write_offset == (data.output_buffer_read_offset + 1) % kOutputBlocks);
  CHECK(data.output_buffer_valid);
}

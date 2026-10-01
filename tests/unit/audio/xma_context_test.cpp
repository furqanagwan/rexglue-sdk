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
#include <filesystem>
#include <fstream>
#include <thread>
#include <vector>

#include <rex/audio/xma/context.h>
#include <rex/audio/xma/helpers.h>
#include <rex/cvar.h>
#include <rex/system/xmemory.h>

#include "test_memory.h"
#include "xma_synth.h"

using rex::audio::kPacketInfo;
using rex::audio::XMA_CONTEXT_DATA;
using rex::audio::XmaContext;
using rex::testing::GetTestMemory;
using namespace xma_synth;
REXCVAR_DECLARE(std::string, xma_dump_dir);

namespace {

constexpr uint32_t kOutputBlocks = 31;
constexpr uint32_t kBlocksPerMonoFrame = 4;

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

// --- Multi-stream buffers ----------------------------------------------------

namespace {

// Writes whole frames into one packet from its first data bit.
void FillPacket(uint8_t* packet, const std::vector<Bits>& frames, uint8_t skip) {
  std::vector<uint8_t> bytes(kPacketBytes, 0);
  uint32_t bit = kHeaderBits;
  for (const Bits& frame : frames) {
    for (bool b : frame) {
      if (b) {
        SetBit(bytes, bit);
      }
      ++bit;
    }
  }
  REQUIRE(bit <= kPacketBits);
  std::memcpy(packet, bytes.data(), kPacketBytes);
  WritePacketHeader(packet, uint32_t(frames.size()), kHeaderBits, true, skip);
}

}  // namespace

TEST_CASE("XMA skip chain reports where it continues in the next buffer", "[audio][xma]") {
  // Three packets: the chain from packet 1 skips two, overrunning by one.
  std::vector<uint8_t> buffer(3 * kPacketBytes, 0);
  uint8_t* p = buffer.data();
  WritePacketHeader(p + 0 * kPacketBytes, 1, kHeaderBits, true, 1);
  WritePacketHeader(p + 1 * kPacketBytes, 0, 0, true, 2);
  WritePacketHeader(p + 2 * kPacketBytes, 1, kHeaderBits, true, 0);
  uint32_t next_buffer_packet = 99;
  CHECK(XmaContext::GetNextPacketReadOffset(p, 1, 3, &next_buffer_packet) == kHeaderBits);
  CHECK(next_buffer_packet == 1);
  CHECK(XmaContext::GetNextPacketReadOffset(p, 3, 3, &next_buffer_packet) == kHeaderBits);
  CHECK(next_buffer_packet == 0);
  CHECK(XmaContext::GetNextPacketReadOffset(p, 2, 3, &next_buffer_packet) ==
        2 * kPacketBits + kHeaderBits);
  CHECK(next_buffer_packet == 0);
}

TEST_CASE("XMA sub-stream continues at its own packet in the next buffer", "[audio][xma]") {
  bool delayed = false;
  SECTION("both buffers ready") {}
  SECTION("next buffer filled on a later kick") {
    delayed = true;
  }
  // A 3-channel sound as 007 Legends streams it: stereo sub-stream A and mono
  // sub-stream B interleaved through both input buffers. The mono context
  // follows B from packet 1 of buffer 0 to packet 1 of buffer 1; restarting at
  // packet 0 would feed it A's stereo frames, which do not decode as mono.
  auto mono = [](bool more) {
    return std::vector<Bits>{SilentFrame(5000, false, true), SilentFrame(5000, false, more)};
  };
  auto stereo = std::vector<Bits>{SilentFrame(5000, true, true), SilentFrame(5000, true, true)};

  Stream first;
  first.bytes.assign(3 * kPacketBytes, 0);
  FillPacket(first.bytes.data() + 0 * kPacketBytes, stereo, 1);      // A -> packet 2
  FillPacket(first.bytes.data() + 1 * kPacketBytes, mono(true), 2);  // B -> next buffer, 1
  FillPacket(first.bytes.data() + 2 * kPacketBytes, stereo, 0);      // A -> next buffer, 0
  Harness h(first);

  using rex::memory::kSystemHeapPhysical;
  const uint32_t second_ptr = h.memory.SystemHeapAlloc(2 * kPacketBytes, 4096, kSystemHeapPhysical);
  REQUIRE(second_ptr);
  uint8_t* second = h.memory.TranslateVirtual(second_ptr);
  FillPacket(second + 0 * kPacketBytes, stereo, 1);
  FillPacket(second + 1 * kPacketBytes, mono(false), 0);

  XMA_CONTEXT_DATA data = h.Load();
  data.input_buffer_read_offset = kPacketBits + kHeaderBits;
  data.input_buffer_1_ptr = h.memory.GetPhysicalAddress(second_ptr);
  data.input_buffer_1_packet_count = 2;
  data.input_buffer_1_valid = !delayed;
  h.Store(data);
  data = h.Kick();

  if (delayed) {
    CHECK(uint32_t(data.current_buffer) == 1);
    CHECK(uint32_t(data.input_buffer_read_offset) == kPacketBits + kHeaderBits);
    CHECK_FALSE(data.IsAnyInputBufferValid());
    CHECK(BlocksWritten(data) == kBlocksPerMonoFrame);
    data.input_buffer_1_valid = 1;
    h.Store(data);
    data = h.Kick();
  }

  CHECK(uint32_t(data.current_buffer) == 0);
  CHECK(uint32_t(data.input_buffer_read_offset) == kHeaderBits);
  CHECK(uint32_t(data.input_buffer_0_valid) == 0);
  CHECK(uint32_t(data.input_buffer_1_valid) == 0);
  CHECK(uint32_t(data.error_status) == 0);
  CHECK(h.context.decode_failure_count() == 0);
  // Four mono frames: the first primes the realignment.
  CHECK(BlocksWritten(data) == 3 * kBlocksPerMonoFrame);
  CHECK_FALSE(data.IsAnyInputBufferValid());
  h.memory.SystemHeapFree(second_ptr);
}

TEST_CASE("XMA split frames use the next buffer's stream packet in either direction",
          "[audio][xma]") {
  bool reverse = false;
  bool split_header = false;
  SECTION("payload split forward") {}
  SECTION("payload split backward") {
    reverse = true;
  }
  SECTION("header split forward") {
    split_header = true;
  }
  SECTION("header split backward") {
    reverse = split_header = true;
  }
  // The first three frames leave either 1352 payload bits or 10 header bits
  // in the first packet. Frame four continues in packet 1 of the next buffer.
  auto mono =
      BuildStream(SilentFrames(split_header ? std::vector<uint32_t>{5000, 5000, 6342, 2000, 2000}
                                            : std::vector<uint32_t>{5000, 5000, 5000, 4000, 2000}),
                  2);
  Stream first;
  first.bytes.assign(3 * kPacketBytes, 0);
  auto stereo = std::vector<Bits>{SilentFrame(5000, true, true), SilentFrame(5000, true, false)};
  FillPacket(first.bytes.data(), stereo, 1);
  FillPacket(first.bytes.data() + 2 * kPacketBytes, stereo, 0);
  std::memcpy(first.bytes.data() + kPacketBytes, mono.bytes.data(), kPacketBytes);
  first.bytes[kPacketBytes + 3] = 2;
  Harness h(first);
  const uint32_t next =
      h.memory.SystemHeapAlloc(2 * kPacketBytes, 4096, rex::memory::kSystemHeapPhysical);
  REQUIRE(next);
  auto* bytes = h.memory.TranslateVirtual(next);
  FillPacket(bytes, stereo, 1);
  std::memcpy(bytes + kPacketBytes, mono.bytes.data() + kPacketBytes, kPacketBytes);
  auto data = h.Load();
  data.input_buffer_1_ptr = h.memory.GetPhysicalAddress(next);
  data.input_buffer_1_packet_count = 2;
  data.input_buffer_1_valid = 1;
  data.input_buffer_read_offset = kPacketBits + kHeaderBits;
  if (reverse) {
    const uint32_t first_ptr = data.input_buffer_0_ptr;
    data.input_buffer_0_ptr = data.input_buffer_1_ptr;
    data.input_buffer_1_ptr = first_ptr;
    data.input_buffer_0_packet_count = 2;
    data.input_buffer_1_packet_count = 3;
    data.current_buffer = 1;
  }
  h.Store(data);
  data = h.Kick();
  CHECK(h.context.decode_failure_count() == 0);
  CHECK(uint32_t(data.error_status) == 0);
  CHECK(BlocksWritten(data) == 4 * kBlocksPerMonoFrame);
  CHECK_FALSE(data.IsAnyInputBufferValid());
  h.memory.SystemHeapFree(next);
}

TEST_CASE("XMA skip remainder survives a short delayed refill", "[audio][xma]") {
  auto first = BuildStream(SilentFrames({1000, 1000}), 1);
  first.bytes[3] = 3;  // Next stream packet lies three packets beyond this buffer.
  Harness h(first);
  auto data = h.Kick();
  REQUIRE(uint32_t(data.current_buffer) == 1);
  REQUIRE(uint32_t(data.input_buffer_read_offset) == 3 * kPacketBits + kHeaderBits);
  // A single-packet refill contains only another stream. It must be skipped
  // without reading it or losing the remaining distance to this stream.
  data.input_buffer_1_ptr = data.input_buffer_0_ptr;
  data.input_buffer_1_packet_count = 1;
  data.input_buffer_1_valid = 1;
  h.Store(data);
  data = h.Kick();
  CHECK(uint32_t(data.current_buffer) == 0);
  CHECK(uint32_t(data.input_buffer_read_offset) == 2 * kPacketBits + kHeaderBits);
  CHECK_FALSE(data.IsAnyInputBufferValid());
  CHECK(h.context.decode_failure_count() == 0);
  CHECK(uint32_t(data.error_status) == 0);
}

TEST_CASE("XMA diagnostic captures failure position and owns the previous input", "[audio][xma]") {
  namespace fs = std::filesystem;
  struct Capture {
    fs::path root =
        fs::temp_directory_path() /
        ("rex-xma-" + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::string old = REXCVAR_GET(xma_dump_dir);
    Capture() {
      fs::create_directory(root);
      REXCVAR_SET(xma_dump_dir, root.string());
    }
    ~Capture() {
      REXCVAR_SET(xma_dump_dir, old);
      std::error_code ec;
      fs::remove_all(root, ec);
    }
  } capture;
  auto first = BuildStream(SilentFrames({1000, 1000}), 1);
  Harness h(first);
  auto data = h.Kick();
  REQUIRE_FALSE(data.IsAnyInputBufferValid());
  // The guest reuses the released input for new content before failure.
  auto bad =
      BuildStream({SilentFrame(1000, false, true), SilentFrame(1000, false, false, true)}, 1);
  std::memcpy(h.memory.TranslateVirtual(h.input_ptr), bad.bytes.data(), bad.bytes.size());
  data.input_buffer_1_ptr = data.input_buffer_0_ptr;
  data.input_buffer_1_packet_count = 1;
  data.input_buffer_1_valid = 1;
  h.Store(data);
  h.Kick();
  REQUIRE(h.context.decode_failure_count() == 1);
  std::vector<fs::path> files;
  for (const auto& file : fs::directory_iterator(capture.root))
    files.push_back(file.path());
  REQUIRE(files.size() == 1);
  std::ifstream input(files.front(), std::ios::binary);
  std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(input)), {});
  REQUIRE(bytes.size() == 4 + sizeof(XMA_CONTEXT_DATA) + 12 + 2 * kPacketBytes);
  REQUIRE(std::memcmp(bytes.data(), "XMAD", 4) == 0);
  XMA_CONTEXT_DATA saved(bytes.data() + 4);
  CHECK(uint32_t(saved.current_buffer) == 1);
  CHECK(uint32_t(saved.input_buffer_read_offset) == kHeaderBits + 1000);
  // The final payload is the original first buffer, not its reused memory.
  CHECK(std::equal(first.bytes.begin(), first.bytes.end(), bytes.end() - kPacketBytes));
}

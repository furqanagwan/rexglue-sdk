/**
******************************************************************************
* Xenia : Xbox 360 Emulator Research Project                                 *
******************************************************************************
* Copyright 2021 Ben Vanik. All rights reserved.                             *
* Released under the BSD license - see LICENSE in the root for more details. *
******************************************************************************
*
* @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
*/

#include <algorithm>
#include <atomic>
#include <cstring>
#include <filesystem>
#include <fstream>

#include <rex/audio/xma/context.h>
#include <rex/audio/xma/decoder.h>
#include <rex/audio/xma/helpers.h>
#include <rex/cvar.h>
#include <rex/dbg.h>
#include <rex/logging.h>
#include <rex/memory/ring_buffer.h>
#include <rex/platform.h>
#include <rex/stream.h>

extern "C" {
#if REX_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4101 4244 5033)
#endif
#include "libavcodec/avcodec.h"
#include "libavutil/error.h"
#if REX_COMPILER_MSVC
#pragma warning(pop)
#endif
}

REXCVAR_DEFINE_STRING(xma_dump_dir, "", "Audio",
                      "Directory to save the context and input buffers of each XMA stream "
                      "whose frames fail to decode (empty: off)");

namespace rex::audio {

using stream::BitStream;

const uint32_t XmaContext::kBitsPerPacketHeader;
const uint32_t XmaContext::kOutputMaxSizeBytes;

XmaContext::XmaContext()
    : work_completion_event_(rex::thread::Event::CreateAutoResetEvent(false)) {}

XmaContext::~XmaContext() {
  if (av_context_) {
    avcodec_free_context(&av_context_);
  }
  if (av_frame_) {
    av_frame_free(&av_frame_);
  }
}

int XmaContext::Setup(uint32_t id, memory::Memory* memory, uint32_t guest_ptr) {
  id_ = id;
  memory_ = memory;
  guest_ptr_ = guest_ptr;

  av_packet_ = av_packet_alloc();
  assert_not_null(av_packet_);
  av_packet_->buf = av_buffer_alloc(128 * 1024);

  av_codec_ = avcodec_find_decoder(AV_CODEC_ID_XMAFRAMES);
  if (!av_codec_) {
    REXAPU_ERROR("XmaContext {}: Codec not found", id);
    return 1;
  }

  av_context_ = avcodec_alloc_context3(av_codec_);
  if (!av_context_) {
    REXAPU_ERROR("XmaContext {}: Couldn't allocate context", id);
    return 1;
  }

  av_context_->channels = 0;
  av_context_->sample_rate = 0;

  av_frame_ = av_frame_alloc();
  if (!av_frame_) {
    REXAPU_ERROR("XmaContext {}: Couldn't allocate frame", id);
    return 1;
  }

  return 0;
}

bool XmaContext::Work() {
  if (!is_allocated() || !is_enabled()) {
    return false;
  }

  std::lock_guard<std::mutex> lock(lock_);
  set_is_enabled(false);

  auto context_ptr = memory()->TranslateVirtual(guest_ptr());
  XMA_CONTEXT_DATA data(context_ptr);
  const XMA_CONTEXT_DATA initial_data = data;

  if (!data.output_buffer_valid) {
    return true;
  }

  memory::RingBuffer output_rb = PrepareOutputRingBuffer(&data);

  if (!stream_start_logged_ && data.IsAnyInputBufferValid()) {
    stream_start_logged_ = true;
    const uint8_t buffer_index = data.IsCurrentInputBufferValid()
                                     ? uint8_t(data.current_buffer)
                                     : uint8_t(data.current_buffer ^ 1);
    const uint32_t address = data.GetInputBufferAddress(buffer_index);
    const uint8_t* start_packet = address ? memory()->TranslatePhysical(address) : nullptr;
    REXAPU_DEBUG(
        "XmaContext {}: stream start: {} Hz {}, current buffer {}, valid {}{}, packets {}/{}, "
        "read offset {}, first packet skip {}",
        id(), GetSampleRate(data.sample_rate), data.is_stereo ? "stereo" : "mono",
        uint32_t(data.current_buffer), uint32_t(data.input_buffer_0_valid),
        uint32_t(data.input_buffer_1_valid), uint32_t(data.input_buffer_0_packet_count),
        uint32_t(data.input_buffer_1_packet_count), uint32_t(data.input_buffer_read_offset),
        start_packet ? xma::GetPacketSkipCount(start_packet) : 0);
  }

  if (data.IsConsumeOnlyContext()) {
    if (current_frame_remaining_subframes_ == 0) {
      return true;
    }
    Consume(&output_rb, &data);
    data.output_buffer_write_offset = output_rb.write_offset() / kOutputBytesPerBlock;

    if (output_rb.empty()) {
      data.output_buffer_valid = 0;
    }
    StoreContextMerged(data, initial_data, context_ptr);
    return true;
  }

  const uint32_t effective_sdc = std::max(static_cast<uint32_t>(1), data.subframe_decode_count);
  const int32_t minimum_subframe_decode_count =
      static_cast<int32_t>(effective_sdc) + data.output_buffer_padding;

  if (minimum_subframe_decode_count > remaining_subframe_blocks_in_output_buffer_) {
    StoreContextMerged(data, initial_data, context_ptr);
    return true;
  }

  while (remaining_subframe_blocks_in_output_buffer_ >= minimum_subframe_decode_count) {
    const uint32_t pre_decode_offset = data.input_buffer_read_offset;
    const uint8_t pre_decode_current_buffer = data.current_buffer;
    const uint8_t pre_remaining_subframes = current_frame_remaining_subframes_;
    const bool pre_carry_valid = carry_valid_;

    Decode(&data);
    Consume(&output_rb, &data);

    if ((!data.IsAnyInputBufferValid() || data.error_status == 4) &&
        current_frame_remaining_subframes_ == 0) {
      break;
    }

    if (pre_remaining_subframes == 0 && current_frame_remaining_subframes_ == 0 &&
        carry_valid_ == pre_carry_valid && data.input_buffer_read_offset == pre_decode_offset &&
        data.current_buffer == pre_decode_current_buffer) {
      REXAPU_DEBUG("XmaContext {}: decode made no progress at offset {}", id(), pre_decode_offset);
      break;
    }
  }

  if (initial_data.IsAnyInputBufferValid()) {
    data.output_buffer_write_offset = output_rb.write_offset() / kOutputBytesPerBlock;
  } else if (data.output_buffer_write_offset != data.output_buffer_read_offset) {
    data.output_buffer_write_offset = data.output_buffer_read_offset;
    data.output_buffer_valid = 0;
  }

  if (remaining_subframe_blocks_in_output_buffer_ == 0 && output_rb.empty()) {
    data.output_buffer_valid = 0;
  }

  StoreContextMerged(data, initial_data, context_ptr);
  return true;
}

void XmaContext::Enable() {
  std::lock_guard<std::mutex> lock(lock_);
  set_is_enabled(true);
}

bool XmaContext::Block(bool poll) {
  if (!lock_.try_lock()) {
    if (poll) {
      return false;
    }
    lock_.lock();
  }
  lock_.unlock();
  return true;
}

void XmaContext::Clear() {
  std::lock_guard<std::mutex> lock(lock_);
  REXAPU_NOISY_DEBUG("XmaContext: reset context {}", id());

  auto context_ptr = memory()->TranslateVirtual(guest_ptr());
  XMA_CONTEXT_DATA data(context_ptr);
  ClearLocked(&data);
  data.Store(context_ptr);
}

void XmaContext::ClearLocked(XMA_CONTEXT_DATA* data) {
  data->input_buffer_0_valid = 0;
  data->input_buffer_1_valid = 0;
  data->output_buffer_valid = 0;

  data->input_buffer_read_offset = kBitsPerPacketHeader;
  data->output_buffer_read_offset = 0;
  data->output_buffer_write_offset = 0;

  ResetDecoderState();
}

void XmaContext::ResetDecoderState() {
  if (av_context_) {
    av_context_->sample_rate = 0;
    av_context_->channels = 0;
  }
  stream_failure_reported_ = false;
  stream_start_logged_ = false;
  previous_buffer_.clear();
  raw_frame_.fill(0);
  decoded_frame_.fill(0);
  carry_frame_.fill(0);
  carry_valid_ = false;
  pending_output_limit_ = 0;
  pending_start_skip_ = 0;
  current_frame_remaining_subframes_ = 0;
  loop_frame_output_limit_ = 0;
  loop_start_skip_pending_ = false;
}

void XmaContext::Disable() {
  std::lock_guard<std::mutex> lock(lock_);
  set_is_enabled(false);
}

void XmaContext::Release() {
  std::lock_guard<std::mutex> lock(lock_);
  assert_true(is_allocated());

  set_is_allocated(false);
  ResetDecoderState();
  auto context_ptr = memory()->TranslateVirtual(guest_ptr());
  std::memset(context_ptr, 0, sizeof(XMA_CONTEXT_DATA));
}

void XmaContext::SwapInputBuffer(XMA_CONTEXT_DATA* data, uint32_t start_packet) {
  if (!REXCVAR_GET(xma_dump_dir).empty() && data->IsCurrentInputBufferValid() &&
      data->GetCurrentInputBufferAddress()) {
    const auto* input = GetCurrentInputBuffer(data);
    previous_buffer_.assign(input, input + GetCurrentInputBufferSize(data));
  }
  if (data->current_buffer == 0) {
    data->input_buffer_0_valid = 0;
  } else {
    data->input_buffer_1_valid = 0;
  }
  data->current_buffer ^= 1;

  data->input_buffer_read_offset = start_packet * kBitsPerPacket + kBitsPerPacketHeader;
}

void XmaContext::UpdateLoopStatus(XMA_CONTEXT_DATA* data) {
  if (data->loop_count == 0) {
    return;
  }

  const uint32_t loop_start = std::max(kBitsPerPacketHeader, data->loop_start);
  const uint32_t loop_end = std::max(kBitsPerPacketHeader, data->loop_end);

  if (data->input_buffer_read_offset != loop_end) {
    return;
  }

  data->input_buffer_read_offset = loop_start;
  loop_start_skip_pending_ = true;

  if (data->loop_count < 255) {
    data->loop_count--;
  }
}

int XmaContext::GetSampleRate(int id) {
  return kIdToSampleRate[std::min(id, 3)];
}

int16_t XmaContext::GetPacketNumber(size_t size, size_t bit_offset) {
  if (bit_offset < kBitsPerPacketHeader) {
    assert_always();
    return -1;
  }
  if (bit_offset >= (size << 3)) {
    assert_always();
    return -1;
  }
  size_t byte_offset = bit_offset >> 3;
  size_t packet_number = byte_offset / kBytesPerPacket;
  return static_cast<int16_t>(packet_number);
}

uint32_t XmaContext::GetCurrentInputBufferSize(XMA_CONTEXT_DATA* data) {
  return data->GetCurrentInputBufferPacketCount() * kBytesPerPacket;
}

uint8_t* XmaContext::GetCurrentInputBuffer(XMA_CONTEXT_DATA* data) {
  return memory()->TranslatePhysical(data->GetCurrentInputBufferAddress());
}

uint32_t XmaContext::GetAmountOfBitsToRead(uint32_t remaining_stream_bits, uint32_t frame_size) {
  return std::min(remaining_stream_bits, frame_size);
}

const uint8_t* XmaContext::GetNextPacket(XMA_CONTEXT_DATA* data, uint32_t next_packet_index,
                                         uint32_t current_input_packet_count) {
  if (next_packet_index < current_input_packet_count) {
    return memory()->TranslatePhysical(data->GetCurrentInputBufferAddress()) +
           next_packet_index * kBytesPerPacket;
  }

  const uint8_t next_buffer_index = data->current_buffer ^ 1;
  if (!data->IsInputBufferValid(next_buffer_index)) {
    return nullptr;
  }

  const uint32_t next_buffer_address = data->GetInputBufferAddress(next_buffer_index);
  if (!next_buffer_address) {
    REXAPU_ERROR("XmaContext {}: Buffer marked valid but has null pointer!", id());
    return nullptr;
  }

  const uint32_t next_buffer_packet = next_packet_index - current_input_packet_count;
  const uint32_t next_buffer_packet_count = next_buffer_index == 0
                                                ? uint32_t(data->input_buffer_0_packet_count)
                                                : uint32_t(data->input_buffer_1_packet_count);
  if (next_buffer_packet >= next_buffer_packet_count) {
    return nullptr;
  }
  return memory()->TranslatePhysical(next_buffer_address) + next_buffer_packet * kBytesPerPacket;
}

uint32_t XmaContext::GetNextPacketReadOffset(const uint8_t* buffer, uint32_t next_packet_index,
                                             uint32_t current_input_packet_count,
                                             uint32_t* next_buffer_packet) {
  uint32_t overrun = 0;
  const uint32_t offset =
      FindStreamFrame(buffer, next_packet_index, current_input_packet_count, &overrun);
  if (next_buffer_packet) {
    *next_buffer_packet = overrun;
  }
  return offset ? offset : kBitsPerPacketHeader;
}

uint32_t XmaContext::FindStreamFrame(const uint8_t* buffer, uint32_t next_packet_index,
                                     uint32_t current_input_packet_count,
                                     uint32_t* next_buffer_packet) {
  *next_buffer_packet = 0;
  while (next_packet_index < current_input_packet_count) {
    const uint8_t* next_packet = buffer + (next_packet_index * kBytesPerPacket);
    const uint32_t packet_frame_offset = xma::GetPacketFrameOffset(next_packet);

    if (packet_frame_offset <= kMaxFrameSizeinBits) {
      return (next_packet_index * kBitsPerPacket) + packet_frame_offset;
    }

    const uint8_t next_skip = xma::GetPacketSkipCount(next_packet);
    if (next_skip == 0xFF) {
      return 0;
    }
    next_packet_index += next_skip + 1;
  }

  *next_buffer_packet = next_packet_index - current_input_packet_count;
  return 0;
}

memory::RingBuffer XmaContext::PrepareOutputRingBuffer(XMA_CONTEXT_DATA* data) {
  const uint32_t output_capacity = data->output_buffer_block_count * kOutputBytesPerBlock;
  const uint32_t output_read_offset = data->output_buffer_read_offset * kOutputBytesPerBlock;
  const uint32_t output_write_offset = data->output_buffer_write_offset * kOutputBytesPerBlock;

  if (output_capacity > kOutputMaxSizeBytes) {
    REXAPU_WARN(
        "XmaContext {}: Output buffer exceeds expected size! "
        "(Actual: {} Max: {})",
        id(), output_capacity, kOutputMaxSizeBytes);
  }

  uint8_t* output_buffer = memory()->TranslatePhysical(data->output_buffer_ptr);

  memory::RingBuffer output_rb(output_buffer, output_capacity);
  output_rb.set_read_offset(output_read_offset);
  output_rb.set_write_offset(output_write_offset);
  remaining_subframe_blocks_in_output_buffer_ =
      static_cast<int32_t>(output_rb.write_count()) / kOutputBytesPerBlock;

  return output_rb;
}

kPacketInfo XmaContext::GetPacketInfo(const uint8_t* packet, uint32_t frame_offset) {
  kPacketInfo packet_info = {};
  packet_info.current_frame_offset_ = frame_offset;

  const uint32_t first_frame_offset = xma::GetPacketFrameOffset(packet);

  BitStream stream(const_cast<uint8_t*>(packet), kBitsPerPacket);
  stream.SetOffset(first_frame_offset);

  bool resolved = false;
  auto consider_frame = [&](uint32_t offset, uint32_t size) {
    if (!resolved && offset >= frame_offset) {
      resolved = true;
      packet_info.current_frame_offset_ = offset;
    }
    if (offset != frame_offset) {
      return;
    }
    packet_info.current_frame_ = packet_info.frame_count_;
    packet_info.current_frame_size_ = size;
  };

  if (frame_offset < first_frame_offset) {
    packet_info.current_frame_ = 0;
    packet_info.current_frame_size_ = first_frame_offset - frame_offset;
    resolved = true;
  }

  while (true) {
    if (stream.BitsRemaining() < kBitsPerFrameHeader) {
      if (stream.BitsRemaining() > 0) {
        consider_frame(static_cast<uint32_t>(stream.offset_bits()), 0);
        packet_info.frame_count_++;
      }
      break;
    }

    const uint64_t frame_size = stream.Peek(kBitsPerFrameHeader);
    if (frame_size == 0 || frame_size == xma::kMaxFrameLength) {
      break;
    }

    consider_frame(static_cast<uint32_t>(stream.offset_bits()), static_cast<uint32_t>(frame_size));

    packet_info.frame_count_++;

    if (frame_size > stream.BitsRemaining()) {
      break;
    }

    stream.Advance(frame_size - 1);

    if (stream.Read(1) == 0) {
      break;
    }
  }

  if (xma::IsPacketXma2Type(packet)) {
    const uint8_t xma2_frame_count = xma::GetPacketFrameCount(packet);
    if (xma2_frame_count > packet_info.frame_count_) {
      if (packet_info.current_frame_size_ == 0) {
        packet_info.current_frame_ = packet_info.frame_count_;
      }
      packet_info.frame_count_ = xma2_frame_count;
    }
  }
  return packet_info;
}

void XmaContext::StoreContextMerged(const XMA_CONTEXT_DATA& data,
                                    const XMA_CONTEXT_DATA& initial_data, uint8_t* context_ptr) {
  XMA_CONTEXT_DATA fresh(context_ptr);

  fresh.loop_count = data.loop_count;
  fresh.output_buffer_write_offset = data.output_buffer_write_offset;
  if (initial_data.input_buffer_0_valid && !data.input_buffer_0_valid) {
    fresh.input_buffer_0_valid = 0;
  }
  if (initial_data.input_buffer_1_valid && !data.input_buffer_1_valid) {
    fresh.input_buffer_1_valid = 0;
  }

  if (initial_data.output_buffer_valid && !data.output_buffer_valid) {
    fresh.output_buffer_valid = 0;
  }

  fresh.input_buffer_read_offset = data.input_buffer_read_offset;
  fresh.error_status = data.error_status;
  fresh.current_buffer = data.current_buffer;
  fresh.output_buffer_read_offset = data.output_buffer_read_offset;

  fresh.Store(context_ptr);
}

void XmaContext::Consume(memory::RingBuffer* output_rb, const XMA_CONTEXT_DATA* data) {
  if (!current_frame_remaining_subframes_) {
    return;
  }

  if (loop_frame_output_limit_ > 0) {
    const uint8_t total_subframes = (kBytesPerFrameChannel / kOutputBytesPerBlock)
                                    << data->is_stereo;
    const uint8_t consumed = total_subframes - current_frame_remaining_subframes_;
    if (consumed >= loop_frame_output_limit_) {
      remaining_subframe_blocks_in_output_buffer_ -= data->output_buffer_padding;
      current_frame_remaining_subframes_ = 0;
      loop_frame_output_limit_ = 0;
      return;
    }
  }

  const uint8_t effective_sdc = std::max(static_cast<uint32_t>(1), data->subframe_decode_count);
  int8_t subframes_to_write = std::min(static_cast<int8_t>(current_frame_remaining_subframes_),
                                       static_cast<int8_t>(effective_sdc));

  if (loop_frame_output_limit_ > 0) {
    const uint8_t total_subframes = (kBytesPerFrameChannel / kOutputBytesPerBlock)
                                    << data->is_stereo;
    const uint8_t consumed = total_subframes - current_frame_remaining_subframes_;
    const int8_t remaining_until_limit = static_cast<int8_t>(loop_frame_output_limit_ - consumed);
    if (subframes_to_write > remaining_until_limit) {
      subframes_to_write = remaining_until_limit;
    }
  }

  const int8_t raw_frame_read_offset =
      ((kBytesPerFrameChannel / kOutputBytesPerBlock) << data->is_stereo) -
      current_frame_remaining_subframes_;

  output_rb->Write(raw_frame_.data() + (kOutputBytesPerBlock * raw_frame_read_offset),
                   subframes_to_write * kOutputBytesPerBlock);

  const int8_t headroom = (current_frame_remaining_subframes_ - subframes_to_write == 0)
                              ? data->output_buffer_padding
                              : 0;

  remaining_subframe_blocks_in_output_buffer_ -= subframes_to_write + headroom;
  current_frame_remaining_subframes_ -= subframes_to_write;
}

int XmaContext::PrepareDecoder(int sample_rate, bool is_two_channel) {
  sample_rate = GetSampleRate(sample_rate);

  uint32_t channels = is_two_channel ? 2 : 1;
  if (av_context_->sample_rate != sample_rate ||
      av_context_->channels != static_cast<int>(channels)) {
    REXAPU_NOISY_DEBUG("XmaContext {}: Codec reinit: rate {} -> {}, channels {} -> {}", id(),
                       av_context_->sample_rate, sample_rate, av_context_->channels, channels);
    avcodec_free_context(&av_context_);
    av_context_ = avcodec_alloc_context3(av_codec_);

    av_context_->sample_rate = sample_rate;
    av_context_->channels = channels;
    av_context_->flags2 |= AV_CODEC_FLAG2_SKIP_MANUAL;

    if (avcodec_open2(av_context_, av_codec_, NULL) < 0) {
      REXAPU_ERROR("XmaContext: Failed to reopen FFmpeg context");
      return -1;
    }
    return 1;
  }
  return 0;
}

void XmaContext::PreparePacket(uint32_t frame_size, uint32_t frame_padding) {
  av_packet_->data = xma_frame_.data();
  av_packet_->size = static_cast<int>(1 + ((frame_padding + frame_size) / 8) +
                                      (((frame_padding + frame_size) % 8) ? 1 : 0));

  auto padding_end = av_packet_->size * 8 - (8 + frame_padding + frame_size);
  assert_true(padding_end < 8);
  xma_frame_[0] = ((frame_padding & 7) << 5) | ((padding_end & 7) << 2);
}

bool XmaContext::DecodePacket(AVCodecContext* av_context, const AVPacket* av_packet,
                              AVFrame* av_frame) {
  auto ret = avcodec_send_packet(av_context, av_packet);
  if (ret < 0) {
    char errbuf[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(ret, errbuf, sizeof(errbuf));
    REXAPU_ERROR("XmaContext {}: Error sending packet for decoding: {} ({})", id(), errbuf, ret);
    return false;
  }
  ret = avcodec_receive_frame(av_context, av_frame);

  if (ret == AVERROR(EAGAIN)) {
    return false;
  }
  if (ret < 0) {
    char errbuf[AV_ERROR_MAX_STRING_SIZE];
    av_strerror(ret, errbuf, sizeof(errbuf));
    REXAPU_ERROR("XmaContext {}: Error during decoding: {} ({})", id(), errbuf, ret);
    return false;
  }
  return true;
}

void XmaContext::ReportStreamFailure(const XMA_CONTEXT_DATA& data, const uint8_t* packet,
                                     uint32_t packet_index) {
  REXAPU_WARN(
      "XmaContext {}: stream does not decode: {} Hz {}, buffer {} ({:08X}, {} packets, valid {}; "
      "other {:08X}, {} packets, valid {}), read offset {}, packet {} header frames {} offset {} "
      "metadata {} skip {}, loop {}..{} x{}, subframes {}",
      id(), GetSampleRate(data.sample_rate), data.is_stereo ? "stereo" : "mono",
      uint32_t(data.current_buffer), data.GetCurrentInputBufferAddress(),
      data.GetCurrentInputBufferPacketCount(), data.IsCurrentInputBufferValid(),
      data.GetInputBufferAddress(data.current_buffer ^ 1),
      data.current_buffer ? uint32_t(data.input_buffer_0_packet_count)
                          : uint32_t(data.input_buffer_1_packet_count),
      data.IsInputBufferValid(data.current_buffer ^ 1), uint32_t(data.input_buffer_read_offset),
      packet_index, xma::GetPacketFrameCount(packet), xma::GetPacketFrameOffset(packet),
      xma::GetPacketMetadata(packet), xma::GetPacketSkipCount(packet), uint32_t(data.loop_start),
      uint32_t(data.loop_end), uint32_t(data.loop_count), uint32_t(data.subframe_decode_count));

  const auto& dump_dir = REXCVAR_GET(xma_dump_dir);
  if (dump_dir.empty()) {
    return;
  }

  static std::atomic<uint32_t> dump_serial = 0;
  std::error_code ec;
  std::filesystem::create_directories(dump_dir, ec);
  if (ec) {
    REXAPU_WARN("XmaContext {}: cannot create dump directory: {}", id(), ec.message());
    return;
  }
  const auto path =
      std::filesystem::path(dump_dir) / fmt::format("xma_{:03}_ctx{:02}.bin", dump_serial++, id());
  std::ofstream out(path, std::ios::binary);
  out.write("XMAD", 4);

  std::array<uint8_t, sizeof(XMA_CONTEXT_DATA)> context_bytes;
  auto snapshot = data;
  snapshot.Store(context_bytes.data());
  out.write(reinterpret_cast<const char*>(context_bytes.data()), context_bytes.size());

  for (uint8_t i = 0; i < 3; ++i) {
    const bool valid = i < 2 && data.IsInputBufferValid(i) && data.GetInputBufferAddress(i);
    const uint32_t packets = i == 0 ? uint32_t(data.input_buffer_0_packet_count)
                                    : uint32_t(data.input_buffer_1_packet_count);
    const uint32_t size =
        i == 2 ? uint32_t(previous_buffer_.size()) : (valid ? packets * kBytesPerPacket : 0);
    const uint8_t length[]{uint8_t(size), uint8_t(size >> 8), uint8_t(size >> 16),
                           uint8_t(size >> 24)};
    out.write(reinterpret_cast<const char*>(length), sizeof(length));
    if (size) {
      const auto* bytes = i == 2 ? previous_buffer_.data()
                                 : memory()->TranslatePhysical(data.GetInputBufferAddress(i));
      out.write(reinterpret_cast<const char*>(bytes), size);
    }
  }
  out.close();
  if (out)
    REXAPU_WARN("XmaContext {}: saved the stream to {}", id(), path.string());
  else
    REXAPU_WARN("XmaContext {}: failed to write stream dump {}", id(), path.string());
}

void XmaContext::Decode(XMA_CONTEXT_DATA* data) {
  SCOPE_profile_cpu_f("apu");

  if (!data->IsAnyInputBufferValid()) {
    return;
  }

  if (current_frame_remaining_subframes_ > 0) {
    return;
  }

  if (!data->IsCurrentInputBufferValid()) {
    SwapInputBuffer(data);
    if (!data->IsCurrentInputBufferValid()) {
      return;
    }
  }

  uint8_t* current_input_buffer = GetCurrentInputBuffer(data);

  input_buffer_.fill(0);

  bool is_loop_end_frame = false;
  if (data->loop_count > 0) {
    const uint32_t loop_end = std::max(kBitsPerPacketHeader, data->loop_end);
    is_loop_end_frame = (data->input_buffer_read_offset == loop_end);
  }

  if (!data->output_buffer_block_count) {
    REXAPU_ERROR("XmaContext {}: Error - Received 0 for output_buffer_block_count!", id());
    return;
  }

  if (data->input_buffer_read_offset < kBitsPerPacketHeader) {
    data->input_buffer_read_offset = kBitsPerPacketHeader;
  }

  const uint32_t current_input_size = GetCurrentInputBufferSize(data);
  const uint32_t current_input_packet_count = current_input_size / kBytesPerPacket;

  const uint32_t start_packet = data->input_buffer_read_offset / kBitsPerPacket;
  if (start_packet >= current_input_packet_count &&
      data->input_buffer_read_offset % kBitsPerPacket == kBitsPerPacketHeader) {
    SwapInputBuffer(data, start_packet - current_input_packet_count);
    return;
  }

  const int16_t packet_index = GetPacketNumber(current_input_size, data->input_buffer_read_offset);

  if (packet_index == -1) {
    REXAPU_ERROR("XmaContext {}: Invalid packet index. Input read offset: {}", id(),
                 static_cast<uint32_t>(data->input_buffer_read_offset));
    return;
  }

  uint8_t* packet = current_input_buffer + (packet_index * kBytesPerPacket);
  const uint32_t packet_first_frame_offset = xma::GetPacketFrameOffset(packet);
  uint32_t relative_offset = data->input_buffer_read_offset % kBitsPerPacket;

  if (relative_offset < packet_first_frame_offset) {
    data->input_buffer_read_offset = (packet_index * kBitsPerPacket) + packet_first_frame_offset;
    relative_offset = packet_first_frame_offset;
  }

  const uint8_t skip_count = xma::GetPacketSkipCount(packet);

  if (skip_count == 0xFF) {
    uint32_t next_buffer_packet = 0;
    const uint32_t next_input_offset = FindStreamFrame(
        current_input_buffer, packet_index + 1, current_input_packet_count, &next_buffer_packet);
    if (!next_input_offset) {
      SwapInputBuffer(data, next_buffer_packet);
      return;
    }
    data->input_buffer_read_offset = next_input_offset;
    return;
  }

  kPacketInfo packet_info = GetPacketInfo(packet, relative_offset);

  if (loop_start_skip_pending_ && packet_info.current_frame_offset_ != relative_offset) {
    REXAPU_DEBUG("XmaContext {}: loop_start {} is not a frame boundary in packet {}, using {}",
                 id(), relative_offset, packet_index, packet_info.current_frame_offset_);
    relative_offset = packet_info.current_frame_offset_;
    data->input_buffer_read_offset = (packet_index * kBitsPerPacket) + relative_offset;
    packet_info = GetPacketInfo(packet, relative_offset);
  }

  const uint32_t packet_to_skip = skip_count + 1;
  const uint32_t next_packet_index = packet_index + packet_to_skip;

  if (packet_info.current_frame_size_ == 0) {
    const uint8_t* next_packet = GetNextPacket(data, next_packet_index, current_input_packet_count);
    if (!next_packet) {
      SwapInputBuffer(data, next_packet_index >= current_input_packet_count
                                ? next_packet_index - current_input_packet_count
                                : 0);
      return;
    }
    std::memcpy(input_buffer_.data(), packet + kBytesPerPacketHeader, kBytesPerPacketData);
    std::memcpy(input_buffer_.data() + kBytesPerPacketData, next_packet + kBytesPerPacketHeader,
                kBytesPerPacketData);

    BitStream combined(input_buffer_.data(), (kBitsPerPacket - kBitsPerPacketHeader) * 2);
    combined.SetOffset(relative_offset - kBitsPerPacketHeader);

    uint64_t frame_size = combined.Peek(kBitsPerFrameHeader);
    if (frame_size == xma::kMaxFrameLength) {
      data->error_status = 4;
      return;
    }
    packet_info.current_frame_size_ = static_cast<uint32_t>(frame_size);
  }

  BitStream stream(current_input_buffer, (packet_index + 1) * kBitsPerPacket);
  stream.SetOffset(data->input_buffer_read_offset);

  const uint64_t bits_to_copy = GetAmountOfBitsToRead(static_cast<uint32_t>(stream.BitsRemaining()),
                                                      packet_info.current_frame_size_);

  if (bits_to_copy == 0) {
    REXAPU_ERROR("XmaContext {}: There are no bits to copy!", id());
    SwapInputBuffer(data);
    return;
  }

  if (packet_info.isLastFrameInPacket()) {
    if (stream.BitsRemaining() < packet_info.current_frame_size_) {
      const uint8_t* next_packet =
          GetNextPacket(data, next_packet_index, current_input_packet_count);
      if (!next_packet) {
        data->error_status = 4;
        return;
      }
      std::memcpy(input_buffer_.data() + kBytesPerPacketData, next_packet + kBytesPerPacketHeader,
                  kBytesPerPacketData);
    }
  }

  std::memcpy(input_buffer_.data(), packet + kBytesPerPacketHeader, kBytesPerPacketData);

  stream = BitStream(input_buffer_.data(), (kBitsPerPacket - kBitsPerPacketHeader) * 2);
  stream.SetOffset(relative_offset - kBitsPerPacketHeader);

  xma_frame_.fill(0);

  const uint32_t padding_start =
      static_cast<uint8_t>(stream.Copy(xma_frame_.data() + 1, packet_info.current_frame_size_));

  decoded_frame_.fill(0);

  if (PrepareDecoder(data->sample_rate, bool(data->is_stereo)) == 1) {
    carry_valid_ = false;
  }
  PreparePacket(packet_info.current_frame_size_, padding_start);
  const bool decoded = DecodePacket(av_context_, av_packet_, av_frame_);
  if (decoded) {
    ConvertFrame(reinterpret_cast<const uint8_t**>(&av_frame_->data), bool(data->is_stereo),
                 decoded_frame_.data());

    const size_t pad_bytes = kDecoderStartPadding * kBytesPerSample << data->is_stereo;
    const size_t carry_bytes = (kBytesPerFrameChannel << data->is_stereo) - pad_bytes;

    const uint8_t decoded_output_limit =
        is_loop_end_frame ? static_cast<uint8_t>((data->loop_subframe_end + 1) << data->is_stereo)
                          : 0;

    const uint8_t decoded_start_skip =
        loop_start_skip_pending_ ? static_cast<uint8_t>(data->loop_subframe_skip << data->is_stereo)
                                 : 0;
    loop_start_skip_pending_ = false;

    if (carry_valid_) {
      std::memcpy(raw_frame_.data(), carry_frame_.data(), carry_bytes);
      std::memcpy(raw_frame_.data() + carry_bytes, decoded_frame_.data(), pad_bytes);

      current_frame_remaining_subframes_ = 4 << data->is_stereo;
      loop_frame_output_limit_ = pending_output_limit_;
      current_frame_remaining_subframes_ -=
          std::min(pending_start_skip_, current_frame_remaining_subframes_);
    }

    std::memcpy(carry_frame_.data(), decoded_frame_.data() + pad_bytes, carry_bytes);
    carry_valid_ = true;
    pending_output_limit_ = decoded_output_limit;
    pending_start_skip_ = decoded_start_skip;
  } else {
    carry_valid_ = false;
    if (!stream_failure_reported_) {
      stream_failure_reported_ = true;
      ReportStreamFailure(*data, packet, packet_index);
    }
    const uint32_t failures = ++decode_failure_count_;
    if ((failures & (failures - 1)) == 0) {
      REXAPU_WARN("XmaContext {}: frame at offset {} produced no audio ({} so far)", id(),
                  static_cast<uint32_t>(data->input_buffer_read_offset), failures);
    }
  }

  if (is_loop_end_frame) {
    UpdateLoopStatus(data);
    return;
  }

  if (!packet_info.isLastFrameInPacket()) {
    const uint32_t next_frame_offset =
        (data->input_buffer_read_offset + bits_to_copy) % kBitsPerPacket;
    data->input_buffer_read_offset = (packet_index * kBitsPerPacket) + next_frame_offset;
    return;
  }

  uint32_t next_buffer_packet = 0;
  uint32_t next_input_offset = FindStreamFrame(current_input_buffer, next_packet_index,
                                               current_input_packet_count, &next_buffer_packet);

  if (!next_input_offset) {
    SwapInputBuffer(data, next_buffer_packet);
    if (!data->IsCurrentInputBufferValid()) {
      return;
    }
    next_input_offset =
        FindStreamFrame(GetCurrentInputBuffer(data), next_buffer_packet,
                        data->GetCurrentInputBufferPacketCount(), &next_buffer_packet);
    if (!next_input_offset) {
      SwapInputBuffer(data, next_buffer_packet);
      return;
    }
  }
  data->input_buffer_read_offset = next_input_offset;
}

void XmaContext::ConvertFrame(const uint8_t** samples, bool is_two_channel,
                              uint8_t* output_buffer) {
  constexpr float scale = (1 << 15) - 1;
  auto out = reinterpret_cast<int16_t*>(output_buffer);

#if REX_ARCH_AMD64
  static_assert(kSamplesPerFrame % 8 == 0);
  const auto in_channel_0 = reinterpret_cast<const float*>(samples[0]);
  const __m128 scale_mm = _mm_set1_ps(scale);
  if (is_two_channel) {
    const auto in_channel_1 = reinterpret_cast<const float*>(samples[1]);
    const __m128i shufmask = _mm_set_epi8(14, 15, 6, 7, 12, 13, 4, 5, 10, 11, 2, 3, 8, 9, 0, 1);
    for (uint32_t i = 0; i < kSamplesPerFrame; i += 4) {
      __m128 in_mm0 = _mm_loadu_ps(&in_channel_0[i]);
      __m128 in_mm1 = _mm_loadu_ps(&in_channel_1[i]);

      in_mm0 = _mm_mul_ps(in_mm0, scale_mm);
      in_mm1 = _mm_mul_ps(in_mm1, scale_mm);

      __m128i out_mm0 = _mm_cvtps_epi32(in_mm0);
      __m128i out_mm1 = _mm_cvtps_epi32(in_mm1);

      __m128i out_mm = _mm_packs_epi32(out_mm0, out_mm1);

      out_mm = _mm_shuffle_epi8(out_mm, shufmask);

      _mm_storeu_si128(reinterpret_cast<__m128i*>(&out[i * 2]), out_mm);
    }
  } else {
    const __m128i shufmask = _mm_set_epi8(14, 15, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1);
    for (uint32_t i = 0; i < kSamplesPerFrame; i += 8) {
      __m128 in_mm0 = _mm_loadu_ps(&in_channel_0[i]);
      __m128 in_mm1 = _mm_loadu_ps(&in_channel_0[i + 4]);

      in_mm0 = _mm_mul_ps(in_mm0, scale_mm);
      in_mm1 = _mm_mul_ps(in_mm1, scale_mm);

      __m128i out_mm0 = _mm_cvtps_epi32(in_mm0);
      __m128i out_mm1 = _mm_cvtps_epi32(in_mm1);

      __m128i out_mm = _mm_packs_epi32(out_mm0, out_mm1);

      out_mm = _mm_shuffle_epi8(out_mm, shufmask);

      _mm_storeu_si128(reinterpret_cast<__m128i*>(&out[i]), out_mm);
    }
  }
#else
  uint32_t o = 0;
  for (uint32_t i = 0; i < kSamplesPerFrame; i++) {
    for (uint32_t j = 0; j <= uint32_t(is_two_channel); j++) {
      auto in = reinterpret_cast<const float*>(samples[j]);

      float scaled_sample = rex::clamp_float(in[i], -1.0f, 1.0f) * scale;

      auto sample = static_cast<int16_t>(scaled_sample);
      out[o++] = rex::byte_swap(sample);
    }
  }
#endif
}

}

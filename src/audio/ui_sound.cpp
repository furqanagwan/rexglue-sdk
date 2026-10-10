/**
 * @file        audio/ui_sound.cpp
 * @brief       Decodes RIFF XMA UI sounds to PCM (RG-GDK-041)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <rex/audio/ui_sound.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>

#include <fmt/format.h>

#include <rex/audio/xma/helpers.h>
#include <rex/stream.h>

extern "C" {
#include "libavcodec/avcodec.h"
}

namespace rex::audio {
namespace {

constexpr uint16_t kFormatXma1 = 0x0165;
constexpr uint16_t kFormatXma2 = 0x0166;
constexpr size_t kPacketBytes = 2048;
constexpr size_t kPacketHeaderBytes = 4;
constexpr uint32_t kFrameHeaderBits = 15;
constexpr uint32_t kMaxFrameBits = 0x4000;

uint16_t Le16(std::span<const uint8_t> b, size_t at) {
  return uint16_t(b[at] | b[at + 1] << 8);
}

uint32_t Le32(std::span<const uint8_t> b, size_t at) {
  return uint32_t(b[at]) | uint32_t(b[at + 1]) << 8 | uint32_t(b[at + 2]) << 16 |
         uint32_t(b[at + 3]) << 24;
}

struct CodecDeleter {
  void operator()(AVCodecContext* c) const { avcodec_free_context(&c); }
  void operator()(AVFrame* f) const { av_frame_free(&f); }
  void operator()(AVPacket* p) const { av_packet_free(&p); }
};

}

std::optional<PcmSound> DecodeXmaFile(std::span<const uint8_t> riff, std::string* error) {
  auto fail = [&](std::string message) -> std::optional<PcmSound> {
    if (error) {
      *error = std::move(message);
    }
    return std::nullopt;
  };
  if (riff.size() < 12 || std::memcmp(riff.data(), "RIFF", 4) != 0 ||
      std::memcmp(riff.data() + 8, "WAVE", 4) != 0) {
    return fail("not a RIFF WAVE file");
  }
  PcmSound sound;
  std::span<const uint8_t> data;
  for (size_t at = 12; at + 8 <= riff.size();) {
    const uint32_t size = Le32(riff, at + 4);
    if (at + 8 + uint64_t(size) > riff.size()) {
      return fail("RIFF chunk runs past the end");
    }
    std::span<const uint8_t> chunk = riff.subspan(at + 8, size);
    if (std::memcmp(riff.data() + at, "fmt ", 4) == 0 && chunk.size() >= 2) {
      const uint16_t tag = Le16(chunk, 0);
      if (tag == kFormatXma1) {
        if (chunk.size() < 12 + 20 || Le16(chunk, 8) != 1) {
          return fail("only single-stream XMA files are supported");
        }
        sound.sample_rate = Le32(chunk, 12 + 4);
        sound.channels = chunk[12 + 17];
      } else if (tag == kFormatXma2) {
        if (chunk.size() < 8) {
          return fail("XMA2 format chunk is truncated");
        }
        sound.channels = Le16(chunk, 2);
        sound.sample_rate = Le32(chunk, 4);
      } else {
        return fail(fmt::format("format {:#06x} is not XMA", tag));
      }
    } else if (std::memcmp(riff.data() + at, "data", 4) == 0) {
      data = chunk;
    }
    at += 8 + size + (size & 1);
  }
  if (sound.channels < 1 || sound.channels > 2 || !sound.sample_rate) {
    return fail("XMA file has no usable format chunk");
  }
  if (data.size() < kPacketBytes) {
    return fail("XMA file has no complete packet");
  }

  std::vector<uint8_t> payload;
  for (size_t p = 0; p + kPacketBytes <= data.size(); p += kPacketBytes) {
    payload.insert(payload.end(), data.begin() + p + kPacketHeaderBytes,
                   data.begin() + p + kPacketBytes);
  }
  payload.resize(payload.size() + 8, 0);
  stream::BitStream bits(payload.data(), (payload.size() - 8) * 8);
  bits.SetOffset(xma::GetPacketFrameOffset(data.data()) - kPacketHeaderBytes * 8);

  const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_XMAFRAMES);
  if (!codec) {
    return fail("the XMA frame decoder is not built in");
  }
  std::unique_ptr<AVCodecContext, CodecDeleter> context(avcodec_alloc_context3(codec));
  std::unique_ptr<AVFrame, CodecDeleter> frame(av_frame_alloc());
  std::unique_ptr<AVPacket, CodecDeleter> packet(av_packet_alloc());
  if (!context || !frame || !packet) {
    return fail("out of memory for the XMA decoder");
  }
  context->sample_rate = int(sound.sample_rate);
  context->channels = int(sound.channels);
  context->flags2 |= AV_CODEC_FLAG2_SKIP_MANUAL;
  if (avcodec_open2(context.get(), codec, nullptr) < 0) {
    return fail("the XMA frame decoder did not open");
  }

  std::array<uint8_t, 1 + kMaxFrameBits / 8 + 2> frame_bytes;
  while (bits.BitsRemaining() >= kFrameHeaderBits) {
    const uint32_t frame_bits = uint32_t(bits.Peek(kFrameHeaderBits));
    if (frame_bits == 0 || frame_bits == xma::kMaxFrameLength || frame_bits >= kMaxFrameBits ||
        frame_bits > bits.BitsRemaining()) {
      break;
    }
    frame_bytes.fill(0);
    const uint32_t padding = uint32_t(bits.Copy(frame_bytes.data() + 1, frame_bits));

    const uint32_t size = 1 + (padding + frame_bits + 7) / 8;
    const uint32_t padding_end = size * 8 - (8 + padding + frame_bits);
    frame_bytes[0] = uint8_t(((padding & 7) << 5) | ((padding_end & 7) << 2));

    bits.SetOffset(bits.offset_bits() - 1);
    const bool more = bits.Read(1) != 0;

    packet->data = frame_bytes.data();
    packet->size = int(size);
    if (avcodec_send_packet(context.get(), packet.get()) >= 0 &&
        avcodec_receive_frame(context.get(), frame.get()) >= 0) {
      const int samples = frame->nb_samples;
      const size_t start = sound.samples.size();
      sound.samples.resize(start + size_t(samples) * sound.channels);
      for (int i = 0; i < samples; ++i) {
        for (uint32_t c = 0; c < sound.channels; ++c) {
          const float v = reinterpret_cast<const float*>(frame->data[c])[i];
          sound.samples[start + size_t(i) * sound.channels + c] =
              int16_t(std::lround(std::clamp(v, -1.0f, 1.0f) * 32767.0f));
        }
      }
    }
    if (!more) {
      break;
    }
  }
  if (sound.samples.empty()) {
    return fail("no XMA frame decoded");
  }
  return sound;
}

}

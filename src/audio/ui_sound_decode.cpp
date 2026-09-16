/**
 * @file        audio/ui_sound_decode.cpp
 * @brief       Decodes console XMA audio files to PCM for interface sounds
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#include <rex/audio/ui_sound.h>

#include <algorithm>
#include <cstring>

#include <rex/logging.h>

extern "C" {
#if REX_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable : 4101 4244 5033)
#endif
#include "libavcodec/avcodec.h"
#include "libavutil/frame.h"
#if REX_COMPILER_MSVC
#pragma warning(pop)
#endif
}  // extern "C"

namespace rex::audio {

namespace {

constexpr uint16_t kFormatXma1 = 0x165;
constexpr uint16_t kFormatXma2 = 0x166;
constexpr size_t kXmaPacketSize = 2048;

uint32_t ReadLE32(std::span<const uint8_t> data, size_t offset) {
  return uint32_t(data[offset]) | (uint32_t(data[offset + 1]) << 8) |
         (uint32_t(data[offset + 2]) << 16) | (uint32_t(data[offset + 3]) << 24);
}

uint16_t ReadLE16(std::span<const uint8_t> data, size_t offset) {
  return uint16_t(data[offset] | (data[offset + 1] << 8));
}

}  // namespace

std::optional<PcmSound> DecodeXmaFile(std::span<const uint8_t> file) {
  if (file.size() < 12 || std::memcmp(file.data(), "RIFF", 4) != 0 ||
      std::memcmp(file.data() + 8, "WAVE", 4) != 0) {
    return std::nullopt;
  }

  std::span<const uint8_t> format;
  std::span<const uint8_t> payload;
  for (size_t offset = 12; offset + 8 <= file.size();) {
    const uint32_t size = ReadLE32(file, offset + 4);
    if (offset + 8 + size > file.size()) {
      break;
    }
    const auto body = file.subspan(offset + 8, size);
    if (std::memcmp(file.data() + offset, "fmt ", 4) == 0) {
      format = body;
    } else if (std::memcmp(file.data() + offset, "data", 4) == 0) {
      payload = body;
    }
    offset += 8 + size + (size & 1);
  }
  if (format.size() < 4 || payload.empty()) {
    return std::nullopt;
  }

  const uint16_t tag = ReadLE16(format, 0);
  AVCodecID codec_id = AV_CODEC_ID_NONE;
  int channels = 0;
  int sample_rate = 0;
  std::vector<uint8_t> extradata;
  if (tag == kFormatXma1) {
    // XMAWAVEFORMAT: 12 bytes, then 20 per stream (rate at 4, channels at 17).
    // FFmpeg takes it from the bits-per-sample field on.
    if (format.size() < 12) {
      return std::nullopt;
    }
    const uint16_t streams = ReadLE16(format, 8);
    if (streams == 0 || format.size() < 12 + size_t(streams) * 20) {
      return std::nullopt;
    }
    for (uint16_t i = 0; i < streams; ++i) {
      const size_t stream = 12 + size_t(i) * 20;
      sample_rate = int(ReadLE32(format, stream + 4));
      channels += format[stream + 17];
    }
    codec_id = AV_CODEC_ID_XMA1;
    extradata.assign(format.begin() + 4, format.begin() + 12 + size_t(streams) * 20);
  } else if (tag == kFormatXma2) {
    // WAVEFORMATEX followed by the XMA2 extension, which FFmpeg reads as-is.
    if (format.size() < 18) {
      return std::nullopt;
    }
    channels = ReadLE16(format, 2);
    sample_rate = int(ReadLE32(format, 4));
    codec_id = AV_CODEC_ID_XMA2;
    extradata.assign(format.begin() + 18, format.end());
  } else {
    return std::nullopt;
  }
  if (channels <= 0 || sample_rate <= 0) {
    return std::nullopt;
  }

  const AVCodec* codec = avcodec_find_decoder(codec_id);
  if (!codec) {
    REXAPU_WARN("UI sound: this build has no XMA{} file decoder", codec_id == AV_CODEC_ID_XMA1 ? 1 : 2);
    return std::nullopt;
  }
  AVCodecContext* context = avcodec_alloc_context3(codec);
  if (!context) {
    return std::nullopt;
  }
  context->channels = channels;
  context->sample_rate = sample_rate;
  context->extradata = static_cast<uint8_t*>(
      av_mallocz(extradata.size() + AV_INPUT_BUFFER_PADDING_SIZE));
  if (!context->extradata) {
    avcodec_free_context(&context);
    return std::nullopt;
  }
  std::memcpy(context->extradata, extradata.data(), extradata.size());
  context->extradata_size = int(extradata.size());
  if (avcodec_open2(context, codec, nullptr) < 0) {
    avcodec_free_context(&context);
    return std::nullopt;
  }

  PcmSound sound;
  sound.sample_rate = uint32_t(sample_rate);
  sound.channels = uint16_t(channels);

  AVPacket* packet = av_packet_alloc();
  AVFrame* frame = av_frame_alloc();
  std::vector<uint8_t> padded(kXmaPacketSize + AV_INPUT_BUFFER_PADDING_SIZE);
  const auto drain = [&]() {
    while (avcodec_receive_frame(context, frame) == 0) {
      const int count = frame->nb_samples;
      const size_t start = sound.samples.size();
      sound.samples.resize(start + size_t(count) * size_t(channels));
      for (int c = 0; c < channels; ++c) {
        const float* plane = reinterpret_cast<const float*>(frame->extended_data[c]);
        for (int s = 0; s < count; ++s) {
          sound.samples[start + size_t(s) * size_t(channels) + size_t(c)] =
              std::clamp(plane[s], -1.0f, 1.0f);
        }
      }
      av_frame_unref(frame);
    }
  };
  for (size_t offset = 0; offset + kXmaPacketSize <= payload.size(); offset += kXmaPacketSize) {
    std::memcpy(padded.data(), payload.data() + offset, kXmaPacketSize);
    packet->data = padded.data();
    packet->size = int(kXmaPacketSize);
    if (avcodec_send_packet(context, packet) < 0) {
      break;
    }
    drain();
  }
  avcodec_send_packet(context, nullptr);
  drain();

  av_frame_free(&frame);
  av_packet_free(&packet);
  avcodec_free_context(&context);

  if (sound.samples.empty()) {
    return std::nullopt;
  }
  return sound;
}

}  // namespace rex::audio

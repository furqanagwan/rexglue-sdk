// Copyright (c) 2026 ReXGlue contributors. BSD-3-Clause; see LICENSE.
// Probe a private XMAD packet chain with the SDK's pinned FFmpeg decoder.
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/log.h>
}

namespace {
uint32_t Little(const uint8_t* p) {
  return uint32_t(p[0]) | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24);
}
uint32_t Big(const uint8_t* p) {
  return uint32_t(p[3]) | (uint32_t(p[2]) << 8) | (uint32_t(p[1]) << 16) | (uint32_t(p[0]) << 24);
}
uint32_t Bits(const std::vector<uint8_t>& stream, size_t at, uint32_t count) {
  if (at + count > stream.size() * 8)
    throw std::runtime_error("truncated frame bits");
  uint32_t result = 0;
  while (count--) {
    result = (result << 1) | ((stream[at / 8] >> (7 - at % 8)) & 1);
    ++at;
  }
  return result;
}
}  // namespace

int main(int argc, char** argv) {
  if (argc != 4) {
    std::fprintf(stderr,
                 "Usage: xma_probe CAPTURE.bin BUFFER_INDEX START_PACKET\n"
                 "Buffers: 0/1 = current inputs, 2 = previous snapshot.\n"
                 "Tests the selected skip chain as mono and stereo; emits no audio.\n");
    return 2;
  }
  try {
    const auto buffer_index = std::stoul(argv[2]);
    const auto start_packet = std::stoul(argv[3]);
    std::ifstream file(argv[1], std::ios::binary | std::ios::ate);
    auto length = file.tellg();
    if (length < 76 || length > 3 * 4095 * 2048 + 80)
      throw std::runtime_error("invalid XMAD file size");
    std::vector<uint8_t> bytes(static_cast<size_t>(length));
    file.seekg(0);
    if (!file.read(reinterpret_cast<char*>(bytes.data()), bytes.size()) ||
        std::memcmp(bytes.data(), "XMAD", 4))
      throw std::runtime_error("invalid XMAD header");
    std::vector<std::vector<uint8_t>> buffers;
    for (size_t at = 68; at < bytes.size();) {
      if (buffers.size() == 3 || at + 4 > bytes.size())
        throw std::runtime_error("invalid buffer table");
      uint32_t size = Little(bytes.data() + at);
      at += 4;
      if (size % 2048 || size > 4095 * 2048 || size > bytes.size() - at)
        throw std::runtime_error("truncated or invalid packet buffer");
      buffers.emplace_back(bytes.begin() + at, bytes.begin() + at + size);
      at += size;
    }
    if (buffers.size() < 2 || buffer_index >= buffers.size())
      throw std::runtime_error("missing input buffer");
    const auto& input = buffers[buffer_index];
    if (start_packet >= input.size() / 2048)
      throw std::runtime_error("start packet outside buffer");
    std::vector<uint8_t> stream;
    std::vector<size_t> starts;
    uint32_t packets = 0;
    size_t packet = start_packet;
    for (; packet < input.size() / 2048; ++packets) {
      const auto* p = input.data() + packet * 2048;
      uint32_t first = ((p[0] & 3) << 13) | (p[1] << 5) | (p[2] >> 3);
      if (first < 2044 * 8)
        starts.push_back(stream.size() * 8 + first);
      stream.insert(stream.end(), p + 4, p + 2048);
      if (p[3] == 255) {
        ++packets;
        break;
      }
      packet += p[3] + 1;
    }
    if (starts.empty())
      throw std::runtime_error("no frame starts in this chain");
    constexpr int rates[]{24000, 32000, 44100, 48000};
    const int rate = rates[(Big(bytes.data() + 8) >> 27) & 3];
    std::printf("buffer %lu packet %lu: %u packets, rate %d Hz", buffer_index, start_packet,
                packets, rate);
    if (packet >= input.size() / 2048)
      std::printf(", next buffer packet %zu", packet - input.size() / 2048);
    std::puts("");
    av_log_set_level(AV_LOG_QUIET);
    const AVCodec* codec = avcodec_find_decoder(AV_CODEC_ID_XMAFRAMES);
    if (!codec)
      throw std::runtime_error("xmaframes decoder unavailable");
    for (int channels : {1, 2}) {
      AVCodecContext* ctx = avcodec_alloc_context3(codec);
      AVPacket* pkt = av_packet_alloc();
      AVFrame* frame = av_frame_alloc();
      if (!ctx || !pkt || !frame)
        throw std::runtime_error("decoder allocation failed");
      ctx->sample_rate = rate;
      ctx->channels = channels;
      ctx->flags2 |= AV_CODEC_FLAG2_SKIP_MANUAL;
      if (avcodec_open2(ctx, codec, nullptr) < 0)
        throw std::runtime_error("decoder open failed");
      int good = 0, bad = 0, incomplete = 0;
      for (size_t at = starts.front(); at + 15 <= stream.size() * 8;) {
        const uint32_t size = Bits(stream, at, 15);
        if (size < 16 || size == 0x7FFF || at + size > stream.size() * 8) {
          ++incomplete;
          break;
        }
        const uint32_t pad = at & 7;
        const size_t count = (pad + size + 7) / 8;
        std::array<uint8_t, 1 + 4096 + AV_INPUT_BUFFER_PADDING_SIZE> data{};
        std::memcpy(data.data() + 1, stream.data() + at / 8, count);
        data[0] = uint8_t((pad << 5) | (((count * 8 - pad - size) & 7) << 2));
        pkt->data = data.data();
        pkt->size = int(1 + count);
        if (avcodec_send_packet(ctx, pkt) >= 0 && avcodec_receive_frame(ctx, frame) >= 0)
          ++good;
        else
          ++bad;
        const bool more = Bits(stream, at + size - 1, 1);
        at += size;
        if (!more) {
          auto next = std::lower_bound(starts.begin(), starts.end(), at);
          if (next == starts.end())
            break;
          at = *next;
        }
      }
      std::printf("%s: %d decoded, %d rejected, %d incomplete tail\n",
                  channels == 1 ? "mono" : "stereo", good, bad, incomplete);
      av_frame_free(&frame);
      av_packet_free(&pkt);
      avcodec_free_context(&ctx);
    }
    return 0;  // A probe result, not a declaration of title compatibility.
  } catch (const std::exception& error) {
    std::fprintf(stderr, "xma_probe: %s\n", error.what());
    return 2;
  }
}

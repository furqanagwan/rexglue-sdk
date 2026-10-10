// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.

#include <rex/system/game_source.h>

#include <algorithm>
#include <cstring>
#include <optional>
#include <vector>

#include <fmt/format.h>
#include <rex/system/lzx.h>

void aes_decrypt_buffer(const uint8_t* session_key, const uint8_t* input_buffer,
                        const size_t input_size, uint8_t* output_buffer, const size_t output_size);

namespace rex::system {
namespace {

constexpr uint8_t kRetailKey[16] = {0x20, 0xB1, 0x85, 0xA5, 0x9D, 0x28, 0xFD, 0xC3,
                                    0x40, 0x58, 0x3F, 0xBB, 0x08, 0x96, 0xBF, 0x91};
constexpr uint8_t kDevKitKey[16] = {};
constexpr uint32_t kResourceInfo = 0x000002FF;
constexpr uint32_t kFileFormatInfo = 0x000003FF;
constexpr uint32_t kImageBaseAddress = 0x00010201;
constexpr size_t kMaxImageSize = 512 * 1024 * 1024;

class Bytes {
 public:
  explicit Bytes(std::span<const uint8_t> bytes) : bytes_(bytes) {}
  bool Has(size_t offset, size_t count) const {
    return offset <= bytes_.size() && bytes_.size() - offset >= count;
  }
  uint16_t Be16(size_t offset) const {
    return Has(offset, 2) ? uint16_t((bytes_[offset] << 8) | bytes_[offset + 1]) : 0;
  }
  uint32_t Be32(size_t offset) const {
    return Has(offset, 4) ? (uint32_t(Be16(offset)) << 16) | Be16(offset + 2) : 0;
  }
  uint64_t Be64(size_t offset) const {
    return Has(offset, 8) ? (uint64_t(Be32(offset)) << 32) | Be32(offset + 4) : 0;
  }
  std::span<const uint8_t> Sub(size_t offset, size_t count) const {
    return Has(offset, count) ? bytes_.subspan(offset, count) : std::span<const uint8_t>{};
  }
  size_t size() const { return bytes_.size(); }

 private:
  std::span<const uint8_t> bytes_;
};

std::optional<uint32_t> OptHeader(const Bytes& xex, uint32_t key) {
  const uint32_t count = xex.Be32(0x14);
  for (uint32_t i = 0; i < count && xex.Has(0x18 + size_t(i) * 8, 8); ++i)
    if (xex.Be32(0x18 + size_t(i) * 8) == key)
      return xex.Be32(0x1C + size_t(i) * 8);
  return std::nullopt;
}

std::vector<uint8_t> Decrypt(std::span<const uint8_t> data, const uint8_t* session_key) {
  std::vector<uint8_t> out(data.size() & ~size_t(15));
  if (!out.empty())
    aes_decrypt_buffer(session_key, data.data(), out.size(), out.data(), out.size());
  return out;
}

std::vector<uint8_t> DecodeImage(const Bytes& xex, uint32_t format, const uint8_t* key) {
  const uint32_t header_size = xex.Be32(0x08);
  const uint32_t security = xex.Be32(0x10);
  const uint32_t image_size = xex.Be32(size_t(security) + 0x04);
  const auto aes_key = xex.Sub(size_t(security) + 0x150, 16);
  if (header_size > xex.size() || aes_key.empty() || !image_size || image_size > kMaxImageSize)
    return {};
  uint8_t session_key[16];
  aes_decrypt_buffer(key, aes_key.data(), 16, session_key, 16);
  const auto payload = xex.Sub(header_size, xex.size() - header_size);
  const bool encrypted = xex.Be16(size_t(format) + 4) == 1;
  const uint16_t compression = xex.Be16(size_t(format) + 6);
  std::vector<uint8_t> plain = encrypted ? Decrypt(payload, session_key)
                                         : std::vector<uint8_t>(payload.begin(), payload.end());
  std::vector<uint8_t> image;
  if (compression == 0) {
    plain.resize(std::min<size_t>(plain.size(), image_size));
    return plain;
  }
  if (compression == 1) {
    const uint32_t info_size = xex.Be32(format);
    const uint32_t blocks = info_size >= 8 ? (info_size - 8) / 8 : 0;
    size_t from = 0;
    for (uint32_t i = 0; i < blocks; ++i) {
      const uint32_t data_size = xex.Be32(size_t(format) + 8 + size_t(i) * 8);
      const uint32_t zero_size = xex.Be32(size_t(format) + 12 + size_t(i) * 8);
      if (plain.size() - from < data_size || image.size() + data_size + zero_size > kMaxImageSize)
        return {};
      image.insert(image.end(), plain.begin() + from, plain.begin() + from + data_size);
      image.resize(image.size() + zero_size);
      from += data_size;
    }
    return image;
  }
  if (compression != 2)
    return {};

  const uint32_t window_size = xex.Be32(size_t(format) + 8);
  uint32_t block_size = xex.Be32(size_t(format) + 12);
  Bytes blocks(plain);
  std::vector<uint8_t> lzx;
  for (size_t at = 0; block_size;) {
    if (!blocks.Has(at, block_size) || block_size < 24)
      return {};
    const size_t end = at + block_size;
    const uint32_t next = blocks.Be32(at);
    for (size_t p = at + 24; p + 2 <= end;) {
      const uint16_t chunk = blocks.Be16(p);
      p += 2;
      if (!chunk)
        break;
      if (end - p < chunk)
        return {};
      lzx.insert(lzx.end(), plain.begin() + p, plain.begin() + p + chunk);
      p += chunk;
    }
    at = end;
    block_size = next;
  }
  image.resize(image_size);
  if (lzx.empty() ||
      lzx_decompress(lzx.data(), lzx.size(), image.data(), image.size(), window_size, nullptr, 0))
    return {};
  return image;
}

std::string XdbfTitle(std::span<const uint8_t> resource) {
  const Bytes xdbf(resource);
  if (xdbf.Be32(0) != 0x58444246)
    return {};
  const uint32_t entry_count = xdbf.Be32(8), entry_used = xdbf.Be32(12), free_count = xdbf.Be32(16);
  const size_t content = 24 + size_t(entry_count) * 18 + size_t(free_count) * 8;
  if (entry_used > entry_count || !xdbf.Has(0, content))
    return {};
  auto find = [&](uint16_t section, uint64_t id) -> std::span<const uint8_t> {
    for (uint32_t i = 0; i < entry_used; ++i) {
      const size_t at = 24 + size_t(i) * 18;
      if (xdbf.Be16(at) == section && xdbf.Be64(at + 2) == id)
        return xdbf.Sub(content + xdbf.Be32(at + 10), xdbf.Be32(at + 14));
    }
    return {};
  };
  uint32_t language = 1;
  if (const auto xstc = Bytes(find(1, 0x58535443)); xstc.Be32(0) == 0x58535443)
    language = xstc.Be32(12);
  for (const uint32_t candidate : {language, 1u}) {
    const Bytes table(find(3, candidate));
    if (table.Be32(0) != 0x58535452)
      continue;
    const uint16_t count = table.Be16(12);
    size_t at = 14;
    for (uint16_t i = 0; i < count && table.Has(at, 4); ++i) {
      const uint16_t id = table.Be16(at), length = table.Be16(at + 2);
      const auto text = table.Sub(at + 4, length);
      if (text.size() != length)
        break;
      if (id == 0x8000)
        return std::string(text.begin(), text.end());
      at += 4 + length;
    }
  }
  return {};
}

}

std::string XexTitleName(std::span<const uint8_t> bytes) {
  const Bytes xex(bytes);
  const uint32_t title_id = XexSourceTitleId(bytes);
  const auto resources = OptHeader(xex, kResourceInfo);
  const auto format = OptHeader(xex, kFileFormatInfo);
  if (!title_id || !resources || !format)
    return {};
  const std::string name = fmt::format("{:08X}", title_id);
  std::optional<std::pair<uint32_t, uint32_t>> resource;
  const uint32_t count = (xex.Be32(*resources) >= 4 ? xex.Be32(*resources) - 4 : 0) / 16;
  for (uint32_t i = 0; i < count; ++i) {
    const size_t at = size_t(*resources) + 4 + size_t(i) * 16;
    const auto label = xex.Sub(at, 8);
    if (label.size() == 8 && std::memcmp(label.data(), name.data(), 8) == 0)
      resource = std::pair(xex.Be32(at + 8), xex.Be32(at + 12));
  }
  if (!resource)
    return {};
  uint32_t base = xex.Be32(size_t(xex.Be32(0x10)) + 0x110);
  if (const auto image_base = OptHeader(xex, kImageBaseAddress))
    base = *image_base;
  if (resource->first < base)
    return {};

  for (const uint8_t* key : {kRetailKey, kDevKitKey}) {
    const auto image = DecodeImage(xex, *format, key);
    const Bytes view(image);
    const auto title = XdbfTitle(view.Sub(resource->first - base, resource->second));
    if (!title.empty())
      return title;
  }
  return {};
}

}

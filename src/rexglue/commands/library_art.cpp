/**
 * @file        rexglue/commands/library_art.cpp
 * @brief       Xbox 360 backward-compatibility style library tiles (RG-GDK-068)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include "library_art.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <limits>

#include <fmt/format.h>

// clang-format off
#include <windows.h>
#include <wincodec.h>
#include <wrl/client.h>
// clang-format on

namespace rexglue::cli {

std::optional<std::vector<uint8_t>> EncodeIco(const Image& image, std::string* error) {
  if (image.width <= 0 || image.height <= 0 ||
      image.pixels.size() != size_t(image.width) * size_t(image.height) * 4) {
    if (error)
      *error = "invalid title image dimensions or pixel count";
    return std::nullopt;
  }
  constexpr std::array<int, 7> sizes = {16, 24, 32, 48, 64, 128, 256};
  std::vector<uint8_t> result(6 + sizes.size() * 16, 0);
  auto put16 = [&result](size_t offset, uint16_t value) {
    result[offset] = uint8_t(value);
    result[offset + 1] = uint8_t(value >> 8);
  };
  auto put32 = [&result](size_t offset, uint32_t value) {
    for (int i = 0; i < 4; ++i)
      result[offset + i] = uint8_t(value >> (8 * i));
  };
  put16(2, 1);  // ICONDIR type: icon, not cursor.
  put16(4, uint16_t(sizes.size()));
  for (size_t i = 0; i < sizes.size(); ++i) {
    const auto resized = Cover(image, sizes[i], sizes[i]);
    std::vector<uint8_t> frame;
    if (sizes[i] == 256) {
      const auto png = EncodePng(resized, error);
      if (!png)
        return std::nullopt;
      frame = *png;
    } else {
      const int size = sizes[i];
      const size_t mask_stride = size_t((size + 31) / 32) * 4;
      frame.resize(40 + size_t(size) * size * 4 + mask_stride * size, 0);
      auto frame32 = [&frame](size_t offset, uint32_t value) {
        for (int j = 0; j < 4; ++j)
          frame[offset + j] = uint8_t(value >> (8 * j));
      };
      frame32(0, 40);  // BITMAPINFOHEADER, with XOR and AND planes stacked.
      frame32(4, size);
      frame32(8, size * 2);
      frame[12] = 1;
      frame[14] = 32;
      frame32(20, uint32_t(frame.size() - 40));
      for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
          const auto* pixel = resized.at(x, y);
          const size_t row = size_t(size - y - 1);
          auto* dest = frame.data() + 40 + (row * size + x) * 4;
          // Icon DIBs store straight BGRA, unlike our premultiplied images.
          for (int c = 0; c < 3; ++c) {
            dest[c] =
                pixel[3]
                    ? uint8_t(std::min(255u, (uint32_t(pixel[c]) * 255 + pixel[3] / 2) / pixel[3]))
                    : 0;
          }
          dest[3] = pixel[3];
          if (!pixel[3]) {
            frame[40 + size_t(size) * size * 4 + row * mask_stride + x / 8] |=
                uint8_t(0x80 >> (x % 8));
          }
        }
      }
    }
    if (result.size() + frame.size() > std::numeric_limits<uint32_t>::max()) {
      return std::nullopt;
    }
    const size_t entry = 6 + i * 16;
    result[entry] = result[entry + 1] = uint8_t(sizes[i]);  // 0 denotes 256.
    put16(entry + 4, 1);
    put16(entry + 6, 32);
    put32(entry + 8, uint32_t(frame.size()));
    put32(entry + 12, uint32_t(result.size()));
    result.insert(result.end(), frame.begin(), frame.end());
  }
  return result;
}

namespace {

using Microsoft::WRL::ComPtr;

IWICImagingFactory* Factory() {
  static ComPtr<IWICImagingFactory> factory = [] {
    // The command may run on a thread COM already set up another way.
    const HRESULT init = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    (void)init;
    ComPtr<IWICImagingFactory> f;
    CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&f));
    return f;
  }();
  return factory.Get();
}

std::optional<Image> Read(IWICBitmapSource* source, std::string* error) {
  ComPtr<IWICBitmapSource> converted;
  UINT width = 0, height = 0;
  if (FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppPBGRA, source, &converted)) ||
      FAILED(converted->GetSize(&width, &height)) || !width || !height) {
    if (error) {
      *error = "the image does not convert to BGRA";
    }
    return std::nullopt;
  }
  Image image;
  image.width = int(width);
  image.height = int(height);
  image.pixels.resize(size_t(width) * height * 4);
  if (FAILED(converted->CopyPixels(nullptr, width * 4, UINT(image.pixels.size()),
                                   image.pixels.data()))) {
    if (error) {
      *error = "the image's pixels do not read";
    }
    return std::nullopt;
  }
  return image;
}

ComPtr<IWICBitmap> ToBitmap(const Image& image) {
  ComPtr<IWICBitmap> bitmap;
  Factory()->CreateBitmapFromMemory(
      UINT(image.width), UINT(image.height), GUID_WICPixelFormat32bppPBGRA, UINT(image.width) * 4,
      UINT(image.pixels.size()), const_cast<BYTE*>(image.pixels.data()), &bitmap);
  return bitmap;
}

Image Blank(int width, int height, uint32_t bgra = 0) {
  Image image;
  image.width = width;
  image.height = height;
  image.pixels.resize(size_t(width) * height * 4);
  for (size_t i = 0; i < image.pixels.size(); i += 4) {
    std::memcpy(&image.pixels[i], &bgra, 4);
  }
  return image;
}

// `src` over `dst` at (x, y); both premultiplied.
void Draw(Image& dst, const Image& src, int x, int y) {
  for (int sy = 0; sy < src.height; ++sy) {
    const int dy = y + sy;
    if (dy < 0 || dy >= dst.height) {
      continue;
    }
    for (int sx = 0; sx < src.width; ++sx) {
      const int dx = x + sx;
      if (dx < 0 || dx >= dst.width) {
        continue;
      }
      const uint8_t* s = src.at(sx, sy);
      uint8_t* d = dst.at(dx, dy);
      const int keep = 255 - s[3];
      for (int c = 0; c < 4; ++c) {
        d[c] = uint8_t(s[c] + (d[c] * keep + 127) / 255);
      }
    }
  }
}

Image Crop(const Image& image, int x, int y, int width, int height) {
  Image out = Blank(width, height);
  for (int row = 0; row < height; ++row) {
    std::memcpy(out.at(0, row), image.at(x, y + row), size_t(width) * 4);
  }
  return out;
}

// Quarter turn anticlockwise: the left edge becomes the bottom.
Image RotateLeft(const Image& image) {
  Image out = Blank(image.height, image.width);
  for (int y = 0; y < out.height; ++y) {
    for (int x = 0; x < out.width; ++x) {
      std::memcpy(out.at(x, y), image.at(image.width - 1 - y, x), 4);
    }
  }
  return out;
}

// The strip, measured on the Store's 1080 x 1080 tiles for Xbox 360 games.
constexpr double kMaster = 1080.0;
constexpr double kStripWidth = 189.0;
constexpr double kWordmarkTop = 494.0, kWordmarkLength = 415.0;
constexpr double kOrbCentreY = 986.5, kOrbDiameter = 113.0;

// The swooshes: bands from the top, each with its lower edge's depth at four
// points across the strip; the edges curve down to the right.
constexpr double kBandX[] = {5.0, 60.0, 120.0, 175.0};
struct Band {
  uint8_t r, g, b;
  double lower[4];
};
constexpr Band kBands[] = {
    {151, 201, 28, {-40, -20, 3, 28}},    {218, 225, 60, {-5, 17, 41, 59}},
    {126, 194, 29, {92, 105, 124, 140}},  {52, 167, 40, {125, 137, 154, 177}},
    {126, 194, 29, {205, 217, 228, 245}}, {15, 124, 15, {207, 219, 241, 263}},
    {45, 165, 13, {282, 291, 306, 322}},  {100, 195, 33, {316, 323, 344, 355}},
    {26, 142, 42, {337, 345, 364, 378}},  {105, 181, 82, {360, 370, 383, 400}},
    {84, 173, 78, {379, 387, 401, 419}},  {59, 164, 73, {400, 405, 412, 428}},
};
// Below the last band, its green fades to white by this depth.
constexpr double kFadeEnd[] = {425, 432, 444, 460};

// y = a + b x + c x^2 through the four points, least squares.
std::array<double, 3> Fit(const double (&y)[4]) {
  double s[5] = {}, t[3] = {};
  for (int i = 0; i < 4; ++i) {
    double p = 1.0;
    for (int k = 0; k < 5; ++k) {
      s[k] += p;
      if (k < 3) {
        t[k] += p * y[i];
      }
      p *= kBandX[i];
    }
  }
  // Normal equations, Cramer's rule.
  const double m[3][3] = {{s[0], s[1], s[2]}, {s[1], s[2], s[3]}, {s[2], s[3], s[4]}};
  auto det = [](const double (&a)[3][3]) {
    return a[0][0] * (a[1][1] * a[2][2] - a[1][2] * a[2][1]) -
           a[0][1] * (a[1][0] * a[2][2] - a[1][2] * a[2][0]) +
           a[0][2] * (a[1][0] * a[2][1] - a[1][1] * a[2][0]);
  };
  const double d = det(m);
  std::array<double, 3> out{};
  for (int col = 0; col < 3; ++col) {
    double a[3][3];
    for (int r = 0; r < 3; ++r) {
      for (int c = 0; c < 3; ++c) {
        a[r][c] = c == col ? t[r] : m[r][c];
      }
    }
    out[col] = det(a) / d;
  }
  return out;
}

double At(const std::array<double, 3>& f, double x) {
  return f[0] + f[1] * x + f[2] * x * x;
}

// The strip's swooshes and white, at the master size, 4 x 4 samples a pixel.
void DrawStrip(Image& tile) {
  std::array<std::array<double, 3>, std::size(kBands)> edges;
  for (size_t i = 0; i < std::size(kBands); ++i) {
    edges[i] = Fit(kBands[i].lower);
  }
  const auto fade = Fit(kFadeEnd);
  const int width = int(kStripWidth);
  for (int y = 0; y < tile.height; ++y) {
    for (int x = 0; x < width; ++x) {
      double rgb[3] = {};
      for (int sy = 0; sy < 4; ++sy) {
        for (int sx = 0; sx < 4; ++sx) {
          const double px = x + (sx + 0.5) / 4.0, py = y + (sy + 0.5) / 4.0;
          double c[3] = {255, 255, 255};
          size_t band = 0;
          while (band < std::size(kBands) && py >= At(edges[band], px)) {
            ++band;
          }
          if (band < std::size(kBands)) {
            c[0] = kBands[band].r, c[1] = kBands[band].g, c[2] = kBands[band].b;
          } else {
            const Band& last = kBands[std::size(kBands) - 1];
            const double top = At(edges[std::size(kBands) - 1], px), end = At(fade, px);
            const double t = std::clamp((py - top) / std::max(end - top, 1.0), 0.0, 1.0);
            c[0] = last.r + (255 - last.r) * t;
            c[1] = last.g + (255 - last.g) * t;
            c[2] = last.b + (255 - last.b) * t;
          }
          for (int k = 0; k < 3; ++k) {
            rgb[k] += c[k] / 16.0;
          }
        }
      }
      uint8_t* p = tile.at(x, y);
      p[0] = uint8_t(rgb[2] + 0.5);
      p[1] = uint8_t(rgb[1] + 0.5);
      p[2] = uint8_t(rgb[0] + 0.5);
      p[3] = 255;
    }
  }
}

}  // namespace

std::optional<Image> DecodeImage(std::span<const uint8_t> bytes, std::string* error) {
  IWICImagingFactory* factory = Factory();
  ComPtr<IWICStream> stream;
  ComPtr<IWICBitmapDecoder> decoder;
  ComPtr<IWICBitmapFrameDecode> frame;
  if (!factory || bytes.empty() || FAILED(factory->CreateStream(&stream)) ||
      FAILED(stream->InitializeFromMemory(const_cast<BYTE*>(bytes.data()), DWORD(bytes.size()))) ||
      FAILED(factory->CreateDecoderFromStream(stream.Get(), nullptr, WICDecodeMetadataCacheOnDemand,
                                              &decoder)) ||
      FAILED(decoder->GetFrame(0, &frame))) {
    if (error) {
      *error = "not an image Windows Imaging Component reads";
    }
    return std::nullopt;
  }
  return Read(frame.Get(), error);
}

std::optional<std::vector<uint8_t>> EncodePng(const Image& image, std::string* error) {
  IWICImagingFactory* factory = Factory();
  auto fail = [&](const char* what) {
    if (error) {
      *error = fmt::format("PNG encoding failed: {}", what);
    }
    return std::nullopt;
  };
  ComPtr<IWICBitmap> bitmap = factory ? ToBitmap(image) : nullptr;
  ComPtr<IWICBitmapSource> straight;
  if (!bitmap ||
      FAILED(WICConvertBitmapSource(GUID_WICPixelFormat32bppBGRA, bitmap.Get(), &straight))) {
    return fail("conversion");
  }
  ComPtr<IStream> stream;
  ComPtr<IWICBitmapEncoder> encoder;
  ComPtr<IWICBitmapFrameEncode> frame;
  ComPtr<IPropertyBag2> options;
  if (FAILED(CreateStreamOnHGlobal(nullptr, TRUE, &stream)) ||
      FAILED(factory->CreateEncoder(GUID_ContainerFormatPng, nullptr, &encoder)) ||
      FAILED(encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache)) ||
      FAILED(encoder->CreateNewFrame(&frame, &options)) ||
      FAILED(frame->Initialize(options.Get())) ||
      FAILED(frame->SetSize(UINT(image.width), UINT(image.height)))) {
    return fail("encoder");
  }
  WICPixelFormatGUID format = GUID_WICPixelFormat32bppBGRA;
  if (FAILED(frame->SetPixelFormat(&format)) || format != GUID_WICPixelFormat32bppBGRA ||
      FAILED(frame->WriteSource(straight.Get(), nullptr)) || FAILED(frame->Commit()) ||
      FAILED(encoder->Commit())) {
    return fail("frame");
  }
  HGLOBAL memory = nullptr;
  if (FAILED(GetHGlobalFromStream(stream.Get(), &memory))) {
    return fail("stream");
  }
  STATSTG stat = {};
  stream->Stat(&stat, STATFLAG_NONAME);
  const auto* data = static_cast<const uint8_t*>(GlobalLock(memory));
  std::vector<uint8_t> out(data, data + stat.cbSize.QuadPart);
  GlobalUnlock(memory);
  return out;
}

Image Resize(const Image& image, int width, int height) {
  if (image.width == width && image.height == height) {
    return image;
  }
  ComPtr<IWICBitmap> bitmap = ToBitmap(image);
  ComPtr<IWICBitmapScaler> scaler;
  Image out = Blank(width, height);
  if (bitmap && SUCCEEDED(Factory()->CreateBitmapScaler(&scaler)) &&
      SUCCEEDED(scaler->Initialize(bitmap.Get(), UINT(width), UINT(height),
                                   WICBitmapInterpolationModeHighQualityCubic))) {
    scaler->CopyPixels(nullptr, UINT(width) * 4, UINT(out.pixels.size()), out.pixels.data());
  }
  // Cubic filtering rings past edges: a colour above its alpha is not
  // premultiplied, and shows as bright specks once the alpha is divided out.
  for (size_t i = 0; i < out.pixels.size(); i += 4) {
    for (int c = 0; c < 3; ++c) {
      out.pixels[i + c] = std::min(out.pixels[i + c], out.pixels[i + 3]);
    }
  }
  return out;
}

Image Cover(const Image& image, int width, int height) {
  const double scale = std::max(double(width) / image.width, double(height) / image.height);
  const int w = std::max(width, int(std::ceil(image.width * scale)));
  const int h = std::max(height, int(std::ceil(image.height * scale)));
  const Image scaled = Resize(image, w, h);
  return Crop(scaled, (w - width) / 2, (h - height) / 2, width, height);
}

std::optional<StripArt> StripArtFromSplash(const Image& splash, std::string* error) {
  auto fail = [&] {
    if (error) {
      *error = "splash_360.png is not the orb above the XBOX 360 wordmark";
    }
    return std::nullopt;
  };
  auto row_inked = [&](int y) {
    for (int x = 0; x < splash.width; ++x) {
      if (splash.at(x, y)[3] > 20) {
        return true;
      }
    }
    return false;
  };
  // Two blocks of rows: the orb, a gap, the wordmark.
  std::vector<std::pair<int, int>> blocks;
  for (int y = 0; y < splash.height; ++y) {
    if (!row_inked(y)) {
      continue;
    }
    if (blocks.empty() || y > blocks.back().second + 1) {
      blocks.push_back({y, y});
    } else {
      blocks.back().second = y;
    }
  }
  if (blocks.size() != 2) {
    return fail();
  }
  // The columns inked between rows `top` and `bottom`.
  auto columns = [&](int top, int bottom) {
    int first = splash.width, last = -1;
    for (int x = 0; x < splash.width; ++x) {
      for (int y = top; y <= bottom; ++y) {
        if (splash.at(x, y)[3] > 20) {
          first = std::min(first, x);
          last = std::max(last, x);
          break;
        }
      }
    }
    return std::pair{first, last};
  };
  StripArt art;
  // The orb: the disc around its block's centre; the trade mark sign at its
  // upper right falls outside.
  const auto [orb_left, orb_right] = columns(blocks[0].first, blocks[0].second);
  const int orb_size = std::min(orb_right - orb_left, blocks[0].second - blocks[0].first) + 1;
  if (orb_size < 32) {
    return fail();
  }
  const double cx = (orb_left + orb_right + 1) / 2.0;
  const double cy = (blocks[0].first + blocks[0].second + 1) / 2.0;
  const double radius = orb_size / 2.0;
  // Made as the strip shows it, turned a quarter left with the wordmark: the
  // white orb, a sphere lit from the upper left, white to light grey, with the
  // splash's X over it in the tiles' green, darker on the left.
  art.orb = Blank(orb_size, orb_size);
  for (int y = 0; y < orb_size; ++y) {
    for (int x = 0; x < orb_size; ++x) {
      // The splash pixel that turns to (x, y).
      const double sx = cx - radius + (orb_size - 1 - y) + 0.5, sy = cy - radius + x + 0.5;
      const int ix = int(sx), iy = int(sy);
      if (ix < 0 || iy < 0 || ix >= splash.width || iy >= splash.height) {
        continue;
      }
      const double dx = x + 0.5 - radius, dy = y + 0.5 - radius;
      const double cover = std::clamp(radius - std::hypot(dx, dy) + 0.5, 0.0, 1.0);
      const double t = std::clamp(0.5 + 0.5 * (dx + dy) / (radius * std::sqrt(2.0)), 0.0, 1.0);
      const double grey = 255.0 - 65.0 * std::pow(t, 1.5);
      const uint8_t* s = splash.at(ix, iy);
      // Saturation picks the X, highlights included; the sphere is grey.
      const int high = std::max({s[0], s[1], s[2]}), low = std::min({s[0], s[1], s[2]});
      const double green = high && s[1] == high
                               ? std::clamp((double(high - low) / high - 0.08) / 0.2, 0.0, 1.0)
                               : 0.0;
      const double across = double(x) / orb_size;
      const double xr = 27 + (92 - 27) * across, xg = 154 + (182 - 154) * across,
                   xb = 2 + (33 - 2) * across;
      uint8_t* p = art.orb.at(x, y);
      p[0] = uint8_t((grey + (xb - grey) * green) * cover + 0.5);
      p[1] = uint8_t((grey + (xg - grey) * green) * cover + 0.5);
      p[2] = uint8_t((grey + (xr - grey) * green) * cover + 0.5);
      p[3] = uint8_t(255 * cover + 0.5);
    }
  }
  // The wordmark: its block's columns inked in its upper 60%; the trade mark
  // sign after it sits at the baseline.
  const auto rows = blocks[1];
  const auto [word_left, word_right] =
      columns(rows.first, rows.first + (rows.second - rows.first) * 3 / 5);
  if (word_left >= word_right) {
    return fail();
  }
  art.wordmark =
      Crop(splash, word_left, rows.first, word_right - word_left + 1, rows.second - rows.first + 1);
  // The trade mark sign tucks under the 0's last columns: clear every piece
  // of ink far smaller than a letter.
  {
    Image& w = art.wordmark;
    std::vector<int> piece(size_t(w.width) * w.height, -1);
    std::vector<std::vector<int>> pieces;
    for (int start = 0; start < int(piece.size()); ++start) {
      if (piece[start] >= 0 || w.pixels[size_t(start) * 4 + 3] <= 20) {
        continue;
      }
      std::vector<int> members, stack = {start};
      piece[start] = int(pieces.size());
      while (!stack.empty()) {
        const int at = stack.back();
        stack.pop_back();
        members.push_back(at);
        const int x = at % w.width, y = at / w.width;
        for (const auto [nx, ny] : {std::pair{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}}) {
          const int next = ny * w.width + nx;
          if (nx >= 0 && ny >= 0 && nx < w.width && ny < w.height && piece[next] < 0 &&
              w.pixels[size_t(next) * 4 + 3] > 20) {
            piece[next] = int(pieces.size());
            stack.push_back(next);
          }
        }
      }
      pieces.push_back(std::move(members));
    }
    size_t largest = 0;
    for (const auto& p : pieces) {
      largest = std::max(largest, p.size());
    }
    for (const auto& p : pieces) {
      if (p.size() * 8 < largest) {
        for (int at : p) {
          // The piece and its soft edge.
          const int x = at % w.width, y = at / w.width;
          for (int ny = std::max(0, y - 1); ny <= std::min(w.height - 1, y + 1); ++ny) {
            for (int nx = std::max(0, x - 1); nx <= std::min(w.width - 1, x + 1); ++nx) {
              if (piece[size_t(ny) * w.width + nx] < 0) {
                std::memset(w.at(nx, ny), 0, 4);
              }
            }
          }
          std::memset(w.at(x, y), 0, 4);
        }
      }
    }
  }
  // In the tiles' colours, the splash's own only as a mask: XBOX dark green,
  // 360 grey.
  for (size_t i = 0; i < art.wordmark.pixels.size(); i += 4) {
    uint8_t* p = &art.wordmark.pixels[i];
    const bool is_green = p[1] > p[2] + 24;
    const uint8_t r = is_green ? 16 : 104, g = is_green ? 120 : 104, b = is_green ? 16 : 104;
    const int a = p[3];
    p[0] = uint8_t((b * a + 127) / 255);
    p[1] = uint8_t((g * a + 127) / 255);
    p[2] = uint8_t((r * a + 127) / 255);
  }
  return art;
}

Image ComposeTile(const Image& cover, double crop_top, const StripArt* strip_art, int size) {
  const int master = int(kMaster);
  Image tile = Blank(master, master, 0xFFFFFFFF);
  DrawStrip(tile);
  // The cover, without its banner, over the rest.
  const int cut = std::clamp(int(std::lround(cover.height * crop_top)), 0, cover.height - 1);
  const Image art = Cover(Crop(cover, 0, cut, cover.width, cover.height - cut),
                          master - int(kStripWidth), master);
  Draw(tile, art, int(kStripWidth), 0);
  if (strip_art) {
    const double centre = kStripWidth / 2.0;
    const Image& word = strip_art->wordmark;
    const int across = int(std::lround(kWordmarkLength * word.height / word.width));
    const Image upright = Resize(RotateLeft(word), across, int(kWordmarkLength));
    Draw(tile, upright, int(std::lround(centre - across / 2.0)), int(kWordmarkTop));
    const int orb = int(kOrbDiameter);
    Draw(tile, Resize(strip_art->orb, orb, orb), int(std::lround(centre - orb / 2.0)),
         int(std::lround(kOrbCentreY - orb / 2.0)));
  }
  return Resize(tile, size, size);
}

}  // namespace rexglue::cli

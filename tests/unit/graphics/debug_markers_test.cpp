/**
 * @file        debug_markers_test.cpp
 * @brief       PIX marker encoding and balanced marker regions (RG-GDK-028)
 *
 * @copyright   Copyright (c) 2026 Tom Clay
 * @license     BSD 3-Clause License
 */

#include <cstdint>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include <rex/graphics/debug_markers.h>

using rex::graphics::DebugMarkerRegions;
namespace pix = rex::graphics::pix;

TEST_CASE("A PIX begin event encodes info, color, context and label", "[debug_markers]") {
  uint64_t words[pix::kMaxEventWords];
  const void* context = reinterpret_cast<const void*>(uintptr_t(0x123456789A0));
  uint32_t size =
      pix::EncodeEvent(words, pix::EventType::kBeginEvent, pix::Color(1, 2, 3), context, "Resolve");

  CHECK(size == 4 * 8);

  CHECK(words[0] == 0xF3084);
  CHECK(words[1] == 0xFF010203);
  CHECK(words[2] == 0x123456789A0);
  CHECK(words[3] == 0x0065766C6F736552);
}

TEST_CASE("A PIX label of whole words gets a zero terminator word", "[debug_markers]") {
  uint64_t words[pix::kMaxEventWords];
  uint32_t size = pix::EncodeEvent(words, pix::EventType::kSetMarker, 0, nullptr, "Frame 12");
  CHECK(size == 5 * 8);
  CHECK(words[0] == (0xF3000 | (2 << 7) | 5));
  CHECK(words[3] == 0x323120656D617246);
  CHECK(words[4] == 0);
}

TEST_CASE("A long PIX label is cut to the maximum length", "[debug_markers]") {
  uint64_t words[pix::kMaxEventWords];
  std::string label(1000, 'x');
  uint32_t size = pix::EncodeEvent(words, pix::EventType::kBeginEvent, 0, nullptr, label);
  CHECK(size == pix::kMaxEventWords * 8);

  CHECK(words[pix::kMaxEventWords - 1] == 0x0078787878787878);
}

TEST_CASE("Nested debug marker regions end in reverse order", "[debug_markers]") {
  DebugMarkerRegions regions;
  uint64_t outer = regions.Begin();
  uint64_t inner = regions.Begin();
  CHECK(regions.depth() == 2);
  CHECK(regions.End(inner));
  CHECK(regions.End(outer));
  CHECK(regions.depth() == 0);
  CHECK(regions.CloseAll() == 0);
}

TEST_CASE("Closing a command list ends its open regions once", "[debug_markers]") {
  DebugMarkerRegions regions;
  uint64_t swap = regions.Begin();
  uint64_t draw = regions.Begin();

  CHECK(regions.CloseAll() == 2);
  CHECK(regions.depth() == 0);

  CHECK_FALSE(regions.End(draw));
  CHECK_FALSE(regions.End(swap));
  CHECK(regions.CloseAll() == 0);
}

TEST_CASE("A stale region never ends a region of the next command list", "[debug_markers]") {
  DebugMarkerRegions regions;
  uint64_t swap = regions.Begin();
  CHECK(regions.CloseAll() == 1);

  uint64_t present = regions.Begin();
  CHECK_FALSE(regions.End(swap));
  CHECK(regions.depth() == 1);
  CHECK(regions.End(present));
  CHECK(regions.depth() == 0);
}

TEST_CASE("Unbalanced ends are ignored", "[debug_markers]") {
  DebugMarkerRegions regions;
  uint64_t region = regions.Begin();
  CHECK(regions.End(region));
  CHECK_FALSE(regions.End(region));
  CHECK(regions.depth() == 0);
}

// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <rex/string/utf8.h>

TEST_CASE("ASCII case conversion changes only ASCII letters", "[core][utf8]") {
  CHECK(rex::string::utf8_upper_ascii("Hello, World 123") == "HELLO, WORLD 123");
  CHECK(rex::string::utf8_upper_ascii("con") == "CON");
  CHECK(rex::string::utf8_upper_ascii("\xC3\xA6"
                                      "ble") ==
        "\xC3\xA6"
        "BLE");
  CHECK(rex::string::utf8_lower_ascii("Hello, World 123") == "hello, world 123");
  CHECK(rex::string::utf8_lower_ascii("\xC3\x86"
                                      "BLE") ==
        "\xC3\x86"
        "ble");
}

TEST_CASE("UTF-8 validity rejects malformed sequences", "[core][utf8]") {
  CHECK(rex::string::utf8_is_valid("default.xex"));
  CHECK(rex::string::utf8_is_valid("\xC3\xA6"));
  CHECK(rex::string::utf8_is_valid(""));
  CHECK_FALSE(rex::string::utf8_is_valid("\xC3("));
  CHECK_FALSE(rex::string::utf8_is_valid("\xFF"));
  CHECK_FALSE(rex::string::utf8_is_valid("a\xE2\x82"));
}

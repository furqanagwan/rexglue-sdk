// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <catch2/catch_test_macros.hpp>

#include <array>

#include <rex/cvar.h>
#include <rex/kernel/xboxkrnl/xconfig.h>
#include <rex/system/flags.h>
#include <rex/system/user_language.h>
#include <rex/types.h>

namespace rex::kernel::xam {
u32 XGetLanguage_entry();
}
namespace rex::kernel::xboxkrnl {
uint32_t xeExGetXConfigSetting(uint16_t category, uint16_t setting, void* buffer,
                               uint16_t buffer_size, uint16_t* required_size);
}

using rex::system::LanguageFromLocale;
using rex::system::XLanguage;

TEST_CASE("PC locales map to supported guest languages", "[language]") {
  CHECK(LanguageFromLocale("en-GB") == XLanguage::kEnglish);
  CHECK(LanguageFromLocale("JA_jp") == XLanguage::kJapanese);
  CHECK(LanguageFromLocale("de-DE") == XLanguage::kGerman);
  CHECK(LanguageFromLocale("fr-CA") == XLanguage::kFrench);
  CHECK(LanguageFromLocale("es-MX") == XLanguage::kSpanish);
  CHECK(LanguageFromLocale("it-IT") == XLanguage::kItalian);
  CHECK(LanguageFromLocale("ko-KR") == XLanguage::kKorean);
  CHECK(LanguageFromLocale("pt-BR") == XLanguage::kPortuguese);
  CHECK(LanguageFromLocale("pl-PL") == XLanguage::kPolish);
  CHECK(LanguageFromLocale("ru-RU") == XLanguage::kRussian);
  CHECK(LanguageFromLocale("zh-TW") == XLanguage::kTChinese);
  CHECK(LanguageFromLocale("zh-HK") == XLanguage::kTChinese);
  CHECK(LanguageFromLocale("zh-MO") == XLanguage::kTChinese);
  CHECK(LanguageFromLocale("zh-Hans-HK") == XLanguage::kSChinese);
  CHECK(LanguageFromLocale("zh-Hant-CN") == XLanguage::kTChinese);
  CHECK(LanguageFromLocale("zh-CN") == XLanguage::kSChinese);
  CHECK(LanguageFromLocale("zh-SG") == XLanguage::kSChinese);
  CHECK(LanguageFromLocale("ar-SA") == XLanguage::kEnglish);
  CHECK(LanguageFromLocale("") == XLanguage::kEnglish);
}

TEST_CASE("XAM and XConfig agree on the selected game language", "[language][kernel]") {
  const auto original = REXCVAR_GET(user_language);
  struct Restore {
    uint32_t value;
    ~Restore() { REXCVAR_SET(user_language, value); }
  } restore{original};
  for (uint32_t id = 0; id <= 12; ++id) {
    REXCVAR_SET(user_language, id);
    const auto resolved = uint32_t(rex::system::GetUserLanguage());
    REQUIRE(resolved >= 1);
    REQUIRE(resolved <= 12);
    if (id)
      CHECK(resolved == id);
    CHECK(uint32_t(rex::kernel::xam::XGetLanguage_entry()) == resolved);
    std::array<uint8_t, 4> bytes = {};
    uint16_t required = 0;
    REQUIRE(rex::kernel::xboxkrnl::xeExGetXConfigSetting(3, 9, bytes.data(), 4, &required) == 0);
    CHECK(required == 4);
    CHECK(bytes == std::array<uint8_t, 4>{0, 0, 0, uint8_t(resolved)});
  }
  REXCVAR_SET(user_language, 99);  // Defensive against callers bypassing validation.
  CHECK(rex::system::GetUserLanguage() == XLanguage::kEnglish);
}

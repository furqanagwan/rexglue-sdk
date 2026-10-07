// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <rex/system/user_language.h>

#include <algorithm>
#include <cctype>
#include <string>

#include <rex/system/flags.h>
#include <rex/platform.h>

#if REX_PLATFORM_WIN32
#include <windows.h>
#endif

namespace rex::system {

XLanguage LanguageFromLocale(std::string_view locale) {
  std::string normalized(locale);
  std::transform(normalized.begin(), normalized.end(), normalized.begin(),
                 [](unsigned char c) { return c == '_' ? '-' : char(std::tolower(c)); });
  const auto primary = normalized.substr(0, normalized.find('-'));
  if (primary == "zh") {
    bool traditional = false;
    size_t pos = normalized.find('-');
    while (pos != std::string::npos) {
      const size_t next = normalized.find('-', pos + 1);
      const auto token = normalized.substr(pos + 1, next - pos - 1);
      if (token == "hant")
        return XLanguage::kTChinese;
      if (token == "hans")
        return XLanguage::kSChinese;
      traditional |= token == "tw" || token == "hk" || token == "mo";
      pos = next;
    }
    return traditional ? XLanguage::kTChinese : XLanguage::kSChinese;
  }
  if (primary == "ja")
    return XLanguage::kJapanese;
  if (primary == "de")
    return XLanguage::kGerman;
  if (primary == "fr")
    return XLanguage::kFrench;
  if (primary == "es")
    return XLanguage::kSpanish;
  if (primary == "it")
    return XLanguage::kItalian;
  if (primary == "ko")
    return XLanguage::kKorean;
  if (primary == "pt")
    return XLanguage::kPortuguese;
  if (primary == "pl")
    return XLanguage::kPolish;
  if (primary == "ru")
    return XLanguage::kRussian;
  return XLanguage::kEnglish;
}

XLanguage GetUserLanguage() {
  const auto language = REXCVAR_GET(user_language);
  if (language > 0 && language < uint32_t(XLanguage::kMaxLanguages)) {
    return static_cast<XLanguage>(language);
  }
  if (language == 0) {
#if REX_PLATFORM_WIN32
    wchar_t locale[LOCALE_NAME_MAX_LENGTH] = {};
    if (GetUserDefaultLocaleName(locale, LOCALE_NAME_MAX_LENGTH)) {
      // Windows locale names contain ASCII language, script and region subtags.
      std::string name;
      for (const wchar_t c : locale) {
        if (!c)
          break;
        name.push_back(char(c));
      }
      return LanguageFromLocale(name);
    }
#endif
  }
  return XLanguage::kEnglish;
}

}  // namespace rex::system

// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <string_view>

#include <rex/system/xcontent.h>

namespace rex::system {

// Map a Windows/BCP-47 locale to a language the guest understands. Unsupported
// locales fall back to English; Chinese script takes priority over region.
XLanguage LanguageFromLocale(std::string_view locale);

// user_language=0 follows Windows; 1..12 selects an explicit guest language.
// All guest APIs and title metadata must use the same resolved value.
XLanguage GetUserLanguage();

}  // namespace rex::system

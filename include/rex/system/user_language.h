// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#pragma once

#include <string_view>

#include <rex/system/xcontent.h>

namespace rex::system {

XLanguage LanguageFromLocale(std::string_view locale);

XLanguage GetUserLanguage();

}

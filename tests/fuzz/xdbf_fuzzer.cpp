// Copyright (c) 2026 ReXGlue contributors. BSD 3-Clause License; see LICENSE.
#include <cstdint>

#include <rex/system/util/xdbf_utils.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using rex::system::XLanguage;
  rex::system::util::XdbfGameData game(data, size);
  if (!game.is_valid()) {
    return 0;
  }
  game.title();
  game.icon();
  game.default_language();
  game.GetAchievements();
  for (auto language : {XLanguage::kEnglish, XLanguage::kJapanese, XLanguage::kGerman}) {
    game.title(language);
    game.GetExistingLanguage(language);
    game.GetStringTableEntry(language, 1);
  }
  return 0;
}

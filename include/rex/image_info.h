/**
 * @file        image_info.h
 * @brief       Image layout descriptor for recompiled binaries
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <rex/types.h>

struct PPCFuncMapping;

namespace rex::system {
class KernelState;
}

namespace rex {

/**
 * Callback for registering recompiled modules with KernelState (multi-binary projects).
 */
using RegisterModulesFunc = void (*)(system::KernelState*);

struct PPCCodegenFlags {
  bool skip_lr = false;
  bool ctr_as_local = false;
  bool xer_as_local = false;
  bool reserved_as_local = false;
  bool skip_msr = false;
  bool cr_as_local = false;
  bool non_argument_as_local = false;
  bool non_volatile_as_local = false;
};

/// A code patch compiled with both instruction versions. `active` is the
/// flag the recompiled code reads; setting it switches the patch live.
struct PPCSwitchablePatch {
  const char* name;
  uint8_t* active;
  const char* category;  ///< "patch" or "mod"
};

/// A cheat code the title's developers built in, for the guide's Cheats page.
struct PPCTitleCheat {
  const char* name;
  const char* code;
  const char* description;  ///< What it unlocks
  const char* where;        ///< Where the game takes the code
};

/// An add-on the title had in the marketplace, for the guide's Manage Game
/// page; its name, description and art come from the built-in catalogue.
struct PPCTitleDlc {
  const char* id;             ///< marketplace media ID
  const char* package_name;   ///< display name in its package, when not the catalogue's
  u32 requires_title_update;  ///< the title update version it needs; 0 for none
};

/// A title update the title had ([[title_update]] in its config), for the
/// guide's Title Updates page: optional, downloaded and installed by the player.
struct PPCTitleUpdate {
  u32 version;             ///< the update's number (Xbox Unity's Version)
  const char* media_id;    ///< the disc's media ID it applies to, 8 hex digits
  u32 base_version;        ///< the executable version it updates (header 0x35C)
  const char* content_id;  ///< package content ID, 40 hex digits (Xbox Unity's hash)
  u32 size_kb;             ///< package size in KB, 0 when unknown
  const char* date;        ///< release or upload date, empty when unknown
  const char* changelog;   ///< what it changes, empty when unknown
};

/// PPC image layout passed from the generated config header into ReXApp.
struct PPCImageInfo {
  u32 code_base;
  u32 code_size;
  u32 image_base;
  u32 image_size;
  /// Where the function dispatch table goes; 0 for image_base + image_size.
  /// Codegen moves it when a guest DLL's image would sit there.
  u32 function_table_base = 0;
  const PPCFuncMapping* func_mappings;
  bool rexcrt_heap = false;  ///< Set by codegen when [rexcrt] has heap functions
  RegisterModulesFunc register_modules = nullptr;  ///< Set by codegen for multi-binary projects
  PPCCodegenFlags codegen_flags{};                 ///< Set by codegen from the config flags
  /// Guest code patches compiled in, comma-separated; empty when none.
  const char* code_patches = "";
  /// Switchable patches, ended by a null name; null when codegen predates them.
  const PPCSwitchablePatch* switchable_patches = nullptr;
  /// The title's own cheat codes, ended by a null name; null when none.
  const PPCTitleCheat* title_cheats = nullptr;
  /// The title's add-ons, ended by a null id; null when none.
  const PPCTitleDlc* title_dlc = nullptr;
  /// The title update this executable was built for; 0 for the original. A
  /// title update build applies that update's XEX patches (update:) at load.
  u32 title_update = 0;
  /// The title updates the title had, ended by a zero version; null when none.
  const PPCTitleUpdate* title_updates = nullptr;
  /// Raw source XEX identity for first-run source validation. Empty for older
  /// generated code. A TU build fingerprints its original, unpatched input XEX.
  u32 source_title_id = 0;
  const char* source_executable_checksum = "";
  const char* source_executable_path = "default.xex";
};

}  // namespace rex

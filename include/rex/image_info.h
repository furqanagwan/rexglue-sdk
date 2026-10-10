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

struct PPCSwitchablePatch {
  const char* name;
  uint8_t* active;
  const char* category;
};

struct PPCTitleCheat {
  const char* name;
  const char* code;
  const char* description;
  const char* where;
};

struct PPCTitleDlc {
  const char* id;
  const char* package_name;
  u32 requires_title_update;
};

struct PPCTitleUpdate {
  u32 version;
  const char* media_id;
  u32 base_version;
  const char* content_id;
  u32 size_kb;
  const char* date;
  const char* changelog;
};

struct PPCImageInfo {
  u32 code_base;
  u32 code_size;
  u32 image_base;
  u32 image_size;

  u32 function_table_base = 0;
  const PPCFuncMapping* func_mappings;
  bool rexcrt_heap = false;
  RegisterModulesFunc register_modules = nullptr;
  PPCCodegenFlags codegen_flags{};

  const char* code_patches = "";

  const PPCSwitchablePatch* switchable_patches = nullptr;

  const PPCTitleCheat* title_cheats = nullptr;

  const PPCTitleDlc* title_dlc = nullptr;

  u32 title_update = 0;

  const PPCTitleUpdate* title_updates = nullptr;

  u32 source_title_id = 0;
  const char* source_executable_checksum = "";
  const char* source_executable_path = "default.xex";

  const char* source_title_name = "";
};

}

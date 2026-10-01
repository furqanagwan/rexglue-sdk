/**
 * @file        rexcodegen/internal/config.h
 * @brief       Recompiler configuration types
 *
 * @copyright   Copyright (c) 2026 Tom Clay <tomc@tctechstuff.com>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <toml++/toml.hpp>

#include <rex/codegen/function_graph.h>  // For JumpTable

namespace rex::codegen {

struct MidAsmHook {
  std::string name;
  std::vector<std::string> registers;

  bool ret = false;
  bool returnOnTrue = false;
  bool returnOnFalse = false;

  uint32_t jumpAddress = 0;
  uint32_t jumpAddressOnTrue = 0;
  uint32_t jumpAddressOnFalse = 0;

  bool afterInstruction = false;
};

// Unified function/chunk configuration
// A "chunk" is simply a function entry with a non-zero parent field
struct FunctionConfig {
  uint32_t size = 0;    // Explicit size in bytes (mutually exclusive with end)
  uint32_t end = 0;     // End address, exclusive (mutually exclusive with size)
  std::string name;     // Custom symbol name (empty = auto-generate sub_XXXXXXXX)
  uint32_t parent = 0;  // Parent function address (0 = standalone, non-zero = chunk)

  // Keep non-volatiles in ctx instead of localizing them. Marks an MSVC SEH
  // funclet, which reads the registers its owner left live and would see a zero
  // from a local. Callers sync their localized copies across the call site.
  bool shareRegisters = false;

  // Get effective size (prefers size over end)
  uint32_t getSize(uint32_t address) const {
    return size ? size : (end > address ? end - address : 0);
  }
  // Returns true if this is a discontinuous chunk belonging to a parent function
  bool isChunk() const { return parent != 0; }
};

// One big-endian write of a code patch.
struct PatchWrite {
  uint32_t address = 0;
  std::vector<uint8_t> bytes;  ///< Written in order starting at `address`
};

// A register a switchable patch sets just before the instruction at
// `address` runs, as a trainer's detour does: [[patch.set]] with address,
// register ("r0".."r31"), value and, optionally, lr (only when the link
// register holds that return address, i.e. that call was the last made).
struct PatchRegisterSet {
  uint32_t address = 0;
  uint32_t reg = 0;
  uint64_t value = 0;
  std::optional<uint32_t> lr;
};

// A named guest code patch applied to the image before analysis (ADR-009
// section 7). Written in the same shape as a Canary game-patches entry, so a
// community patch copies over: [[patch]] with name, enabled and
// [[patch.be8]] / be16 / be32 / be64 tables of address and value.
struct CodePatch {
  std::string name;
  bool enabled = true;
  /// Compiled with both instruction versions behind a runtime flag, so the
  /// player can switch it while the title runs; `enabled` is the default.
  bool switchable = false;
  /// How the guide lists a switchable patch: "patch" (fixes, frame rate) or
  /// "mod" (changes to play, such as a trainer's infinite ammo). "cheat",
  /// the earlier name for "mod", is read as "mod".
  std::string category = "patch";
  std::vector<PatchWrite> writes;
  std::vector<PatchRegisterSet> sets;  ///< Switchable patches only
  std::string source;                  ///< Config file that last defined the writes
  std::string error;                   ///< Why the entry is unusable; applying it fails
};

// A cheat the title's developers built in: a code the game's own menu takes.
// Nothing is patched; the guide's Cheats page lists them so a player need not
// look them up. [[cheat]] with name, code, description and where.
struct TitleCheat {
  std::string name;
  std::string code;
  std::string description;  ///< What it unlocks
  std::string where;        ///< Where the game takes the code
};

// An add-on the title had in the Xbox 360 marketplace, for the guide's Manage
// Game page. [[dlc]] with the marketplace media ID (id), and optionally the
// title update the add-on needs (requires_title_update, its version) and the
// display name in its package when the catalogue's title differs (package_name).
// `rexglue dlc-find <title ID>` prints a title's entries.
struct TitleDlc {
  std::string id;
  std::string package_name;
  uint32_t requires_title_update = 0;  ///< 0: none
};

// A title update the title had, for the guide's Manage Game page, where the
// player can download and turn it on (an update is always optional).
// [[title_update]] with version, media_id, base_version and content_id (Xbox
// Unity's "hash": the package's STFS content ID), optionally size_kb, date and
// changelog. The update runs only in a build that has its executable (a
// manifest [[title_update]]).
struct TitleUpdateInfo {
  uint32_t version = 0;
  std::string media_id;
  uint32_t base_version = 0;
  std::string content_id;
  uint32_t size_kb = 0;
  std::string date;
  std::string changelog;
};

// Section info for analysis output
struct SectionInfo {
  std::string name;
  uint64_t address = 0;
  uint64_t size = 0;
  std::string flags;  // "rx", "rw", "r" etc.
};

// Function entry for analysis output
struct FunctionEntry {
  uint64_t address = 0;
  uint64_t size = 0;
  std::string name;  // optional, defaults to "sub_XXXXXXXX"
};

struct RecompilerConfig {
  // === Required user-provided fields ===
  std::string projectName = "rex";  ///< Project name for output files
  std::string filePath;             ///< Path to XEX/ELF file
  std::string outDirectoryPath;     ///< Output directory for generated code
  std::string templateDir;          ///< Optional custom template directory for overrides

  /// Every TOML that fed this config, in load order. LoadFromTable() gets a
  /// parsed table, so a manifest-embedded entry omits the manifest itself.
  std::vector<std::string> loadedFiles;

  // === Code generation options (optional) ===
  bool skipLr = false;
  bool ctrAsLocalVariable = false;
  bool xerAsLocalVariable = false;
  bool reservedRegisterAsLocalVariable = false;
  bool skipMsr = false;
  bool crRegistersAsLocalVariables = false;
  bool nonArgumentRegistersAsLocalVariables = false;
  bool nonVolatileRegistersAsLocalVariables = false;
  bool generateExceptionHandlers = false;  ///< Generate SEH exception handler wrappers

  // === Analysis tuning (optional) ===
  uint32_t maxJumpExtension = 65536;  ///< Max bytes to extend function for jump table targets
  uint32_t dataRegionThreshold = 16;  ///< Consecutive invalid instructions to mark as data region
  uint32_t largeFunctionThreshold = 1048576;  ///< 1MB - warn if function exceeds this size

  // Optional override for DLL module flag. If unset, the orchestrator infers
  // from the module's position in the manifest (entrypoint = false, modules = true).
  std::optional<bool> isDll;

  /// The title update this executable is built for (a manifest
  /// [[title_update]]); 0 for the original. Compiled into PPCImageInfo.
  uint32_t titleUpdateVersion = 0;

  // === Manual overrides ===
  std::unordered_map<uint32_t, FunctionConfig> functions;  ///< Function/chunk configuration
  std::unordered_map<uint32_t, JumpTable> switchTables;
  std::unordered_map<uint32_t, MidAsmHook> midAsmHooks;
  /// Guest code patches in definition order, keyed by name: a later file with
  /// the same name replaces the writes it lists and the enabled flag it sets.
  std::vector<CodePatch> patches;
  /// The title's own cheat codes, in definition order, keyed by name.
  std::vector<TitleCheat> cheats;
  /// The title's add-ons, in definition order, keyed by id.
  std::vector<TitleDlc> dlc;
  /// The title's updates, in definition order, keyed by version.
  std::vector<TitleUpdateInfo> titleUpdates;
  uint32_t longJmpAddress = 0;
  uint32_t setJmpAddress = 0;
  // Analysis-only guard for the recognized CRT's optional setjmp hook.
  uint32_t setJmpHookAddress = 0;

  // === rexcrt: CRT function address overrides ===
  // Maps function name -> guest address (e.g. "CreateFileA" -> 0x8248B780)
  // Parsed from [rexcrt] TOML table. Codegen generates rexcrt_<Name> entries.
  std::unordered_map<std::string, uint32_t> rexcrtFunctions;

  // === User hints (merged with analysis results in AnalysisState) ===
  std::unordered_map<uint32_t, uint32_t> invalidInstructionHints;  ///< addr -> size
  std::unordered_set<uint32_t>
      knownIndirectCallHints;  ///< bctr addresses that are vtable/computed calls
  std::vector<uint32_t> exceptionHandlerFuncHints;  ///< Additional exception handler addresses

  /**
   * Load configuration from a TOML file.
   *
   * Supports an optional `includes` array for layered config. Paths in
   * `includes` resolve relative to the including file's directory.  Merge
   * semantics: scalars last-wins, keyed tables additive (same key = last
   * wins), arrays-of-tables deduplicated by primary key, sets additive.
   *
   * @param configFilePath Path to the TOML config file
   * @return true on success, false on error (parse failure, circular
   *         include, depth exceeded)
   */
  bool Load(const std::string_view& configFilePath);

  /**
   * Load configuration from an in-memory TOML table (e.g. an inline binary
   * entry inside a manifest). Includes referenced from the table resolve
   * relative to `base_dir`. Same merge semantics as Load().
   */
  bool LoadFromTable(const toml::table& tbl, const std::filesystem::path& base_dir);

  /// Validation result containing warnings and errors.
  struct ValidationResult {
    bool valid = true;                  ///< true if no errors (warnings OK)
    std::vector<std::string> warnings;  ///< Non-fatal issues
    std::vector<std::string> errors;    ///< Fatal issues that block codegen

    explicit operator bool() const { return valid; }
  };

  /**
   * Validate the loaded configuration.
   * Checks address alignment, required fields, and sanity constraints.
   * @return ValidationResult with warnings and errors
   */
  ValidationResult Validate() const;
};

}  // namespace rex::codegen

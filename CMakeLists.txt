# ReXGlue SDK - Xbox 360 Recompilation Toolkit
cmake_minimum_required(VERSION 3.25...4.4)

# CMP0155 (CMake 3.28) scans every C++ source for module imports. Nothing here
# uses C++20 modules, and under Ninja Multi-Config the scan makes imgui emit one
# modmap path from two configurations, which ninja rejects as a duplicate
# output. Set before any target is defined, since a target takes its scanning
# behaviour when it is created.
if(POLICY CMP0155)
    cmake_policy(SET CMP0155 OLD)
endif()

set(REXGLUE_LANGUAGES C CXX)

project(ReXGlue
    VERSION 0.10.0
    LANGUAGES ${REXGLUE_LANGUAGES}
    DESCRIPTION "Xbox 360 Recompilation SDK"
)
# Floor only: bump MAJOR.MINOR for API changes. Patch is derived from git tags
# in cmake/rex_version.cmake. See docs/RELEASING.md.

#==========================================================
# Build Options
#==========================================================
option(REXGLUE_BUILD_TESTS       "Build PPC instruction and unit tests" OFF)
option(REXGLUE_ENABLE_SANITIZERS "Enable UndefinedBehaviorSanitizer" OFF)
option(REXGLUE_ENABLE_FIDELITYFX "Enable optional AMD FidelityFX integration (experimental)" OFF)
option(REXGLUE_ENABLE_TRACY                "Enable Tracy profiler integration" ON)
option(REXGLUE_ENABLE_PERF_COUNTERS        "Enable lightweight perf counter registry and overlay" ON)
# Propagate profiling defines globally (compiled out in Release)
if(REXGLUE_ENABLE_TRACY)
    add_compile_definitions($<$<NOT:$<CONFIG:Release>>:REXGLUE_ENABLE_PROFILING>)
endif()
if(REXGLUE_ENABLE_PERF_COUNTERS)
    add_compile_definitions(REXGLUE_ENABLE_PERF_COUNTERS)
endif()

# Graphics backend: Direct3D 12 and nothing else. The target is DirectX 12
# Ultimate on Windows and Xbox, so there is one backend rather than a choice.
if(NOT WIN32)
    message(FATAL_ERROR "ReXGlue targets Windows and Xbox; Direct3D 12 is the only backend")
endif()
set(REXGLUE_USE_D3D12 ON)

# The application carries its own D3D12Core so DirectX 12 Ultimate and DirectSR
# do not depend on what the player's Windows build happens to ship.
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rexglue_agility.cmake)

# Root of the SDK source tree
set(REXGLUE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# SDK install support
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rexglue_helpers.cmake)

# Enforce the LLVM Clang toolchain used by the GDK build
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(FATAL_ERROR "ReXGlue requires LLVM Clang. Please set CMAKE_CXX_COMPILER to clang++")
endif()

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "18.0")
    message(FATAL_ERROR "ReXGlue requires Clang 18 or newer (found ${CMAKE_CXX_COMPILER_VERSION})")
endif()

# Enforce x64 architecture
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "ReXGlue only supports 64‑bit architectures (x86_64 or ARM64)")
endif()

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_RELWITHDEBINFO_POSTFIX rd)

# CMAKE_<CONFIG>_POSTFIX seeds libraries only, so without this every config of an
# executable installs over the last one.
function(rex_config_postfix target)
    set_target_properties(${target} PROPERTIES
        DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
        RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}")
endfunction()

# Global compile options
add_compile_options(
    -fno-strict-aliasing
    -ffp-model=strict
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:RELEASE>:-DNDEBUG>
    -fno-char8_t
)

# The GDK and Project Helix baseline is AMD64 Windows.
set(REX_TARGET_PROCESSOR "${CMAKE_SYSTEM_PROCESSOR}")
if(NOT REX_TARGET_PROCESSOR MATCHES "AMD64|x86_64")
    message(FATAL_ERROR "ReXGlue supports the AMD64 Windows GDK target only")
endif()
set(REX_PLATFORM "win-amd64")
add_compile_definitions(REX_PLATFORM_WINDOWS=1)

# Build config as compile definition (multi-config generators don't know config at configure time)
add_compile_definitions(REXGLUE_BUILD_CONFIG="$<CONFIG>")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rex_pch.cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rex_version.cmake)
# SOURCE_DIR matters here: the default is CMAKE_SOURCE_DIR, which points at the
# *consumer's* top-level source directory whenever the SDK is pulled in with
# add_subdirectory. git describe then runs in the wrong repository and a release
# tag in the consuming project is compared against the SDK's version floor.
rex_resolve_version(REXGLUE_FULL_VERSION
    FLOOR_MAJOR ${PROJECT_VERSION_MAJOR}
    FLOOR_MINOR ${PROJECT_VERSION_MINOR}
    SOURCE_DIR  ${REXGLUE_ROOT})

# Strip the -id trailer (if any) for the numeric-only version.
string(REGEX REPLACE "-.*$" "" REXGLUE_NUMERIC_VERSION "${REXGLUE_FULL_VERSION}")

# Parse up to 4 numeric components for consumers that want integer access.
string(REGEX MATCH "^([0-9]+)\\.([0-9]+)(\\.([0-9]+))?(\\.([0-9]+))?" _ "${REXGLUE_NUMERIC_VERSION}")
set(REXGLUE_DERIVED_MAJOR "${CMAKE_MATCH_1}")
set(REXGLUE_DERIVED_MINOR "${CMAKE_MATCH_2}")
if(CMAKE_MATCH_4)
    set(REXGLUE_DERIVED_PATCH "${CMAKE_MATCH_4}")
else()
    set(REXGLUE_DERIVED_PATCH "0")
endif()
if(CMAKE_MATCH_6)
    set(REXGLUE_DERIVED_TWEAK "${CMAKE_MATCH_6}")
else()
    set(REXGLUE_DERIVED_TWEAK "0")
endif()

set(REXGLUE_FLOOR_VERSION
    "${REXGLUE_DERIVED_MAJOR}.${REXGLUE_DERIVED_MINOR}.${REXGLUE_DERIVED_PATCH}")

rex_version_channel(REXGLUE_VERSION_CHANNEL VERSION "${REXGLUE_FULL_VERSION}")

# Generate version header -- must run after REX_PLATFORM is set
# Timestamp is set at configure time -- intentionally not updated on every rebuild
string(TIMESTAMP REXGLUE_BUILD_TIMESTAMP "%Y%m%d_%H%M")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rex/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/rex/version.h
    @ONLY
)

# Output directories (multi-config appends /<Config>/ automatically)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${REXGLUE_ROOT}/out/${REX_PLATFORM}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${REXGLUE_ROOT}/out/${REX_PLATFORM}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${REXGLUE_ROOT}/out/${REX_PLATFORM}")

# Sanitizer support for debugging memory corruption and undefined behavior
if(REXGLUE_ENABLE_SANITIZERS)
    message(STATUS "Enabling UndefinedBehaviorSanitizer (UBSan only - ASan conflicts with custom memory mapping)")
    # Note: ASan doesn't work well with the custom mmap at 0x100000000, so we only use UBSan
    add_compile_options(-fsanitize=undefined -fno-omit-frame-pointer -g)
    add_link_options(-fsanitize=undefined)
endif()

if(REXGLUE_BUILD_TESTS)
    list(APPEND CMAKE_MODULE_PATH "${REXGLUE_ROOT}/cmake")
    list(APPEND CMAKE_MODULE_PATH "${REXGLUE_ROOT}/thirdparty/catch2/extras")
endif()

# Third-party dependencies (vendored sources only)
add_subdirectory(thirdparty)

# Enable warnings after thirdparty
add_compile_options(
    -Wall
    -Wextra
)

include_directories(${REXGLUE_ROOT}/include)

add_subdirectory(src/core)
add_subdirectory(src/filesystem)
add_subdirectory(src/ui)
add_subdirectory(src/input)
add_subdirectory(src/audio)
add_subdirectory(src/graphics)
add_subdirectory(src/system)
add_subdirectory(src/kernel)
    add_subdirectory(src/codegen)
    add_subdirectory(src/rexglue)

# Add tests subdirectory if tests are enabled
if(REXGLUE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

include(cmake/rexglue_link_audit.cmake)

# Print configuration summary
message(STATUS "===========================================")
message(STATUS "ReXGlue Configuration Summary:")
message(STATUS "  Version: ${REXGLUE_FULL_VERSION} (${REXGLUE_VERSION_CHANNEL})")
message(STATUS "  Platform: ${REX_PLATFORM}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Configurations: ${CMAKE_CONFIGURATION_TYPES}")
message(STATUS "  Output Dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "  C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "  Graphics: Direct3D 12")
message(STATUS "  FidelityFX: ${REXGLUE_ENABLE_FIDELITYFX}")
message(STATUS "  Tracy: ${REXGLUE_ENABLE_TRACY}")
message(STATUS "  Perf Counters: ${REXGLUE_ENABLE_PERF_COUNTERS}")
message(STATUS "===========================================")

# SDK install/export rules (skipped when consumed as a subdirectory)
if(PROJECT_IS_TOP_LEVEL)
    include(cmake/rexglue_devenv.cmake)
    include(cmake/rexglue_install.cmake)
else()
    # When consumed via add_subdirectory(), provide the same interface as find_package().
    # This sets REXGLUE_SHARE_DIR and makes rexglue_configure_target() available.
    set(REXGLUE_SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ui" PARENT_SCOPE)
    set(REXGLUE_SHARE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/ui")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/rexglue_helpers.cmake)
endif()

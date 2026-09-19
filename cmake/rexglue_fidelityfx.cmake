# rexglue_fidelityfx.cmake — Optional AMD FidelityFX integration via FetchContent
#
# Expects REXGLUE_ENABLE_FIDELITYFX to be set before inclusion.
# On success, creates amd_fidelityfx_vk and/or amd_fidelityfx_dx12 targets
# and sets REXGLUE_FIDELITYFX_SOURCE_DIR to the fetched SDK root.

if(NOT REXGLUE_ENABLE_FIDELITYFX)
    return()
endif()

# ── Fetch FidelityFX SDK ─────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    fidelityfx
    GIT_REPOSITORY https://github.com/rexglue/FidelityFX-SDK.git
    GIT_TAG        eee08db1688ac3d1275a70b728f4a8ba22914213
    GIT_SHALLOW    OFF
)
FetchContent_GetProperties(fidelityfx)
if(NOT fidelityfx_POPULATED)
    FetchContent_Populate(fidelityfx)
endif()

set(REXGLUE_FIDELITYFX_SOURCE_DIR "${fidelityfx_SOURCE_DIR}" CACHE INTERNAL
    "Root of the fetched FidelityFX SDK source tree")

# ── Backend ──────────────────────────────────────────────────────────────
# Direct3D 12 is the only graphics backend, so there is nothing to select.
set(FFX_API_BACKEND DX12_X64 CACHE STRING "" FORCE)

# ── Build FidelityFX ─────────────────────────────────────────────────────
set(FFX_API_ENABLE_FRAMEGEN_PROVIDER OFF CACHE BOOL "" FORCE)
if(WIN32)
    set(FFX_API_AUTO_COMPILE_SHADERS ON CACHE BOOL "" FORCE)
else()
    set(FFX_API_AUTO_COMPILE_SHADERS OFF CACHE BOOL "" FORCE)
endif()
add_subdirectory("${fidelityfx_SOURCE_DIR}/ffx-api" "${fidelityfx_BINARY_DIR}/ffx-api" EXCLUDE_FROM_ALL)

# The upstream FidelityFX targets expose source-tree include paths in
# INTERFACE_INCLUDE_DIRECTORIES, which breaks our install export checks.
# We only link against these targets internally, so no public includes are
# needed on the exported interface.
if(TARGET amd_fidelityfx_vk)
    set_target_properties(amd_fidelityfx_vk PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ""
    )
endif()
if(TARGET amd_fidelityfx_dx12)
    set_target_properties(amd_fidelityfx_dx12 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES ""
    )
endif()

# FidelityFX's toolchain.cmake force-sets CMAKE_GENERATOR_PLATFORM (for VS generators).
# With Ninja this variable is invalid and poisons every subsequent try_compile() call.
# Clear it from the cache.
unset(CMAKE_GENERATOR_PLATFORM CACHE)

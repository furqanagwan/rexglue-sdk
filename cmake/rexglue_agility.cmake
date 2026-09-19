# rexglue_agility.cmake — DirectX 12 Agility SDK
#
# Windows ships a D3D12Core that follows the OS, so a machine on an older build
# has older Direct3D whatever the driver supports. The Agility SDK lets the
# application carry its own D3D12Core and get the same runtime everywhere,
# which is what makes DirectX 12 Ultimate and DirectSR something that can be
# relied on rather than probed for.
#
# Two things are needed and neither can live in a DLL:
#   - D3D12SDKVersion and D3D12SDKPath exported from the executable, read by
#     d3d12.dll before the device exists, and
#   - D3D12Core.dll present at that path beside the executable.
#
# rexglue_stage_agility_sdk(<target>) does the second; the first comes from
# agility_exports.cpp, compiled into the host executable by
# rexglue_configure_target.

include_guard(GLOBAL)

if(NOT WIN32)
    return()
endif()

# The NuGet package is a zip, so FetchContent reads it directly. Pinning the
# version pins the runtime every player gets.
set(REXGLUE_AGILITY_VERSION "1.619.6" CACHE STRING
    "Microsoft.Direct3D.D3D12 (Agility SDK) package version")
# D3D12SDKVersion is the middle component of the package version - 1.619.x
# carries 619, which is also D3D12Core.dll's own file version. Deriving it
# rather than storing it separately means the number the executable exports
# cannot disagree with the binary staged beside it.
if(NOT REXGLUE_AGILITY_VERSION MATCHES "^[0-9]+\.([0-9]+)\.")
    message(FATAL_ERROR
        "REXGLUE_AGILITY_VERSION='${REXGLUE_AGILITY_VERSION}' is not a "
        "major.minor.patch Agility SDK version")
endif()
set(REXGLUE_AGILITY_SDK_VERSION "${CMAKE_MATCH_1}")

include(FetchContent)
FetchContent_Declare(
    agility_sdk
    URL "https://api.nuget.org/v3-flatcontainer/microsoft.direct3d.d3d12/${REXGLUE_AGILITY_VERSION}/microsoft.direct3d.d3d12.${REXGLUE_AGILITY_VERSION}.nupkg"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(agility_sdk)

set(REXGLUE_AGILITY_ROOT "${agility_sdk_SOURCE_DIR}" CACHE INTERNAL
    "Root of the fetched Agility SDK package")
set(REXGLUE_AGILITY_INCLUDE_DIR "${agility_sdk_SOURCE_DIR}/build/native/include"
    CACHE INTERNAL "Agility SDK headers")
set(REXGLUE_AGILITY_BIN_DIR "${agility_sdk_SOURCE_DIR}/build/native/bin/x64"
    CACHE INTERNAL "Agility SDK redistributable binaries")

if(NOT EXISTS "${REXGLUE_AGILITY_BIN_DIR}/D3D12Core.dll")
    message(FATAL_ERROR
        "Agility SDK ${REXGLUE_AGILITY_VERSION} did not contain D3D12Core.dll at "
        "${REXGLUE_AGILITY_BIN_DIR}")
endif()

message(STATUS "Agility SDK ${REXGLUE_AGILITY_VERSION} (D3D12SDKVersion ${REXGLUE_AGILITY_SDK_VERSION})")

# The redistributable is installed beside the SDK's own share files so a
# consumer build can stage it without having this module; the function that
# does the copying lives in rexglue_helpers.cmake, which consumers do get.
install(FILES
    "${REXGLUE_AGILITY_BIN_DIR}/D3D12Core.dll"
    DESTINATION share/rexglue/D3D12
)
if(EXISTS "${REXGLUE_AGILITY_BIN_DIR}/d3d12SDKLayers.dll")
    install(FILES
        "${REXGLUE_AGILITY_BIN_DIR}/d3d12SDKLayers.dll"
        DESTINATION share/rexglue/D3D12
    )
endif()

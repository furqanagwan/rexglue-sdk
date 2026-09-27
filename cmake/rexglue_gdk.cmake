#==========================================================
# rexglue_gdk.cmake - Opt-in Microsoft GDK (PC) toolchain selection
#
# rexglue_find_gdk(ROOT <edition directory> EDITION <yymmqq>)
#
# Validates an installed PC GDK edition and defines the imported INTERFACE
# target rex::gdk (GDK headers, xgameruntime.lib, REXGLUE_GDK_EDITION). Used
# by the SDK build (REXGLUE_USE_GDK, RG-GDK-002) and by the installed package
# config, so consumers resolve the GDK on their own machine: no GDK path,
# header or library is exported or redistributed.
#==========================================================
include_guard(GLOBAL)

function(rexglue_find_gdk)
    cmake_parse_arguments(ARG "" "ROOT;EDITION" "" ${ARGN})

    if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8 OR NOT CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64")
        message(FATAL_ERROR "The GDK build is only proven for Windows x64 (RG-GDK-002)")
    endif()
    if(NOT ARG_ROOT)
        message(FATAL_ERROR
            "No GDK edition selected. Install the April 2026 PC GDK (${ARG_EDITION}) or pass "
            "-DREXGLUE_GDK_ROOT=\"C:/Program Files (x86)/Microsoft GDK/${ARG_EDITION}\" "
            "(the default comes from the GameDKCoreLatest environment variable).")
    endif()

    get_filename_component(root "${ARG_ROOT}" ABSOLUTE)
    set(include_dir "${root}/windows/include")
    set(runtime_lib "${root}/windows/lib/x64/xgameruntime.lib")
    foreach(required "${include_dir}/grdk.h" "${include_dir}/XGameRuntime.h" "${runtime_lib}")
        if(NOT EXISTS "${required}")
            message(FATAL_ERROR
                "REXGLUE_GDK_ROOT is not an installed PC GDK edition: missing ${required}. "
                "Pass the edition directory, for example "
                "\"C:/Program Files (x86)/Microsoft GDK/${ARG_EDITION}\".")
        endif()
    endforeach()

    file(STRINGS "${include_dir}/grdk.h" edition_line REGEX "^#define _GRDK_EDITION[ \t]+[0-9]+")
    string(REGEX MATCH "[0-9]+$" edition "${edition_line}")
    if(edition STREQUAL "")
        message(FATAL_ERROR "Cannot read _GRDK_EDITION from ${include_dir}/grdk.h")
    endif()
    if(ARG_EDITION AND NOT edition STREQUAL ARG_EDITION)
        message(FATAL_ERROR
            "GDK edition mismatch: ${root} is ${edition}, but ${ARG_EDITION} is required. "
            "Point REXGLUE_GDK_ROOT at the ${ARG_EDITION} edition directory.")
    endif()

    if(NOT TARGET rex::gdk)
        add_library(rex::gdk INTERFACE IMPORTED GLOBAL)
        set_target_properties(rex::gdk PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${include_dir}"
            INTERFACE_LINK_LIBRARIES "${runtime_lib}"
            INTERFACE_COMPILE_DEFINITIONS "REXGLUE_GDK_EDITION=${edition}")
    endif()

    set(REXGLUE_GDK_ROOT_RESOLVED "${root}" PARENT_SCOPE)
    set(REXGLUE_GDK_EDITION_FOUND "${edition}" PARENT_SCOPE)
endfunction()

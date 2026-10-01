#==========================================================
# rexglue_helpers.cmake
#
# Three helpers, each with a single responsibility:
#   rexglue_apply_target_settings(<target>)        - common compile/platform flags
#   rexglue_configure_target(<target>)             - host application
#   rexglue_configure_module_target(<target> ...)  - guest DLL module
#==========================================================
include_guard(GLOBAL)

#==========================================================
# rexglue_apply_target_settings(<target>) - Common flags
#
# Applied to both host apps and guest DLL modules. Compile/link flags only;
# runtime DLL staging is the host's job (see rexglue_configure_target).
#==========================================================
function(rexglue_apply_target_settings target_name)
    if(NOT MSVC)
        if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
            target_compile_options(${target_name} PRIVATE -msse4.1)
        endif()
    endif()
endfunction()

#==========================================================
# rexglue_configure_target(<target>) - Host application
#
# Adds:
#   - Win32 entry point source (windowed_app_main.cpp)
#   - ReXApp base class source (rex_app.cpp)
#   - Build-config define for the version stamp
#   - Windows POST_BUILD copy of TARGET_RUNTIME_DLLS and the FidelityFX DLLs.
#     Guest modules colocate with the host (see rexglue_configure_module_target),
#     so this single copy handles them transitively.
#==========================================================
function(rexglue_configure_target target_name)
    cmake_parse_arguments(ARG "" "" "GPU_PLUGINS" ${ARGN})

    target_sources(${target_name} PRIVATE
        ${REXGLUE_SHARE_DIR}/windowed_app_main.cpp
        ${REXGLUE_SHARE_DIR}/rex_app.cpp)

    target_compile_definitions(${target_name} PRIVATE
        REXGLUE_BUILD_CONFIG="$<CONFIG>")

    rexglue_apply_target_settings(${target_name})
    _rexglue_embed_xbox_guide(${target_name})
    _rexglue_embed_dlc_catalog(${target_name})

    if(WIN32)
        # Stage runtime DLLs (rexruntime, TracyClient, etc.) next to the host
        # binary on every link. copy_if_different is a no-op when up to date.
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND "$<$<BOOL:$<TARGET_RUNTIME_DLLS:${target_name}>>:${CMAKE_COMMAND};-E;copy_if_different;$<TARGET_RUNTIME_DLLS:${target_name}>;$<TARGET_FILE_DIR:${target_name}>>"
            COMMAND_EXPAND_LISTS
            VERBATIM
        )
    endif()

    if(WIN32)
        # FidelityFX is linked PRIVATE by rexui (to avoid propagating DLL
        # requirements to tool-mode targets), so copy its DLLs explicitly.
        foreach(_fx amd_fidelityfx_dx12)
            if(TARGET ${_fx})
                add_custom_command(TARGET ${target_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        $<TARGET_FILE:${_fx}>
                        $<TARGET_FILE_DIR:${target_name}>
                    VERBATIM
                )
            endif()
        endforeach()
    endif()

    # Stage requested GPU emulation plugins next to the executable. Plugins
    # are runtime-loaded (never linked), so TARGET_RUNTIME_DLLS misses them.
    foreach(_plugin IN LISTS ARG_GPU_PLUGINS)
        if(TARGET rexgpu-${_plugin})
            # In-tree build: depend on it so it gets built.
            set(_plugin_target rexgpu-${_plugin})
            add_dependencies(${target_name} ${_plugin_target})
        elseif(TARGET rex::gpu-${_plugin})
            # Installed SDK import.
            set(_plugin_target rex::gpu-${_plugin})
        else()
            message(FATAL_ERROR
                "rexglue_configure_target: unknown GPU plugin '${_plugin}' "
                "(no target rexgpu-${_plugin} or rex::gpu-${_plugin})")
        endif()
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${_plugin_target}>
                $<TARGET_FILE_DIR:${target_name}>
            VERBATIM
        )
        unset(_plugin_target)
    endforeach()

endfunction()

#==========================================================
# The Xbox guide (RG-GDK-041), built into every title
#
# The guide runs the console's own scenes. They come from the builder's own
# console system update (like the game files, never shipped with the SDK),
# named by REXGLUE_SYSTEM_UPDATE or the environment variable of that name.
# `rexglue guide-bundle` takes the four modules the guide reads (about 3 MB)
# and the executable embeds them, so players need nothing for the guide.
#==========================================================
set(REXGLUE_SYSTEM_UPDATE "$ENV{REXGLUE_SYSTEM_UPDATE}" CACHE PATH
    "Console $SystemUpdate (dashboard 2.0.17559) built into each title for the Xbox guide")

function(_rexglue_embed_xbox_guide target_name)
    if(NOT REXGLUE_SYSTEM_UPDATE)
        message(STATUS "${target_name}: Xbox guide not built in; set REXGLUE_SYSTEM_UPDATE "
                       "to the console's $SystemUpdate folder")
        return()
    endif()
    if(NOT EXISTS "${REXGLUE_SYSTEM_UPDATE}")
        message(FATAL_ERROR "REXGLUE_SYSTEM_UPDATE: '${REXGLUE_SYSTEM_UPDATE}' does not exist")
    endif()
    if(TARGET rexglue)
        set(_rexglue_cli rexglue)
    else()
        set(_rexglue_cli rex::rexglue)
    endif()

    string(MAKE_C_IDENTIFIER "${target_name}" _id)
    set(_dir "${CMAKE_CURRENT_BINARY_DIR}/rexglue_guide")
    set(_bundle "${_dir}/${_id}_xbox_guide.bin")
    set(_source "${_dir}/${_id}_xbox_guide.cpp")
    if(IS_DIRECTORY "${REXGLUE_SYSTEM_UPDATE}")
        file(GLOB_RECURSE _inputs CONFIGURE_DEPENDS "${REXGLUE_SYSTEM_UPDATE}/*")
    else()
        set(_inputs "${REXGLUE_SYSTEM_UPDATE}")
    endif()
    add_custom_command(
        OUTPUT "${_bundle}"
        COMMAND $<TARGET_FILE:${_rexglue_cli}> guide-bundle "${REXGLUE_SYSTEM_UPDATE}"
                -o "${_bundle}"
        DEPENDS ${_inputs}
        COMMENT "Building the Xbox guide into ${target_name}"
        VERBATIM)

    # The bundle goes into read-only data as it is; .incbin needs Clang.
    file(TO_CMAKE_PATH "${_bundle}" _bundle_path)
    file(WRITE "${_source}.in"
"// Generated by rexglue_configure_target - DO NOT EDIT
#include <cstddef>
#include <cstdint>

namespace rex::ui::guide {
bool RegisterEmbeddedGuide(const std::uint8_t* data, std::size_t size);
}  // namespace rex::ui::guide

extern \"C\" const std::uint8_t rexglue_xbox_guide_${_id}[];
extern \"C\" const std::uint8_t rexglue_xbox_guide_${_id}_end[];
__asm__(\".section .rdata,\\\"dr\\\"\\n\"
        \".p2align 4\\n\"
        \".globl rexglue_xbox_guide_${_id}\\n\"
        \"rexglue_xbox_guide_${_id}:\\n\"
        \".incbin \\\"${_bundle_path}\\\"\\n\"
        \".globl rexglue_xbox_guide_${_id}_end\\n\"
        \"rexglue_xbox_guide_${_id}_end:\\n\"
        \".text\\n\");

namespace {
const bool kRegistered = rex::ui::guide::RegisterEmbeddedGuide(
    rexglue_xbox_guide_${_id},
    std::size_t(rexglue_xbox_guide_${_id}_end - rexglue_xbox_guide_${_id}));
}  // namespace
")
    configure_file("${_source}.in" "${_source}" COPYONLY)
    set_source_files_properties("${_source}" PROPERTIES OBJECT_DEPENDS "${_bundle}")
    target_sources(${target_name} PRIVATE "${_source}")
    message(STATUS "${target_name}: Xbox guide built in from ${REXGLUE_SYSTEM_UPDATE}")
endfunction()

#==========================================================
# The title's add-on catalogue (RG-GDK-050), built into it
#
# The title's config lists its add-ons as [[dlc]] entries, which codegen
# passes on as REXGLUE_TITLE_DLC_IDS. `rexglue dlc-catalog` fetches their
# names, descriptions and art from the Xbox 360 marketplace catalogue in the
# builder's language, once (the file is kept until the list changes), and the
# executable embeds it, so the guide's Manage Game page works offline. A build
# without internet embeds the IDs only and says so.
#==========================================================
set(REXGLUE_DLC_LOCALE "" CACHE STRING
    "Marketplace language and market for the add-on catalogue, such as en-GB (default: this PC's)")

function(_rexglue_embed_dlc_catalog target_name)
    if(NOT REXGLUE_TITLE_DLC_IDS)
        return()
    endif()
    if(TARGET rexglue)
        set(_rexglue_cli rexglue)
    else()
        set(_rexglue_cli rex::rexglue)
    endif()
    string(MAKE_C_IDENTIFIER "${target_name}" _id)
    set(_dir "${CMAKE_CURRENT_BINARY_DIR}/rexglue_dlc")
    # Named by its inputs, so a changed list or locale fetches it again.
    string(MD5 _key "${REXGLUE_TITLE_DLC_IDS}|${REXGLUE_DLC_LOCALE}")
    string(SUBSTRING "${_key}" 0 12 _key)
    set(_catalog "${_dir}/${_id}_dlc_${_key}.bin")
    set(_source "${_dir}/${_id}_dlc.cpp")
    string(REPLACE ";" "," _ids "${REXGLUE_TITLE_DLC_IDS}")
    set(_locale_args)
    if(REXGLUE_DLC_LOCALE)
        set(_locale_args --locale "${REXGLUE_DLC_LOCALE}")
    endif()
    add_custom_command(
        OUTPUT "${_catalog}"
        COMMAND $<TARGET_FILE:${_rexglue_cli}> dlc-catalog --ids "${_ids}" ${_locale_args}
                -o "${_catalog}"
        COMMENT "Fetching the add-on catalogue for ${target_name}"
        VERBATIM)

    file(TO_CMAKE_PATH "${_catalog}" _catalog_path)
    file(WRITE "${_source}.in"
"// Generated by rexglue_configure_target - DO NOT EDIT
#include <cstddef>
#include <cstdint>

namespace rex::ui::guide {
bool RegisterEmbeddedDlcCatalog(const std::uint8_t* data, std::size_t size);
}  // namespace rex::ui::guide

extern \"C\" const std::uint8_t rexglue_dlc_catalog_${_id}[];
extern \"C\" const std::uint8_t rexglue_dlc_catalog_${_id}_end[];
__asm__(\".section .rdata,\\\"dr\\\"\\n\"
        \".p2align 4\\n\"
        \".globl rexglue_dlc_catalog_${_id}\\n\"
        \"rexglue_dlc_catalog_${_id}:\\n\"
        \".incbin \\\"${_catalog_path}\\\"\\n\"
        \".globl rexglue_dlc_catalog_${_id}_end\\n\"
        \"rexglue_dlc_catalog_${_id}_end:\\n\"
        \".text\\n\");

namespace {
const bool kRegistered = rex::ui::guide::RegisterEmbeddedDlcCatalog(
    rexglue_dlc_catalog_${_id},
    std::size_t(rexglue_dlc_catalog_${_id}_end - rexglue_dlc_catalog_${_id}));
}  // namespace
")
    configure_file("${_source}.in" "${_source}" COPYONLY)
    set_source_files_properties("${_source}" PROPERTIES OBJECT_DEPENDS "${_catalog}")
    target_sources(${target_name} PRIVATE "${_source}")
    message(STATUS "${target_name}: add-on catalogue of ${REXGLUE_TITLE_DLC_IDS} built in")
endfunction()

#==========================================================
# rexglue_configure_module_target(<target> [HOST <host_target>])
#   - Guest DLL module
#
# Output is colocated with HOST (or CMAKE_RUNTIME_OUTPUT_DIRECTORY) so the
# host's LoadUserModule finds it; the host is wired to depend on the module
# so a top-level build of the host pulls in all guest DLLs. No runtime DLL
# staging here; the host's POST_BUILD copy covers shared dependencies.
#==========================================================
function(rexglue_configure_module_target target_name)
    cmake_parse_arguments(ARG "" "HOST" "" ${ARGN})

    if(ARG_HOST)
        set_target_properties(${target_name} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${ARG_HOST}>
            RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${ARG_HOST}>
            ARCHIVE_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:${ARG_HOST}>
        )
        # Defer add_dependencies so the host target may be declared after
        # this module call. Wrapping in EVAL CODE expands the variables now,
        # which DEFER CALL otherwise treats as literal argument text.
        cmake_language(EVAL CODE
            "cmake_language(DEFER CALL add_dependencies ${ARG_HOST} ${target_name})")
    elseif(CMAKE_RUNTIME_OUTPUT_DIRECTORY)
        set_target_properties(${target_name} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        )
    endif()

    rexglue_apply_target_settings(${target_name})
endfunction()

#==========================================================
# rexglue_embed_metadata(<target> DIRECTORY <dir> [PREFIX <relative-prefix>])
#
# Embeds files into the host executable as metadata assets. Runtime lookups use
# paths relative to the metadata root, so embedding metadata/icons with PREFIX
# icons makes "icons/foo.png" resolve without a loose sidecar file.
#==========================================================
function(rexglue_embed_metadata target_name)
    cmake_parse_arguments(ARG "" "DIRECTORY;PREFIX" "" ${ARGN})

    if(NOT TARGET ${target_name})
        message(FATAL_ERROR "rexglue_embed_metadata: target '${target_name}' does not exist")
    endif()
    if(NOT ARG_DIRECTORY)
        message(FATAL_ERROR "rexglue_embed_metadata: DIRECTORY is required")
    endif()
    if(NOT IS_DIRECTORY "${ARG_DIRECTORY}")
        message(FATAL_ERROR "rexglue_embed_metadata: '${ARG_DIRECTORY}' is not a directory")
    endif()

    file(GLOB_RECURSE _rexglue_metadata_files
        CONFIGURE_DEPENDS
        "${ARG_DIRECTORY}/*")

    set(_rexglue_regular_files)
    foreach(_rexglue_file IN LISTS _rexglue_metadata_files)
        if(NOT IS_DIRECTORY "${_rexglue_file}")
            list(APPEND _rexglue_regular_files "${_rexglue_file}")
        endif()
    endforeach()

    if(NOT _rexglue_regular_files)
        message(STATUS "rexglue_embed_metadata: no files found in ${ARG_DIRECTORY}")
        return()
    endif()

    string(MAKE_C_IDENTIFIER "${target_name}" _rexglue_target_id)
    set(_rexglue_output_dir "${CMAKE_CURRENT_BINARY_DIR}/rexglue_embedded_metadata")
    set(_rexglue_output "${_rexglue_output_dir}/${_rexglue_target_id}_embedded_metadata.cpp")
    file(MAKE_DIRECTORY "${_rexglue_output_dir}")

    set(_rexglue_content "// Auto-generated by rexglue_embed_metadata - DO NOT EDIT\n")
    string(APPEND _rexglue_content
        "#include <cstddef>\n"
        "#include <cstdint>\n"
        "#include <rex/embedded_metadata.h>\n\n"
        "namespace {\n\n")

    set(_rexglue_count 0)
    foreach(_rexglue_file IN LISTS _rexglue_regular_files)
        file(RELATIVE_PATH _rexglue_rel "${ARG_DIRECTORY}" "${_rexglue_file}")
        string(REPLACE "\\" "/" _rexglue_rel "${_rexglue_rel}")
        if(ARG_PREFIX)
            string(REPLACE "\\" "/" _rexglue_prefix "${ARG_PREFIX}")
            string(REGEX REPLACE "/$" "" _rexglue_prefix "${_rexglue_prefix}")
            set(_rexglue_asset_path "${_rexglue_prefix}/${_rexglue_rel}")
        else()
            set(_rexglue_asset_path "${_rexglue_rel}")
        endif()
        string(REPLACE "\"" "\\\"" _rexglue_asset_path "${_rexglue_asset_path}")

        string(MD5 _rexglue_asset_id "${_rexglue_asset_path}")
        file(READ "${_rexglue_file}" _rexglue_hex HEX)
        string(REGEX REPLACE "([0-9A-Fa-f][0-9A-Fa-f])" "0x\\1," _rexglue_bytes "${_rexglue_hex}")

        string(APPEND _rexglue_content
            "const std::uint8_t kAsset_${_rexglue_asset_id}[] = {${_rexglue_bytes}};\n"
            "const bool kRegistered_${_rexglue_asset_id} = "
            "::rex::RegisterEmbeddedMetadataAsset(\"${_rexglue_asset_path}\", "
            "kAsset_${_rexglue_asset_id}, sizeof(kAsset_${_rexglue_asset_id}));\n\n")
        math(EXPR _rexglue_count "${_rexglue_count} + 1")
    endforeach()

    string(APPEND _rexglue_content "}  // namespace\n")
    file(WRITE "${_rexglue_output}" "${_rexglue_content}")
    target_sources(${target_name} PRIVATE "${_rexglue_output}")
    message(STATUS "Embedded ${_rexglue_count} metadata asset(s) into ${target_name}")
endfunction()

#==========================================================
# rexglue_add_game_config(<target> DIRECTORY <dir>)
#
# Stages the MicrosoftGame.config and ShellVisuals images that
# `rexglue init gameconfig` wrote into <dir> next to the target's executable,
# so the build output is a loose PC layout that `wdapp register` and
# `makepkg genmap/pack /pc` accept (RG-GDK-022, docs/gdk-packaging.md).
#==========================================================
function(rexglue_add_game_config target_name)
    cmake_parse_arguments(ARG "" "DIRECTORY" "" ${ARGN})
    if(NOT ARG_DIRECTORY OR NOT EXISTS "${ARG_DIRECTORY}/MicrosoftGame.config")
        message(FATAL_ERROR
            "rexglue_add_game_config: no MicrosoftGame.config in '${ARG_DIRECTORY}'. "
            "Generate one with 'rexglue init gameconfig'.")
    endif()
    file(GLOB _images CONFIGURE_DEPENDS "${ARG_DIRECTORY}/*.png")
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ARG_DIRECTORY}/MicrosoftGame.config" ${_images}
            $<TARGET_FILE_DIR:${target_name}>
        VERBATIM
    )
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
        "${ARG_DIRECTORY}/MicrosoftGame.config")
endfunction()

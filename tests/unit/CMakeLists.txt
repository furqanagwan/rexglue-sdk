# Unit Tests for ReXGlue core components

add_executable(unit_tests
    test_memory.cpp
    memory/heap_allocation_test.cpp
    kernel/object_table_test.cpp
    kernel/xecrypt_md5_test.cpp
    core/cvar_test.cpp
    core/fiber_test.cpp
    core/filesystem_test.cpp
    core/data_locations_test.cpp
    filesystem/stfs_container_test.cpp
    filesystem/disc_image_test.cpp
    core/vfs_overwrite_test.cpp
    core/hash_test.cpp
    core/utf8_ascii_case_test.cpp
    core/stream_test.cpp
    core/chrono_test.cpp
    core/log_prune_test.cpp
    core/timer_resolution_test.cpp
    graphics/texture_layout_test.cpp
    graphics/zpd_report_test.cpp
    graphics/float_precision_test.cpp
    graphics/debug_markers_test.cpp
    graphics/frame_stats_test.cpp
    graphics/vblank_pacer_test.cpp
    graphics/storage_seed_test.cpp
    graphics/fetch_conversion_test.cpp
    graphics/shader_replacements_test.cpp
    graphics/scaling_list_test.cpp
    ppc/import_function_test.cpp
    ppc/stack_test.cpp
    ppc/nonlocal_jump_test.cpp
    ppc/fp_test.cpp
    system/guest_path_test.cpp
    system/achievement_manager_test.cpp
    system/function_dispatcher_test.cpp
    system/gaming_runtime_test.cpp
    system/title_display_name_test.cpp
    system/user_language_test.cpp
    system/game_source_test.cpp
    system/file_read_statistics_test.cpp
    system/gpu_plugin_name_test.cpp
    system/release_update_test.cpp
    system/game_media_recovery_test.cpp
    audio/xma_context_test.cpp
    audio/audio_client_lifetime_test.cpp
    audio/conversion_test.cpp
    audio/master_volume_test.cpp
    audio/ui_sound_test.cpp
    input/input_assignment_test.cpp
    input/input_system_test.cpp
    input/mnk_keystroke_test.cpp
    input/keystroke_synthesizer_test.cpp
    input/gamepad_devices_test.cpp
    ui/win32_window_test.cpp
    ui/display_mode_test.cpp
    ui/launch_settings_test.cpp
    ui/game_source_test.cpp
    codegen/codegen_writer_test.cpp
    codegen/function_table_layout_test.cpp
    codegen/output_partition_test.cpp
    codegen/output_stamp_test.cpp
    codegen/jump_table_test.cpp
    codegen/indirect_discovery_test.cpp
    codegen/crt_jump_scanner_test.cpp
    codegen/code_patch_test.cpp
    codegen/game_config_test.cpp
    codegen/title_update_manifest_test.cpp
    codegen/indirect_trace_test.cpp
    rexglue/app_name_test.cpp
)

xbox_guide_attach_tests(unit_tests)

if(WIN32)
    target_sources(unit_tests PRIVATE audio/xaudio2_driver_test.cpp)
endif()

if(REXGLUE_USE_GDK)
    target_sources(unit_tests PRIVATE gdk/gdk_runtime_test.cpp gdk/gameinput_test.cpp)
endif()

target_sources(unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src/rexglue/ui/ui.cpp
    ${PROJECT_SOURCE_DIR}/src/rexglue/ui/progress.cpp
    ${PROJECT_SOURCE_DIR}/src/rexglue/commands/project_scan.cpp
)

if(WIN32)
    target_sources(unit_tests PRIVATE
        rexglue/library_art_test.cpp
        ${PROJECT_SOURCE_DIR}/src/rexglue/commands/library_art.cpp
    )
    target_link_libraries(unit_tests PRIVATE windowscodecs)
endif()

target_include_directories(unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/thirdparty/stb
    ${PROJECT_SOURCE_DIR}/thirdparty  # crypto/TinySHA1.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(unit_tests PRIVATE
    rexcodegen
    rexruntime
    imgui::imgui  # the guide's headers (xbox_guide.h)
    Catch2::Catch2WithMain
)

# ReXApp is shipped as source for recomp projects, rather than compiled into
# rexui. Keep its SDK-consumer compilation path covered by the test build.
add_library(rexapp_compile_test OBJECT
    ${PROJECT_SOURCE_DIR}/src/ui/rex_app.cpp
)
target_link_libraries(rexapp_compile_test PRIVATE
    rexruntime
    rexui
    rexinput
    rexaudio
)
add_dependencies(unit_tests rexapp_compile_test)

# Strip Tracy/profiling instrumentation from test targets
target_compile_options(unit_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING
    -UREXGLUE_ENABLE_PERF_COUNTERS -UREXGLUE_PROFILE_GUEST_FUNCTIONS
)

set_target_properties(unit_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>
)

# Discover tests
include(Catch)
# Exercise CPU primitive conversion without linking the runtime-loaded GPU plugin.
# Compile its actual production sources against a small CPU allocation adapter.
add_executable(primitive_tests
    graphics/primitive_cache_test.cpp
    test_memory.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/primitive_processor.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/shared_memory.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/register_file.cpp
)
target_include_directories(primitive_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(primitive_tests PRIVATE rexruntime Catch2::Catch2WithMain)
target_compile_options(primitive_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING -UREXGLUE_ENABLE_PERF_COUNTERS)
set_target_properties(primitive_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>)
catch_discover_tests(primitive_tests TEST_PREFIX "primitive." ADD_TAGS_AS_LABELS
    PROPERTIES LABELS "unit" TIMEOUT 60)

add_executable(shader_parse_tests
    graphics/alu_scalar_operand_test.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/pipeline/shader/shader.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/pipeline/shader/translator.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/pipeline/shader/translator_disasm.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/format/ucode.cpp
    ${PROJECT_SOURCE_DIR}/src/graphics/flags.cpp
)
target_include_directories(shader_parse_tests PRIVATE ${PROJECT_SOURCE_DIR}/thirdparty/renderdoc)
target_link_libraries(shader_parse_tests PRIVATE rexruntime Catch2::Catch2WithMain)
target_compile_options(shader_parse_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING -UREXGLUE_ENABLE_PERF_COUNTERS)
set_target_properties(shader_parse_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>)
catch_discover_tests(shader_parse_tests TEST_PREFIX "shader." ADD_TAGS_AS_LABELS
    PROPERTIES LABELS "unit" TIMEOUT 60)

catch_discover_tests(unit_tests
    TEST_PREFIX "unit."
    ADD_TAGS_AS_LABELS
    PROPERTIES
        LABELS "unit"
        TIMEOUT 60
)

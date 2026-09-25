# Unit Tests for ReXGlue core components

add_executable(unit_tests
    test_memory.cpp
    memory/heap_allocation_test.cpp
    kernel/object_table_test.cpp
    core/cvar_test.cpp
    core/fiber_test.cpp
    core/filesystem_test.cpp
    core/hash_test.cpp
    core/stream_test.cpp
    core/chrono_test.cpp
    graphics/texture_layout_test.cpp
    graphics/zpd_report_test.cpp
    graphics/float_precision_test.cpp
    ppc/import_function_test.cpp
    ppc/stack_test.cpp
    system/guest_path_test.cpp
    system/achievement_manager_test.cpp
    system/function_dispatcher_test.cpp
    audio/xma_context_test.cpp
    audio/audio_client_lifetime_test.cpp
    input/input_assignment_test.cpp
    input/keystroke_synthesizer_test.cpp
    input/gamepad_devices_test.cpp
    ui/win32_window_test.cpp
    codegen/codegen_writer_test.cpp
    codegen/output_partition_test.cpp
    codegen/output_stamp_test.cpp
    codegen/jump_table_test.cpp
)

if(REXGLUE_USE_GDK)
    target_sources(unit_tests PRIVATE gdk/gdk_runtime_test.cpp gdk/gameinput_test.cpp)
endif()

target_sources(unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/src/rexglue/ui/ui.cpp
    ${PROJECT_SOURCE_DIR}/src/rexglue/ui/progress.cpp
)

target_include_directories(unit_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(unit_tests PRIVATE
    rexcodegen
    rexruntime
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
catch_discover_tests(unit_tests
    TEST_PREFIX "unit."
    PROPERTIES
        LABELS "unit"
        TIMEOUT 60
)

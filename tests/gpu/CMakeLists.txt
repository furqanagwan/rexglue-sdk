# GPU capability and fixture tests (RG-GDK-006). They create real D3D12 devices,
# so they carry the "gpu" label; WARP cases run anywhere, hardware cases skip
# when no hardware adapter is present.

add_executable(gpu_tests
    d3d12_provider_test.cpp
    gpu_fixture.cpp
    pm4_fixture_test.cpp
    resolve_fixture_test.cpp
    edram_layout_fixture_test.cpp
    zpd_fixture_test.cpp
    ring_fixture_test.cpp
    memexport_fixture_test.cpp
    alu_fixture_test.cpp
    win32_present_test.cpp
    pix_capture_fixture_test.cpp
    async_draw_fixture_test.cpp
    shader_replacement_fixture_test.cpp
    native_resolve_fixture_test.cpp
)

# The replacement shader the fixture swaps in, compiled like a title's
# (rexglue_configure_target SHADER_REPLACEMENTS).
file(GLOB _gpu_test_fxc "$ENV{ProgramFiles\(x86\)}/Windows Kits/10/bin/*/x64/fxc.exe")
list(SORT _gpu_test_fxc COMPARE NATURAL ORDER DESCENDING)
list(GET _gpu_test_fxc 0 _gpu_test_fxc)
set(_replacement_dxbc "${CMAKE_CURRENT_BINARY_DIR}/replacement_magenta.ps.dxbc")
add_custom_command(OUTPUT "${_replacement_dxbc}"
    COMMAND "${_gpu_test_fxc}" /nologo /T ps_5_1 /E main /Fo "${_replacement_dxbc}"
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/replacement_magenta.ps.hlsl"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/replacement_magenta.ps.hlsl"
    VERBATIM)
target_sources(gpu_tests PRIVATE "${_replacement_dxbc}")
set_source_files_properties("${_replacement_dxbc}" PROPERTIES HEADER_FILE_ONLY TRUE)
target_compile_definitions(gpu_tests PRIVATE
    REXGLUE_TEST_REPLACEMENT_DXBC="${_replacement_dxbc}")

target_include_directories(gpu_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(gpu_tests PRIVATE
    rexruntime
    Catch2::Catch2WithMain
)

target_compile_options(gpu_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING
    -UREXGLUE_ENABLE_PERF_COUNTERS -UREXGLUE_PROFILE_GUEST_FUNCTIONS
)

set_target_properties(gpu_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>
)

# The fixture host loads the GPU plugin through the plugin ABI, like a title.
add_dependencies(gpu_tests rexgpu-xenos)
add_custom_command(TARGET gpu_tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:rexgpu-xenos>
        $<TARGET_FILE_DIR:gpu_tests>
    VERBATIM
)

include(Catch)
catch_discover_tests(gpu_tests
    TEST_PREFIX "gpu."
    PROPERTIES
        LABELS "gpu"
        TIMEOUT 60
        SKIP_RETURN_CODE 4
)

# Device loss is fatal in the backend, so the removal fixture runs as its own
# process and passes on the fatal-error report rather than on its exit code.
add_test(NAME gpu.device_removal_is_reported
    COMMAND gpu_tests "[.device-removal]")
set_tests_properties(gpu.device_removal_is_reported PROPERTIES
    LABELS "gpu"
    TIMEOUT 60
    PASS_REGULAR_EXPRESSION "FATAL ERROR: Graphics device lost"
    SKIP_REGULAR_EXPRESSION "GPU fixture host unavailable"
)

# Resolves at a non-power-of-two resolution scale, read back through the
# downscale shader (#58). 3x2 exercises both axes and the unit arithmetic that
# power-of-two scales can hide.
add_test(NAME gpu.resolve_readback_scaled_3x2
    COMMAND gpu_tests "[resolve]")
set_tests_properties(gpu.resolve_readback_scaled_3x2 PROPERTIES
    LABELS "gpu"
    TIMEOUT 120
    SKIP_RETURN_CODE 4
    ENVIRONMENT "REXGLUE_GPU_FIXTURE_CVARS=draw_resolution_scale_x=3\;draw_resolution_scale_y=2"
)

# ZPD occlusion query counts are normalized by the draw resolution scale, so the
# strict-mode fixtures must report the same guest sample counts at 3x2.
add_test(NAME gpu.zpd_scaled_3x2
    COMMAND gpu_tests "[zpd]")
set_tests_properties(gpu.zpd_scaled_3x2 PROPERTIES
    LABELS "gpu"
    TIMEOUT 120
    SKIP_RETURN_CODE 4
    ENVIRONMENT "REXGLUE_GPU_FIXTURE_CVARS=draw_resolution_scale_x=3\;draw_resolution_scale_y=2"
)

# PIX for Windows capture of a labeled draw and resolve (RG-GDK-028): PIX
# launches the hidden [.pix-capture] case, and the script checks the capture's
# markers, a debug-layer replay and that no binary imports the PIX runtime.
# Skips when PIX is not installed.
add_test(NAME gpu.pix_capture
    COMMAND powershell -NoProfile -ExecutionPolicy Bypass
        -File ${CMAKE_SOURCE_DIR}/scripts/pix_capture_fixture.ps1
        -Tests $<TARGET_FILE:gpu_tests>
        -Output ${CMAKE_CURRENT_BINARY_DIR}/pix_capture_$<CONFIG>)
set_tests_properties(gpu.pix_capture PROPERTIES
    LABELS "gpu;pix"
    TIMEOUT 300
    SKIP_RETURN_CODE 77
    RUN_SERIAL TRUE
)

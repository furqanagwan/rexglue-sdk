# GPU capability and fixture tests (RG-GDK-006). They create real D3D12 devices,
# so they carry the "gpu" label; WARP cases run anywhere, hardware cases skip
# when no hardware adapter is present.

add_executable(gpu_tests
    d3d12_provider_test.cpp
)

target_include_directories(gpu_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
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

include(Catch)
catch_discover_tests(gpu_tests
    TEST_PREFIX "gpu."
    PROPERTIES
        LABELS "gpu"
        TIMEOUT 60
        SKIP_RETURN_CODE 4
)

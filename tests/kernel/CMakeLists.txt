# Kernel and XAM service tests against a Runtime set up without a title image
# (RG-GDK-017). A Runtime owns the process-wide guest Memory, so these live in
# their own executable rather than in unit_tests.

add_executable(kernel_tests
    content_test.cpp
    profile_test.cpp
)

target_include_directories(kernel_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(kernel_tests PRIVATE
    rexruntime
    Catch2::Catch2WithMain
)

target_compile_options(kernel_tests PRIVATE
    -UTRACY_ENABLE -UREXGLUE_ENABLE_PROFILING
    -UREXGLUE_ENABLE_PERF_COUNTERS -UREXGLUE_PROFILE_GUEST_FUNCTIONS
)

set_target_properties(kernel_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY $<TARGET_FILE_DIR:rexruntime>
)

include(Catch)
catch_discover_tests(kernel_tests
    TEST_PREFIX "kernel."
    PROPERTIES
        LABELS "kernel"
        TIMEOUT 120
)

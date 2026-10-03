# The opt-in DXIL toolchain (REXGLUE_SHADER_DXIL, RG-GDK-032 stage 1): Mesa
# spirv_to_dxil, dxil.dll signing and the Agility SDK runtime, end to end.

add_executable(dxil_smoke_tests dxil_smoke_test.cpp)
target_include_directories(dxil_smoke_tests PRIVATE "${REXGLUE_DXC_INCLUDE_DIR}")
target_compile_definitions(dxil_smoke_tests PRIVATE
    REXGLUE_D3D12_SDK_VERSION=${REXGLUE_D3D12_SDK_VERSION})
target_link_libraries(dxil_smoke_tests PRIVATE
    rex::spirv_to_dxil
    d3d12
    Catch2::Catch2WithMain
)
# Mesa is built release with /MD; the test links the same CRT in every
# configuration.
set_target_properties(dxil_smoke_tests PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
rexglue_deploy_d3d12_redist(dxil_smoke_tests)

include(Catch)
catch_discover_tests(dxil_smoke_tests
    TEST_PREFIX "dxil."
    PROPERTIES
        LABELS "dxil;gpu"
        TIMEOUT 60
        SKIP_RETURN_CODE 4
)

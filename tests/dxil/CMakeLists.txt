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

# The xenia-edge SPIR-V translator on guest microcode, to signed DXIL. The
# translator lives in the GPU plugin (hidden visibility), so its sources are
# compiled into the test.
set(_gfx "${PROJECT_SOURCE_DIR}/src/graphics")
add_executable(spirv_translator_tests
    spirv_translator_test.cpp
    ${_gfx}/pipeline/shader/shader.cpp
    ${_gfx}/pipeline/shader/translator.cpp
    ${_gfx}/pipeline/shader/translator_disasm.cpp
    ${_gfx}/format/ucode.cpp
    ${_gfx}/flags.cpp
    ${_gfx}/registers.cpp
    ${_gfx}/pipeline/render_target/cache.cpp
    ${_gfx}/util/draw.cpp
    ${_gfx}/util/draw_extent_estimator.cpp
    ${_gfx}/pipeline/shader/interpreter.cpp
    ${_gfx}/pipeline/shader/spirv.cpp
    ${_gfx}/pipeline/shader/spirv_builder.cpp
    ${_gfx}/pipeline/shader/spirv_builtin_geometry_shader.cpp
    ${_gfx}/pipeline/shader/spirv_fsi_system_constants.cpp
    ${_gfx}/pipeline/shader/spirv_to_dxil_compiler.cpp
    ${_gfx}/pipeline/shader/spirv_translator.cpp
    ${_gfx}/pipeline/shader/spirv_translator_alu.cpp
    ${_gfx}/pipeline/shader/spirv_translator_fetch.cpp
    ${_gfx}/pipeline/shader/spirv_translator_memexport.cpp
    ${_gfx}/pipeline/shader/spirv_translator_rb.cpp
)
target_include_directories(spirv_translator_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/thirdparty/renderdoc
    "${REXGLUE_GLSLANG_INCLUDE_DIR}" "${REXGLUE_DXC_INCLUDE_DIR}")
target_compile_definitions(spirv_translator_tests PRIVATE REXGLUE_SHADER_DXIL=1)
target_link_libraries(spirv_translator_tests PRIVATE
    rexruntime
    glslang::SPIRV
    rex::spirv_to_dxil
    Catch2::Catch2WithMain
)
set_target_properties(spirv_translator_tests PROPERTIES MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
rexglue_deploy_d3d12_redist(spirv_translator_tests)
catch_discover_tests(spirv_translator_tests
    TEST_PREFIX "dxil."
    PROPERTIES
        LABELS "dxil"
        TIMEOUT 60
)

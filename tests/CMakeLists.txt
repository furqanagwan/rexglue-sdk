# ReXGlue Tests
# Test infrastructure for PPC instruction validation and unit tests

# Unit tests for core components
add_subdirectory(unit)

# D3D12 capability/fixture tests (Windows D3D12 only)
add_subdirectory(gpu)

# PPC instruction tests (requires PPC toolchain)
add_subdirectory(ppc)

# The precompiled DXBC shaders must rebuild byte for byte from their sources
# (scripts/build_shaders.py, RG-GDK-009). Needs the Windows SDK's FXC.
find_package(Python3 COMPONENTS Interpreter)
if(WIN32 AND Python3_FOUND)
  add_test(NAME shaders.bytecode_reproducible
    COMMAND Python3::Interpreter ${CMAKE_SOURCE_DIR}/scripts/build_shaders.py --check)
endif()

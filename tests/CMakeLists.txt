# ReXGlue Tests
# Test infrastructure for PPC instruction validation and unit tests

# Unit tests for core components
add_subdirectory(unit)

# D3D12 capability/fixture tests (Windows D3D12 only)
add_subdirectory(gpu)

# PPC instruction tests (requires PPC toolchain)
add_subdirectory(ppc)

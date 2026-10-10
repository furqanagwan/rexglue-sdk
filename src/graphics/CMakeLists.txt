# rexgpu-xenos: Xenos GPU emulation plugin (ported from Xenia)
# Namespace: rex::graphics
#
# Runtime-loaded via rex::system::LoadGpuPlugin; consumers never link this
# target. The Xenos format layer is compiled into rexcore.

set(REXGPU_XENOS_SOURCES
    plugin_main.cpp

    # Core GPU types
    flags.cpp
    register_file.cpp
    registers.cpp
    pipeline/shader/shader.cpp
    format/ucode.cpp
    sampler_info.cpp

    # GPU system
    graphics_system.cpp
    command_processor.cpp
    util/draw_extent_estimator.cpp
    util/draw.cpp
    packet_disassembler.cpp
    primitive_processor.cpp
    pipeline/render_target/cache.cpp
    shared_memory.cpp
    pipeline/texture/cache.cpp
    pipeline/shader/interpreter.cpp
    pipeline/shader/translator.cpp
    pipeline/shader/translator_disasm.cpp
)

# D3D12 backend
if(REXGLUE_USE_D3D12)
    # DXBC third-party dependency
    set(REXGPU_XENOS_DXBC_THIRDPARTY_SOURCES
        ${REXGLUE_ROOT}/thirdparty/dxbc/DXBCChecksum.cpp
    )

    # DXBC shader translation (required for D3D12)
    set(REXGPU_XENOS_DXBC_SOURCES
        pipeline/shader/dxbc.cpp
        pipeline/shader/dxbc_translator.cpp
        pipeline/shader/dxbc_translator_alu.cpp
        pipeline/shader/dxbc_translator_container.cpp
        pipeline/shader/dxbc_translator_fetch.cpp
        pipeline/shader/dxbc_translator_memexport.cpp
        pipeline/shader/dxbc_translator_om.cpp
        pipeline/shader/dxbc_translator_om_rov.cpp
        pipeline/shader/dxbc_translator_vertex_fetch.cpp
    )

    # D3D12 GPU backend
    set(REXGPU_XENOS_D3D12_SOURCES
        d3d12/graphics_system.cpp
        d3d12/command_processor.cpp
        d3d12/command_processor_bindings.cpp
        d3d12/command_processor_descriptors.cpp
        d3d12/command_processor_draw.cpp
        d3d12/command_processor_submission.cpp
        d3d12/primitive_processor.cpp
        d3d12/render_target_cache.cpp
        d3d12/render_target_cache_dump.cpp
        d3d12/render_target_cache_transfer_pipelines.cpp
        d3d12/render_target_cache_transfers.cpp
        d3d12/shader.cpp
        d3d12/shared_memory.cpp
        d3d12/texture_cache.cpp
        d3d12/texture_cache_scaled_resolve.cpp
        d3d12/deferred_command_list.cpp
        d3d12/pipeline_cache.cpp
        d3d12/pipeline_cache_dxil.cpp
        d3d12/pipeline_cache_geometry_shader.cpp
        d3d12/pipeline_cache_storage.cpp
        d3d12/zpd_query_pool.cpp
    )
endif()

if(REXGLUE_USE_D3D12)
    list(APPEND REXGPU_XENOS_SOURCES
        ${REXGPU_XENOS_DXBC_THIRDPARTY_SOURCES}
        ${REXGPU_XENOS_DXBC_SOURCES}
        ${REXGPU_XENOS_D3D12_SOURCES})
endif()

# The SPIR-V -> DXIL guest shader path (RG-GDK-032), opt-in.
if(REXGLUE_SHADER_DXIL)
    list(APPEND REXGPU_XENOS_SOURCES
        pipeline/shader/spirv.cpp
        pipeline/shader/spirv_builder.cpp
        pipeline/shader/spirv_builtin_geometry_shader.cpp
        pipeline/shader/spirv_fsi_system_constants.cpp
        pipeline/shader/spirv_shader_cache.cpp
        pipeline/shader/spirv_to_dxil_compiler.cpp
        pipeline/shader/spirv_translator.cpp
        pipeline/shader/spirv_translator_alu.cpp
        pipeline/shader/spirv_translator_fetch.cpp
        pipeline/shader/spirv_translator_fragment.cpp
        pipeline/shader/spirv_translator_memexport.cpp
        pipeline/shader/spirv_translator_operands.cpp
        pipeline/shader/spirv_translator_rb.cpp
        pipeline/shader/spirv_translator_rb_color.cpp
        pipeline/shader/spirv_translator_rb_depth_stencil.cpp
        pipeline/shader/spirv_translator_texture_bindings.cpp
        pipeline/shader/spirv_translator_vertex.cpp
        pipeline/shader/spirv_translator_vertex_fetch.cpp)
endif()

add_library(rexgpu-xenos SHARED ${REXGPU_XENOS_SOURCES})
add_library(rex::gpu-xenos ALIAS rexgpu-xenos)

set_target_properties(rexgpu-xenos PROPERTIES
    EXPORT_NAME gpu-xenos
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_include_directories(rexgpu-xenos PRIVATE
    ${REXGLUE_ROOT}/thirdparty/renderdoc
    ${REXGLUE_ROOT}  # For thirdparty/dxbc/DXBCChecksum.h include
)

target_compile_options(rexgpu-xenos PRIVATE -Wno-unused-variable)

rex_target_pch(rexgpu-xenos
    <mutex>
    <unordered_map>
    <rex/math.h>
    <rex/memory.h>
    <rex/thread/mutex.h>
    <rex/system/xmemory.h>
    <rex/graphics/xenos.h>
    <rex/graphics/registers.h>
    <rex/graphics/format/ucode.h>
    <rex/graphics/pipeline/shader/shader.h>
)

if(REXGPU_XENOS_DXBC_THIRDPARTY_SOURCES)
    set_source_files_properties(${REXGPU_XENOS_DXBC_THIRDPARTY_SOURCES}
        PROPERTIES SKIP_PRECOMPILE_HEADERS ON)
endif()

# Everything PRIVATE: the plugin has no consumers. Never link the OBJECT
# libraries (rexcore/rexui) here; rexruntime already contains those objects
# and relinking them would duplicate global state.
target_link_libraries(rexgpu-xenos PRIVATE
    rexruntime
    xxHash::xxhash
)

if(REXGLUE_SHADER_DXIL)
    target_link_libraries(rexgpu-xenos PRIVATE glslang::SPIRV rex::spirv_to_dxil)
    target_include_directories(rexgpu-xenos PRIVATE
        "${REXGLUE_GLSLANG_INCLUDE_DIR}" "${REXGLUE_DXC_INCLUDE_DIR}")
    target_compile_definitions(rexgpu-xenos PRIVATE REXGLUE_SHADER_DXIL=1)

    # The host tessellation vertex and hull shaders for the SPIR-V -> DXIL
    # path: xenia-edge's GLSL, compiled as Edge does (Vulkan 1.0, SPIR-V 1.0)
    # with the pinned glslang. Generated, never checked in.
    set(_rex_spirv_shader_dir "${CMAKE_CURRENT_SOURCE_DIR}/shaders/spirv")
    set(_rex_spirv_bytecode_dir "${CMAKE_CURRENT_BINARY_DIR}/generated/spirv_shaders")
    file(MAKE_DIRECTORY "${_rex_spirv_bytecode_dir}")
    file(GLOB _rex_spirv_shader_sources CONFIGURE_DEPENDS "${_rex_spirv_shader_dir}/*.glsl")
    set(_rex_spirv_shader_outputs "")
    foreach(_src IN LISTS _rex_spirv_shader_sources)
        get_filename_component(_name "${_src}" NAME)
        string(REGEX REPLACE "\\.glsl$" "" _id "${_name}")
        string(REPLACE "." "_" _id "${_id}")
        # The stage from the name: name.vs.glsl or name.hs.glsl.
        if(_id MATCHES "_hs$")
            set(_stage tesc)
        else()
            set(_stage vert)
        endif()
        set(_out "${_rex_spirv_bytecode_dir}/${_id}.h")
        add_custom_command(
            OUTPUT "${_out}"
            COMMAND $<TARGET_FILE:glslang-standalone> -V --target-env vulkan1.0 -S ${_stage}
                --vn ${_id} -o "${_out}" "${_src}"
            DEPENDS "${_src}" "${_rex_spirv_shader_dir}/xenos_draw.glsli" glslang-standalone
            COMMENT "SPIR-V: ${_name}"
            VERBATIM)
        list(APPEND _rex_spirv_shader_outputs "${_out}")
    endforeach()
    add_custom_target(rexgpu-spirv-shaders DEPENDS ${_rex_spirv_shader_outputs})
    add_dependencies(rexgpu-xenos rexgpu-spirv-shaders)
    target_include_directories(rexgpu-xenos PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/generated")
endif()

if(REXGLUE_USE_D3D12)
    target_link_libraries(rexgpu-xenos PRIVATE
        d3d12
        dxgi
        dxguid
    )
endif()

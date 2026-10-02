# ReXGlue 

add_executable(rexglue
    main.cpp
    ui/ui.cpp
    ui/progress.cpp
    commands/codegen_command.cpp
    commands/dlc_command.cpp
    commands/guide_bundle_command.cpp
    commands/http_client.cpp
    commands/library_art.cpp
    commands/library_art_command.cpp
    commands/init_command.cpp
    commands/test_recompiler.cpp
    commands/project_scan.cpp
)

rex_config_postfix(rexglue)

target_include_directories(rexglue
    PRIVATE
        ${REXGLUE_ROOT}/src
        ${REXGLUE_ROOT}/thirdparty/disasm
        ${REXGLUE_ROOT}/thirdparty/cli11/include
)

target_link_libraries(rexglue
    PRIVATE
        rexcodegen
)
# HTTP for dlc-catalog and dlc-find (RG-GDK-050); WIC for library-art (RG-GDK-068).
if(WIN32)
    target_link_libraries(rexglue PRIVATE winhttp windowscodecs)
endif()

rex_target_pch(rexglue <CLI/CLI.hpp>)

# Delay-load FidelityFX DLLs so rexglue can run in tool mode without them.
if(WIN32)
    if(TARGET amd_fidelityfx_dx12)
        target_link_options(rexglue PRIVATE
            "LINKER:/DELAYLOAD:$<TARGET_FILE_NAME:amd_fidelityfx_dx12>")
    endif()
    if(TARGET amd_fidelityfx_dx12)
        target_link_libraries(rexglue PRIVATE delayimp)
    endif()
endif()

add_executable(rex::rexglue ALIAS rexglue)

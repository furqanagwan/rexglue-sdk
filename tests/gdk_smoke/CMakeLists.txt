# Minimal SDK title for the Gaming Runtime deployment smoke (RG-GDK-022).
# Builds into its own directory so the output is a loose PC layout holding
# only the title and the DLLs it needs; scripts/gdk_smoke.ps1 adds the
# MicrosoftGame.config and runs it unpackaged and registered.

add_executable(gdk_smoke_title WIN32 main.cpp)
target_link_libraries(gdk_smoke_title PRIVATE rexruntime)
set_target_properties(gdk_smoke_title PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/layout")
add_custom_command(TARGET gdk_smoke_title POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:gdk_smoke_title>
        $<TARGET_FILE_DIR:gdk_smoke_title>
    COMMAND_EXPAND_LISTS
    VERBATIM)

set(_smoke_args
    -NoProfile -ExecutionPolicy Bypass
    -File ${CMAKE_SOURCE_DIR}/scripts/gdk_smoke.ps1
    -Title $<TARGET_FILE:gdk_smoke_title>
    -Rexglue $<TARGET_FILE:rexglue>)

# Unpackaged launch plus the startup error paths. Always safe to run.
add_test(NAME gdk.smoke_unpackaged COMMAND powershell ${_smoke_args})
set_tests_properties(gdk.smoke_unpackaged PROPERTIES LABELS "gdk" TIMEOUT 120)

# These add and then remove an app for the current user (a registered loose
# layout; an MSIXVC from makepkg pack /pc), so they run only when asked: set
# REXGLUE_GDK_DEPLOY_SMOKE=1. Registration needs Windows Developer Mode.
foreach(_mode Registered Installed)
    string(TOLOWER ${_mode} _name)
    add_test(NAME gdk.smoke_${_name} COMMAND powershell ${_smoke_args} -Mode ${_mode})
    set_tests_properties(gdk.smoke_${_name} PROPERTIES
        LABELS "gdk" TIMEOUT 300 SKIP_RETURN_CODE 77 RUN_SERIAL TRUE)
endforeach()

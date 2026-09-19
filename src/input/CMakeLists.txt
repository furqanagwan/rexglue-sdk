# rexinput - Input system library
# Input system and drivers for Xbox 360 controller emulation

add_library(rexinput OBJECT
    input_system.cpp
    device_assignment.cpp
    state_merge.cpp
    mnk/mnk_input_driver.cpp
    nop/nop_input_driver.cpp
)
add_library(rex::input ALIAS rexinput)

rex_target_pch(rexinput
    <mutex>
    <rex/math.h>
    <rex/string.h>
    <rex/memory.h>
    <rex/filesystem.h>
    <rex/thread.h>
    <rex/thread/mutex.h>
    <rex/ppc/context.h>
    <rex/system/kernel_state.h>
    <rex/system/xthread.h>
    <rex/ui/window.h>
    <rex/ui/presenter.h>
)

target_include_directories(rexinput PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
if(WIN32)
    target_sources(rexinput PRIVATE sdl/sdl_input_driver.cpp xinput/xinput_input_driver.cpp)
    target_sources(rexinput PRIVATE sdl/sdl_input_driver.cpp)
endif()

# GameInput is the current Microsoft input API and the one a GDK title is
# expected to use. Only its header is needed: GameInput.dll is loaded at
# runtime, so a build made with the GDK still starts where it is absent.
# The GDK edition this targets, as its folder is named. Windows is a GDK-only
# target now, so this is the one place to change when moving to a newer one.
set(REXGLUE_GDK_EDITION "260404" CACHE STRING "Microsoft GDK edition (April 2026)")
set(REXGLUE_GDK_ROOT "C:/Program Files (x86)/Microsoft GDK/${REXGLUE_GDK_EDITION}/windows"
    CACHE PATH "Microsoft GDK windows folder, for the GameInput header")
if(WIN32 AND EXISTS "${REXGLUE_GDK_ROOT}/include/GameInput.h")
    message(STATUS "rexinput: GameInput header found at ${REXGLUE_GDK_ROOT}")
    target_sources(rexinput PRIVATE gameinput/gameinput_input_driver.cpp)
    target_compile_definitions(rexinput PUBLIC REX_HAS_GAMEINPUT=1)
    target_include_directories(rexinput PRIVATE "${REXGLUE_GDK_ROOT}/include")
endif()

target_link_libraries(rexinput PUBLIC rexcore rexui)
    target_link_libraries(rexinput PUBLIC SDL3::SDL3)

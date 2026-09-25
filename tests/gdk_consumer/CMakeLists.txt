# External consumer of an installed GDK build of the SDK (RG-GDK-002).
# Standalone: configure against the install tree, never the source tree.
# See docs/gdk-toolchain.md for the commands.
cmake_minimum_required(VERSION 3.25)
project(rexglue_gdk_consumer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(rexglue CONFIG REQUIRED)
if(NOT TARGET rex::gdk)
    message(FATAL_ERROR "The installed SDK at ${rexglue_DIR} was not built with REXGLUE_USE_GDK")
endif()

add_executable(rexglue_gdk_consumer main.cpp)
target_link_libraries(rexglue_gdk_consumer PRIVATE rex::runtime)
rexglue_apply_target_settings(rexglue_gdk_consumer)

# The installed rexruntime and GPU plugin are Release only; stage both next
# to the executable (the plugin is loaded at runtime, never linked).
add_custom_command(TARGET rexglue_gdk_consumer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:rexglue_gdk_consumer>
        $<TARGET_FILE:rex::gpu-xenos>
        $<TARGET_FILE_DIR:rexglue_gdk_consumer>
    COMMAND_EXPAND_LISTS
    VERBATIM)

enable_testing()
add_test(NAME rexglue_gdk_consumer COMMAND rexglue_gdk_consumer)

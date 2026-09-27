cmake_minimum_required(VERSION 3.25)
project(rexglue_gdk_toolchain_probe LANGUAGES CXX)

if(NOT WIN32 OR NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "The GDK PC probe requires a 64-bit Windows toolchain")
endif()

if(NOT DEFINED GDK_ROOT OR GDK_ROOT STREQUAL "")
  message(FATAL_ERROR "Pass -DGDK_ROOT=<exact installed GDK edition>, for example .../Microsoft GDK/260404")
endif()

get_filename_component(GDK_ROOT "${GDK_ROOT}" ABSOLUTE)
set(gdk_include "${GDK_ROOT}/windows/include")
set(gdk_import_library "${GDK_ROOT}/windows/lib/x64/xgameruntime.lib")
if(NOT EXISTS "${gdk_include}/XGameRuntime.h" OR NOT EXISTS "${gdk_import_library}")
  message(FATAL_ERROR "GDK_ROOT lacks windows/include/XGameRuntime.h or windows/lib/x64/xgameruntime.lib: ${GDK_ROOT}")
endif()

add_executable(rexglue_gdk_toolchain_probe main.cpp)
target_compile_features(rexglue_gdk_toolchain_probe PRIVATE cxx_std_23)
target_include_directories(rexglue_gdk_toolchain_probe PRIVATE "${gdk_include}")
target_link_libraries(rexglue_gdk_toolchain_probe PRIVATE "${gdk_import_library}")

message(STATUS "GDK edition: ${GDK_ROOT}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "GDK import library: ${gdk_import_library}")

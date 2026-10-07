cmake_minimum_required(VERSION 3.25)
project(GuidePresentationConsumer LANGUAGES CXX)
find_package(rexglue CONFIG REQUIRED)
set(TEST_GUIDE_PRESENTATION "xbox360" CACHE STRING "Presentation to validate")
add_executable(guide_presentation_consumer WIN32 ../launch_settings/main.cpp)
target_compile_features(guide_presentation_consumer PRIVATE cxx_std_23)
target_link_libraries(guide_presentation_consumer PRIVATE rex::runtime)
rexglue_configure_target(guide_presentation_consumer
    GUIDE_PRESENTATION "${TEST_GUIDE_PRESENTATION}"
    GPU_PLUGINS xenos
    CVAR_DEFAULTS "gpu_plugin=xenos" "launch_menu=true" "fullscreen=false"
                  "xbox_guide=false" "gaming_runtime=off")
get_target_property(_definitions guide_presentation_consumer COMPILE_DEFINITIONS)
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/guide-selection.txt"
    CONTENT "presentation=${TEST_GUIDE_PRESENTATION}\ndefinitions=${_definitions}\n")

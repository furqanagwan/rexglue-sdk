cmake_minimum_required(VERSION 3.25)
project(LaunchSettingsConsumer LANGUAGES CXX)
find_package(rexglue CONFIG REQUIRED)
add_executable(launch_settings_consumer WIN32 main.cpp)
target_compile_features(launch_settings_consumer PRIVATE cxx_std_23)
target_link_libraries(launch_settings_consumer PRIVATE rex::runtime)
rexglue_configure_target(launch_settings_consumer GPU_PLUGINS xenos
    CVAR_DEFAULTS "gpu_plugin=xenos" "launch_menu=true" "fullscreen=false" "xbox_guide=false" "gaming_runtime=off")

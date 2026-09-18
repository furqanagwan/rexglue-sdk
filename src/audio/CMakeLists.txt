# rexaudio - Audio subsystem library
# Audio processing and XMA decoding for Xbox 360 emulation

add_library(rexaudio OBJECT
    
    audio_driver.cpp
    audio_system.cpp
    downmix.cpp
    xma_context.cpp
    xma_decoder.cpp
    xma_register_file.cpp
    ui_sound_decode.cpp
    # NOP backend (always available)
    nop/nop_audio_system.cpp
)
if(REXGLUE_PLATFORM_UWP)
    target_sources(rexaudio PRIVATE
        xaudio2/xaudio2_audio_system.cpp
        xaudio2/xaudio2_audio_driver.cpp
        nop/ui_sound_player_nop.cpp
    )
else()
    target_sources(rexaudio PRIVATE
        sdl/sdl_audio_system.cpp
        sdl/sdl_audio_driver.cpp
        sdl/ui_sound_player.cpp
    )
endif()
add_library(rex::audio ALIAS rexaudio)

rex_target_pch(rexaudio
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
)

target_include_directories(rexaudio PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(rexaudio
    PUBLIC rexcore
    PRIVATE libavcodec libavutil
)
if(NOT REXGLUE_PLATFORM_UWP)
    target_link_libraries(rexaudio PUBLIC SDL3::SDL3)
endif()

# xma_context.cpp uses _mm_shuffle_epi8 / _mm_packus_epi32 / _mm_packs_epi32 and
# conversion.h inlines pshufb byte swaps, so this target needs the same x86
# flags as the rest. Inert on MSVC; on Linux clang it is what makes them build.
rexglue_apply_target_settings(rexaudio)

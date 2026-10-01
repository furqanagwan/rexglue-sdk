# rexaudio - Audio subsystem library
# Audio processing and XMA decoding for Xbox 360 emulation

add_library(rexaudio OBJECT
    
    audio_backend.cpp
    audio_driver.cpp
    audio_system.cpp
    downmix.cpp
    ui_sound.cpp
    xma_context.cpp
    xma_decoder.cpp
    xma_register_file.cpp
    # NOP backend (always available)
    nop/nop_audio_system.cpp
)
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

# XAudio2 2.9 output (inbox XAudio2_9.dll, Windows 10 and later)
if(WIN32)
    target_sources(rexaudio PRIVATE
        xaudio2/xaudio2_audio_driver.cpp
        xaudio2/xaudio2_audio_system.cpp
        xaudio2/ui_sound_player.cpp
    )
    target_link_libraries(rexaudio PUBLIC xaudio2 ole32)
endif()

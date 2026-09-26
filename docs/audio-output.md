# Audio output

Guest audio reaches the host through an `AudioDriver` per guest render client
(`XAudioRegisterRenderDriverClient`). The backend is chosen at startup by the
`audio_backend` cvar (restart to change):

| Value | Output | Notes |
| --- | --- | --- |
| `sdl` (default) | `src/audio/sdl` | SDL3 audio stream |
| `xaudio2` | `src/audio/xaudio2` | XAudio2 2.9, Windows 10 and later (RG-GDK-019) |
| `nop` | none | Client registration fails; for tools |

SDL stays the default until XAudio2 has been compared with it on titles (see
Limitations). `rex::audio::CreateDefaultAudioSystem` applies the cvar; `ReXApp`
uses it.

## XAudio2 driver

`XAudio2AudioDriver` follows the structure of Xenia's XAudio2 driver
(xenia-edge `src/xenia/apu/xaudio2`, last changed `71dcd5004`): a thread that
holds a COM MTA scope owns the engine, a source voice takes one buffer per
guest frame, and `OnBufferEnd` releases the client semaphore that paces the
guest. It uses the Windows SDK's `xaudio2.h` and the inbox `XAudio2_9.dll`,
where Xenia hand-declares the 2.7 and 2.8 interfaces and loads
`XAudio2_8.dll`.

- **Format.** Guest frames are 256 samples of six big-endian float channels
  (fl fr fc lf bl br) at 48 kHz, one channel after another. They are converted
  with the same functions, fold, surround mix, master gain and `audio_mute` as
  the SDL output. A mono or stereo endpoint gets the stereo fold. A wider one
  gets 5.1 with the matching speaker mask, and XAudio2 maps it onto the
  endpoint.
- **Device.** The mastering voice uses the default device, channel count and
  rate. The default device ID selects Windows' virtual audio client, which
  follows default-device changes itself, and not forcing a rate lets it move to
  a 44.1 kHz endpoint
  ([XAudio 2.9 guide](https://learn.microsoft.com/windows/win32/xaudio2/xaudio2-redistributable)).
- **One release per frame.** Every frame the guest submits releases the client
  semaphore exactly once: when the device finishes playing it, or, when there
  is no usable device, on a wall clock at the frame rate (5.33 ms). A title
  therefore never waits on audio hardware (the Canary #600 freeze).
- **Losing the device.** `OnCriticalError`, a failed submit, or queued buffers
  with no `OnBufferEnd` for a second (the stall watchdog) mark the device lost.
  The frames the dead voice held move to the clock, and the service thread
  destroys the engine and immediately tries to create a new one on the current
  default device, then every two seconds while there is none.
- **Teardown.** The engine is stopped before its voices are destroyed (as in
  xenia-edge `9371e73d9`), outside the driver lock that callbacks take. Frames
  still queued when a client unregisters are not released: the client is
  going away (RG-GDK-018 covers the unregister ordering).

No redistributable is involved. The Windows SDK's `XAudio2Create` is an
inline helper that loads `xaudio2_9.dll` from System32 at run time and keeps it
loaded, so `rexruntime.dll` has no load-time XAudio2 import (checked with
`dumpbin /dependents` on the Release build). Windows 10 and later ship the DLL;
without it, engine creation fails and frames are paced by the clock.

## Tests

- `unit_tests [audio][conversion]`: an impulse on each guest channel lands in
  the right 5.1 slot and on the right stereo side with the fold weights; mix
  weights and gain per channel; clamping to [-1, 1].
- `unit_tests [audio][xaudio2]`, against the machine's XAudio2 and default
  endpoint (the device cases skip without one):
  - frames are played and paced, with one release each;
  - with no device, frames are released on the clock;
  - a simulated critical error releases the voice's frames and reopens the device;
  - a silently stopped voice is caught by the stall watchdog;
  - a device that appears later is picked up;
  - more frames than slots still release once each;
  - 25 create, submit and teardown cycles, plus two clients at once;
  - `audio_backend` selection, and a guest client registered, fed from guest
    memory and unregistered.

## Limitations

- No title has been run on the XAudio2 output, so the default stays SDL.
- Unplugging and reconnecting a real device, and switching between 48 kHz and
  44.1-kHz-only endpoints, were not exercised. The loss paths are covered by
  simulated critical errors and stalls. This machine has one active endpoint
  (NVIDIA HDMI audio on the monitor).
- The 5.1 speaker mapping on a real surround endpoint was not checked by ear;
  the conversion tests cover the channel order handed to XAudio2.
- Output is not resampled to the guest clock (Xenia's `SetFrequencyRatio` from
  the guest time scalar), matching the SDL output. Canary's audio pacing
  (`6e5b8324f`, oreyg, merged into Edge) is not ported.
- SDL audio stays built: it is the default, and SDL itself is removed only by
  RG-GDK-022 once every SDL consumer has a validated replacement.

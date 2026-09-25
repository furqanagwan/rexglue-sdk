# GameInput driver (RG-GDK-020)

GDK builds (`win-amd64-gdk`, see [GDK toolchain](gdk-toolchain.md)) include a native GameInput gamepad driver. It is **opt-in**: `input_backend` still defaults to `sdl`, and SDL and XInput stay in place until the driver reaches parity (issue acceptance: no dependency removal before parity).

```toml
[Input]
input_backend = "gameinput"
```

`input_backend = "gameinput"` falls back to SDL, with a warning, in a non-GDK build or when GameInput cannot start.

## Runtime and deployment

| Item | Pinned / observed |
| --- | --- |
| Header | `260404/windows/include/GameInput.h` (C interface, `IGameInput` IID `11BE2A7E-4254-445A-9C09-FFC40F006918`) |
| Runtime entry | `GameInput.dll` (`GameInputCreate`), loaded at startup with `LoadLibrary`, not linked |
| Observed runtime | inbox `GameInput.dll` 0.2309.26100.9502, `GameInputRedist.dll` 3.5.270.0 |
| Redistributable | GameInput redistributable (`GameInputRedist.msi`) from Microsoft; not copied into this repository |

Because the DLL is loaded at runtime, a machine without GameInput still starts. The log names the failure and the fix: `GameInput.dll not found`, no `GameInputCreate` export, or `GameInputCreate failed (0x…)` with a pointer to the redistributable. The input system then uses SDL.

`GameInput.dll` stays loaded for the process lifetime. The runtime keeps worker threads after the last `IGameInput` release, and unloading the DLL under them crashes.

## Guest-facing behavior

The guest-facing state lives in `GamepadDevices` (`include/rex/input/gameinput/gamepad_devices.h`). It holds no GameInput types, so these rules are unit-tested without the GDK or devices:

* **Slots:** each connection gets a fresh `DeviceId` (`0x4749…`). `InputSystem` assigns guest users as it does for every driver: in connection order, a survivor keeps its user when another pad is unplugged, and a new or reconnected pad takes the lowest free user. After a disconnect nothing from that pad reaches the guest: the user reports `ERROR_DEVICE_NOT_CONNECTED` until a pad arrives.
* **Packet numbers:** start at 1 and advance once per state change the guest can see. Several host updates between polls count once, and a focus change counts.
* **Focus:** while the input system reports inactive (window unfocused, overlay open), the pad reads untouched. Held buttons return with focus, and keystrokes send key-ups on focus loss and key-downs on return.
* **Rumble:** holds until the guest changes it, as in XInput. It stops on focus loss and resumes on return; a request made while unfocused is kept and applied on return. It is stopped on disconnect and never carried into a reconnection. The left motor drives GameInput's low-frequency motor, the right the high-frequency one, and trigger motors stay off.
* **Dead zones:** none applied. GameInput gamepad readings have none, and titles apply their own, as with XInput. Sticks map -1..1 to -32768..32767; triggers 0..1 to 0..255.
* **Buttons:** the 14 GameInput gamepad buttons map one-to-one to XInput's. Guide comes from `RegisterGuideButtonCallback` and is reported only with `guide_button = true`, as in the SDL driver.
* **Keystrokes:** `XInputGetKeystroke` events come from `KeystrokeSynthesizer`, which is now shared with the SDL driver (same order, thresholds and repeat).
* **Capabilities:** a standard gamepad (type 1, subtype 1), plus `X_INPUT_CAPS_WIRELESS` from `GameInputDeviceWireless`.

## Tests

* `unit_tests [input][gameinput]` (all builds): four pads to four users; unplug keeps the others; same and different pad reconnecting; no phantom input; packet numbers; unfocused pad; rumble hold, focus stop and resume; no rumble after reconnect; keystroke release on focus loss; capabilities.
* `unit_tests [keystroke]` (all builds): edge order, repeat timing, analog thresholds, inactive release.
* `unit_tests [gdk][gameinput]` (GDK builds): stick, trigger and button mapping edges including NaN and clamping, rumble conversion, and driver setup against the installed runtime. That test enumerated and read the one pad connected on the development machine.
* The existing `[input]` assignment and merge tests pass unchanged, with SDL now on the shared synthesizer.

## Not established

* Hardware matrix: behavior is proven through `GamepadDevices` and one connected pad's enumeration and reading. Four physical pads, hot-plug, wireless, rumble on hardware and focus loss in a running title were not exercised on devices.
* Instruments: GameInput reports no XInput subtype, so guitars, drums and wheels read as gamepads (subtype 1). Canary #1230 (subtype override, whammy neutral) is still an open SDL PR and is not adopted; guitar tests need guitar hardware.
* A packaged title with the runtime missing: the missing-runtime path is implemented and logged, but not exercised on a machine without GameInput.
* An XInput-versus-GameInput side-by-side on the same device.

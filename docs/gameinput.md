# GameInput driver (RG-GDK-020)

GDK builds (`win-amd64-gdk`, see [GDK toolchain](gdk-toolchain.md)) include a native GameInput gamepad driver. It is the **default** in GDK builds (owner decision, 2026-09-28); builds without the GDK use XInput. SDL3, the earlier fallback, was removed (RG-GDK-033); `input_backend = "sdl"` in an old config starts the default with a warning.

```toml
[Input]
input_backend = "gameinput"
```

`input_backend = "gameinput"` falls back to XInput, with a warning, in a non-GDK build or when GameInput cannot start.

## Runtime and deployment

| Item | Pinned / observed |
| --- | --- |
| Header | `260404/windows/include/GameInput.h` (C interface, `IGameInput` IID `11BE2A7E-4254-445A-9C09-FFC40F006918`) |
| Runtime entry | `GameInput.dll` (`GameInputCreate`), loaded at startup with `LoadLibrary`, not linked |
| Observed runtime | inbox `GameInput.dll` 0.2309.26100.9502, `GameInputRedist.dll` 3.5.270.0 |
| Redistributable | GameInput redistributable (`GameInputRedist.msi`) from Microsoft; not copied into this repository |

Because the DLL is loaded at runtime, a machine without GameInput still starts. The log names the failure and the fix: `GameInput.dll not found`, no `GameInputCreate` export, or `GameInputCreate failed (0x…)` with a pointer to the redistributable. The input system then uses XInput.

`GameInput.dll` stays loaded for the process lifetime. The runtime keeps worker threads after the last `IGameInput` release, and unloading the DLL under them crashes.

## Guest-facing behavior

The guest-facing state lives in `GamepadDevices` (`include/rex/input/gameinput/gamepad_devices.h`). It holds no GameInput types, so these rules are unit-tested without the GDK or devices:

* **Slots:** each connection gets a fresh `DeviceId` (`0x4749…`). `InputSystem` assigns guest users as it does for every driver: in connection order, a survivor keeps its user when another pad is unplugged, and a new or reconnected pad takes the lowest free user. After a disconnect nothing from that pad reaches the guest: the user reports `ERROR_DEVICE_NOT_CONNECTED` until a pad arrives.
* **Packet numbers:** start at 1 and advance once per state change the guest can see. Several host updates between polls count once, and a focus change counts.
* **Focus:** while the input system reports inactive (window unfocused, overlay open), the pad reads untouched. Held buttons return with focus, and keystrokes send key-ups on focus loss and key-downs on return.
* **Rumble:** holds until the guest changes it, as in XInput. It stops on focus loss and resumes on return; a request made while unfocused is kept and applied on return. It is stopped on disconnect and never carried into a reconnection. The left motor drives GameInput's low-frequency motor, the right the high-frequency one, and trigger motors stay off.
* **Dead zones:** none by default. GameInput gamepad readings have none, and titles apply their own, as with XInput. Sticks map -1..1 to -32768..32767; triggers 0..1 to 0..255. `left_stick_deadzone_percentage` and `right_stick_deadzone_percentage` (0 to 1, default 0) add one in the shared input layer, for every backend. The scale matches Xenia Canary's cvars of the same name, so 0.12 is about XInput's 7849.
* **Buttons:** the 14 GameInput gamepad buttons map one-to-one to XInput's. There is no guide button: it is not in `GameInputGamepadState`, and `RegisterGuideButtonCallback` is not used. On the installed runtime (inbox `GameInput.dll` 0.2309.26100.9502 forwarding to GameInputRedist 3.5.270) that call wrote its callback token through the `context` argument, over the driver's vtable pointer. The first virtual call after startup (ReXApp's `AttachWindow`) then crashed. Found running Quantum of Solace on 2026-09-27. Capabilities no longer advertise a guide button, even with `guide_button = true`.
* **Keystrokes:** `XInputGetKeystroke` events come from `KeystrokeSynthesizer`, which the removed SDL driver shared (same order, thresholds and repeat).
* **Capabilities:** a gamepad (type 1) with every input, plus `X_INPUT_CAPS_WIRELESS` from `GameInputDeviceWireless`. The subtype comes from the device's `supportedInput`: a racing wheel is `XINPUT_DEVSUBTYPE_WHEEL` (2), an arcade stick 3 and a flight stick 4, even when it also offers the gamepad kind; anything else is a gamepad (1). A device without both body motors in `supportedRumbleMotors` reports zero vibration speeds, as XInput does. The connect log line records the kinds, subtype, motors and connection.
* **Vibration switch:** `vibration = false` (default true) stops every backend's motors in the shared layer. `SetState` still succeeds, so titles see a connected pad.
* **Dialogs:** while a XAM dialog (message box, keyboard, device selector) is open, the guest reads an untouched pad and no keystrokes. Buttons held as it closes stay hidden until released, and keystrokes made during it are discarded, so the press that dismissed it does not also act in the game.
* **Hot-plug:** a guest user connecting or disconnecting sends `XN_SYS_INPUTDEVICESCHANGED` (0x12), which titles use to re-read capabilities. The first poll after startup sends it once.

## Bluetooth pads and battery (RG-GDK-047)

Measured on 2026-10-01 with an ASUS ROG Raikiri II, which has three modes:

| Mode | IDs | GameInput | XInput | Battery source |
| --- | --- | --- | --- | --- |
| 2.4 GHz dongle | 0B05:1C92 | Xbox 360 family, wired, battery not present | wired, full | none: the dongle presents the pad as a wired 360 pad |
| Bluetooth LE | 0B05:1C93 | absent from the blocking enumeration; arrives about 3 to 12 s later as an Xbox One pad, reported **wired**, battery not present | wireless (`xinputhid`), battery type disconnected | GATT Battery Service, 82 to 83% (matches the pad) |
| USB cable | not tested | | | |

Windows.Gaming.Input reported the Bluetooth pad's battery as 100 of 1000 mWh (10%) while its Battery Service said 83%, so it is not used.

* **XInput supplement:** beside GameInput, an XInput driver lists only the pads GameInput does not serve. It matches pads by USB vendor and product ID, read with `XInputGetCapabilitiesEx` (`xinput1_4.dll` ordinal 108). This covers the Bluetooth pad's first seconds. When GameInput then connects it, the XInput slot drops out and the guest user keeps its pad. In dongle mode one pad is listed, not two. Without ordinal 108 the supplement lists nothing.
* **Battery:** `InputDriver::GetDeviceBattery` and `InputSystem::GetBattery` report whether the pad is wireless, its level (0 to 100, or unknown) and whether it is charging.
  * GameInput uses `IGameInputDevice::GetBatteryState`.
  * XInput uses `XInputGetBatteryInformation`, with its four levels reported as 5, 30, 60 and 100.
  * When neither has a level, `BleBatteryMonitor` (`src/input/ble_battery.cpp`) reads the Battery Level characteristic (0x2A19) of a connected Bluetooth LE device with the same IDs. A pad found that way is wireless.
  * Reads from the device run on a detached worker thread, refreshed every 60 s. A sleeping device's read took 15 s to time out, and a connected one's took 49 ms. Callers get the last value.
* **Guide:** shows player 1's battery as the console's Little, Low, Medium and High frames, and hides it for wired pads or an unknown level (see [Xbox guide](xbox-guide.md)).

Not established: the Raikiri's level in dongle or cable mode. ASUS's vendor HID collections (usage pages FF13, FF03 and FFC3 on interface 4) send nothing unprompted, and their request format is not public. Guessed commands are not sent to the pad. Charging state over Bluetooth is not reported either: the Battery Service carries only the level. An Xbox Wireless Adapter pad and a 360 wireless receiver pad were not available to test GameInput's and XInput's own battery paths.

## Tests

* `unit_tests [input][gameinput]` (all builds): four pads to four users; unplug keeps the others; same and different pad reconnecting; no phantom input; packet numbers; unfocused pad; rumble hold, focus stop and resume; no rumble after reconnect; keystroke release on focus loss; capabilities.
* `unit_tests [keystroke]` (all builds): edge order, repeat timing, analog thresholds, inactive release.
* `unit_tests [gdk][gameinput]` (GDK builds): stick, trigger and button mapping edges including NaN and clamping, rumble conversion, device kinds to subtypes, motors to vibration capability, and driver setup against the installed runtime. That test enumerated and read the one pad connected on the development machine and checked its capabilities carry the identified subtype.
* `unit_tests [deadzone],[vibration],[ui_block],[hotplug]` (all builds): the shared layer every backend goes through.
* `unit_tests [input]` "GetBattery reports the power of the user's pad" (all builds): battery routed to the user's pad, and none for an absent pad or a driver that cannot tell.
* The existing `[input]` assignment and merge tests pass unchanged.

## Not established

* Hardware matrix: behavior is proven through `GamepadDevices` and one connected pad's enumeration and reading. Four physical pads, hot-plug, wireless, rumble on hardware and focus loss in a running title were not exercised on devices.
* Instruments: GameInput identifies wheels and arcade and flight sticks, but not Xbox 360 guitars, drums or dance pads, which read as gamepads (subtype 1). The removed SDL driver guessed those from the device name; XInput reports its own subtype. No wheel or stick was connected to confirm the kinds a real device reports. Canary #1230 (subtype override, whammy neutral) is still an open SDL PR and is not adopted; guitar tests need guitar hardware.
* A packaged title with the runtime missing: the missing-runtime path is implemented and logged, but not exercised on a machine without GameInput.
* An XInput-versus-GameInput side-by-side on the same device.

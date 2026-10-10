# Virtual key: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/virtual_key.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L18)

```text
// Windows and Xbox 360 / XInput virtual key enumeration.
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L19)

```text
// This is what platform-specific keys should be translated to, for both HID
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L20)

```text
// keystroke emulation and Xenia-internal UI events. On Windows, the translation
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L21)

```text
// is a simple cast.
```

## Source note 5, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L22)

```text
// This is uint16_t as it's WPARAM (which was 16-bit back in Win16 days, where
```

## Source note 6, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L23)

```text
// virtual key codes were added), and XINPUT_KEYSTROKE stores the virtual key as
```

## Source note 7, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L24)

```text
// a WORD. In some cases (see kPacket), bits above 16 may be used as well, but
```

## Source note 8, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L25)

```text
// VK_ on Windows are defined up to 0xFF (0xFE not counting the reserved 0xFF)
```

## Source note 9, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L26)

```text
// as of Windows SDK 10.0.19041.0, and XInput virtual key codes are 16-bit.
```

## Source note 10, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L27)

```text
// Base virtual key codes as of _WIN32_WINNT 0x0500 (Windows 2000, which the
```

## Source note 11, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L28)

```text
// Xbox 360's kernel is based on), virtual key codes added later are marked
```

## Source note 12, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L29)

```text
// explicitly as such.
```

## Source note 13, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L31)

```text
// Not a valid key - MapVirtualKey returns zero when there is no translation.
```

## Source note 14, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L36)

```text
// Control-break.
```

## Source note 15, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L37)

```text
// Not contiguous with kLButton and kRButton.
```

## Source note 16, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L39)

```text
// Not contiguous with kLButton and kRButton.
```

## Source note 17, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L40)

```text
// Not contiguous with kLButton and kRButton.
```

## Source note 18, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L42)

```text
// Backspace.
```

## Source note 19, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L46)

```text
// Enter.
```

## Source note 20, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L49)

```text
// Ctrl.
```

## Source note 21, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L50)

```text
// Alt.
```

## Source note 22, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L52)

```text
// Caps Lock.
```

## Source note 23, line 55

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L55)

```text
// Old name.
```

## Source note 24, line 72

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L72)

```text
// Page Up.
```

## Source note 25, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L73)

```text
// Page Down.
```

## Source note 26, line 88

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L88)

```text
// Same as ASCII '0' - '9'.
```

## Source note 27, line 100

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L100)

```text
// Same as ASCII 'A' - 'Z'.
```

## Source note 28, line 175

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L175)

```text
// VK_NAVIGATION_* added in _WIN32_WINNT 0x0604, but marked as reserved in
```

## Source note 29, line 176

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L176)

```text
// WinUser.h and not documented on MSDN.
```

## Source note 30, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L189)

```text
// NEC PC-9800 keyboard.
```

## Source note 31, line 190

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L190)

```text
// '=' key on the numpad.
```

## Source note 32, line 192

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L192)

```text
// Fujitsu/OASYS keyboard.
```

## Source note 33, line 193

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L193)

```text
// 'Dictionary' key.
```

## Source note 34, line 194

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L194)

```text
// 'Unregister word' key.
```

## Source note 35, line 195

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L195)

```text
// 'Register word' key.
```

## Source note 36, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L196)

```text
// 'Left OYAYUBI' key.
```

## Source note 37, line 197

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L197)

```text
// 'Right OYAYUBI' key.
```

## Source note 38, line 199

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L199)

```text
// Left and right Alt, Ctrl and Shift virtual keys.
```

## Source note 39, line 200

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L200)

```text
// On Windows (from WinUser.h):
```

## Source note 40, line 201

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L201)

```text
// "Used only as parameters to GetAsyncKeyState() and GetKeyState().
```

## Source note 41, line 202

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L202)

```text
//  No other API or message will distinguish left and right keys in this way."
```

## Source note 42, line 230

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L230)

```text
// ';:' for the US.
```

## Source note 43, line 231

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L231)

```text
// '+' for any country.
```

## Source note 44, line 232

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L232)

```text
// ',' for any country.
```

## Source note 45, line 233

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L233)

```text
// '-' for any country.
```

## Source note 46, line 234

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L234)

```text
// '.' for any country.
```

## Source note 47, line 235

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L235)

```text
// '/?' for the US.
```

## Source note 48, line 236

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L236)

```text
// '`~' for the US.
```

## Source note 49, line 238

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L238)

```text
// VK_GAMEPAD_* (since _WIN32_WINNT 0x0604) virtual key codes are marked as
```

## Source note 50, line 239

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L239)

```text
// reserved in WinUser.h and are mostly not documented on MSDN (with the
```

## Source note 51, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L240)

```text
// exception of the Xbox Device Portal Remote Input REST API in the "UWP on
```

## Source note 52, line 241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L241)

```text
// Xbox One" section).
```

## Source note 53, line 242

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L242)

```text
// Xenia uses VK_PAD_* (kXInputPad*) for HID emulation internally instead
```

## Source note 54, line 243

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L243)

```text
// because XInput is the API used for the Xbox 360 controller.
```

## Source note 55, line 244

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L244)

```text
// To avoid confusion between VK_GAMEPAD_* and VK_PAD_*, here they are
```

## Source note 56, line 245

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L245)

```text
// prefixed with kXboxOne and kXInput respectively.
```

## Source note 57, line 271

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L271)

```text
// '[{' for the US.
```

## Source note 58, line 272

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L272)

```text
// '\|' for the US.
```

## Source note 59, line 273

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L273)

```text
// ']}' for the US.
```

## Source note 60, line 274

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L274)

```text
// ''"' for the US.
```

## Source note 61, line 277

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L277)

```text
// 'AX' key on the Japanese AX keyboard.
```

## Source note 62, line 278

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L278)

```text
// "<>" or "\|" on the RT 102-key keyboard.
```

## Source note 63, line 279

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L279)

```text
// Help key on the Olivetti keyboard (ICO).
```

## Source note 64, line 280

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L280)

```text
// 00 key on the ICO.
```

## Source note 65, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L286)

```text
// From MSDN:
```

## Source note 66, line 287

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L287)

```text
// "Used to pass Unicode characters as if they were keystrokes. The VK_PACKET
```

## Source note 67, line 288

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L288)

```text
//  key is the low word of a 32-bit Virtual Key value used for non-keyboard
```

## Source note 68, line 289

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L289)

```text
//  input methods."
```

## Source note 69, line 292

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L292)

```text
// Nokia/Ericsson.
```

## Source note 70, line 317

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L317)

```text
// VK_PAD_* from XInput.h for XInputGetKeystroke. kXInput prefix added to
```

## Source note 71, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L318)

```text
// distinguish from VK_GAMEPAD_*, added much later for the Xbox One
```

## Source note 72, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L319)

```text
// controller.
```

## Source note 73, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/virtual_key.h#L325)

```text
// RShoulder before LShoulder, not a typo.
```

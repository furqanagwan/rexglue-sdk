# Xma decoder: audio source notes

This record preserves technical and API notes moved from `src/audio/xma_decoder.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L27)

```text
// extern "C"
```

## Source note 2, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L31)

```text
// As with normal Microsoft, there are like twelve different ways to access
```

## Source note 3, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L32)

```text
// the audio APIs. Early games use XMA*() methods almost exclusively to touch
```

## Source note 4, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L33)

```text
// decoders. Later games use XAudio*() and direct memory writes to the XMA
```

## Source note 5, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L34)

```text
// structures (as opposed to the XMA* calls), meaning that we have to support
```

## Source note 6, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L35)

```text
// both.
```

## Source note 7, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L37)

```text
// The XMA*() functions just manipulate the audio system in the guest context
```

## Source note 8, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L38)

```text
// and let the normal XmaDecoder handling take it, to prevent duplicate
```

## Source note 9, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L39)

```text
// implementations. They can be found in xboxkrnl_audio_xma.cc
```

## Source note 10, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L41)

```text
// XMA details:
```

## Source note 11, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L42)

```text
// https://devel.nuclex.org/external/svn/directx/trunk/include/xma2defs.h
```

## Source note 12, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L43)

```text
// https://github.com/gdawg/fsbext/blob/master/src/xma_header.h
```

## Source note 13, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L45)

```text
// XAudio2 uses XMA under the covers, and seems to map with the same
```

## Source note 14, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L46)

```text
// restrictions of frame/subframe/etc:
```

## Source note 15, line 47

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L47)

```text
// https://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.xaudio2.xaudio2_buffer(v=vs.85).aspx
```

## Source note 16, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L49)

```text
// XMA contexts are 64b in size and tight bitfields. They are in physical
```

## Source note 17, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L50)

```text
// memory not usually available to games. Games will use MmMapIoSpace to get
```

## Source note 18, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L51)

```text
// the 64b pointer in user memory so they can party on it. If the game doesn't
```

## Source note 19, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L52)

```text
// do this, it's likely they are either passing the context to XAudio or
```

## Source note 20, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L53)

```text
// using the XMA* functions.
```

## Source note 21, line 90

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L90)

```text
// Setup ffmpeg logging callback
```

## Source note 22, line 93

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L93)

```text
// Register APU/XMA MMIO handlers
```

## Source note 23, line 94

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L94)

```text
// XMA registers are at 0x7FEA0000-0x7FEAFFFF
```

## Source note 24, line 96

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L96)

```text
// base address
```

## Source note 25, line 98

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L98)

```text
// size (64KB)
```

## Source note 26, line 99

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L99)

```text
// context (XmaDecoder*)
```

## Source note 27, line 104

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L104)

```text
// Setup XMA context data.
```

## Source note 28, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L105)

```text
// The Xbox 360 kernel allocates the contexts with X_PAGE_NOCACHE |
```

## Source note 29, line 106

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L106)

```text
// X_PAGE_READWRITE and writes MmGetPhysicalAddress for the address to the
```

## Source note 30, line 107

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L107)

```text
// register.
```

## Source note 31, line 114

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L114)

```text
// Setup XMA contexts.
```

## Source note 32, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L142)

```text
// Okay, let's loop through XMA contexts to find ones we need to decode!
```

## Source note 33, line 162

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L162)

```text
// No work done this iteration, block until signaled.
```

## Source note 34, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L182)

```text
// Wait up to 2 seconds for worker thread to exit gracefully.
```

## Source note 35, line 209

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L209)

```text
// Out of contexts.
```

## Source note 36, line 246

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L246)

```text
// 0606h (1818h) is rotating context processing # set to hardware ID of
```

## Source note 37, line 247

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L247)

```text
// context being processed.
```

## Source note 38, line 248

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L248)

```text
// If bit 200h is set, the locking code will possibly collide on hardware
```

## Source note 39, line 249

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L249)

```text
// IDs and error out, so we should never set it (I think?).
```

## Source note 40, line 252

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L252)

```text
// To prevent games from seeing a stuck XMA context, return a rotating
```

## Source note 41, line 253

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L253)

```text
// number.
```

## Source note 42, line 281

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L281)

```text
// Context kick command.
```

## Source note 43, line 282

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L282)

```text
// This will kick off the given hardware contexts.
```

## Source note 44, line 283

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L283)

```text
// Basically, this kicks the SPU and says "hey, decode that audio!"
```

## Source note 45, line 286

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L286)

```text
// The context ID is a bit in the range of the entire context array.
```

## Source note 46, line 296

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L296)

```text
// Decode inline. waiting on the worker sweep stalls the realtime
```

## Source note 47, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L297)

```text
// audio thread 50-100ms during kick bursts.
```

## Source note 48, line 309

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L309)

```text
// Context lock command.
```

## Source note 49, line 310

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L310)

```text
// This requests a lock by flagging the context.
```

## Source note 50, line 318

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L318)

```text
// [XMA fix] Added Block(false) after Disable(). Without this, the game
```

## Source note 51, line 319

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L319)

```text
// could call XMADisableContext and start modifying the context struct
```

## Source note 52, line 320

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L320)

```text
// while a decode was still in progress on the worker thread. Block()
```

## Source note 53, line 321

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L321)

```text
// waits for the context mutex to be free (poll=false means wait, not spin).
```

## Source note 54, line 325

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L325)

```text
// Signal the decoder thread to start processing.
```

## Source note 55, line 326

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L326)

```text
// work_event_->Set();
```

## Source note 56, line 328

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L328)

```text
// Context clear command.
```

## Source note 57, line 329

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L329)

```text
// This will reset the given hardware contexts.
```

## Source note 58, line 339

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L339)

```text
// 0601h (1804h) is written to with 0x02000000 and 0x03000000 around a lock
```

## Source note 59, line 343

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L343)

```text
// Stored above; nothing else to do. Logged, it was hundreds of lines a
```

## Source note 60, line 344

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/audio/xma_decoder.cpp#L344)

```text
// second in Blood Stone.
```

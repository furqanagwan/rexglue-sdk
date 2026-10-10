# Mmio handler: system source notes

This record preserves technical and API notes moved from `include/rex/system/mmio_handler.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L41)

```text
// NOTE: only one can exist at a time!
```

## Source note 2, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L51)

```text
// access_violation_callback is called with global_critical_region locked once
```

## Source note 3, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L52)

```text
// on the thread, so if multiple threads trigger an access violation in the
```

## Source note 4, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L53)

```text
// same page, the callback will be called only once.
```

## Source note 5, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L62)

```text
// Called with the faulting host PC when a guest access violation reaches no
```

## Source note 6, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L63)

```text
// handler, just before it is passed on and the process fails. Diagnostic
```

## Source note 7, line 64

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L64)

```text
// only: it runs on the faulting thread and must not take locks.
```

## Source note 8, line 108

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L108)

```text
// Matches the Xn/Wn register number for 0 reads and ignored writes in many
```

## Source note 9, line 109

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L109)

```text
// usage cases.
```

## Source note 10, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L112)

```text
// Matches the actual register number encoding for an SP base in AArch64
```

## Source note 11, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L113)

```text
// load and store instructions.
```

## Source note 12, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L121)

```text
// Inidicates this is a load (or conversely a store).
```

## Source note 13, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L123)

```text
// Indicates the memory must be swapped.
```

## Source note 14, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L125)

```text
// Source (for store) or target (for load) register.
```

## Source note 15, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L126)

```text
// For x86-64:
```

## Source note 16, line 127

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L127)

```text
// AX  CX  DX  BX  SP  BP  SI  DI   // REX.R=0
```

## Source note 17, line 128

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L128)

```text
// R8  R9  R10 R11 R12 R13 R14 R15  // REX.R=1
```

## Source note 18, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L129)

```text
// For AArch64:
```

## Source note 19, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L130)

```text
// - kArm64ValueRegX0 + [0...30]: Xn (Wn for 32 bits - upper 32 bits of Xn
```

## Source note 20, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L131)

```text
//   are zeroed on Wn write).
```

## Source note 21, line 132

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L132)

```text
// - kArm64ValueRegZero: Zero constant for register read, ignored register
```

## Source note 22, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L133)

```text
//   write (though memory must still be accessed - a MMIO load may have side
```

## Source note 23, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L134)

```text
//   effects even if the result is discarded).
```

## Source note 24, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L135)

```text
// - kArm64ValueRegV0 + [0...31]: Vn (Sn for 32 bits).
```

## Source note 25, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L137)

```text
// [base + (index * scale) + displacement]
```

## Source note 26, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L139)

```text
// On AArch64, if mem_base_reg is kArm64MemBaseRegSp, the base register is
```

## Source note 27, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L140)

```text
// SP, not Xn.
```

## Source note 28, line 142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L142)

```text
// For AArch64 pre- and post-indexing. In case of a load, the base register
```

## Source note 29, line 143

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L143)

```text
// is written back after the loaded data is written to the register,
```

## Source note 30, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/mmio_handler.h#L144)

```text
// overwriting the value register if it's the same.
```

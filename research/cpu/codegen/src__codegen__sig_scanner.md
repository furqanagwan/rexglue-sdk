# Sig scanner: codegen source notes

This record preserves technical and API notes moved from `src/codegen/sig_scanner.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L27)

```text
// Scan all executable sections
```

## Source note 2, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L28)

```text
// TODO(tomc): maybe i wanna scan other sections...
```

## Source note 3, line 66

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L66)

```text
// Find section containing this range
```

## Source note 4, line 83

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L83)

```text
// Scan through the range (4-byte aligned for PPC)
```

## Source note 5, line 111

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L111)

```text
// __savegprlr_14 pattern:
```

## Source note 6, line 112

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L112)

```text
// The save helpers are a sequence of stw rN, offset(r12) instructions
```

## Source note 7, line 113

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L113)

```text
// followed by stw r0, 8(r12) and blr
```

## Source note 8, line 115

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L115)

```text
// stw rN, offset(r12) = 0x9180XXXX where XX encodes the offset
```

## Source note 9, line 116

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L116)

```text
// For r14: stw r14, -0x48(r12) = 0x91CBFFB8
```

## Source note 10, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L118)

```text
// We look for the first instruction of the sequence.
```

## Source note 11, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L119)

```text
// stw r14, -0x48(r12) = 0x91CBFFB8
```

## Source note 12, line 123

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L123)

```text
// stw r14, -0x48(r12)
```

## Source note 13, line 124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L124)

```text
// Exact match
```

## Source note 14, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L125)

```text
// Entry at pattern start
```

## Source note 15, line 126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L126)

```text
// Size computed from stride
```

## Source note 16, line 129

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L129)

```text
// __restgprlr_14 pattern:
```

## Source note 17, line 130

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L130)

```text
// lwz rN, offset(r12) followed by eventually mtlr r0 and blr
```

## Source note 18, line 131

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L131)

```text
// lwz r14, -0x48(r12) = 0x81CBFFB8
```

## Source note 19, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L134)

```text
// lwz r14, -0x48(r12)
```

## Source note 20, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L135)

```text
// Exact match
```

## Source note 21, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L139)

```text
// __savefpr_14 pattern:
```

## Source note 22, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L140)

```text
// stfd frN, offset(r12)
```

## Source note 23, line 141

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L141)

```text
// stfd fr14, -0x98(r12) = 0xD9CCFF68
```

## Source note 24, line 144

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L144)

```text
// stfd fr14, -0x98(r12)
```

## Source note 25, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L149)

```text
// __restfpr_14 pattern:
```

## Source note 26, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L150)

```text
// lfd frN, offset(r12)
```

## Source note 27, line 151

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L151)

```text
// lfd fr14, -0x98(r12) = 0xC9CCFF68
```

## Source note 28, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L154)

```text
// lfd fr14, -0x98(r12)
```

## Source note 29, line 163

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/src/codegen/sig_scanner.cpp#L163)

```text
// TODO(tomc): mayhaps have signatures memset, memmove, memcpy, strcmp patterns
```

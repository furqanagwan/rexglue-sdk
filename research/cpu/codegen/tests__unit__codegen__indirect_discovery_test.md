# Indirect discovery test: codegen source notes

This record preserves technical and API notes moved from `tests/unit/codegen/indirect_discovery_test.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `b82fed2` (the builder rename on main).

## Source note 1, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L38)

```text
// b / bl from `from` to `to`.
```

## Source note 2, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L45)

```text
// beq cr0 from `from` to `to`.
```

## Source note 3, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L52)

```text
// `pointer`, when set, is held by a data section as a method table would.
```

## Source note 4, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L73)

```text
// Runs the full analysis on `words` at kBase, with the given entries known
```

## Source note 5, line 74

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L74)

```text
// from config (as pdata or a title hint would give them).
```

## Source note 6, line 80

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L80)

```text
// `sized` entries get a declared size, as a function table entry gives one.
```

## Source note 7, line 81

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L81)

```text
// `pointer`, when set, is held in data.
```

## Source note 8, line 117

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L117)

```text
// 0x00 entry.
```

## Source note 9, line 118

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L118)

```text
// 0x04 Y: li r3,7; blr                 (a gap function)
```

## Source note 10, line 119

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L119)

```text
// 0x0C T: addi r3,r3,-4; b Y           (a thunk tail-calling Y)
```

## Source note 11, line 120

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L120)

```text
// 0x14 F: li r3,1; blr                 (only ever reached indirectly)
```

## Source note 12, line 121

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L121)

```text
// Gap fill cuts T..F as one segment, since Y isn't known when it splits;
```

## Source note 13, line 122

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L122)

```text
// discovery ends T at its `b`, and F used to be claimed by no one.
```

## Source note 14, line 133

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L133)

```text
// 0x00 E: bl T; blr                   (8 bytes, from config)
```

## Source note 15, line 134

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L134)

```text
// 0x08 T: addi r3,r3,-4; b Y           (found by E's call, before gap fill)
```

## Source note 16, line 135

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L135)

```text
// 0x10 F: li r3,1; blr                 (reached only by G's tail branch)
```

## Source note 17, line 136

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L136)

```text
// 0x18 G: b F                          (an entry from config)
```

## Source note 18, line 137

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L137)

```text
// 0x1C Y: li r3,7; blr
```

## Source note 19, line 138

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L138)

```text
// Gap fill cuts T..F as one segment starting at T, a known entry, so the
```

## Source note 20, line 139

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L139)

```text
// whole segment used to be skipped (Blood Stone 0x8222D588, 007 Legends
```

## Source note 21, line 140

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L140)

```text
// 0x826D3F38).
```

## Source note 22, line 147

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L147)

```text
// T follows its branch to Y, not yet known, as its own code.
```

## Source note 23, line 154

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L154)

```text
// 0x00 E: cmpwi r3,0; beq 0x0C; blr; bctr   (16 bytes, as .pdata gives)
```

## Source note 24, line 155

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L155)

```text
// 0x10 T: b Z                               (only ever reached indirectly)
```

## Source note 25, line 156

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L156)

```text
// 0x14 Z: li r3,1; blr                      (an entry from config)
```

## Source note 26, line 157

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L157)

```text
// Gap fill cuts 0x0C..0x14 as one segment, which starts inside E, so it
```

## Source note 27, line 158

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L158)

```text
// used to be skipped (007 Legends 0x82225D90).
```

## Source note 28, line 169

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L169)

```text
// 0x00 entry: bl T; blr
```

## Source note 29, line 170

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L170)

```text
// 0x08 T: cmpwi r3,0; beq L; blr       (found by the call)
```

## Source note 30, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L171)

```text
// 0x14 L: li r3,2; blr                 (T's own code, after its first blr)
```

## Source note 31, line 181

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L181)

```text
// S: cmpwi r3,0; beq case; li r3,5; blr; case: li r3,9; blr.
```

## Source note 32, line 182

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L182)

```text
// The later caller tail-branches backwards into S's case.
```

## Source note 33, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L189)

```text
// S keeps the case as its own label.
```

## Source note 34, line 196

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L196)

```text
// As above: S branches to `case`, which is also an entry now.
```

## Source note 35, line 203

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L203)

```text
// S's own beq: a local goto, which discovery already made it.
```

## Source note 36, line 205

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L205)

```text
// The entry's b: a tail call into the other function.
```

## Source note 37, line 207

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L207)

```text
// Calls to it are calls, whoever makes them.
```

## Source note 38, line 240

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L240)

```text
// A shared epilogue that reads the caller's frame is not a standalone leaf.
```

## Source note 39, line 297

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L297)

```text
// As below, but a method table holds 0x14: an empty method (Blood Stone's
```

## Source note 40, line 298

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/b82fed2/tests/unit/codegen/indirect_discovery_test.cpp#L298)

```text
// sub_8218F208).
```

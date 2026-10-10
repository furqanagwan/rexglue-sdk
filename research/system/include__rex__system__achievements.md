# Achievements: system source notes

This record preserves technical and API notes moved from `include/rex/system/achievements.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L19)

```text
// Free-function facade over the active KernelState's AchievementManager,
```

## Source note 2, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L20)

```text
// intended for guest hooks (REX_HOOK) and recomp app code that just want to
```

## Source note 3, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L21)

```text
// fire achievement calls without reaching through kernel_state()->achievements()
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L22)

```text
// every time.
```

## Source note 5, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L24)

```text
// Every call is null-safe: if no runtime/kernel is live yet, it is a no-op that
```

## Source note 6, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L25)

```text
// returns false. For advanced use -- listing, callbacks, persistence control --
```

## Source note 7, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L26)

```text
// reach the manager directly via rex::system::kernel_state()->achievements().
```

## Source note 8, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L28)

```text
// Defines a new achievement or overrides an existing one with the same ID.
```

## Source note 9, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L29)

```text
// Call before unlocking it, e.g. from ReXApp::OnPostLoadXexImage(). IDs must be
```

## Source note 10, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L30)

```text
// non-zero; to avoid colliding with title (XDBF) achievement IDs, use a high
```

## Source note 11, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L31)

```text
// range (e.g. 0x10000+) for recomp-authored achievements.
```

## Source note 12, line 34

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L34)

```text
// Unlocks an achievement by ID. Shows the unlock toast by default. Safe to call
```

## Source note 13, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L35)

```text
// from any thread, including guest hook threads. No-op if the ID was never
```

## Source note 14, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L36)

```text
// registered. Returns true only on a first-time unlock (false if already
```

## Source note 15, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L37)

```text
// unlocked, unknown, or no runtime is live).
```

## Source note 16, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/system/achievements.h#L40)

```text
// True if the achievement is currently unlocked.
```

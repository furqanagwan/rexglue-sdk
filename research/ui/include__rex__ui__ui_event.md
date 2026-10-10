# Ui event: ui source notes

This record preserves technical and API notes moved from `include/rex/ui/ui_event.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 105

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L105)

```text
// Key previously down(true) or up(false)
```

## Source note 2, line 125

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L125)

```text
// Matching Windows WHEEL_DELTA.
```

## Source note 3, line 148

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L148)

```text
// Platform-reported motion since the previous event, in physical pixels.
```

## Source note 4, line 149

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L149)

```text
// Still moves under Window::SetRelativeMouseMode, where x/y do not.
```

## Source note 5, line 150

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L150)

```text
// Fractional, so accumulate before rounding.
```

## Source note 6, line 160

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L160)

```text
// Positive is up (away from the user), negative is down (towards the user).
```

## Source note 7, line 171

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L171)

```text
// Should be treated as an up event, but without performing the usual action
```

## Source note 8, line 172

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L172)

```text
// for releasing.
```

## Source note 9, line 177

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L177)

```text
// Can be used by event listeners as the value for when there's no current
```

## Source note 10, line 178

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L178)

```text
// pointer, for example.
```

## Source note 11, line 189

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/ui/ui_event.h#L189)

```text
// Can be outside the boundaries of the surface.
```

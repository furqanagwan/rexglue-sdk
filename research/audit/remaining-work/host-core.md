# Host core: unresolved source notes

These notes preserve uncertainty from the implementation; they are not
verified hardware behavior or authorization for speculative changes.
The source-comment migration changes no executable code. Retained questions
must be researched and tested separately before a fix is considered complete.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, 2026-10-10 inventory. Source author names and
links below are preserved from the existing BSD-licensed SDK comments.

Tracking issue: [retained investigations](https://github.com/furqanagwan/rexglue-sdk/issues/260).

## Required investigation

For each retained note, compare the current implementation with its stated
concern and existing issues. Record a reproduction or a source-backed reason
to retire the concern. Changes require bounded regression tests; GPU changes
also require the applicable vendor/title gates. Preserve guest ABI, endian
and status contracts, static dispatch, and title-profile opt-ins. Do not
restore retired host backends or transplant CPU-JIT machinery.

## Note 1: src/core/bit_stream.cpp:50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/bit_stream.cpp#L50)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: Have a flag specifying endianness of data?
```

## Note 2: src/core/bit_stream.cpp:71

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/bit_stream.cpp#L71)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO: This is totally not tested!
```

## Note 3: src/core/clock.cpp:222

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/clock.cpp#L222)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): check for overflow?
```

## Note 4: src/core/cvar.cpp:668

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/cvar.cpp#L668)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(tomc): dumb workaround for the stupid chicken and its egg.
    //             dont call rex logging funcs here for now.
```

## Note 5: src/core/exception_handler_win.cpp:124

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/exception_handler_win.cpp#L124)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): do we need a continue handler if a debugger is
      // attached?
      // vch_handle_ = AddVectoredContinueHandler(1, ExceptionHandlerCallback);
```

## Note 6: src/core/filesystem_win.cpp:241

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/filesystem_win.cpp#L241)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): pick correct response.
```

## Note 7: src/core/memory.cpp:33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/memory.cpp#L33)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(benvanik): fancy AVX versions.
// https://github.com/gnuradio/volk/blob/master/kernels/volk/volk_16u_byteswap.h
// https://github.com/gnuradio/volk/blob/master/kernels/volk/volk_32u_byteswap.h
// https://github.com/gnuradio/volk/blob/master/kernels/volk/volk_64u_byteswap.h
// Original links:
// https://gnuradio.org/redmine/projects/gnuradio/repository/revisions/cb32b70b79f430456208a2cd521d028e0ece5d5b/entry/volk/kernels/volk/volk_16u_byteswap.h
// https://gnuradio.org/redmine/projects/gnuradio/repository/revisions/f2bc76cc65ffba51a141950f98e75364e49df874/entry/volk/kernels/volk/volk_32u_byteswap.h
// https://gnuradio.org/redmine/projects/gnuradio/repository/revisions/2c4c371885c31222362f70a1cd714415d1398021/entry/volk/kernels/volk/volk_64u_byteswap.h
```

## Note 8: src/core/memory.cpp:50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/memory.cpp#L50)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(Joel Linn): Remove this when fixed GCC versions are common place.
```

## Note 9: src/core/utf8.cpp:126

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/src/core/utf8.cpp#L126)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): this is a separate inline function instead of inline within
// split due to a Clang bug: reference to local binding 'needle_begin' declared
// in enclosing function 'split'.
```

## Note 10: include/rex/chrono/chrono.h:27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/chrono/chrono.h#L27)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(JoelLinn) define xstead_clock xsystem_clock etc.
```

## Note 11: include/rex/stream.h:45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/stream.h#L45)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(DrChat): Not tested!
```

## Note 12: include/rex/string/numeric.h:101

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/string/numeric.h#L101)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): do something more with errors?
```

## Note 13: include/rex/string/numeric.h:142

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e/include/rex/string/numeric.h#L142)

Disposition: retained investigation; not yet reproduced or resolved.

```text
// TODO(gibbed): do something more with errors?
```

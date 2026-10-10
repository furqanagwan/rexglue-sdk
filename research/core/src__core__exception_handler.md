# Exception handler: core source notes

This record preserves technical and API notes moved from `src/core/exception_handler.cpp`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 16

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L16)

```text
// Based on VIXL Instruction::IsLoad and IsStore.
```

## Source note 2, line 17

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L17)

```text
// https://github.com/Linaro/vixl/blob/d48909dd0ac62197edb75d26ed50927e4384a199/src/aarch64/instructions-aarch64.cc#L484
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L20)

```text
// All rights reserved.
```

## Source note 4, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L22)

```text
// Redistribution and use in source and binary forms, with or without
```

## Source note 5, line 23

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L23)

```text
// modification, are permitted provided that the following conditions are met:
```

## Source note 6, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L26)

```text
//     this list of conditions and the following disclaimer.
```

## Source note 7, line 28

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L28)

```text
//     this list of conditions and the following disclaimer in the documentation
```

## Source note 8, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L29)

```text
//     and/or other materials provided with the distribution.
```

## Source note 9, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L30)

```text
//   * Neither the name of ARM Limited nor the names of its contributors may be
```

## Source note 10, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L31)

```text
//     used to endorse or promote products derived from this software without
```

## Source note 11, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L32)

```text
//     specific prior written permission.
```

## Source note 12, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L35)

```text
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
```

## Source note 13, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L36)

```text
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
```

## Source note 14, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L38)

```text
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
```

## Source note 15, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L39)

```text
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
```

## Source note 16, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L40)

```text
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
```

## Source note 17, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L41)

```text
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
```

## Source note 18, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L42)

```text
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
```

## Source note 19, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/src/core/exception_handler.cpp#L43)

```text
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

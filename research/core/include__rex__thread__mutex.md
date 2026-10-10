# Mutex: core source notes

This record preserves technical and API notes moved from `include/rex/thread/mutex.h`.
Names and executable tokens are unchanged; licence and attribution headers
remain in the source. Historical explanations are retained as source evidence,
not newly validated hardware claims. Unanswered task notes are tracked by
[#229](https://github.com/furqanagwan/rexglue-sdk/issues/229) and its topic issues.

Part of [#230](https://github.com/furqanagwan/rexglue-sdk/issues/230).
Source pin: `bf367e7`.

## Source note 1, line 18

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L18)

```text
// The global critical region mutex singleton.
```

## Source note 2, line 19

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L19)

```text
// This must guard any operation that may suspend threads or be sensitive to
```

## Source note 3, line 20

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L20)

```text
// being suspended such as global table locks and such.
```

## Source note 4, line 21

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L21)

```text
// To prevent deadlocks this should be the first lock acquired and be held
```

## Source note 5, line 22

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L22)

```text
// for the entire duration of the critical region (longer than any other lock).
```

## Source note 6, line 24

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L24)

```text
// As a general rule if some code can only be accessed from the guest you can
```

## Source note 7, line 25

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L25)

```text
// guard it with only the global critical region and be assured nothing else
```

## Source note 8, line 26

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L26)

```text
// will touch it. If it will be accessed from non-guest threads you may need
```

## Source note 9, line 27

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L27)

```text
// some additional protection.
```

## Source note 10, line 29

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L29)

```text
// You can think of this as disabling interrupts in the guest. The thread in the
```

## Source note 11, line 30

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L30)

```text
// global critical region has exclusive access to the entire system and cannot
```

## Source note 12, line 31

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L31)

```text
// be preempted. This also means that all activity done while in the critical
```

## Source note 13, line 32

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L32)

```text
// region must be extremely fast (no IO!), as it has the chance to block any
```

## Source note 14, line 33

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L33)

```text
// other thread until its done.
```

## Source note 15, line 35

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L35)

```text
// For example, in the following situation thread 1 will not be able to suspend
```

## Source note 16, line 36

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L36)

```text
// thread 0 until it has exited its critical region, preventing it from being
```

## Source note 17, line 37

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L37)

```text
// suspended while holding the table lock:
```

## Source note 18, line 38

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L38)

```text
//   [thread 0]:
```

## Source note 19, line 39

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L39)

```text
//     DoKernelStuff():
```

## Source note 20, line 40

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L40)

```text
//       auto global_lock = global_critical_region_.Acquire();
```

## Source note 21, line 41

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L41)

```text
//       std::lock_guard<std::mutex> table_lock(table_mutex_);
```

## Source note 22, line 42

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L42)

```text
//       table_->InsertStuff();
```

## Source note 23, line 43

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L43)

```text
//   [thread 1]:
```

## Source note 24, line 44

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L44)

```text
//     MySuspendThread():
```

## Source note 25, line 45

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L45)

```text
//       auto global_lock = global_critical_region_.Acquire();
```

## Source note 26, line 46

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L46)

```text
//       ::SuspendThread(thread0);
```

## Source note 27, line 48

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L48)

```text
// To use the region it's strongly recommended that you keep an instance near
```

## Source note 28, line 49

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L49)

```text
// the data requiring it. This makes it clear to those reading that the data
```

## Source note 29, line 50

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L50)

```text
// is protected by the global critical region. For example:
```

## Source note 30, line 51

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L51)

```text
// class MyType {
```

## Source note 31, line 52

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L52)

```text
//   // Implies my_list_ is protected:
```

## Source note 32, line 53

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L53)

```text
//   xe::global_critical_region global_critical_region_;
```

## Source note 33, line 54

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L54)

```text
//   std::list<...> my_list_;
```

## Source note 34, line 60

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L60)

```text
// Acquires a lock on the global critical section.
```

## Source note 35, line 61

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L61)

```text
// Use this when keeping an instance is not possible. Otherwise, prefer
```

## Source note 36, line 62

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L62)

```text
// to keep an instance of global_critical_region near the members requiring
```

## Source note 37, line 63

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L63)

```text
// it to keep things readable.
```

## Source note 38, line 68

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L68)

```text
// Acquires a lock on the global critical section.
```

## Source note 39, line 73

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L73)

```text
// Acquires a deferred lock on the global critical section.
```

## Source note 40, line 78

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L78)

```text
// Tries to acquire a lock on the glboal critical section.
```

## Source note 41, line 79

[Pinned source](https://github.com/furqanagwan/rexglue-sdk/blob/bf367e7/include/rex/thread/mutex.h#L79)

```text
// Check owns_lock() to see if the lock was successfully acquired.
```

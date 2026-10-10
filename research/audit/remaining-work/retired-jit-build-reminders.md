# Retired CPU-JIT build reminders

The two commented-out monitor entries in `src/kernel/CMakeLists.txt` asked
for CPU-JIT methods to be translated to AOT. They are inactive and their
reminders do not establish a missing static-runtime feature. ADR-004 keeps
CPU-JIT execution and trampolines outside this SDK. No build entries change.

Source: SDK `7ec3b080f65e9e94eacbf3b1dbd8f999f3ae216e`, lines 36-37. Original reminders:

```text
    # xboxkrnl/cert_monitor.cpp    # TODO: Translate JIT methods for AOT
    # xboxkrnl/debug_monitor.cpp   # TODO: Translate JIT methods for AOT
```

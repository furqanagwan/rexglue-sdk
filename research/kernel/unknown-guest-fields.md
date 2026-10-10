# Unknown guest fields

Names that still start with `unk` after [#232](https://github.com/furqanagwan/rexglue-sdk/issues/232).
Each is a guest structure field, export parameter or local whose meaning is not
known: upstream Xenia (Canary and Edge) uses the same `unk` name or has no
counterpart. Rename one only with evidence (a guest disassembly, a matching
Microsoft or nxdk definition, or an upstream rename), and record the evidence in
this file when it is removed from the list.

## Named in #232

- `X_KTHREAD` (`kernel_thread.h`), from Edge `src/xenia/kernel/xthread.h`:
  - `mutants_list` (0x10);
  - `processor_mode`, `wait_next`, `wait_reason`, `wait_blocks` (0xA5-0xAB);
  - `saturation_increment`, `base_priority`, `priority_decrement` (0xB8-0xBA);
  - `process_priority_class`, `base_priority_copy`, `max_dynamic_priority` (0xC8-0xCA);
  - `vscr` (0x170, the vector status register's word in its 128-bit slot);
  - `vmx_context`, `fpscr`, `fpu_context` (0x180-0xA87).

  The structure is still 0xAB0 bytes; `static_assert_size` holds.
- `X_KPROCESS` (`kernel_state.h`), from Edge `kernel_state.h`: `process_priority_class`,
  `default_thread_priority`, `max_dynamic_priority`, `disable_quantum_decay` (0x18-0x1B).
- `X_OBJECT_TYPE` (`kernel_object.h`): `close_procedure`, `delete_procedure`,
  `parse_procedure`, `default_object`. The seven-word layout is the original Xbox
  kernel's `OBJECT_TYPE` (Allocate, Free, Close, Delete, Parse, DefaultObject,
  PoolTag); the 360 kernel's object manager descends from it, and the existing
  `constructor`, `destructor` and `pool_tag` already matched it.
- 32 export parameters, named after the same parameter of the same export in Edge
  (same arity, same position). Examples: `XamCreateEnumeratorHandle(user_index,
  app_id, open_message, close_message, extra_size, item_count, flags, out_handle)`,
  `XamContentResolve`, `XamShowSigninUI`, `NtReleaseMutant(previous_count)`,
  `VdSetDisplayModeOverride(width, height)`.

## Still unknown (at `7af2bc4`)

| File | Name | Line |
| --- | --- | --- |
| `include/rex/audio/xma/context.h` | `unk_dword_1_a` | 44 |
| `include/rex/audio/xma/context.h` | `unk_dword_1_c` | 52 |
| `include/rex/audio/xma/context.h` | `unk_dwords_10_15` | 82 |
| `include/rex/graphics/format/dxbc.h` | `unknown_0` | 212 |
| `include/rex/graphics/format/dxbc.h` | `unknown_22` | 509 |
| `include/rex/graphics/format/dxbc.h` | `unknown_26` | 513 |
| `include/rex/graphics/format/dxbc.h` | `unknown_28` | 516 |
| `include/rex/graphics/format/dxbc.h` | `unknown_29` | 517 |
| `include/rex/graphics/format/ucode.h` | `unk` | 563 |
| `include/rex/kernel/xam/apps/xmp_app.h` | `unk` | 81 |
| `include/rex/kernel/xam/apps/xmp_app.h` | `unknown_flags_` | 100 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_00` | 24 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_04` | 25 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_08` | 26 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_0C` | 27 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_10` | 28 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_14` | 29 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_1C` | 31 |
| `include/rex/kernel/xboxkrnl/debug_monitor.h` | `unk_20` | 32 |
| `include/rex/system/kernel_object.h` | `unk_04` | 85 |
| `include/rex/system/kernel_state.h` | `unk_50` | 107 |
| `include/rex/system/kernel_state.h` | `unk_54` | 108 |
| `include/rex/system/kernel_state.h` | `unk_5C` | 109 |
| `include/rex/system/kernel_thread.h` | `unk_0A` | 178 |
| `include/rex/system/kernel_thread.h` | `unk_0F` | 182 |
| `include/rex/system/kernel_thread.h` | `unk_118` | 266 |
| `include/rex/system/kernel_thread.h` | `unk_124` | 268 |
| `include/rex/system/kernel_thread.h` | `unk_128` | 269 |
| `include/rex/system/kernel_thread.h` | `unk_12C` | 270 |
| `include/rex/system/kernel_thread.h` | `unk_154` | 277 |
| `include/rex/system/kernel_thread.h` | `unk_15C` | 278 |
| `include/rex/system/kernel_thread.h` | `unk_168` | 281 |
| `include/rex/system/kernel_thread.h` | `unk_1C` | 146 |
| `include/rex/system/kernel_thread.h` | `unk_20` | 147 |
| `include/rex/system/kernel_thread.h` | `unk_2AC` | 207 |
| `include/rex/system/kernel_thread.h` | `unk_38` | 193 |
| `include/rex/system/kernel_thread.h` | `unk_3C` | 152 |
| `include/rex/system/kernel_thread.h` | `unk_40` | 196 |
| `include/rex/system/kernel_thread.h` | `unk_58` | 215 |
| `include/rex/system/kernel_thread.h` | `unk_60` | 198 |
| `include/rex/system/kernel_thread.h` | `unk_68` | 162 |
| `include/rex/system/kernel_thread.h` | `unk_A88` | 288 |
| `include/rex/system/kernel_thread.h` | `unk_AC` | 244 |
| `include/rex/system/kernel_thread.h` | `unk_CB` | 260 |
| `include/rex/system/kernel_thread.h` | `unk_D` | 142 |
| `include/rex/system/kernel_thread.h` | `unk_mask_64` | 161 |
| `include/rex/system/kernel_thread.h` | `unk_stack_5c` | 197 |
| `include/rex/system/util/xdbf_utils.h` | `unk14` | 88 |
| `include/rex/system/util/xdbf_utils.h` | `unk18` | 89 |
| `include/rex/system/util/xdbf_utils.h` | `unk1C` | 90 |
| `include/rex/system/util/xdbf_utils.h` | `unk20` | 91 |
| `include/rex/system/util/xdbf_utils.h` | `unkE` | 86 |
| `include/rex/system/util/xex2_info.h` | `unk_108` | 555 |
| `include/rex/system/xam/user_profile.h` | `unk` | 102 |
| `include/rex/system/xam/user_profile.h` | `unk04` | 60 |
| `include/rex/system/xam/user_profile.h` | `unk14` | 66 |
| `include/rex/system/xam/user_profile.h` | `unk_1` | 36 |
| `include/rex/system/xam/user_profile.h` | `unk_4` | 37 |
| `include/rex/system/xvideo.h` | `unknown_0x01` | 32 |
| `include/rex/system/xvideo.h` | `unknown_0x8a` | 31 |
| `src/graphics/packet_disassembler.cpp` | `unk0` | 191 |
| `src/graphics/packet_disassembler.cpp` | `unk1` | 192 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk` | 87 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_00` | 81 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_04` | 43 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_14` | 47 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_1C` | 49 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_40` | 82 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_44` | 83 |
| `src/kernel/xam/apps/xam_app.cpp` | `unk_48` | 84 |
| `src/kernel/xam/apps/xmp_app.cpp` | `unk` | 153 |
| `src/kernel/xam/apps/xmp_app.cpp` | `unk3_ptr` | 417 |
| `src/kernel/xam/apps/xmp_app.cpp` | `unk_ptr` | 334 |
| `src/kernel/xam/apps/xmp_app.cpp` | `unknown_flags_` | 31 |
| `src/kernel/xam/xam_avatar.cpp` | `unk1` | 23 |
| `src/kernel/xam/xam_avatar.cpp` | `unk2` | 23 |
| `src/kernel/xam/xam_avatar.cpp` | `unk5` | 24 |
| `src/kernel/xam/xam_avatar.cpp` | `unk6` | 24 |
| `src/kernel/xam/xam_content_aggregate.cpp` | `unk3` | 82 |
| `src/kernel/xam/xam_info.cpp` | `unk` | 73 |
| `src/kernel/xam/xam_input.cpp` | `unk` | 67 |
| `src/kernel/xam/xam_msg.cpp` | `unk_0` | 49 |
| `src/kernel/xam/xam_msg.cpp` | `unk_1` | 50 |
| `src/kernel/xam/xam_nui.cpp` | `unk0` | 25 |
| `src/kernel/xam/xam_nui.cpp` | `unk1` | 26 |
| `src/kernel/xam/xam_nui.cpp` | `unk2` | 27 |
| `src/kernel/xam/xam_nui.cpp` | `unk4` | 29 |
| `src/kernel/xam/xam_nui.cpp` | `unk5` | 30 |
| `src/kernel/xam/xam_task.cpp` | `unknown_00` | 35 |
| `src/kernel/xam/xam_task.cpp` | `unknown_04` | 36 |
| `src/kernel/xam/xam_task.cpp` | `unknown_08` | 37 |
| `src/kernel/xam/xam_task.cpp` | `unknown_14` | 40 |
| `src/kernel/xam/xam_user.cpp` | `unk` | 149 |
| `src/kernel/xam/xam_user.cpp` | `unk08` | 82 |
| `src/kernel/xam/xam_user.cpp` | `unk1` | 379 |
| `src/kernel/xam/xam_user.cpp` | `unk10` | 84 |
| `src/kernel/xam/xam_user.cpp` | `unk14` | 85 |
| `src/kernel/xam/xam_user.cpp` | `unk2` | 390 |
| `src/kernel/xam/xam_user.cpp` | `unk3` | 390 |
| `src/kernel/xam/xam_user.cpp` | `unk4` | 391 |
| `src/kernel/xam/xam_user.cpp` | `unk_0` | 460 |
| `src/kernel/xam/xam_user.cpp` | `unk_2` | 283 |
| `src/kernel/xam/xam_user.cpp` | `unk_4` | 461 |
| `src/kernel/xboxkrnl/xboxkrnl_audio.cpp` | `unk` | 40 |
| `src/kernel/xboxkrnl/xboxkrnl_hid.cpp` | `unk1` | 23 |
| `src/kernel/xboxkrnl/xboxkrnl_hid.cpp` | `unk2` | 23 |
| `src/kernel/xboxkrnl/xboxkrnl_hid.cpp` | `unk3` | 23 |
| `src/kernel/xboxkrnl/xboxkrnl_io.cpp` | `unk` | 664 |
| `src/kernel/xboxkrnl/xboxkrnl_io.cpp` | `unk_0` | 602 |
| `src/kernel/xboxkrnl/xboxkrnl_io.cpp` | `unk_1` | 602 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk` | 604 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk0` | 503 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk_0` | 512 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk_1` | 513 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk_2` | 514 |
| `src/kernel/xboxkrnl/xboxkrnl_memory.cpp` | `unk_3` | 515 |
| `src/kernel/xboxkrnl/xboxkrnl_ob.cpp` | `unk` | 30 |
| `src/kernel/xboxkrnl/xboxkrnl_threading.cpp` | `unk0` | 1057 |
| `src/kernel/xboxkrnl/xboxkrnl_threading.cpp` | `unk1` | 1057 |
| `src/kernel/xboxkrnl/xboxkrnl_threading.cpp` | `unk_zero` | 686 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk` | 282 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk0` | 231 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk1` | 337 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk1_ptr` | 321 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk1_value` | 324 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk2` | 337 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk3` | 227 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk4` | 227 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk5` | 337 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unk9` | 288 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unknown_0x01` | 204 |
| `src/kernel/xboxkrnl/xboxkrnl_video.cpp` | `unknown_0x8a` | 203 |
| `src/system/kernel_state.cpp` | `unk_54` | 131 |
| `src/system/kernel_thread.cpp` | `unk_154` | 257 |
| `src/system/xmemory.cpp` | `unk_phys_alloc` | 171 |
| `src/system/xmemory.cpp` | `unknown_xex_range` | 175 |

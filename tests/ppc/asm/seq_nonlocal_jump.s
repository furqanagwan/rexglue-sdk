# Synthetic helpers are identified by the test harness's reserved symbols.
# Their bodies must never run: calls use the production native-jump emitter.
__rex_test_setjmp:
  trap
  blr
__rex_test_longjmp:
  trap
  blr

test_nonlocal_jump_zero:
  #_ REGISTER_IN r14 0x12345678
  li r3, 4096
  bl __rex_test_setjmp
  cmpwi r3, 0
  bne jump_zero_done
  li r14, 99
  li r3, 4096
  li r4, 0
  bl __rex_test_longjmp
  li r14, 100
jump_zero_done:
  blr
  #_ REGISTER_OUT r3 1
  #_ REGISTER_OUT r14 0x12345678

test_nonlocal_jump_negative:
  #_ REGISTER_IN r14 0x12345678
  li r3, 4100
  bl __rex_test_setjmp
  cmpwi r3, 0
  bne jump_negative_done
  li r14, 99
  li r3, 4100
  li r4, -7
  bl __rex_test_longjmp
  li r14, 100
jump_negative_done:
  blr
  #_ REGISTER_OUT r3 0xFFFFFFFFFFFFFFF9
  #_ REGISTER_OUT r14 0x12345678

test_nonlocal_jump_two_buffers:
  #_ REGISTER_IN r14 11
  li r3, 4104
  bl __rex_test_setjmp
  cmpwi r3, 0
  bne jump_two_done
  li r14, 22
  li r3, 4108
  bl __rex_test_setjmp
  li r3, 4104
  li r4, 7
  bl __rex_test_longjmp
jump_two_done:
  blr
  #_ REGISTER_OUT r3 7
  #_ REGISTER_OUT r14 11

test_addo_sets_ov_and_so:
  #_ REGISTER_IN r4 0x7FFFFFFFFFFFFFFF
  #_ REGISTER_IN r5 1

  addo. r3, r4, r5
  blr
  #_ REGISTER_OUT r3 0x8000000000000000
  #_ REGISTER_OUT xer 0xC0000000
  #_ REGISTER_OUT cr 0x90000000

test_addo_preserves_sticky_so:
  #_ REGISTER_IN r4 1
  #_ REGISTER_IN r5 2
  #_ REGISTER_IN xer 0x80000000

  addo. r3, r4, r5
  blr
  #_ REGISTER_OUT r3 3
  #_ REGISTER_OUT xer 0x80000000
  #_ REGISTER_OUT cr 0x50000000

test_mcrxr_moves_and_clears_xer:
  #_ REGISTER_IN xer 0xE0000000

  .long 0x7D000400  # mcrxr cr2 (not accepted by bundled Power7 assembler)
  mfcr r3
  blr
  #_ REGISTER_OUT r3 0x00E00000
  #_ REGISTER_OUT xer 0

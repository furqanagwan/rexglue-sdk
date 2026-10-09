test_lmw_signed_offset_and_zero_extended_words:
  #_ MEMORY_IN 0x10001000 [80, 00, 00, 01, 12, 34, 56, 78]
  #_ REGISTER_IN r4 0x10001004
  lmw r30, -4(r4)
  blr
  #_ REGISTER_OUT r30 0x0000000080000001
  #_ REGISTER_OUT r31 0x0000000012345678

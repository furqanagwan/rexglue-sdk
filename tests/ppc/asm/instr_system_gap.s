test_isync_icbi:
  #_ REGISTER_IN r3 0x10001000

  isync
  icbi 0, r3
  blr
  #_ REGISTER_OUT r3 0x10001000

test_rotld_alias:
  #_ REGISTER_IN r4 0x123456789ABCDEF0
  #_ REGISTER_IN r5 8

  rotld r3, r4, r5
  blr
  #_ REGISTER_OUT r3 0x3456789ABCDEF012

test_mfmsr_guest_value:
  mfmsr r3
  blr
  #_ REGISTER_OUT r3 0x9030

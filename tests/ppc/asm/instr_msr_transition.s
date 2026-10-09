test_msr_disable_nested_restore:
  #_ REGISTER_IN r3 0
  #_ REGISTER_IN r6 0x9030
  mfmsr r4
  mtmsrd r3
  mfmsr r5
  mtmsr r3
  mfmsr r7
  mtmsrd r3
  mfmsr r8
  mtmsr r6
  mfmsr r9
  blr
  #_ REGISTER_OUT r4 0x9030
  #_ REGISTER_OUT r5 0x1030
  #_ REGISTER_OUT r7 0x1030
  #_ REGISTER_OUT r8 0x1030
  #_ REGISTER_OUT r9 0x9030

test_msr_enable_without_prior_disable:
  #_ REGISTER_IN r3 0x9030
  mtmsr r3
  mtmsrd r3
  mfmsr r4
  blr
  #_ REGISTER_OUT r4 0x9030

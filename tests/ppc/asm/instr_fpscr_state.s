test_mcrfs_transfers_field_and_clears_exception_flags:
  #_ REGISTER_IN f1 0x00000000A0000001
  #_ REGISTER_IN f5 0

  mtfsf 255, f1
  mcrfs 2, 0
  mfcr r3
  mffs f4
  mtfsf 1, f5  # restore the host rounding mode for later test cases
  blr
  #_ REGISTER_OUT r3 0x00A00000
  #_ REGISTER_OUT f4 0x0000000020000001

test_mcrfs_preserves_rounding_and_enables:
  #_ REGISTER_IN f1 0x0000000000000003
  #_ REGISTER_IN f5 0
  mtfsf 255, f1
  mcrfs 2, 7
  mfcr r3
  mffs f4
  mtfsf 255, f5
  blr
  #_ REGISTER_OUT r3 0x00300000
  #_ REGISTER_OUT f4 0x0000000000000003

test_mcrfs_preserves_result_flags:
  #_ REGISTER_IN f1 0x000000000001F000
  #_ REGISTER_IN f5 0
  mtfsf 255, f1
  mcrfs 2, 4
  mfcr r3
  mffs f4
  mtfsf 255, f5
  blr
  #_ REGISTER_OUT r3 0x00F00000
  #_ REGISTER_OUT f4 0x000000000001F000

test_fpscr_fadd_inexact_is_reported_by_mffs:
  #_ REGISTER_IN f1 0x3FB999999999999A
  #_ REGISTER_IN f2 0x3FC999999999999A
  fadd f3, f1, f2
  mffs f4
  blr
  #_ REGISTER_OUT f4 0x82000000

test_fpscr_record_form_reports_enabled_exception_in_cr1:
  #_ REGISTER_IN f1 0x3FB999999999999A
  #_ REGISTER_IN f2 0x3FC999999999999A
  #_ REGISTER_IN f5 0x8
  mtfsf 255, f5
  fadd. f3, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x0C000000
  #_ REGISTER_OUT f4 0xC2000008

test_fpscr_infinity_minus_infinity_records_its_cause:
  #_ REGISTER_IN f1 0x7FF0000000000000
  #_ REGISTER_IN f2 0x7FF0000000000000
  fsub f3, f1, f2
  mffs f4
  blr
  #_ REGISTER_OUT f4 0xA0800000

test_fpscr_clearing_summary_keeps_unread_exception_cause:
  #_ REGISTER_IN f1 0x3FB999999999999A
  #_ REGISTER_IN f2 0x3FC999999999999A
  fadd f3, f1, f2
  mcrfs 1, 0
  mffs f4
  blr
  #_ REGISTER_OUT f4 0x02000000

test_fpscr_fcmpu_signaling_nan_records_vxsnan:
  #_ REGISTER_IN f1 0x7FF0000000000001
  #_ REGISTER_IN f2 0x3FF0000000000000
  fcmpu cr0, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x10000000
  #_ REGISTER_OUT f4 0xA1000000

test_fpscr_fcmpu_quiet_nan_does_not_signal:
  #_ REGISTER_IN f1 0x7FF8000000000001
  #_ REGISTER_IN f2 0x3FF0000000000000
  fcmpu cr0, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x10000000
  #_ REGISTER_OUT f4 0x00000000

test_fpscr_fcmpo_quiet_nan_records_invalid_compare:
  #_ REGISTER_IN f1 0x7FF8000000000001
  #_ REGISTER_IN f2 0x3FF0000000000000
  fcmpo cr0, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x10000000
  #_ REGISTER_OUT f4 0xA0080000

test_fpscr_fcmpo_signaling_nan_records_invalid_compare_when_ve_disabled:
  #_ REGISTER_IN f1 0x7FF0000000000001
  #_ REGISTER_IN f2 0x3FF0000000000000
  fcmpo cr0, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x10000000
  #_ REGISTER_OUT f4 0xA1080000

test_fpscr_fcmpo_signaling_nan_with_ve_enabled:
  #_ REGISTER_IN f1 0x7FF0000000000001
  #_ REGISTER_IN f2 0x3FF0000000000000
  #_ REGISTER_IN f5 0x80
  mtfsf 255, f5
  fcmpo cr0, f1, f2
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x10000000
  #_ REGISTER_OUT f4 0xE1000080

test_fpscr_fctiw_inexact_sets_xx:
  #_ REGISTER_IN f1 0x3FF8000000000000
  fctiw f2, f1
  mffs f4
  blr
  #_ REGISTER_OUT f2 0x0000000000000002
  #_ REGISTER_OUT f4 0x82000000

test_fpscr_fctiw_out_of_range_sets_vxcvi:
  #_ REGISTER_IN f1 0x41E0000000000000
  fctiw f2, f1
  mffs f4
  blr
  #_ REGISTER_OUT f2 0x000000007FFFFFFF
  #_ REGISTER_OUT f4 0xA0000100

test_fpscr_fctiw_quiet_nan_sets_vxcvi:
  #_ REGISTER_IN f1 0x7FF8000000000001
  fctiw f2, f1
  mffs f4
  blr
  #_ REGISTER_OUT f2 0xFFFFFFFF80000000
  #_ REGISTER_OUT f4 0xA0000100

test_fpscr_fctiw_signaling_nan_sets_vxsnan:
  #_ REGISTER_IN f1 0x7FF0000000000001
  fctiw f2, f1
  mffs f4
  blr
  #_ REGISTER_OUT f2 0xFFFFFFFF80000000
  #_ REGISTER_OUT f4 0xA1000000

test_fpscr_fctiw_record_form_reports_enabled_inexact:
  #_ REGISTER_IN f1 0x3FF8000000000000
  #_ REGISTER_IN f5 0x8
  mtfsf 255, f5
  fctiw. f2, f1
  mfcr r3
  mffs f4
  blr
  #_ REGISTER_OUT r3 0x0C000000
  #_ REGISTER_OUT f4 0xC2000008

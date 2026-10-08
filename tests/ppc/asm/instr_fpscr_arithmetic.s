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

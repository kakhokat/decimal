#include "check_s21_decimal.h"

int main() {
  int number_failed = 0;
  Suite* suites[] = {test_add(),
                     test_sub(),
                     test_mul(),
                     test_div(),
                     s21_is_equal_suite(),
                     s21_is_not_equal_suite(),
                     s21_is_greater_suite(),
                     s21_is_less_suite(),
                     s21_is_less_or_equal_suite(),
                     s21_is_greater_or_equal_suite(),
                     s21_from_int_to_decimal_suite(),
                     s21_from_float_to_decimal_suite(),
                     s21_from_decimal_to_int_suite(),
                     s21_from_decimal_to_float_suite(),
                     s21_negate_suite(),
                     s21_truncate_suite(),
                     s21_floor_suite(),
                     s21_round_suite(),
                     NULL};
  SRunner* sr = srunner_create(NULL);
  for (int i = 0; suites[i] != NULL; ++i) srunner_add_suite(sr, suites[i]);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
#include "check_s21_decimal.h"

START_TEST(positive_zero_check_s21_from_float_to_decimal) {
  int result[4] = {0, 0, 0, 0};
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(+0.f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(negative_zero_check_s21_from_float_to_decimal) {
  int result[4] = {0, 0, 0, 1u << 31};
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(-0.f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(small_fraction_check_s21_from_float_to_decimal) {
  int result[4] = {0, 0, 0, 0};
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(1e-29f, &test),
                   CODE_CONVERTATION_ERROR);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(overflow_check_s21_from_float_to_decimal) {
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(powf(2.f, 96.f), &test),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(infinity_check_s21_from_float_to_decimal) {
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(INFINITY, &test),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(negative_infinity_check_s21_from_float_to_decimal) {
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(-INFINITY, &test),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(many_digits_fraction_check_s21_from_float_to_decimal) {
  int result[4] = {1234568, 0, 0, 3 << 16};
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(1234.5678f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(big_integer_check_s21_from_float_to_decimal) {
  int result4[] = {4292878464u, 8191, 0, 1u << 31};
  s21_decimal test;
  ck_assert_int_eq(s21_from_float_to_decimal(-powf(2.f, 45.f), &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result4, sizeof(int) * 4);
}
END_TEST

START_TEST(additional_check_s21_from_float_to_decimal) {
  int result[4] = {228, 0, 0, 0};
  s21_decimal test;
  result[3] |= 1 << 16;
  ck_assert_int_eq(s21_from_float_to_decimal(22.8f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);

  result[0] = 106001;
  ck_assert_int_eq(s21_from_float_to_decimal(10600.100f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);

  result[0] = 1337;
  result[3] |= 1u << 31;
  result[3] |= 3 << 16;
  ck_assert_int_eq(s21_from_float_to_decimal(-1.337f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);

  int result2[] = {228, 0, 0, 5 << 16};
  ck_assert_int_eq(s21_from_float_to_decimal(0.00228f, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result2, sizeof(int) * 4);

  int result3[] = {2842171, 0, 0, 20 << 16};
  ck_assert_int_eq(s21_from_float_to_decimal(powf(2.f, -45.f), &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result3, sizeof(int) * 4);
}
END_TEST

Suite *s21_from_float_to_decimal_suite() {
  Suite *s = suite_create("s21_from_float_to_decimal");
  TCase *tc_corner = tcase_create("corner"),
        *tc_additional = tcase_create("additional");

  tcase_add_test(tc_corner, positive_zero_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, negative_zero_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, small_fraction_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, infinity_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, overflow_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, negative_infinity_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner,
                 many_digits_fraction_check_s21_from_float_to_decimal);
  tcase_add_test(tc_corner, big_integer_check_s21_from_float_to_decimal);
  suite_add_tcase(s, tc_corner);

  tcase_add_test(tc_additional, additional_check_s21_from_float_to_decimal);
  suite_add_tcase(s, tc_additional);

  return s;
}

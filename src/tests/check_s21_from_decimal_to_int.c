#include "check_s21_decimal.h"

START_TEST(zero_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(negative_one_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test = {{1, 0, 0, 1u << 31}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(fraction_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test = {{11, 0, 0, 1 << 16}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(big_fraction_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test = {{3751282716u, 121, 0, 6 << 16}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, 523442);
}
END_TEST

START_TEST(overflow_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test = {{228, 4, 111, 0}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(incorrect_decimal_check_s21_from_decimal_to_int) {
  int result, test_data[4] = {228, 0, 0, 30 << 16};
  s21_decimal test = {{228, 0, 0, 3}};
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result),
                   CODE_CONVERTATION_ERROR);
  memcpy(test.bits, test_data, sizeof(int) * 4);
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(additional_check_s21_from_decimal_to_int) {
  int result;
  s21_decimal test;

  s21_from_int_to_decimal(-228, &test);
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, -228);

  null_decimal(&test);
  test.bits[0] = 22800;
  test.bits[3] = 2 << 16;
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, 228);

  s21_from_float_to_decimal(228.228, &test);
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, 228);

  s21_from_float_to_decimal(-228.228, &test);
  ck_assert_int_eq(s21_from_decimal_to_int(test, &result), CODE_OK);
  ck_assert_int_eq(result, -228);
}
END_TEST

Suite *s21_from_decimal_to_int_suite() {
  Suite *s = suite_create("s21_from_decimal_to_int");
  TCase *tc_corner = tcase_create("corner"),
        *tc_additional = tcase_create("additional");

  tcase_add_test(tc_corner, zero_check_s21_from_decimal_to_int);
  tcase_add_test(tc_corner, negative_one_check_s21_from_decimal_to_int);
  tcase_add_test(tc_corner, fraction_check_s21_from_decimal_to_int);
  tcase_add_test(tc_corner, big_fraction_check_s21_from_decimal_to_int);
  tcase_add_test(tc_corner, overflow_check_s21_from_decimal_to_int);
  tcase_add_test(tc_corner, incorrect_decimal_check_s21_from_decimal_to_int);
  suite_add_tcase(s, tc_corner);

  tcase_add_test(tc_additional, additional_check_s21_from_decimal_to_int);
  suite_add_tcase(s, tc_additional);

  return s;
}

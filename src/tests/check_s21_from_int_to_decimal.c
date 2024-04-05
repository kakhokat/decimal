#include "check_s21_decimal.h"

START_TEST(zero_check_s21_from_int_to_decimal) {
  int result[4] = {0, 0, 0, 0};
  s21_decimal test;
  ck_assert_int_eq(s21_from_int_to_decimal(0, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(one_check_s21_from_int_to_decimal) {
  int result[4] = {1, 0, 0, 0};
  s21_decimal test;
  ck_assert_int_eq(s21_from_int_to_decimal(1, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(negative_one_check_s21_from_int_to_decimal) {
  int result[4] = {1, 0, 0, 1u << 31};
  s21_decimal test;
  ck_assert_int_eq(s21_from_int_to_decimal(-1, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

START_TEST(additional_check_s21_from_int_to_decimal) {
  int result[4] = {228, 0, 0, 0};
  s21_decimal test;
  ck_assert_int_eq(s21_from_int_to_decimal(228, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);

  result[0] = 106000;
  ck_assert_int_eq(s21_from_int_to_decimal(106000, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);

  result[0] = 1337000;
  result[3] |= 1u << 31;
  ck_assert_int_eq(s21_from_int_to_decimal(-1337000, &test), CODE_OK);
  ck_assert_mem_eq(test.bits, result, sizeof(int) * 4);
}
END_TEST

Suite *s21_from_int_to_decimal_suite() {
  Suite *s = suite_create("s21_from_int_to_decimal");
  TCase *tc_corner = tcase_create("corner"),
        *tc_additional = tcase_create("additional");

  tcase_add_test(tc_corner, zero_check_s21_from_int_to_decimal);
  tcase_add_test(tc_corner, one_check_s21_from_int_to_decimal);
  tcase_add_test(tc_corner, negative_one_check_s21_from_int_to_decimal);
  suite_add_tcase(s, tc_corner);

  tcase_add_test(tc_additional, additional_check_s21_from_int_to_decimal);
  suite_add_tcase(s, tc_additional);

  return s;
}

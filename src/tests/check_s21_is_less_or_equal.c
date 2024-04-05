#include "check_s21_decimal.h"

START_TEST(is_less_or_equal_1) {
  int val1 = 1;
  int val2 = 1;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_2) {
  int val1 = -13;
  int val2 = 1;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_3) {
  int val1 = 6;
  int val2 = 2;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_4) {
  int val1 = 33333;
  int val2 = 1231111;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_5) {
  float val1 = 123.1234;
  float val2 = 123.123;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_6) {
  float val1 = -123.99;
  float val2 = -124.00;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_7) {
  s21_decimal res1 = {
      {0b00000000000000011000011010011111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000001010000000000000000}};
  s21_decimal res2 = {
      {0b00000000000000011000011010011111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b00000000000000110000000000000000}};
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_or_equal_8) {
  s21_decimal res1 = {{0b00000000100110000110111101111001,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000001000000000000000000}};  // -999.0010
  s21_decimal res2 = {{0b00000000100110000111001101010111,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000001000000000000000000}};  // -999.0999
  ck_assert_int_eq(s21_is_less_or_equal(res1, res2), FALSE);
}
END_TEST

Suite *s21_is_less_or_equal_suite() {
  Suite *s = suite_create("s21_is_less_or_equal_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_less_or_equal_1);
  tcase_add_test(tc_corner, is_less_or_equal_2);
  tcase_add_test(tc_corner, is_less_or_equal_3);
  tcase_add_test(tc_corner, is_less_or_equal_4);
  tcase_add_test(tc_corner, is_less_or_equal_5);
  tcase_add_test(tc_corner, is_less_or_equal_6);
  tcase_add_test(tc_corner, is_less_or_equal_7);
  tcase_add_test(tc_corner, is_less_or_equal_8);

  suite_add_tcase(s, tc_corner);

  return s;
}
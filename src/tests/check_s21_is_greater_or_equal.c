#include "check_s21_decimal.h"

START_TEST(is_greater_or_equal_1) {
  int val1 = 9;
  int val2 = 8;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_or_equal_2) {
  float val1 = 0;
  float val2 = 0.0000;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_or_equal_3) {
  int val1 = -10;
  int val2 = -12;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_or_equal_4) {
  float val1 = 0.99989;
  float val2 = 0.99998;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_or_equal_5) {
  s21_decimal res1 = {{1234, 0, 0, 0}};
  s21_decimal res2 = {{1234, 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_or_equal_6) {
  s21_decimal res1 = {{10, 0, 0, 0}};
  s21_decimal res2 = {{10, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_or_equal_7) {
  s21_decimal res1 = {{0b00000000000000000000000000001001,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b00000000000000100000000000000000}};  // 0.09000
  s21_decimal res2 = {{0b00000000000000000000000001100011,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b00000000000000100000000000000000}};  // 0.9900
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_or_equal_8) {
  s21_decimal res1 = {{0b00000000000000000010001100110001,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000001010000000000000000}};  // -0.09009
  s21_decimal res2 = {{0b00000000000000000000000001100011,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000000100000000000000000}};  // -0.9900
  ck_assert_int_eq(s21_is_greater_or_equal(res1, res2), TRUE);
}
END_TEST

Suite *s21_is_greater_or_equal_suite() {
  Suite *s = suite_create("s21_is_greater_or_equal_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_greater_or_equal_1);
  tcase_add_test(tc_corner, is_greater_or_equal_2);
  tcase_add_test(tc_corner, is_greater_or_equal_3);
  tcase_add_test(tc_corner, is_greater_or_equal_4);
  tcase_add_test(tc_corner, is_greater_or_equal_5);
  tcase_add_test(tc_corner, is_greater_or_equal_6);
  tcase_add_test(tc_corner, is_greater_or_equal_7);
  tcase_add_test(tc_corner, is_greater_or_equal_8);

  suite_add_tcase(s, tc_corner);

  return s;
}
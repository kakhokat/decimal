#include "check_s21_decimal.h"

START_TEST(is_equal_1) {
  int val1 = 0;
  int val2 = 1;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_equal_2) {
  int val1 = 23131;
  int val2 = 23131;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_equal_3) {
  int val1 = -1234;
  int val2 = -1234;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_equal_4) {
  float val1 = 2.3123;
  float val2 = 33.1234;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_equal_5) {
  float val1 = -99.0199;
  float val2 = -99.019;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_equal_6) {
  float val1 = 7.1e+24;
  float val2 = 1.3314;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_equal_7) {
  float val1 = 1.001;
  float val2 = 1.001000;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_equal_8) {
  float val1 = -0.99000;
  float val2 = -0.99;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_equal_9) {
  float val1 = 3.99999;
  float val2 = 4;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_equal(res1, res2), FALSE);
}
END_TEST

Suite *s21_is_equal_suite() {
  Suite *s = suite_create("s21_is_equal_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_equal_1);
  tcase_add_test(tc_corner, is_equal_2);
  tcase_add_test(tc_corner, is_equal_3);
  tcase_add_test(tc_corner, is_equal_4);
  tcase_add_test(tc_corner, is_equal_5);
  tcase_add_test(tc_corner, is_equal_6);
  tcase_add_test(tc_corner, is_equal_7);
  tcase_add_test(tc_corner, is_equal_8);
  tcase_add_test(tc_corner, is_equal_9);
  suite_add_tcase(s, tc_corner);

  return s;
}
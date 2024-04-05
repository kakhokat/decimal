#include "check_s21_decimal.h"

START_TEST(is_not_equal_1) {
  int val1 = 123;
  int val2 = 123;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_not_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_not_equal_2) {
  int val1 = 123;
  int val2 = -123;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_not_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_not_equal_3) {
  float val1 = 0.0;
  float val2 = 0.0000;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_not_equal(res1, res2), FALSE);
}
END_TEST

START_TEST(is_not_equal_4) {
  float val1 = 3999.99;
  float val2 = 4000;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_not_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_not_equal_5) {
  s21_decimal res1 = {{323, 0, 0, 0}};
  s21_decimal res2 = {{323, 1, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(res1, res2), TRUE);
}
END_TEST

START_TEST(is_not_equal_6) {
  s21_decimal res1 = {{2, 0, 0, 0}};
  int val = 2;
  val |= (unsigned)1 << 31;
  s21_decimal res2;
  s21_from_int_to_decimal(val, &res2);
  ck_assert_int_eq(s21_is_not_equal(res1, res2), TRUE);
}
END_TEST

Suite *s21_is_not_equal_suite() {
  Suite *s = suite_create("s21_is_not_equal_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_not_equal_1);
  tcase_add_test(tc_corner, is_not_equal_2);
  tcase_add_test(tc_corner, is_not_equal_3);
  tcase_add_test(tc_corner, is_not_equal_4);
  tcase_add_test(tc_corner, is_not_equal_5);
  tcase_add_test(tc_corner, is_not_equal_6);

  suite_add_tcase(s, tc_corner);

  return s;
}
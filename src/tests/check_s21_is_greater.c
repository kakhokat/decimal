#include "check_s21_decimal.h"

START_TEST(is_greater_1) {
  int val1 = 123;
  int val2 = 123;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_2) {
  int val1 = 912;
  int val2 = -912;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_3) {
  int val1 = -1;
  int val2 = 1;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_4) {
  int val1 = -0;
  int val2 = 0;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_5) {
  s21_decimal lhs_test = {{5, 0, 0, (unsigned)1 << 31}},
              rhs_test = {{1, 0, 0, (unsigned)1 << 31}};
  ck_assert_int_eq(s21_is_greater(lhs_test, rhs_test), FALSE);
}
END_TEST

START_TEST(is_greater_6) {
  float val1 = -5.0009;
  float val2 = -6.999999;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_7) {
  float val1 = 5.999999;
  float val2 = -6.999999;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_8) {
  s21_decimal res1 = {{1, 0, 0, 0}};
  s21_decimal res2 = {{1, 1, 0, 0}};
  ck_assert_int_eq(s21_is_greater(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_9) {
  s21_decimal res1 = {{1, 0, 0, 0}};
  s21_decimal res2 = {{1, 0, 0, 0}};
  res2.bits[3] |= (unsigned)1 << 31;
  ck_assert_int_eq(s21_is_greater(res1, res2), TRUE);
}
END_TEST

START_TEST(is_greater_10) {
  float val1 = 2.9000;
  float val2 = 2.9;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_greater(res1, res2), FALSE);
}
END_TEST

START_TEST(is_greater_11) {
  s21_decimal res1 = {{-1, -1, -1, 0}};
  s21_decimal res2 = {{17, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(res1, res2), TRUE);
}
END_TEST

Suite *s21_is_greater_suite() {
  Suite *s = suite_create("s21_is_greater_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_greater_1);
  tcase_add_test(tc_corner, is_greater_2);
  tcase_add_test(tc_corner, is_greater_3);
  tcase_add_test(tc_corner, is_greater_4);
  tcase_add_test(tc_corner, is_greater_5);
  tcase_add_test(tc_corner, is_greater_6);
  tcase_add_test(tc_corner, is_greater_7);
  tcase_add_test(tc_corner, is_greater_8);
  tcase_add_test(tc_corner, is_greater_9);
  tcase_add_test(tc_corner, is_greater_10);
  tcase_add_test(tc_corner, is_greater_11);

  suite_add_tcase(s, tc_corner);

  return s;
}
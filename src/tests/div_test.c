#include "check_s21_decimal.h"

START_TEST(add_int_1) {
  s21_decimal decimal_1 = {{1000, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{1000, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_div(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 1);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_2) {
  s21_decimal decimal_1 = {{1, 0, 0, 0}};
  s21_decimal decimal_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_div(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 1);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_3) {
  s21_decimal decimal_1 = {{2147483647, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{0, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_div(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, 3);
}
END_TEST

START_TEST(add_int_4) {
  s21_decimal decimal_1 = {{104, 0, 0, 0}};
  s21_decimal decimal_2 = {{26, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_div(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 4);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal_set_sign(&val1, 1);
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal_set_sign(&val1, 1);
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal_set_sign(&val1, 1);
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {0};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal_set_sign(&val2, 1);
  s21_decimal res = {0};
  ck_assert_int_eq(0, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal_set_sign(&val1, 1);
  s21_decimal val2 = {{0}};
  s21_decimal res = {0};
  ck_assert_int_eq(3, s21_div(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  src1.bits[0] = 11200;
  src2.bits[0] = 11200;
  s21_div(src1, src2, &result);
  ck_assert_uint_eq(1, result.bits[0]);
}
END_TEST

Suite *test_div() {
  Suite *s = suite_create("s21_test_div_suite");
  TCase *tc = tcase_create("div");

  tcase_add_test(tc, add_int_1);
  tcase_add_test(tc, add_int_2);
  tcase_add_test(tc, add_int_3);
  tcase_add_test(tc, add_int_4);
  tcase_add_test(tc, add_0);
  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);

  suite_add_tcase(s, tc);
  return s;
}
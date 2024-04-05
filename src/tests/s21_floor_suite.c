#include "check_s21_decimal.h"

START_TEST(test1_zero_decimal) {
  s21_decimal test = {{0, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(s21_floor(test, &result), CODE_OK);
  int a;
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, 0);
}
END_TEST

START_TEST(test2_one) {
  s21_decimal test = {{1, 0, 0, 0}}, result = {{0}};
  ck_assert_int_eq(s21_floor(test, &result), CODE_OK);
  int a;
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, 1);
}
END_TEST

START_TEST(test3_negative_one) {
  s21_decimal test = {{14, 0, 0, 0}}, result = {{0}};
  s21_decimal_set_sign(&test, 1);
  s21_decimal_set_power(&test, 1);
  ck_assert_int_eq(s21_floor(test, &result), CODE_OK);
  int a;
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, -2);
}
END_TEST

START_TEST(test4_incorrect_dec) {
  s21_decimal test = {{228, 11, 321, 3}}, result = {{0}};
  ck_assert_int_eq(s21_floor(test, &result), CODE_CALCULATING_ERROR);
}
END_TEST

START_TEST(test5_random_dec) {
  s21_decimal test = {{54, 0, 0, 0}}, result = {{0}};
  s21_decimal_set_power(&test, 1);
  ck_assert_int_eq(s21_floor(test, &result), CODE_OK);
  int a;
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, 5);
}
END_TEST

START_TEST(test6_random_negative_dec) {
  s21_decimal test = {{544, 0, 0, 0}}, result = {{0}};
  s21_decimal_set_sign(&test, 1);
  s21_decimal_set_power(&test, 2);
  ck_assert_int_eq(s21_floor(test, &result), CODE_OK);
  int a;
  s21_from_decimal_to_int(result, &a);
  ck_assert_int_eq(a, -6);
}
END_TEST

Suite *s21_floor_suite() {
  Suite *s = suite_create("s21_floor_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, test1_zero_decimal);
  tcase_add_test(tc_corner, test2_one);
  tcase_add_test(tc_corner, test3_negative_one);
  tcase_add_test(tc_corner, test4_incorrect_dec);
  tcase_add_test(tc_corner, test5_random_dec);
  tcase_add_test(tc_corner, test6_random_negative_dec);
  suite_add_tcase(s, tc_corner);

  return s;
}
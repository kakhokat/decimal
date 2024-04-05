#include "check_s21_decimal.h"

START_TEST(is_less_1) {
  int val1 = 0;
  int val2 = -1;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_2) {
  int val1 = -1;
  int val2 = 0;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_3) {
  int val1 = 0;
  int val2 = 0;
  s21_decimal res1, res2;
  s21_from_int_to_decimal(val1, &res1);
  s21_from_int_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_4) {
  s21_decimal res1 = {{9, 0, 0, 5 << 16}}, res2 = {{9, 0, 0, 4 << 16}};
  ck_assert_int_eq(s21_is_less(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_5) {
  float val1 = -0.00009;
  float val2 = 0.00009;
  s21_decimal res1, res2;
  s21_from_float_to_decimal(val1, &res1);
  s21_from_float_to_decimal(val2, &res2);
  ck_assert_int_eq(s21_is_less(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_6) {
  s21_decimal res1 = {{0b00000000000000000000000000010111,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000000010000000000000000}};  // -2.3
  s21_decimal res2 = {{0b00000000000000000000000000010111,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b00000000000000010000000000000000}};  // 2.3
  ck_assert_int_eq(s21_is_less(res1, res2), TRUE);
}
END_TEST

START_TEST(is_less_7) {
  s21_decimal res1 = {{0b00000000000000000000011111001111,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000000110000000000000000}};  // -1.999
  s21_decimal res2 = {{0b00000000000000000000000000000010,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000000000000000000000000}};  // -2
  ck_assert_int_eq(s21_is_less(res1, res2), FALSE);
}
END_TEST

START_TEST(is_less_8) {
  s21_decimal res1 = {
      {0b11111111111111111111111111111111, 0b00000000000000000000000000000000,
       0b00000000000000000000000000000000, 0b10000000000000000000000000000000}};
  s21_decimal res2 = {{0b00000000000000000000000000000010,
                       0b00000000000000000000000000000000,
                       0b00000000000000000000000000000000,
                       0b10000000000000000000000000000000}};  // -2
  ck_assert_int_eq(s21_is_less(res1, res2), TRUE);
}
END_TEST

Suite *s21_is_less_suite() {
  Suite *s = suite_create("s21_is_less_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, is_less_1);
  tcase_add_test(tc_corner, is_less_2);
  tcase_add_test(tc_corner, is_less_3);
  tcase_add_test(tc_corner, is_less_4);
  tcase_add_test(tc_corner, is_less_5);
  tcase_add_test(tc_corner, is_less_6);
  tcase_add_test(tc_corner, is_less_7);
  tcase_add_test(tc_corner, is_less_8);

  suite_add_tcase(s, tc_corner);

  return s;
}
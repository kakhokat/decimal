#include "check_s21_decimal.h"

START_TEST(test1_zero_decimal) {
  s21_decimal test = {{15, 0, 0, 0}}, result = {{0}}, answer = {{1, 0, 0, 0}};
  s21_decimal_set_power(&test, 1);
  s21_decimal_set_sign(&test, 1);
  s21_decimal_set_sign(&answer, 1);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test2_one) {
  s21_decimal test = {{12345, 0, 0, 0}}, result = {{0}},
              answer = {{1234, 0, 0, 0}};
  s21_decimal_set_power(&test, 1);
  s21_decimal_set_sign(&test, 1);
  s21_decimal_set_sign(&answer, 1);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test3_negative_one) {
  s21_decimal test = {{987654, 0, 0, 0}}, result = {{0}},
              answer = {{9, 0, 0, 0}};
  s21_decimal_set_power(&test, 5);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test4_incorrect_dec) {
  s21_decimal test = {{456123, 0, 0, 0}}, result = {{0}},
              answer = {{0, 0, 0, 0}};
  s21_decimal_set_power(&test, 10);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test5_random_dec) {
  s21_decimal test = {{523443, 12321, 3213, 10 << 16}}, result = {{0}},
              answer = {{-115992306, 1379, 0, 0}};
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test6_random_negative_dec) {
  s21_decimal test = {{523443, 12321, 3213, 10 << 16}}, result = {{0}},
              answer = {{-115992306, 1379, 0, 0}};
  s21_decimal_set_sign(&answer, 1);
  s21_decimal_set_sign(&test, 1);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

START_TEST(test7_incorrect_decimal) {
  s21_decimal test = {{228, 11, 321, 3}}, result = {{0}};
  ck_assert_int_eq(s21_truncate(test, &result), CODE_CALCULATING_ERROR);
}
END_TEST

START_TEST(test8_no_scale_dec) {
  s21_decimal test = {{12345, 0, 0, 0}}, result = {{0}},
              answer = {{12345, 0, 0, 0}};
  s21_decimal_set_sign(&test, 1);
  s21_decimal_set_sign(&answer, 1);
  ck_assert_int_eq(s21_truncate(test, &result), CODE_OK);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(answer.bits[i], result.bits[i]);
  }
}
END_TEST

Suite *s21_truncate_suite() {
  Suite *s = suite_create("s21_truncate_suite");
  TCase *tc_corner = tcase_create("corner");

  tcase_add_test(tc_corner, test1_zero_decimal);
  tcase_add_test(tc_corner, test2_one);
  tcase_add_test(tc_corner, test3_negative_one);
  tcase_add_test(tc_corner, test4_incorrect_dec);
  tcase_add_test(tc_corner, test5_random_dec);
  tcase_add_test(tc_corner, test6_random_negative_dec);
  tcase_add_test(tc_corner, test7_incorrect_decimal);
  tcase_add_test(tc_corner, test8_no_scale_dec);
  suite_add_tcase(s, tc_corner);

  return s;
}
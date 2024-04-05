#include "check_s21_decimal.h"

START_TEST(zero_check_s21_from_decimal_to_float) {
  float result;
  s21_decimal test = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(negative_one_check_s21_from_decimal_to_float) {
  float result;
  s21_decimal test = {{1, 0, 0, 1u << 31}};
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, -1.0f);
}
END_TEST

START_TEST(incorrect_decimal_check_s21_from_decimal_to_float) {
  float result;
  s21_decimal test = {{228, 11, 321, 3}};
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result),
                   CODE_CONVERTATION_ERROR);
}
END_TEST

START_TEST(additional_check_s21_from_decimal_to_float) {
  float result, test1 = 1.53242f, test2 = 5.532432f, test3 = 432.5324f,
                test4 = 35188667056127,
                test5 = -5.6467209477203267135030885114f;
  s21_decimal test;

  s21_from_float_to_decimal(test1, &test);
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, test1);

  s21_from_float_to_decimal(test2, &test);
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, test2);

  s21_from_float_to_decimal(test3, &test);
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, test3);

  null_decimal(&test);
  test.bits[0] = -1;
  test.bits[1] = 8192;
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, test4);

  null_decimal(&test);
  test.bits[0] = 4210752250u;
  test.bits[1] = 2013877370u;
  test.bits[2] = 3061093559u;
  test.bits[3] = 2149318656u;
  ck_assert_int_eq(s21_from_decimal_to_float(test, &result), CODE_OK);
  ck_assert_float_eq(result, test5);
}
END_TEST

Suite *s21_from_decimal_to_float_suite() {
  Suite *s = suite_create("s21_from_decimal_to_float");
  TCase *tc_corner = tcase_create("corner"),
        *tc_additional = tcase_create("additional");

  tcase_add_test(tc_corner, zero_check_s21_from_decimal_to_float);
  tcase_add_test(tc_corner, negative_one_check_s21_from_decimal_to_float);
  tcase_add_test(tc_corner, incorrect_decimal_check_s21_from_decimal_to_float);
  suite_add_tcase(s, tc_corner);

  tcase_add_test(tc_additional, additional_check_s21_from_decimal_to_float);
  suite_add_tcase(s, tc_additional);

  return s;
}
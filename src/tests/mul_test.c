#include "check_s21_decimal.h"

START_TEST(add_int_1) {
  s21_decimal decimal_1 = {{17, 0, 0, 0}};
  s21_decimal decimal_2 = {{16, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 272);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_2) {
  s21_decimal decimal_1 = {{17, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal_set_power(&decimal_1, 1);
  // -1.7 + 2
  s21_decimal decimal_2 = {{2, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  float dst = 0;
  int test = s21_from_decimal_to_float(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_float_eq(dst, -3.4);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_3) {
  s21_decimal decimal_1 = {{1000, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{1000, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 1000000);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_4) {
  s21_decimal decimal_1 = {{1, 0, 0, 0}};
  s21_decimal decimal_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 1);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_5) {
  s21_decimal decimal_1 = {{MAX_INT - 1, 0, 0, 0}};
  s21_decimal decimal_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, MAX_INT - 1);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_6) {
  s21_decimal decimal_1 = {{2, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{3, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 6);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_7) {
  s21_decimal decimal_1 = {{2147483647, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{0, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 0);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_8) {
  s21_decimal decimal_1 = {{159, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 0);
  s21_decimal decimal_2 = {{150, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, -23850);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_9) {
  s21_decimal decimal_1 = {{256000, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{255999, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  ck_assert_uint_eq(result.bits[0], 1111234560);
  ck_assert_uint_eq(result.bits[1], 15);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_int_eq(s21_decimal_get_sign(result), 1);
  ck_assert_int_eq(s21_decimal_get_power(result), 0);
}
END_TEST
START_TEST(add_int_10) {
  // -1 * -255999
  s21_decimal decimal_1 = {{1, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{255999, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  int dst = 0;
  int test = s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(dst, 255999);
  ck_assert_int_eq(test, OK);
}
END_TEST

START_TEST(add_int_11) {
  // 104 * 26
  s21_decimal decimal_1 = {{104, 0, 0, 0}};
  s21_decimal decimal_2 = {{26, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  ck_assert_int_eq(result.bits[0], 2704);
}
END_TEST

START_TEST(add_int_12) {
  // 1.004 * 267
  s21_decimal decimal_1 = {{1004, 0, 0, 0}};
  s21_decimal_set_power(&decimal_1, 3);
  s21_decimal decimal_2 = {{267, 0, 0, 0}};
  s21_decimal_set_power(&decimal_2, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, (268.068));
}
END_TEST
START_TEST(add_int_13) {
  //
  s21_decimal decimal_1 = {{MAX_UINT, 0, 0, 0}};
  s21_decimal decimal_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal true_result = {{MAX_UINT, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  for (int i = 0; i < 4; i++) {
    ck_assert_uint_eq(result.bits[i], true_result.bits[i]);
  }

  ck_assert_int_eq(state, OK);
}
END_TEST

START_TEST(add_0) {
  s21_decimal val1 = {{15, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int state = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, state);
}
END_TEST

START_TEST(add_1) {
  s21_decimal val1 = {{15, 0, 0, 0}};
  s21_decimal val2 = {{15, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  int state = s21_mul(val1, val2, &res);
  ck_assert_int_eq(0, state);
}
END_TEST

START_TEST(add_2) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_3) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_4) {
  s21_decimal val1 = {{8, 0, 0, 0}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_5) {
  s21_decimal val1 = {{2, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_6) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{2, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_7) {
  s21_decimal val1 = {{2, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{8, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_8) {
  s21_decimal val1 = {{0}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_9) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{8, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_10) {
  s21_decimal val1 = {{8, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_11) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal_set_sign(&val1, 1);
  s21_decimal val2 = {{4, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_12) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{4, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_13) {
  s21_decimal val1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal val2 = {{4, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_14) {
  s21_decimal val1 = {{4, 0, 0, 0}};
  s21_decimal val2 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_15) {
  s21_decimal val1 = {{4, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_16) {
  s21_decimal val1 = {{4, 0, 0, ~(MAX_UINT / 2)}};
  s21_decimal val2 = {{MAX_UINT, MAX_UINT, MAX_UINT, ~(MAX_UINT / 2)}};
  s21_decimal res = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_mul(val1, val2, &res));
}
END_TEST

START_TEST(add_19) {
  s21_decimal decimal_1 = {{20, 0, 0, 0}};
  s21_decimal decimal_2 = {{17, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, 340);
}
END_TEST

START_TEST(add_20) {
  s21_decimal decimal_1 = {{20, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal decimal_2 = {{17, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, -340);
}
END_TEST

START_TEST(add_21) {
  s21_decimal decimal_1 = {{20, 0, 0, 0}};
  s21_decimal decimal_2 = {{17, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_mul(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, -340);
}
END_TEST

START_TEST(test_s21_add_22) {
  s21_decimal test_value_1 = {{-1, 0, 0, 0}};
  s21_decimal test_value_2 = {{100, 0, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mul(test_value_1, test_value_2, &result_dec);
  unsigned a = result_dec.bits[0];
  ck_assert_uint_eq(a, 4294967196);
  ck_assert_uint_eq(result_dec.bits[1], 99);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_25) {
  // 428 * 165
  s21_decimal test_value_1 = {{428, 0, 0, 0}};
  s21_decimal test_value_2 = {{165, 0, 0, 131072}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_mul(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 70620);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
  ck_assert_uint_eq(result_dec.bits[3], 131072);
}
END_TEST

START_TEST(add_25) {
  // -1234 * 1.234
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  null_decimal(&src1);
  null_decimal(&src2);
  null_decimal(&result);

  float res_origin = -1522.756;
  float res_our;

  src1.bits[0] = 1234;
  s21_decimal_set_sign(&src1, 1);

  src2.bits[0] = 1234;
  s21_decimal_set_power(&src2, 3);
  s21_decimal_set_sign(&src2, 0);

  s21_mul(src1, src2, &result);

  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_26) {
  // -1234 * -1.234
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int a = -1234;
  src2.bits[0] = 1234;
  s21_decimal_set_power(&src2, 3);
  s21_decimal_set_sign(&src2, 1);
  float res_origin = 1522.756;
  float res_our;
  s21_from_int_to_decimal(a, &src1);
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_27) {
  // -1234 * -221.23401
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  src1.bits[0] = 1234;
  s21_decimal_set_sign(&src1, 1);

  src2.bits[0] = 22123401;
  s21_decimal_set_power(&src2, 5);
  s21_decimal_set_sign(&src2, 1);
  float res_origin = 273002.76834;
  float res_our;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_28) {
  // 0.00234 * -9403
  s21_decimal src1 = {0}, src2 = {0}, result = {0};

  float res_origin = -22.00302;
  float res_our;

  src2.bits[0] = 234;
  s21_decimal_set_power(&src2, 5);

  src1.bits[0] = 9403;
  s21_decimal_set_sign(&src1, 1);

  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_29) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  float res_origin = -220.0302;
  float res_our;

  src2.bits[0] = 234;
  s21_decimal_set_power(&src2, 3);
  // 0.234 * -940.3
  src1.bits[0] = 9403;
  s21_decimal_set_power(&src1, 1);
  s21_decimal_set_sign(&src1, 1);

  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_30) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  float res_origin = -20.704734197;
  float res_our;
  // -0.9401
  src1.bits[0] = 9401;
  s21_decimal_set_sign(&src1, 1);
  s21_decimal_set_power(&src1, 4);

  src2.bits[0] = 2202397;
  s21_decimal_set_sign(&src2, 0);
  s21_decimal_set_power(&src2, 5);
  // 22.02397

  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_31) {
  // -0.9403 * -112.0234
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  float res_origin = 105.335603;
  float res_our;
  src1.bits[0] = 9403;
  s21_decimal_set_power(&src1, 4);
  s21_decimal_set_sign(&src1, 1);

  src2.bits[0] = 1120234;
  s21_decimal_set_power(&src2, 4);
  s21_decimal_set_sign(&src2, 1);

  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_32) {
  // -940 * -11200
  s21_decimal src1 = {0}, src2 = {0}, result = {0}, res = {0};
  src1.bits[0] = 940;
  s21_decimal_set_sign(&src1, 1);
  src2.bits[0] = 11200;
  s21_decimal_set_sign(&src2, 1);
  res.bits[0] = 10528000;
  s21_decimal_set_sign(&res, 0);

  float res_our, res_origin;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our);
  s21_from_decimal_to_float(res, &res_origin);
  ck_assert_float_eq(res_our, res_origin);
}
END_TEST

START_TEST(add_33) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  src1.bits[0] = 940;
  src2.bits[0] = 11200;
  s21_mul(src1, src2, &result);
  ck_assert_float_eq(10528000, result.bits[0]);
}
END_TEST

START_TEST(add_34) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  src1.bits[0] = 1000000000;
  src2.bits[0] = 1;
  s21_decimal_set_power(&src1, 10);
  s21_decimal_set_power(&src2, 20);
  s21_mul(src1, src2, &result);
  ck_assert_float_eq(10000000, result.bits[0]);
}
END_TEST

Suite *test_mul() {
  Suite *s = suite_create("s21_test_mul_suite");
  TCase *tc = tcase_create("mul");

  tcase_add_test(tc, add_int_1);
  tcase_add_test(tc, add_int_2);
  tcase_add_test(tc, add_int_3);
  tcase_add_test(tc, add_int_4);
  tcase_add_test(tc, add_int_5);
  tcase_add_test(tc, add_int_6);
  tcase_add_test(tc, add_int_7);
  tcase_add_test(tc, add_int_8);
  tcase_add_test(tc, add_int_9);
  tcase_add_test(tc, add_int_10);
  tcase_add_test(tc, add_int_11);
  tcase_add_test(tc, add_int_12);
  tcase_add_test(tc, add_int_13);
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
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);
  tcase_add_test(tc, add_13);
  tcase_add_test(tc, add_14);
  tcase_add_test(tc, add_15);
  tcase_add_test(tc, add_16);
  tcase_add_test(tc, add_19);
  tcase_add_test(tc, add_20);
  tcase_add_test(tc, add_21);
  tcase_add_test(tc, test_s21_add_22);
  tcase_add_test(tc, test_s21_add_25);
  tcase_add_test(tc, add_25);
  tcase_add_test(tc, add_26);
  tcase_add_test(tc, add_27);
  tcase_add_test(tc, add_28);
  tcase_add_test(tc, add_29);
  tcase_add_test(tc, add_30);
  tcase_add_test(tc, add_31);
  tcase_add_test(tc, add_32);
  tcase_add_test(tc, add_33);
  tcase_add_test(tc, add_34);

  suite_add_tcase(s, tc);
  return s;
}
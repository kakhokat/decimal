#include "check_s21_decimal.h"

START_TEST(sub_int_1) {
  s21_decimal decimal_1 = {{20, 0, 0, 0}};
  s21_decimal decimal_2 = {{17, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, 37);
}
END_TEST

START_TEST(sub_int_2) {
  s21_decimal decimal_1 = {{5439, 0, 0, 0}};
  s21_decimal decimal_2 = {{343, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, -(5439 + 343));
}
END_TEST

START_TEST(sub_int_3) {
  s21_decimal decimal_1 = {{10, 0, 0, 0}};
  s21_decimal decimal_2 = {{15, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, (-10 - (-15)));
}
END_TEST

START_TEST(sub_int_4) {
  s21_decimal decimal_1 = {{15, 0, 0, 0}};
  s21_decimal decimal_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(decimal_1, decimal_2, &result);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, (15 - 10));
}
END_TEST

START_TEST(sub_int_5) {
  s21_decimal decimal_1 = {{10, 0, 0, 0}};
  s21_decimal decimal_2 = {{15, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_sub(decimal_1, decimal_2, &result);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, (10 - 15));
}
END_TEST

START_TEST(sub_int_6) {
  s21_decimal decimal_1 = {{438324, 0, 0, 0}};
  s21_decimal decimal_2 = {{9999999, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, (438324 - 9999999));
}
END_TEST

START_TEST(sub_int_7) {
  s21_decimal decimal_1 = {{438928429, 0, 0, 0}};
  s21_decimal decimal_2 = {{4130001, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  int dst = 0;
  s21_from_decimal_to_int(result, &dst);
  ck_assert_int_eq(dst, (438928429 - 4130001));
}
END_TEST

START_TEST(sub_float_1) {
  s21_decimal decimal_1 = {{132, 0, 0, 0}};
  s21_decimal_set_power(&decimal_1, 1);
  s21_decimal decimal_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, (13.2 - 10));
}
END_TEST

START_TEST(sub_float_2) {
  s21_decimal decimal_1 = {{349321, 0, 0, 0}};
  s21_decimal_set_power(&decimal_1, 2);
  s21_decimal decimal_2 = {{349321, 0, 0, 0}};
  s21_decimal_set_power(&decimal_2, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, 0);
}
END_TEST

START_TEST(sub_float_3) {
  s21_decimal decimal_1 = {{93493321, 0, 0, 0}};
  s21_decimal_set_power(&decimal_1, 2);
  s21_decimal decimal_2 = {{12349321, 0, 0, 0}};
  s21_decimal_set_power(&decimal_2, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, (934933.21 - 1234.9321));
}
END_TEST

START_TEST(sub_float_4) {
  s21_decimal decimal_1 = {{93493321, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal_set_power(&decimal_1, 2);
  s21_decimal decimal_2 = {{12349321, 0, 0, 0}};
  s21_decimal_set_power(&decimal_2, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, -(934933.21 + 1234.9321));
}
END_TEST

START_TEST(sub_float_5) {
  s21_decimal decimal_1 = {{93493321, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_1, 1);
  s21_decimal_set_power(&decimal_1, 2);
  s21_decimal decimal_2 = {{12349321, 0, 0, 0}};
  s21_decimal_set_sign(&decimal_2, 1);
  s21_decimal_set_power(&decimal_2, 4);
  s21_decimal result = {{0, 0, 0, 0}};
  int state = s21_sub(decimal_1, decimal_2, &result);
  ck_assert_int_eq(state, OK);
  float dst = 0;
  s21_from_decimal_to_float(result, &dst);
  ck_assert_float_eq(dst, (-934933.21 + 1234.9321));
}
END_TEST

START_TEST(test_s21_sub_1) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  int a = 9403;
  int b = 202;
  int res_origin = 9201;
  int res_our = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_sub(src1, src2, &result);
  s21_from_decimal_to_int(result, &res_our);
  ck_assert_int_eq(res_our, res_origin);
}
END_TEST

START_TEST(test_s21_sub_7) {
  s21_decimal src1 = {0}, src2 = {0}, result = {0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin = {0};
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_sub_8) {
  s21_decimal test_value_1 = {{999, 1, 0, 0}};
  s21_decimal test_value_2 = {{1999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1000);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_9) {
  s21_decimal test_value_1 = {{-1, 0, 0, 0}};
  s21_decimal test_value_2 = {{999999999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1000000000);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_10) {
  s21_decimal test_value_1 = {{-4001, 0, 0, 0}};
  s21_decimal test_value_2 = {{1000001999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 1000006000);
  ck_assert_uint_eq(result_dec.bits[1], 0);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST
START_TEST(test_s21_sub_11) {
  s21_decimal test_value_1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal_set_sign(&test_value_1, 1);
  s21_decimal test_value_2 = {{1000001999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_sub(test_value_1, test_value_2, &result_dec));
}
END_TEST
START_TEST(test_s21_sub_12) {
  s21_decimal test_value_2 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_value_1 = {{1000001999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_sub(test_value_1, test_value_2, &result_dec));
}
END_TEST
START_TEST(test_s21_sub_13) {
  s21_decimal test_value_1 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_value_2 = {{1000001999, 1, 0, ~(MAX_UINT / 2)}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_sub(test_value_1, test_value_2, &result_dec));
}
END_TEST
START_TEST(test_s21_sub_14) {
  s21_decimal test_value_2 = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
  s21_decimal test_value_1 = {{1000001999, 1, 0, 0}};
  s21_decimal result_dec = {{0, 0, 0, 0}};
  ck_assert_int_eq(0, s21_sub(test_value_1, test_value_2, &result_dec));
}
END_TEST

Suite *test_sub() {
  Suite *s = suite_create("s21_test_sub_suite");
  TCase *tc = tcase_create("sub");

  tcase_add_test(tc, sub_int_1);
  tcase_add_test(tc, sub_int_2);
  tcase_add_test(tc, sub_int_3);
  tcase_add_test(tc, sub_int_4);
  tcase_add_test(tc, sub_int_5);
  tcase_add_test(tc, sub_int_6);
  tcase_add_test(tc, sub_int_7);
  tcase_add_test(tc, sub_float_1);
  tcase_add_test(tc, sub_float_2);
  tcase_add_test(tc, sub_float_3);
  tcase_add_test(tc, sub_float_4);
  tcase_add_test(tc, sub_float_5);
  tcase_add_test(tc, test_s21_sub_1);
  tcase_add_test(tc, test_s21_sub_7);
  tcase_add_test(tc, test_s21_sub_8);
  tcase_add_test(tc, test_s21_sub_9);
  tcase_add_test(tc, test_s21_sub_10);
  tcase_add_test(tc, test_s21_sub_11);
  tcase_add_test(tc, test_s21_sub_12);
  tcase_add_test(tc, test_s21_sub_13);
  tcase_add_test(tc, test_s21_sub_14);

  suite_add_tcase(s, tc);
  return s;
}
#include "s21_mul.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res;
  if ((value_1.bits[0] == 0 && value_1.bits[1] == 0 && value_1.bits[2] == 0) ||
      (value_2.bits[0] == 0 && value_2.bits[1] == 0 && value_2.bits[2] == 0)) {
    int sign_result = 5;
    if (s21_decimal_get_sign(value_1) != s21_decimal_get_sign(value_2)) {
      sign_result = 1;
    } else {
      sign_result = 0;
    }
    res = 0;
    int power = s21_decimal_get_power(value_1) + s21_decimal_get_power(value_2);
    s21_decimal_set_power(result, power);
    s21_decimal_set_sign(result, sign_result);
  } else {
    if (s21_is_greater(value_1, value_2)) {
      res = s21_mul_process(value_2, value_1, result);
    } else {
      res = s21_mul_process(value_1, value_2, result);
    }
  }
  if (s21_decimal_get_power(*result) > MAX_POWER) {
    s21_normalyze(result);
  }
  return res;
}

int s21_mul_process(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
  int res = 0;
  int sign_result = 5;
  if (s21_decimal_get_sign(value_1) != s21_decimal_get_sign(value_2)) {
    sign_result = 1;
  } else {
    sign_result = 0;
  }
  s21_decimal_set_sign(&value_1, 0);
  s21_decimal_set_sign(&value_2, 0);
  int bit1 = s21_decimal_get_last_bit(value_1);
  for (int i = 0; i <= bit1 && !res; i++) {
    s21_big_decimal tmp_value_2_big = {0};
    s21_big_decimal tmp_result_big = s21_from_decimal_to_big_decimal(*result);
    int value_bit_1 = s21_get_bit(value_1, i);
    if (value_bit_1) {
      tmp_value_2_big = s21_from_decimal_to_big_decimal(value_2);
      s21_big_mantissa_shift_left(&tmp_value_2_big, i);
      s21_big_sum(tmp_result_big, tmp_value_2_big, &tmp_result_big);
      s21_big_decimal_set_power(
          &tmp_result_big,
          s21_decimal_get_power(value_1) + s21_decimal_get_power(value_2));
      res = s21_from_big_decimal_to_decimal(tmp_result_big, result);
    }
  }
  s21_decimal_set_sign(result, sign_result);
  if (res && sign_result) res = 2;
  return res;
}
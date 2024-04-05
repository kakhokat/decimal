#include "s21_sub.h"

// пока без вычитания и без проверки на переполнение
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (s21_is_equal_sign(value_1, value_2) == true) {
    if (s21_decimal_get_sign_char(value_1) ==
        '-') {  // (-3) - (-5) = -(3 - 5) = 5 - 3
      s21_decimal_set_sign(&value_1, 0);
      s21_decimal_set_sign(&value_2, 0);
      s21_sub(value_2, value_1, result);
    } else {
      s21_to_one_denominator(&value_1, &value_2);
      s21_decimal temp_result = {0};
      if (s21_is_greater(value_1, value_2)) {
        s21_minus(value_1, value_2, &temp_result);
        s21_decimal_set_sign(&temp_result, s21_decimal_get_sign(value_1));
      } else {
        s21_minus(value_2, value_1, &temp_result);
        s21_decimal_set_sign(&temp_result, !s21_decimal_get_sign(value_2));
      }
      s21_decimal_set_power(&temp_result, s21_decimal_get_power(value_1));
      *result = temp_result;
    }

  } else {
    s21_decimal_set_sign(&value_2, !s21_decimal_get_sign(value_2));
    error = s21_add(value_1, value_2, result);
  }
  return error;
}

void s21_minus(s21_decimal max_value, s21_decimal min_value,
               s21_decimal *result) {
  int bits_to_change = 0;
  for (int cur_bit = START_OF_BIT_3 - 1; cur_bit >= 0; cur_bit--) {
    if (s21_get_bit(max_value, cur_bit) == s21_get_bit(min_value, cur_bit)) {
      s21_set_bit(result, cur_bit, 0);
    } else if (s21_get_bit(max_value, cur_bit) == 1) {
      s21_set_bit(result, cur_bit, 1);
    } else {
      while (s21_get_bit(*result, cur_bit) != 1) {
        cur_bit++;
        bits_to_change++;
      }
      s21_set_bit(result, cur_bit, 0);
      while (bits_to_change != 0) {
        cur_bit--;
        bits_to_change--;
        s21_set_bit(result, cur_bit, 1);
      }
    }
  }
}
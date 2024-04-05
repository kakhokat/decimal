#include "s21_is_equal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  bool Result = false;
  s21_to_one_denominator(&value_1, &value_2);
  if (s21_is_equal_sign(value_1, value_2) == true) {
    if (s21_is_equal_get_main_result(value_1, value_2) == true) {
      Result = true;
    }
  }
  return Result;
}

int s21_is_equal_sign(s21_decimal value_1, s21_decimal value_2) {
  bool Result = false;
  if (s21_decimal_get_sign_char(value_1) ==
      s21_decimal_get_sign_char(value_2)) {
    Result = true;
  }
  return Result;
}

int s21_is_equal_get_main_result(s21_decimal value_1, s21_decimal value_2) {
  int Result = 1;
  int current_bit = 95;  // START_OF_BIT_3 - 1
  while (current_bit >= 0 && Result == 1) {
    if (s21_get_bit(value_1, current_bit) !=
        s21_get_bit(value_2, current_bit)) {
      Result = 0;
    }
    current_bit--;
  }
  return Result == 1 ? true : false;
}
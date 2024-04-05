#include "s21_is_greater.h"

// если 2 отрицательных правильно ли работает проверить
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  bool Result = false;
  s21_to_one_denominator(&value_1, &value_2);
  if (s21_is_equal(value_1, value_2) == true) {
    Result = false;
  } else if (s21_is_greater_sign(value_1, value_2) == true) {
    Result = true;
  } else if (s21_is_greater_get_main_result(value_1, value_2) == true &&
             s21_is_equal_sign(value_1, value_2) == true) {
    Result = true;
  }
  return Result;
}

int s21_is_greater_sign(s21_decimal value_1, s21_decimal value_2) {
  bool Result = false;
  if (s21_decimal_get_sign_char(value_1) == '+' &&
      s21_decimal_get_sign_char(value_2) == '-') {
    Result = true;
  } else {
    Result = false;
  }
  return Result;
}

int s21_is_greater_get_main_result(s21_decimal value_1, s21_decimal value_2) {
  int Result = -1;
  int current_bit = 95;  // START_OF_BIT_3 - 1
  if (s21_is_equal_sign(value_1, value_2) == true &&
      s21_decimal_get_sign_char(value_1) == '-') {
    while (current_bit >= 0 && Result == -1) {
      if (s21_get_bit(value_1, current_bit) >
          s21_get_bit(value_2, current_bit)) {
        Result = 0;
      } else if (s21_get_bit(value_1, current_bit) <
                 s21_get_bit(value_2, current_bit)) {
        Result = 1;
      }
      current_bit--;
    }
  } else {
    while (current_bit >= 0 && Result == -1) {
      if (s21_get_bit(value_1, current_bit) <
          s21_get_bit(value_2, current_bit)) {
        Result = 0;
      } else if (s21_get_bit(value_1, current_bit) >
                 s21_get_bit(value_2, current_bit)) {
        Result = 1;
      }
      current_bit--;
    }
  }
  return Result == 1 ? true : false;
}
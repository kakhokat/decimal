#include "help.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int check_minus = 0;
  s21_decimal half = {0};  // создаем decimal = 0,5
  half.bits[0] = 5;
  s21_decimal_set_power(&half, 1);
  s21_decimal number_one = {0};
  number_one.bits[0] = 1;
  if (is_correct_decimal(value) == 1 ||
      result == NULL) {  // проверяем, что decimal корректный и что выделено
                         // место под результат
    return 1;
  }
  s21_truncate(value, result);
  s21_decimal value_2 = *result;
  s21_sub(value, value_2, result);
  s21_decimal non_integer_part = *result;
  if (s21_decimal_get_sign(non_integer_part) == 1) {
    s21_negate(non_integer_part, result);
    non_integer_part = *result;
    check_minus = 1;
  }
  if (s21_is_greater_or_equal(non_integer_part, half) == 1) {
    s21_truncate(value, result);
    if (check_minus == 1) {
      s21_sub(*result, number_one, result);
    } else {
      s21_add(*result, number_one, result);
    }
  } else {
    s21_truncate(value, result);
  }
  return 0;
}
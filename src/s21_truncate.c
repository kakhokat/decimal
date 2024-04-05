#include "help.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_decimal number_zero = {0};
  if (is_correct_decimal(value) == 1 ||
      result == NULL) {  // проверяем, что decimal корректный и что выделено
                         // место под результат
    return 1;
  }
  int decimal_power = s21_decimal_get_power(value);
  for (int i = 0; i < decimal_power; i++) {
    s21_divide_by_10(&value);
  }
  s21_decimal_set_power(&value, 0);
  *result = value;
  s21_decimal check = *result;
  if (number_zero.bits[0] == check.bits[0] &&
      number_zero.bits[1] == check.bits[1] &&
      number_zero.bits[2] == check.bits[2]) {  // проверка на равенство 0, далее
                                               // делаем его положительным
    s21_decimal_set_sign(result, 0);
  }
  return 0;
}
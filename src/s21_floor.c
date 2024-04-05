#include "help.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal number_one = {0};
  number_one.bits[0] = 1;
  if (is_correct_decimal(value) == 1 ||
      result == NULL) {  // проверяем, что decimal корректный и что выделено
                         // место под результат
    return 1;
  }
  s21_truncate(value, result);
  if (s21_is_equal(value, *result) == 1) {
    s21_truncate(value, result);
  } else {
    if (s21_decimal_get_sign(value) ==
        0) {  // если знак + => убираем дробную часть
      s21_truncate(value, result);
    } else {
      if (!(value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0)) {
        s21_truncate(value, result);
        value = *result;
        s21_sub(value, number_one, result);
      }
    }
  }
  return 0;
}
#include "help.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (is_correct_decimal(value) == 1 ||
      result == NULL) {  // проверяем, что decimal корректный и что выделено
                         // место под результат
    return 1;
  }
  if (s21_decimal_get_sign(value) == 1) {
    s21_decimal_set_sign(&value, 0);
  } else {
    s21_decimal_set_sign(&value, 1);
  }
  *result = value;
  return 0;
}
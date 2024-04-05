#ifndef S21_SUB_H
#define S21_SUB_H

#include "help.h"
#include "s21_is_equal.h"

void s21_minus(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_try_to_avoid_overflow_for_sub(s21_decimal *decimal1,
                                      s21_decimal *decimal2);
#endif
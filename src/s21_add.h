#ifndef S21_ADD_H
#define S21_ADD_H

#include "help.h"
#include "s21_big_decimal.h"

void s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_try_to_avoid_overflow_for_add(s21_decimal *decimal1,
                                      s21_decimal *decimal2);
#endif
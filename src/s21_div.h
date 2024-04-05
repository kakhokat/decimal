#ifndef S21_DIV_H
#define S21_DIV_H

#include "help.h"
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div1(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *tmp);

#endif
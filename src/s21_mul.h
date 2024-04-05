#ifndef S21_MUL_H
#define S21_MUL_H

#include "help.h"
#include "s21_add.h"
#include "s21_big_decimal.h"
#include "s21_sub.h"

int s21_mul_process(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
#endif
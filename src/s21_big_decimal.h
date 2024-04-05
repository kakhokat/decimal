#ifndef S21_BIG_DECIMAL_H
#define S21_BIG_DECIMAL_H

#include "help.h"
#include "s21_add.h"
#include "s21_div.h"
#include "s21_is_equal.h"

typedef struct s21_big_decimal {
  unsigned int bits[7];
} s21_big_decimal;

int s21_big_get_bit(const s21_big_decimal big_decimal, int index);

void s21_big_set_bit(s21_big_decimal *big_decimal, int index, int value);

void s21_big_mantissa_shift_left_ones(s21_big_decimal *big_decimal);

s21_big_decimal s21_big_mantissa_shift_left_copy_ones(
    s21_big_decimal big_decimal);

void s21_big_mantissa_shift_right_ones(s21_big_decimal *big_decimal);

// s21_decimal s21_mantissa_shift_right_copy_ones(s21_decimal decimal);

s21_big_decimal s21_big_new_decimal(int sign, int power, unsigned int int1,
                                    unsigned int int2, unsigned int int3,
                                    unsigned int int4, unsigned int int5,
                                    unsigned int int6);

void s21_big_clear_decimal(s21_big_decimal *big_decimal);

int s21_big_decimal_get_sign_char(s21_big_decimal big_decimal);
int s21_big_decimal_get_sign(s21_big_decimal big_decimal);

void s21_big_decimal_set_sign(s21_big_decimal *big_decimal, int sign);

int s21_big_decimal_get_power(s21_big_decimal big_decimal);

void s21_big_decimal_set_power(s21_big_decimal *big_decimal,
                               unsigned int power);

void s21_big_print_decimal(s21_big_decimal big_decimal);
void s21_big_multiply_by_10(s21_big_decimal *big_decimal);

// // потом сделаю как надо
void s21_big_divide_by_10(s21_big_decimal *big_decimal);

void s21_big_to_one_denominator(s21_big_decimal *big_decimal1,
                                s21_big_decimal *big_decimal2);

void s21_big_to_one_denominator_proccess(s21_big_decimal *big_decimal1,
                                         s21_big_decimal *big_decimal2);
void s21_big_print_decimal_as_ints(s21_big_decimal big_decimal);
s21_big_decimal s21_from_decimal_to_big_decimal(s21_decimal decimal);

int s21_from_big_decimal_to_decimal(s21_big_decimal big_decimal,
                                    s21_decimal *result);
void s21_big_sum(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result);

// ------------------------------------------------------------------

int s21_big_is_equal(s21_big_decimal value_1, s21_big_decimal value_2);

int s21_big_is_equal_sign(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_big_is_equal_get_main_result(s21_big_decimal value_1,
                                     s21_big_decimal value_2);
int s21_big_is_greater(s21_big_decimal value_1, s21_big_decimal value_2);

int s21_big_is_greater_sign(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_big_is_greater_get_main_result(s21_big_decimal value_1,
                                       s21_big_decimal value_2);
int s21_big_is_greater(s21_big_decimal value_1, s21_big_decimal value_2);

int s21_big_is_less_or_equal(s21_big_decimal value_1, s21_big_decimal value_2);

void s21_big_minus(s21_big_decimal max_value, s21_big_decimal min_value,
                   s21_big_decimal *result);

void bank_round(s21_big_decimal val, s21_big_decimal *result);

s21_big_decimal s21_div_supp(s21_big_decimal value_1, s21_big_decimal value_2,
                             s21_big_decimal *result);
s21_big_decimal s21_big_new_divide_by_10(s21_big_decimal *value_1);
void s21_big_mantissa_shift_left(s21_big_decimal *big_decimal, int i);
#endif
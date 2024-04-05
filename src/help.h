#ifndef HELP_H
#define HELP_H

#define MAX_INDEX 127
#define COUNT_OF_bits 128
#define MAX_POWER 28
#define SHIFT_TO_START_OF_POWER 16
#define START_OF_BIT_1 32
#define START_OF_BIT_2 64
#define START_OF_BIT_3 96
#define START_OF_BIT_4 128
#define START_OF_BIT_5 160
#define START_OF_BIT_6 192
#define NUM_bits 32


#define OK 0
#define INF(X) (X == (1.0 / 0.0))
#define NEG_INF(X) (X == (-1.0 / 0.0))
#define MAX_UINT 4294967295
//               -1
//               4294962297
#define MAX_INT 2147483647
//               2147483648
// 1  1111111111 1111111111 1111111111
// 11 1111111111 1111111111 1111111111
// 10 0000000000 0000000000 0000000000
#define MIN_INT 2147483648
#define s21_NULL (void *)0
#define MAX_DEC 79228162514264337593543950336.0f
#define SCALE 0x00ff0000

// проверить что POWER_MASK правильно
#define POWER_MASK 0b00000000111111110000000000000000U
#define SIGN_MASK 0b10000000000000000000000000000000U
#define CORRECT_DECIMAL_MASK 0b01111111000000001111111111111111

#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "s21_decimal.h"

// определяет порядковый номер массива десимал по индексу бита
int s21_get_sequence_number_of_bit(int index);

// индекс бита внутри массива
int s21_get_rounded_index(int index);

/**
 * получить значение бита
 * @param decimal десимал
 * @param index индекс бита
 * @return значение бита
 */
int s21_get_bit(s21_decimal decimal, int index);

/**
 * установить значение бита
 * @param decimal десимал
 * @param index индекс бита
 * @param value значение
 */
void s21_set_bit(s21_decimal *decimal, int index, int value);

// создание десимала
s21_decimal s21_new_decimal(int sign, int power, unsigned int int1,
                            unsigned int int2, unsigned int int3);

// обнуление десимала
void s21_clear_decimal(s21_decimal *decimal);

/**
 * получение знака
 * @param decimal десимал
 * @return '-' или '+'
 */
int s21_decimal_get_sign_char(s21_decimal decimal);

// получение знака (1 - минус, 0 - плюс)
int s21_decimal_get_sign(s21_decimal decimal);

// установка знака ('-' или 1 - минус, '+' или 0 - плюс)
void s21_decimal_set_sign(s21_decimal *decimal, int sign);

// получение степени
int s21_decimal_get_power(s21_decimal decimal);

// установка степени
void s21_decimal_set_power(s21_decimal *decimal, unsigned int power);

// печать десимала
void s21_print_decimal(s21_decimal declimal);

// сдвиг десимала влево на 1
void s21_mantissa_shift_left_ones(s21_decimal *decimal);
s21_decimal s21_mantissa_shift_left_copy_ones(s21_decimal decimal);

// сдвиг десимала вправо на 1
void s21_mantissa_shift_right_ones(s21_decimal *decimal);
s21_decimal s21_mantissa_shift_right_copy_ones(s21_decimal decimal);

// приведение к общему знаменателю с нормализацией
void s21_to_one_denominator(s21_decimal *decimal1, s21_decimal *decimal2);

// приведение к общему знаменателю
void s21_to_one_denominator_proccess(s21_decimal *decimal1,
                                     s21_decimal *decimal2);

// нормализация
void s21_normalyze(s21_decimal *decimal);

// попытка избежать переполнения
int s21_try_to_avoid_overflow(s21_decimal *decimal1, s21_decimal *decimal2);

// умножение на 10
void s21_multiply_by_10(s21_decimal *decimal);

// деление на 10
void s21_divide_by_10(s21_decimal *decimal);

// печать десимала в виде целых чисел
void s21_print_decimal_as_ints(s21_decimal decimal);

int s21_shift_left(unsigned int number, int size);
int s21_shift_right(unsigned int number, int size);

// --------------------------------------------------------
s21_decimal abs_decimal(s21_decimal val);

int s21_decimal_get_last_bit(s21_decimal decimal);
void s21_mantissa_shift_left(s21_decimal *decimal, int shift);
void s21_mantissa_shift_right(s21_decimal *decimal, int shift);
void s21_decimal_scale_decrease(s21_decimal *decimal, int shift);
void null_decimal(s21_decimal* dec);
int is_correct_decimal(s21_decimal value);

#endif
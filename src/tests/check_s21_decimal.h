#ifndef CHECK_S21_DECIMAL_H
#define CHECK_S21_DECIMAL_H

#include <check.h>
#include <stdlib.h>
#include <string.h>

#include "../help.h"
#include "../s21_big_decimal.h"

#define TRUE 1
#define FALSE 0
#define MAX_UINT 4294967295

#define CODE_OK 0
#define CODE_CONVERTATION_ERROR 1
#define CODE_CALCULATING_ERROR 1
#define OK 0
#define INF(X) (X == (1.0 / 0.0))
#define NEG_INF(X) (X == (-1.0 / 0.0))
#define MAX_INT 2147483647
//               2147483648
// 1  1111111111 1111111111 1111111111
// 11 1111111111 1111111111 1111111111
// 10 0000000000 0000000000 0000000000
#define MIN_INT 2147483648
#define s21_NULL (void *)0
#define MAX_DEC 79228162514264337593543950336.0f
Suite *test_add(void);
Suite *test_sub(void);
Suite *test_mul(void);
Suite *test_div(void);

Suite *s21_is_equal_suite();
Suite *s21_is_not_equal_suite();
Suite *s21_is_greater_suite();
Suite *s21_is_less_suite();
Suite *s21_is_less_or_equal_suite();
Suite *s21_is_greater_or_equal_suite();

Suite *s21_from_int_to_decimal_suite();
Suite *s21_from_float_to_decimal_suite();
Suite *s21_from_decimal_to_int_suite();
Suite *s21_from_decimal_to_float_suite();

Suite *s21_floor_suite();
Suite *s21_round_suite();
Suite *s21_truncate_suite();
Suite *s21_negate_suite();

#endif

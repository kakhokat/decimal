#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

// Арифметические операторы
// Возвращаемое значение:
// 0 - ОК
// 1 - число слишком велико или равно бесконечности
// 2 - число слишком мало или равно отрицательной бесконечности
// 3 - деление на 0

// Сложение +
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Вычитание -
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Умножение *
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Деление /
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Уточнение о числах, не въезжающих в мантиссу:
// При получении чисел, не въезжающих в мантиссу при арифметических операциях,
// используйте банковское округление (например, 79 228 162 514 264 337 593 543
// 950 335 - 0,6 = 79 228 162 514 264 337 593 543 950 334)
// -------------------------------------------

// Операторы сравнения
// Возвращаемое значение:
// 0 – ЛОЖЬ
// 1 – ВЕРНО

// Меньше <
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
// Больше >
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
// Равно ==
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
// Не равно !=
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
// -------------------------------------------

// Преобразователи
// Возвращаемое значение – код ошибки:
// 0 - ОК
// 1 - ошибка конвертации

// Из int
int s21_from_int_to_decimal(int src, s21_decimal *dst);

// Из float
int s21_from_float_to_decimal(float src, s21_decimal *dst);

// В int
int s21_from_decimal_to_int(s21_decimal src, int *dst);

// В float
int s21_from_decimal_to_float(s21_decimal src, float *dst);
// -------------------------------------------

// Другие функции
// Возвращаемое значение - код ошибки:
// 0 - OK
// 1 - ошибка вычисления

// Округляет указанное Decimal число до ближайшего целого числа в сторону
//     отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);

// Возвращает целые цифры указанного Decimal числа;
// любые дробные цифры отбрасываются,
//     включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

#endif
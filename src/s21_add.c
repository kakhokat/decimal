#include "s21_add.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (s21_is_equal_sign(value_1, value_2) == true) {
    s21_big_decimal big_value_1 = s21_from_decimal_to_big_decimal(value_1);
    s21_big_decimal big_value_2 = s21_from_decimal_to_big_decimal(value_2);
    s21_big_decimal big_result = {0U};
    s21_big_to_one_denominator(&big_value_1, &big_value_2);
    s21_big_decimal_set_sign(&big_result,
                             s21_big_decimal_get_sign(big_value_1));
    s21_big_decimal_set_power(&big_result,
                              s21_big_decimal_get_power(big_value_1));

    s21_big_sum(big_value_1, big_value_2, &big_result);

    error = s21_from_big_decimal_to_decimal(big_result, result);
    if (s21_decimal_get_power(*result) > MAX_POWER) {
      s21_normalyze(result);
    }
  } else if (s21_is_greater(value_1, value_2)) {
    s21_decimal_set_sign(&value_2, 0);
    error = s21_sub(value_1, value_2, result);
  } else if (s21_is_greater(value_2, value_1)) {
    s21_decimal_set_sign(&value_1, 0);
    error = s21_sub(value_2, value_1, result);
  }
  return error;
}

void s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int overflow = 0;
  for (int cur_bit = 0; cur_bit < START_OF_BIT_3; cur_bit++) {
    s21_set_bit(result, cur_bit,
                (s21_get_bit(value_1, cur_bit) + s21_get_bit(value_2, cur_bit) +
                 overflow) %
                    2);
    overflow = s21_get_bit(value_1, cur_bit) + s21_get_bit(value_2, cur_bit) +
                           overflow >
                       1
                   ? 1
                   : 0;
  }
}

// void s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int overflow = 0;
//   for (int cur_bit = 0; cur_bit < START_OF_BIT_3; cur_bit++) {
//     s21_set_bit(result, cur_bit,
//                 (s21_get_bit(value_1, cur_bit) + s21_get_bit(value_2,
//                 cur_bit) +
//                  overflow) %
//                     2);
//     overflow = s21_get_bit(value_1, cur_bit) + s21_get_bit(value_2, cur_bit)
//     +
//                            overflow >
//                        1
//                    ? 1
//                    : 0;
//   }
// }

// int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   int error = 0;
//   s21_to_one_denominator(&value_1, &value_2);  // приводим к одной степени

//   if (s21_is_equal_sign(value_1, value_2) == true) {
//     error = s21_try_to_avoid_overflow_for_add(&value_1, &value_2);
//     if (!error) {
//       s21_sum(value_1, value_2, result);
//       s21_decimal_set_power(result, s21_decimal_get_power(value_1));
//       s21_decimal_set_sign(result, s21_decimal_get_sign(value_1));
//     }
//   } else if (s21_is_greater(value_1, value_2)) {
//     s21_decimal_set_sign(&value_2, 0);
//     error = s21_sub(value_1, value_2, result);
//   } else if (s21_is_greater(value_2, value_1)) {
//     s21_decimal_set_sign(&value_1, 0);
//     error = s21_sub(value_2, value_1, result);
//   }
//   return error;
// }

// int s21_try_to_avoid_overflow_for_add(s21_decimal *decimal1,
//                                       s21_decimal *decimal2) {
//   int error = 0;
//   if ((s21_get_bit(*decimal1, START_OF_BIT_3 - 1) == 1) &&
//       (s21_get_bit(*decimal2, START_OF_BIT_3 - 1) == 1) &&
//       (s21_decimal_get_power(*decimal1) > 1) &&
//       (s21_decimal_get_power(*decimal2) > 1)) {
//     int power1 = s21_decimal_get_power(*decimal1);
//     s21_mantissa_shift_right_ones(decimal2);
//     power1++;
//     s21_decimal_set_power(decimal1, power1);

//     int power2 = s21_decimal_get_power(*decimal2);
//     s21_mantissa_shift_right_ones(decimal2);
//     power2++;
//     s21_decimal_set_power(decimal2, power2);
//   } else {
//     if ((s21_get_bit(*decimal1, START_OF_BIT_3 - 1) == 1) &&
//         (s21_get_bit(*decimal2, START_OF_BIT_3 - 1) == 1)) {
//       if (s21_decimal_get_sign_char(*decimal1) == '-') {
//         error = 2;
//       } else {
//         error = 1;
//       }
//     }
//   }
//   return error;
// }
#include "s21_big_decimal.h"

int s21_big_get_bit(const s21_big_decimal big_decimal, int index) {
  return (big_decimal.bits[index / 32] >> (index % 32)) & 1U;
}

void s21_big_set_bit(s21_big_decimal *big_decimal, int index, int value) {
  big_decimal->bits[index / 32] &= ~(1U << (index % 32));
  big_decimal->bits[index / 32] |= (value << (index % 32));
}

void s21_big_mantissa_shift_left_ones(s21_big_decimal *big_decimal) {
  int end_of_bit0 = s21_big_get_bit(*big_decimal, START_OF_BIT_1 - 1);
  int end_of_bit1 = s21_big_get_bit(*big_decimal, START_OF_BIT_2 - 1);
  int end_of_bit2 = s21_big_get_bit(*big_decimal, START_OF_BIT_3 - 1);
  int end_of_bit3 = s21_big_get_bit(*big_decimal, START_OF_BIT_4 - 1);
  int end_of_bit4 = s21_big_get_bit(*big_decimal, START_OF_BIT_5 - 1);

  big_decimal->bits[0] <<= 1;
  big_decimal->bits[1] <<= 1;
  big_decimal->bits[2] <<= 1;
  big_decimal->bits[3] <<= 1;
  big_decimal->bits[4] <<= 1;
  big_decimal->bits[5] <<= 1;

  s21_big_set_bit(big_decimal, START_OF_BIT_1, end_of_bit0);
  s21_big_set_bit(big_decimal, START_OF_BIT_2, end_of_bit1);
  s21_big_set_bit(big_decimal, START_OF_BIT_3, end_of_bit2);
  s21_big_set_bit(big_decimal, START_OF_BIT_4, end_of_bit3);
  s21_big_set_bit(big_decimal, START_OF_BIT_5, end_of_bit4);
}

s21_big_decimal s21_big_mantissa_shift_left_copy_ones(
    s21_big_decimal big_decimal) {
  int end_of_bit0 = s21_big_get_bit(big_decimal, START_OF_BIT_1 - 1);
  int end_of_bit1 = s21_big_get_bit(big_decimal, START_OF_BIT_2 - 1);
  int end_of_bit2 = s21_big_get_bit(big_decimal, START_OF_BIT_3 - 1);
  int end_of_bit3 = s21_big_get_bit(big_decimal, START_OF_BIT_4 - 1);
  int end_of_bit4 = s21_big_get_bit(big_decimal, START_OF_BIT_5 - 1);

  big_decimal.bits[0] <<= 1;
  big_decimal.bits[1] <<= 1;
  big_decimal.bits[2] <<= 1;
  big_decimal.bits[3] <<= 1;
  big_decimal.bits[4] <<= 1;
  big_decimal.bits[5] <<= 1;

  s21_big_set_bit(&big_decimal, START_OF_BIT_1, end_of_bit0);
  s21_big_set_bit(&big_decimal, START_OF_BIT_2, end_of_bit1);
  s21_big_set_bit(&big_decimal, START_OF_BIT_3, end_of_bit2);
  s21_big_set_bit(&big_decimal, START_OF_BIT_4, end_of_bit3);
  s21_big_set_bit(&big_decimal, START_OF_BIT_5, end_of_bit4);
  return big_decimal;
}

void s21_big_mantissa_shift_left(s21_big_decimal *big_decimal, int i) {
  for (int j = 0; j < i; j++) {
    s21_big_mantissa_shift_left_ones(big_decimal);
  }
}

int s21_big_decimal_get_sign(s21_big_decimal big_decimal) {
  return (SIGN_MASK & big_decimal.bits[6]) ? 1 : 0;
}

void s21_big_decimal_set_sign(s21_big_decimal *big_decimal, int sign) {
  if (sign == '-' || sign == 1) {
    big_decimal->bits[6] = SIGN_MASK | big_decimal->bits[3];
  } else if (sign == '+' || sign == 0) {
    big_decimal->bits[6] = ~SIGN_MASK & big_decimal->bits[3];
  }
}

int s21_big_decimal_get_power(s21_big_decimal big_decimal) {
  return (POWER_MASK & big_decimal.bits[6]) >> SHIFT_TO_START_OF_POWER;
}

void s21_big_decimal_set_power(s21_big_decimal *big_decimal,
                               unsigned int power) {
  big_decimal->bits[6] = ~POWER_MASK & big_decimal->bits[6];
  big_decimal->bits[6] =
      s21_shift_left(power, SHIFT_TO_START_OF_POWER) | big_decimal->bits[6];
}

void s21_big_multiply_by_10(s21_big_decimal *big_decimal) {
  s21_big_decimal big_decimal_copy = *big_decimal;
  s21_big_decimal shifted_by_1 =
      s21_big_mantissa_shift_left_copy_ones(big_decimal_copy);
  s21_big_decimal shifted_by_3 =
      s21_big_mantissa_shift_left_copy_ones(big_decimal_copy);
  shifted_by_3 = s21_big_mantissa_shift_left_copy_ones(shifted_by_3);
  shifted_by_3 = s21_big_mantissa_shift_left_copy_ones(shifted_by_3);
  s21_big_sum(shifted_by_1, shifted_by_3, big_decimal);
}

// // потом сделаю как надо
void s21_big_divide_by_10(s21_big_decimal *big_decimal) {
  unsigned int remainder = 0;

  for (int i = 5; i >= 0; --i) {
    unsigned long long temp = (unsigned long long)big_decimal->bits[i] +
                              ((unsigned long long)remainder << 32);
    big_decimal->bits[i] = temp / 10;
    remainder = temp % 10;
  }
}

void s21_big_to_one_denominator(s21_big_decimal *big_decimal1,
                                s21_big_decimal *big_decimal2) {
  s21_big_to_one_denominator_proccess(big_decimal1, big_decimal2);
}

void s21_big_to_one_denominator_proccess(s21_big_decimal *big_decimal1,
                                         s21_big_decimal *big_decimal2) {
  int power1 = s21_big_decimal_get_power(*big_decimal1);
  int power2 = s21_big_decimal_get_power(*big_decimal2);

  while (power1 > power2 &&
         !s21_big_get_bit(*big_decimal2, START_OF_BIT_5 - 1)) {
    s21_big_multiply_by_10(big_decimal2);
    power2++;
    s21_big_decimal_set_power(big_decimal2, power2);
  }

  while (power1 < power2 &&
         !s21_big_get_bit(*big_decimal1, START_OF_BIT_5 - 1)) {
    s21_big_multiply_by_10(big_decimal1);
    power1++;
    s21_big_decimal_set_power(big_decimal1, power1);
  }

  while (power1 < power2) {
    s21_big_divide_by_10(big_decimal2);
    power2--;
    s21_big_decimal_set_power(big_decimal2, power2);
  }

  while (power1 > power2) {
    s21_big_divide_by_10(big_decimal1);
    power1--;
    s21_big_decimal_set_power(big_decimal1, power1);
  }
}

s21_big_decimal s21_from_decimal_to_big_decimal(s21_decimal decimal) {
  s21_big_decimal big_decimal = {0U};
  big_decimal.bits[0] = decimal.bits[0];
  big_decimal.bits[1] = decimal.bits[1];
  big_decimal.bits[2] = decimal.bits[2];
  big_decimal.bits[6] = decimal.bits[3];
  return big_decimal;
}

int s21_from_big_decimal_to_decimal(s21_big_decimal big_decimal,
                                    s21_decimal *result) {
  int error = 0;
  while ((big_decimal.bits[5] != 0U || big_decimal.bits[4] != 0U ||
          big_decimal.bits[3] != 0U) &&
         (s21_big_decimal_get_power(big_decimal) != 0)) {
    s21_big_divide_by_10(&big_decimal);
    s21_big_decimal_set_power(&big_decimal,
                              s21_big_decimal_get_power(big_decimal) - 1);
  }
  if (s21_big_decimal_get_power(big_decimal) == 0 &&
      (big_decimal.bits[5] != 0U || big_decimal.bits[4] != 0U ||
       big_decimal.bits[3] != 0U)) {
    error = s21_big_decimal_get_sign(big_decimal) == 0 ? 1 : 2;
  }
  result->bits[0] = big_decimal.bits[0];
  result->bits[1] = big_decimal.bits[1];
  result->bits[2] = big_decimal.bits[2];
  result->bits[3] = big_decimal.bits[6];
  return error;
}

void s21_big_sum(s21_big_decimal big_value_1, s21_big_decimal big_value_2,
                 s21_big_decimal *big_result) {
  int overflow = 0;
  for (int cur_bit = 0; cur_bit < START_OF_BIT_6; cur_bit++) {
    s21_big_set_bit(big_result, cur_bit,
                    (s21_big_get_bit(big_value_1, cur_bit) +
                     s21_big_get_bit(big_value_2, cur_bit) + overflow) %
                        2);
    overflow = s21_big_get_bit(big_value_1, cur_bit) +
                           s21_big_get_bit(big_value_2, cur_bit) + overflow >
                       1
                   ? 1
                   : 0;
  }
}
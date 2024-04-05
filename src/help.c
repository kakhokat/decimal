#include "help.h"

#include "s21_add.h"
#include "s21_big_decimal.h"
#include "s21_sub.h"

int s21_get_bit(const s21_decimal decimal, int index) {
  return (decimal.bits[index / 32] >> (index % 32)) & 1U;
}

void s21_set_bit(s21_decimal *decimal, int index, int value) {
  decimal->bits[index / 32] &= ~(1U << (index % 32));
  decimal->bits[index / 32] |= (value << (index % 32));
}

int s21_shift_left(unsigned int number, int size) { return number << size; }

void s21_mantissa_shift_left_ones(s21_decimal *decimal) {
  int end_of_bit0 = s21_get_bit(*decimal, START_OF_BIT_1 - 1);
  int end_of_bit1 = s21_get_bit(*decimal, START_OF_BIT_2 - 1);

  decimal->bits[0] <<= 1;
  decimal->bits[1] <<= 1;
  decimal->bits[2] <<= 1;

  s21_set_bit(decimal, START_OF_BIT_1, end_of_bit0);
  s21_set_bit(decimal, START_OF_BIT_2, end_of_bit1);
}

/**
 * сдвигает мантису влево
 */
void s21_mantissa_shift_left(s21_decimal *decimal, int shift) {
  for (int i = 0; i < shift; i++) {
    s21_mantissa_shift_left_ones(decimal);
  }
}

s21_decimal s21_mantissa_shift_left_copy_ones(s21_decimal decimal) {
  int end_of_bit0 = s21_get_bit(decimal, START_OF_BIT_1 - 1);
  int end_of_bit1 = s21_get_bit(decimal, START_OF_BIT_2 - 1);

  decimal.bits[0] <<= 1;
  decimal.bits[1] <<= 1;
  decimal.bits[2] <<= 1;

  s21_set_bit(&decimal, START_OF_BIT_1, end_of_bit0);
  s21_set_bit(&decimal, START_OF_BIT_2, end_of_bit1);
  return decimal;
}

s21_decimal s21_new_decimal(int sign, int power, unsigned int int1,
                            unsigned int int2, unsigned int int3) {
  s21_decimal decimal;
  s21_clear_decimal(&decimal);

  decimal.bits[0] = int1;
  decimal.bits[1] = int2;
  decimal.bits[2] = int3;

  s21_decimal_set_sign(&decimal, sign);
  s21_decimal_set_power(&decimal, power);

  return decimal;
}

void s21_clear_decimal(s21_decimal *decimal) {
  decimal->bits[0] = 0U;
  decimal->bits[1] = 0U;
  decimal->bits[2] = 0U;
  decimal->bits[3] = 0U;
}

int s21_decimal_get_sign_char(s21_decimal decimal) {
  return s21_get_bit(decimal, 127) ? '-' : '+';
}
int s21_decimal_get_sign(s21_decimal decimal) {
  return s21_get_bit(decimal, 127);
}

void s21_decimal_set_sign(s21_decimal *decimal, int sign) {
  s21_set_bit(decimal, 127, sign);
}

int s21_decimal_get_power(s21_decimal decimal) {
  return (POWER_MASK & decimal.bits[3]) >> SHIFT_TO_START_OF_POWER;
}

void s21_decimal_set_power(s21_decimal *decimal, unsigned int power) {
  unsigned sign = s21_decimal_get_sign(*decimal);
  unsigned scle_new = power << 16;
  decimal->bits[3] = 0;
  decimal->bits[3] |= scle_new;
  s21_decimal_set_sign(decimal, sign);
}

void s21_multiply_by_10(s21_decimal *decimal) {
  s21_decimal decimal_copy = *decimal;
  s21_decimal shifted_by_1 = s21_mantissa_shift_left_copy_ones(decimal_copy);
  s21_decimal shifted_by_3 = s21_mantissa_shift_left_copy_ones(decimal_copy);
  shifted_by_3 = s21_mantissa_shift_left_copy_ones(shifted_by_3);
  shifted_by_3 = s21_mantissa_shift_left_copy_ones(shifted_by_3);
  s21_sum(shifted_by_1, shifted_by_3, decimal);
}

void s21_divide_by_10(s21_decimal *value) {
  unsigned long remainder = 0;
  for (int i = 2; i >= 0; --i) {
    unsigned long temp =
        (unsigned long)value->bits[i] + ((unsigned long)remainder << 32);
    value->bits[i] = temp / 10;
    remainder = (unsigned long)temp % 10;
  }
}

void s21_to_one_denominator(s21_decimal *decimal1, s21_decimal *decimal2) {
  if (s21_decimal_get_power(*decimal1) > MAX_POWER) {
    s21_normalyze(decimal1);  // загоняем в степень в рамки (28; 0)
  }
  if (s21_decimal_get_power(*decimal2) > MAX_POWER) {
    s21_normalyze(decimal2);
  }
  s21_to_one_denominator_proccess(decimal1, decimal2);
}

void s21_to_one_denominator_proccess(s21_decimal *decimal1,
                                     s21_decimal *decimal2) {
  int power1 = s21_decimal_get_power(*decimal1);
  int power2 = s21_decimal_get_power(*decimal2);

  while (power1 > power2 && !s21_get_bit(*decimal2, START_OF_BIT_3 - 1)) {
    s21_multiply_by_10(decimal2);
    power2++;
    s21_decimal_set_power(decimal2, power2);
  }

  while (power1 > power2) {
    s21_divide_by_10(decimal1);
    power1--;
    s21_decimal_set_power(decimal1, power1);
  }

  while (power1 < power2 && !s21_get_bit(*decimal1, START_OF_BIT_3 - 1)) {
    s21_multiply_by_10(decimal1);
    power1++;
    s21_decimal_set_power(decimal1, power1);
  }

  while (power1 < power2) {
    s21_divide_by_10(decimal2);
    power2--;
    s21_decimal_set_power(decimal2, power2);
  }
}

void s21_normalyze(s21_decimal *decimal) {
  s21_decimal normalizer =
      s21_new_decimal(0, 28, 0, 0, 1024U * 1024U * 1024U * 2U);
  s21_to_one_denominator_proccess(decimal, &normalizer);
}

int s21_decimal_get_last_bit(s21_decimal decimal) {
  int last_bit = 95;
  for (; (last_bit >= 0) && (!s21_get_bit(decimal, last_bit));) last_bit -= 1;
  return last_bit;
}

void null_decimal(s21_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}

int is_correct_decimal(s21_decimal value) {
  int correct_power, correct_decimal;
  if (s21_decimal_get_power(value) >= 0 && s21_decimal_get_power(value) <= 28) {
    correct_power = 0;
  } else {
    correct_power = 1;
  }
  if ((value.bits[3] & CORRECT_DECIMAL_MASK) == 0) {
    correct_decimal = 0;
  } else
    correct_decimal = 1;
  if (correct_power == 0 && correct_decimal == 0) {
    return 0;
  }  // если decimal корректный, функция возвращает 0
  else
    return 1;  // если decimal некорректный, функция возвращает 1
}
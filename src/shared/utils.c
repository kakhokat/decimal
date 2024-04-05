#include "utils.h"

void MakeZero(s21_decimal *dec) {
  dec->bits[0] = 0;
  dec->bits[1] = 0;
  dec->bits[2] = 0;
  dec->bits[3] = 0;
}

bool IsCorrectDecimal(const s21_decimal *dec) {
  return (dec->bits[3] & INCORRECT_DECIMAL_CONST) == 0 &&
         ((dec->bits[3] & (255 << 16)) >> 16) <= 28;
}

void SumStrings(const char *lhs, const char *rhs, char *result) {
  int len = strlen(lhs);
  memset(result, '0', len);
  for (int i = len - 1; i >= 0; --i) {
    result[i] += rhs[i] + lhs[i] - 96;
    if (i != 0) result[i - 1] += (result[i] - '0') / 10;
    result[i] = (result[i] - '0') % 10 + '0';
  }
}

void TurnRight(char *num, int amount) {
  int len = strlen(num);
  memcpy(num + len - amount, num, amount);
  for (int i = 0; i < len - amount; ++i) num[i] = '0';
}

void FromDecimalToString(const s21_decimal *dec, char *result) {
  char bit0[30] = "", bit1[30] = "", bit2[30] = "", temp_result[30] = "";
  int power = (dec->bits[3] & (255 << 16)) >> 16, amount = 0, not_end = 1,
      bit_len = 29;
  temp_result[bit_len] = '\0';

  amount = sprintf(bit0, "%u", (unsigned)dec->bits[0]);
  bit0[bit_len] = '\0';
  memset(bit0 + amount, '0', bit_len - amount);
  TurnRight(bit0, amount);

  amount =
      sprintf(bit1, "%.0Lf", (long double)(unsigned)dec->bits[1] * powl(2, 32));
  bit1[bit_len] = '\0';
  memset(bit1 + amount, '0', bit_len - amount);
  TurnRight(bit1, amount);

  amount =
      sprintf(bit2, "%.0Lf", (long double)(unsigned)dec->bits[2] * powl(2, 64));
  bit2[bit_len] = '\0';
  memset(bit2 + amount, '0', bit_len - amount);
  TurnRight(bit2, amount);

  SumStrings(bit0, bit1, temp_result);
  SumStrings(temp_result, bit2, result + 1);

  memcpy(result, result + 1, bit_len - power + 1);
  result[bit_len - power + 1] = '\0';
  if (power != 0) result[bit_len - power] = '.';
  amount = 0;
  for (int i = 0; i < bit_len - 1 && not_end; ++i)
    if (result[i] != '0')
      --not_end;
    else
      ++amount;
  if (amount == bit_len)
    result[1] = '\0';
  else {
    memcpy(result, result + amount, bit_len - amount + 1);
    result[bit_len - amount + 1] = '\0';
  }
}

int CompareNumericStrings(char *lhs, char *rhs) {
  int lhs_len = strlen(lhs), rhs_len = strlen(rhs), result = 0;
  if (lhs_len < rhs_len)
    --result;
  else if (lhs_len > rhs_len)
    ++result;
  else
    for (int i = 0; i < lhs_len && !result; ++i)
      if (lhs[i] < rhs[i])
        --result;
      else if (lhs[i] > rhs[i])
        ++result;
  return result;
}

void DivideByTwo(char *num) {
  int len = strlen(num);
  if (len != 0) {
    num[len - 1] = (num[len - 1] - '0') / 2 + '0';
    for (int i = len - 2; i >= 0; --i) {
      if ((num[i] - '0') % 2 == 1) num[i + 1] += 5;
      num[i] = (num[i] - '0') / 2 + '0';
    }
  }
}

unsigned GetLast32Bits(char *num) {
  int len = strlen(num);
  long result = 0, curr_bit_value = 1;
  for (int i = 0; i < 32; ++i) {
    if (num[len - 1] % 2 == 1) result += curr_bit_value;
    curr_bit_value *= 2;
    DivideByTwo(num);
  }
  return result;
}

void FromStringToDecimal(char *num, int sign, int power, s21_decimal *result) {
  MakeZero(result);
  s21_decimal_set_sign(result, sign);
  s21_decimal_set_power(result, power);
  result->bits[0] = GetLast32Bits(num);
  result->bits[1] = GetLast32Bits(num);
  result->bits[2] = GetLast32Bits(num);
}
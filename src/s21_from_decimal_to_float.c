#include "help.h"
#include "shared/utils.h"

#define CODE_OK 0
#define CODE_CONVERTATION_ERROR 1

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exit_code = CODE_OK;
  if (IsCorrectDecimal(&src)) {
    long double result = (long double)(unsigned)src.bits[0] +
                         (long double)(unsigned)src.bits[1] * powl(2, 32) +
                         (long double)(unsigned)src.bits[2] * powl(2, 64);
    int sign = (unsigned)src.bits[3] >> 31,
        power = (src.bits[3] & 255 << 16) >> 16;
    result /= powl(10, power);
    *dst = sign ? -result : result;
  } else
    exit_code = CODE_CONVERTATION_ERROR;
  return exit_code;
}

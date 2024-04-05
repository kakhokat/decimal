#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "help.h"
#include "shared/utils.h"

#define CODE_OK 0
#define CODE_CONVERTATION_ERROR 1

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int exit_code = CODE_OK;
  if (fabsf(src) < 1e-28f && fabsf(src) > 0.f) {
    exit_code = CODE_CONVERTATION_ERROR;
    null_decimal(dst);
  } else if (fabsf(src) >= MAX_DEC || isinf(src) || isnan(src))
    exit_code = CODE_CONVERTATION_ERROR;
  else {
    char num[40] = "";
    sprintf(num, "%e", fabsf(src));
    int len = 12, power = atoi(num + len - 3);
    num[len - 4] = '\0';
    memcpy(num + 1, num + 2, 6);
    num[7] = '\0';
    len = 7;
    for (int i = len - 1; i >= 0; --i)
      if (num[i] == '0')
        --len;
      else
        i = -1;
    num[len] = '\0';
    power -= len - 1;
    if (power > 0) {
      memset(num + len, '0', power);
      num[len + power] = '\0';
      power = 0;
    }
    FromStringToDecimal(num, signbit(src) != 0, -power, dst);
  }
  return exit_code;
}
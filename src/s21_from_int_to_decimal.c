#include <stdlib.h>

#include "help.h"
#include "shared/utils.h"

#define CODE_OK 0
#define CODE_CONVERTATION_ERROR 1

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int exit_code = CODE_OK;
  null_decimal(dst);
  s21_decimal_set_sign(dst, src < 0 ? 1 : 0);
  dst->bits[0] = abs(src);
  return exit_code;
}

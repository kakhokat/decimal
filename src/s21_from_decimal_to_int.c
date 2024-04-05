#include "help.h"
#include "shared/utils.h"

#define CODE_OK 0
#define CODE_CONVERTATION_ERROR 1

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int exit_code = CODE_OK;
  if (IsCorrectDecimal(&src)) {
    int sign = s21_decimal_get_sign(src);
    char num[32] = "";
    FromDecimalToString(&src, num);
    char *point = strchr(num, '.');
    if (point != NULL) *point = '\0';
    if (sign == 0 && CompareNumericStrings(num, "2147483648") == -1)
      *dst = atoi(num);
    else if (sign == 1 && CompareNumericStrings(num, "2147483649") == -1)
      *dst = -atoi(num);
    else
      exit_code = CODE_CONVERTATION_ERROR;
  } else
    exit_code = CODE_CONVERTATION_ERROR;
  return exit_code;
}
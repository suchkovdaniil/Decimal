#include "../s21_string.h"
#include "s21_pow.h"

#define MAX_LONG_LONG_INT_LENGTH 18

void normalize_and_round(double *number, int *exponent, int precision) {
  if (*number == 0.0) {
    *exponent = 0;
    return;
  }
  int sign = (*number < 0.0) ? -1 : 1;
  *number = sign * (*number);
  while (*number >= 10.0) {
    *number /= 10.0;
    (*exponent)++;
  }
  while (*number < 1.0 && *number != 0.0) {
    *number *= 10.0;
    (*exponent)--;
  }
  double rounding_factor = 0.5 / s21_pow(10, precision);
  *number += rounding_factor;

  if (*number >= 10.0) {
    *number /= 10.0;
    (*exponent)++;
  }

  *number *= sign;
}

void format_number(double number, int precision, int exponent, int is_upper,
                   char *str) {
  int index = 0;
  int int_part = (int)number;
  str[index++] = int_part + '0';
  number -= int_part;
  if (precision > 0) {
    str[index++] = '.';
    for (int i = 0; i < precision; i++) {
      number *= 10.0;
      int digit = (int)number;
      str[index++] = digit + '0';
      number -= digit;
    }
  }
  str[index++] = is_upper ? 'E' : 'e';
  str[index++] = exponent < 0 ? '-' : '+';
  if (exponent < 0) {
    exponent = -exponent;
  }
  char exp_str[3] = {0};
  int exp_index = 0;
  do {
    exp_str[exp_index++] = (exponent % 10) + '0';
    exponent /= 10;
  } while (exponent > 0);
  while (exp_index < 2) {
    exp_str[exp_index++] = '0';
  }
  for (int i = exp_index - 1; i >= 0; i--) {
    str[index++] = exp_str[i];
  }
  str[index] = '\0';
}

void s21_etoa(double number, char *str, int precision, int is_upper) {
  if (precision < 0) {
    precision = 6;
  }

  int exponent = 0;

  normalize_and_round(&number, &exponent, precision);
  format_number(number, precision, exponent, is_upper, str);
}

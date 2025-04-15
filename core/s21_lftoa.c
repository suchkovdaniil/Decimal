#include "../s21_string.h"
#include "s21_ltoa.h"
#include "s21_pow.h"

#define MAX_LONG_LONG_INT_LENGTH 19

void frac_to_string(char *str, int *index, long double fractional_part,
                    int precision) {
  char frac_str[precision];
  int left_precision = precision;
  do {
    int frac_index = 0;
    int current_precision = left_precision > MAX_LONG_LONG_INT_LENGTH
                                ? MAX_LONG_LONG_INT_LENGTH
                                : left_precision;
    fractional_part *= s21_pow(10, current_precision);
    if (current_precision == left_precision) fractional_part += 0.5;

    long long int frac_part = (long long int)(fractional_part);
    fractional_part -= frac_part;

    left_precision -= current_precision;
    for (int i = 0; i < current_precision; i++) {
      frac_str[frac_index++] = (frac_part % 10) + '0';
      frac_part /= 10;
    }

    for (int j = frac_index - 1; j >= 0; j--) {
      str[(*index)++] = frac_str[j];
    }
  } while (left_precision > 0);
}

void s21_lftoa(long double number, char *str, int precision, int point) {
  if (precision == -1) {
    precision = 6;
  }
  if (precision == 0) {
    if (number > 0) {
      number += 0.5;
    } else {
      number -= 0.5;
    }
  }
  int int_part = (int)number;
  long double fractional_part = number - int_part;
  if (fractional_part < 0) fractional_part = -fractional_part;
  int index = 0;
  s21_ltoa(int_part, str, 10);
  index = s21_strlen(str);
  if (precision > 0) {
    str[index++] = '.';
    frac_to_string(str, &index, fractional_part, precision);
  }
  if (point && precision <= 0) {
    str[index++] = '.';
  }
  str[index] = '\0';
}

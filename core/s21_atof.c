#include "../s21_string.h"
#include "s21_isdigit.h"
#include "s21_pow.h"

double s21_atof(const char *str) {
  double result = 0.0;
  double is_minus = 1.0;

  while (*str == ' ') str++;
  if (*str == '-') {
    is_minus = -1.0;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str != '\0' && s21_isdigit(*str)) {
    result = result * 10.0 + (*str - '0');
    str++;
  }
  if (*str == '.') {
    double reminder = 1.0;
    str++;
    while (*str != '\0' && s21_isdigit(*str)) {
      result = result + (*str - '0') * (reminder /= 10.0);
      str++;
    }
  }
  if (*str == 'e' || *str == 'E') {
    str++;
    int exp_is_minus = 1;
    if (*str == '-') {
      exp_is_minus = -1;
      str++;
    } else if (*str == '+') {
      str++;
    }
    int exponent = 0;
    while (*str != '\0' && s21_isdigit(*str)) {
      exponent = exponent * 10 + (*str - '0');
      str++;
    }
    result = result * s21_pow(10, exp_is_minus * exponent);
  }
  return is_minus * result;
}
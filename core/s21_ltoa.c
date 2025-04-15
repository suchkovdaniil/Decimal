#include "../s21_string.h"
#include "s21_reverse.h"

char *s21_ltoa(long long int number, char *str, int base) {
  int is_minus = 0;
  int i = 0;
  if (number == 0) {
    str[i] = '0';
    i++;
  }
  if (number < 0) {
    is_minus = 1;
    number = -number;
    if (base != 10) {
      number = __INT32_MAX__ * 2ll - number + 2;
    }
  }
  while (number != 0) {
    int reminder = number % base;
    str[i] = (reminder > 9) ? (reminder - 10) + 'a' : reminder + '0';
    number = number / base;
    i++;
  }
  if (is_minus && base == 10) {
    str[i] = '-';
    i++;
  }
  str[i] = '\0';
  s21_reverse(str);
  return str;
}

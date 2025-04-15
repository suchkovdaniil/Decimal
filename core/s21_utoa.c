#include "../s21_string.h"
#include "s21_reverse.h"

char *s21_utoa(unsigned int value, char *str) {
  char *start = str;
  if (value == 0) {
    *str++ = '0';
  } else {
    while (value > 0) {
      *str++ = (value % 10) + '0';
      value /= 10;
    }
  }
  *str = '\0';
  s21_reverse(start);
  return start;
}
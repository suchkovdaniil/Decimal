#include "../s21_string.h"

char *s21_reverse(char *str) {
  s21_size_t len = s21_strlen(str);
  for (s21_size_t i = 0; i < len / 2; i++) {
    char c = str[len - 1 - i];
    str[len - 1 - i] = str[i];
    str[i] = c;
  }
  return str;
}

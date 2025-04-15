#include "../s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *result = 0;
  const char *start = str;
  s21_size_t len = s21_strlen(str);
  str += len;
  while (str >= start && result == 0) {
    if (*str == c) {
      result = (char *)str;
    }
    str--;
  }
  return result;
}
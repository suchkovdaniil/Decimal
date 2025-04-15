#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *start = s21_memcpy(dest, src, n);
  return start;
}
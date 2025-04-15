#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = s21_memcmp(str1, str2, n);
  return result;
}
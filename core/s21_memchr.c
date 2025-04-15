#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *result = s21_NULL;
  const char *src = (const char *)str;
  for (s21_size_t i = 0; i < n && result == s21_NULL; ++i, ++src) {
    if (*src == c) {
      result = (void *)src;
    }
  }
  return result;
}
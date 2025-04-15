#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dst = (char *)dest;
  const char *source = (const char *)src;
  for (s21_size_t i = 0; i < n; ++i) {
    dst[i] = source[i];
  }
  return (void *)dst;
}
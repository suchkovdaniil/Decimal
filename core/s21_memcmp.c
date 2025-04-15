#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0;
  const char *src1 = (const char *)str1;
  const char *src2 = (const char *)str2;
  for (s21_size_t i = 0; i < n && result == 0; ++i) {
    if (src1[i] != src2[i]) {
      result = src1[i] < src2[i] ? -1 : 1;
    }
  }
  return result;
}
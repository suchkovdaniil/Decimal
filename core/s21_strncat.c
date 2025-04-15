#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *start = dest;
  s21_size_t len_dest = s21_strlen(dest);
  s21_size_t len_src = s21_strlen(src);
  if (len_src > n) {
    len_src = n;
  }
  dest += len_dest;
  dest[len_src] = '\0';
  s21_memcpy(dest, src, len_src);
  return start;
}
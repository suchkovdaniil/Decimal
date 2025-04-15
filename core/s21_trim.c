#include <stdlib.h>

#include "../s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = s21_NULL;
  s21_size_t start = 0;
  s21_size_t end = 0;
  if (src) {
    trim_chars = trim_chars ? trim_chars : " \t\n\r";
    end = s21_strlen(src);

    while (start < end && s21_strchr(trim_chars, src[start])) {
      start++;
    }
    while (end > start && s21_strchr(trim_chars, src[end - 1])) {
      end--;
    }

    res = (char *)malloc(end - start + 1);
  }
  if (res) {
    s21_memcpy(res, src + start, end - start);
    res[end - start] = '\0';
  }

  return (void *)res;
}
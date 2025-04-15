#include <stdlib.h>

#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = s21_NULL;
  if (src != s21_NULL && str != s21_NULL) {
    result = calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));
  }
  if (result != s21_NULL) {
    s21_strncpy(result, src, start_index - 1);
    s21_strncpy(result + start_index - 1, str, s21_strlen(str));
    s21_strncpy(result + start_index + s21_strlen(str) - 1,
                src + start_index - 1, s21_strlen(src) - start_index + 1);
  }
  return (void *)result;
}

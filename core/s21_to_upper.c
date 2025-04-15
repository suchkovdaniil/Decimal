#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  char *res_str = s21_NULL;
  if (str) {
    res_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
  }
  if (res_str) {
    s21_strncpy(res_str, str, s21_strlen(str) + 1);
    for (char *i = res_str; *i; i++) {
      if (*i >= 97 && *i <= 122) {
        *i -= 32;
      }
    }
  }
  return (void *)res_str;
}

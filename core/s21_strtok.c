#include "../s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *old = s21_NULL;
  if (str == s21_NULL) {
    str = old;
  }
  s21_size_t find = 0;
  for (find = s21_strcspn(str, delim); find == 0 && *str != '\0';
       find = s21_strcspn(str, delim)) {
    str++;
  }
  char *result = s21_NULL;
  if (*str != '\0') {
    if (str[find] == '\0') {
      old = &str[find];
    } else {
      str[find] = '\0';
      old = str + find + 1;
    }
    result = str;
  }
  return result;
}
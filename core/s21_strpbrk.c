#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t len1 = s21_strlen(str1);
  s21_size_t find = s21_strcspn(str1, str2);
  return find == len1 ? s21_NULL : (char *)(str1 + find);
}
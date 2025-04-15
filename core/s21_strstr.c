#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = s21_NULL;
  s21_size_t stack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  int found = 0;
  for (s21_size_t i = 0; i < stack_len - needle_len + 1 && !found; ++i) {
    found = s21_strncmp(&haystack[i], needle, needle_len) == 0;
    if (found) {
      result = (char *)&haystack[i];
    }
  }
  return found ? result : s21_NULL;
}
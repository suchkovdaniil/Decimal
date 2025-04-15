#include "../s21_string.h"

char* s21_ctos(char c, char* str) {
  str[0] = c;
  str[1] = '\0';
  return str;
}
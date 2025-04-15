#include "../s21_string.h"
#include "s21_ltoa.h"

char *s21_ptoa(char *str, void *pointer) {
  if (pointer == s21_NULL) {
    s21_strncpy(str, "(nil)", 6);
  } else {
    s21_strncpy(str, "0x", 3);
    unsigned long long ptr_value = (unsigned long long)pointer;
    char temp[20];
    s21_ltoa(ptr_value, temp, 16);
    int len = s21_strlen(temp);
    s21_strncat(str, temp, len);
  }
  return str;
}
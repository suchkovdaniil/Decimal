#include "../s21_string.h"

double s21_pow(double x, int n) {
  if (n < 0) {
    x = 1 / x;
    n = -n;
  }
  double result = 1.0;
  if (n > 0) {
    for (int i = 0; i < n; i++) {
      result *= x;
    }
  }
  return result;
}
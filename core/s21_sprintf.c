#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_atof.h"
#include "s21_ctos.h"
#include "s21_etoa.h"
#include "s21_lftoa.h"
#include "s21_ltoa.h"
#include "s21_pow.h"
#include "s21_ptoa.h"
#include "s21_utoa.h"

#define TEMP_BUFFER_SIZE 1024

typedef struct {
  // block A
  int align_left;
  int show_sign;
  int space;
  int sharp;
  int zero;
  // block B
  int width;
  // block C
  int precision;
  // block D
  int h;
  int l;
  int L;
} flag_t;

void apply_precision_to_number(char *insert, flag_t *flags,
                               s21_size_t insert_len) {
  s21_size_t prec_diff =
      (s21_size_t)flags->precision >
              (insert[0] == '-' ? insert_len - 1 : insert_len)
          ? (s21_size_t)flags->precision -
                (insert[0] == '-' ? insert_len - 1 : insert_len)
          : 0;

  if (prec_diff > 0) {
    char *temp = calloc(insert_len + prec_diff + 2, sizeof(char));
    if (insert[0] == '-') {
      temp[0] = '-';
      s21_memset(temp + 1, '0', prec_diff);
      s21_strncpy(temp + 1 + prec_diff, insert + 1, insert_len - 1);
    } else {
      s21_memset(temp, '0', prec_diff);
      s21_strncpy(temp + prec_diff, insert, insert_len);
    }
    s21_strncpy(insert, temp, insert_len + prec_diff);
    insert[prec_diff + insert_len] = '\0';
    free(temp);
  }
}

void apply_precision_to_string(char *insert, flag_t *flags,
                               s21_size_t *insert_len) {
  if ((s21_size_t)flags->precision < *insert_len) {
    insert[flags->precision] = '\0';
    *insert_len = (s21_size_t)flags->precision;
  }
}

void apply_sign_or_space(char *insert, flag_t *flags, s21_size_t *insert_len) {
  if (flags->space || flags->show_sign) {
    char *temp = calloc(*insert_len + 2, sizeof(char));
    s21_strncpy(temp + 1, insert, *insert_len);
    temp[0] = flags->show_sign ? '+' : ' ';
    s21_strncpy(insert, temp, *insert_len + 1);
    insert[*insert_len + 1] = '\0';
    *insert_len += 1;
    free(temp);
  }
}

void apply_width(char *insert, flag_t *flags, s21_size_t *insert_len,
                 int is_number) {
  s21_size_t width_diff = (s21_size_t)flags->width > *insert_len
                              ? (s21_size_t)flags->width - *insert_len
                              : 0;
  if (width_diff > 0) {
    char *temp = calloc(flags->width + 1, sizeof(char));
    if (flags->align_left) {
      s21_strncpy(temp, insert, *insert_len);
      s21_memset(temp + *insert_len, ' ', width_diff);
    } else {
      if (is_number && flags->zero && (insert[0] == '+' || insert[0] == ' ')) {
        temp[0] = insert[0];
        s21_memset(temp + 1, '0', width_diff);
        s21_strncpy(temp + 1 + width_diff, insert + 1, *insert_len - 1);
      } else {
        s21_memset(temp, flags->zero ? '0' : ' ', width_diff);
        s21_strncpy(temp + width_diff, insert, *insert_len);
      }
    }
    s21_strncpy(insert, temp, flags->width);
    insert[flags->width] = '\0';
    *insert_len = (s21_size_t)flags->width;
    free(temp);
  }
}

void process_flags(char *insert, flag_t *flags, int is_number) {
  s21_size_t insert_len = s21_strlen(insert);

  if (flags->precision >= 0) {
    if (is_number) {
      apply_precision_to_number(insert, flags, insert_len);
    } else {
      apply_precision_to_string(insert, flags, &insert_len);
    }
  }

  if (is_number && (flags->space || flags->show_sign) && insert[0] != '-') {
    apply_sign_or_space(insert, flags, &insert_len);
  }

  if ((s21_size_t)flags->width > insert_len) {
    apply_width(insert, flags, &insert_len, is_number);
  }
}

void s_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  const char *insert = va_arg(*args, char *);
  if (insert == s21_NULL) {
    insert = "(null)";
  }
  char temp[TEMP_BUFFER_SIZE] = {0};
  s21_size_t insert_len = s21_strlen(insert);
  s21_strncpy(temp, insert, insert_len + 1);
  process_flags(temp, flags, 0);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void c_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  int insert = va_arg(*args, int);
  char temp[TEMP_BUFFER_SIZE] = {0};
  s21_ctos(insert, temp);
  process_flags(temp, flags, 0);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void d_i_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  long int value = va_arg(*args, long int);
  char temp[TEMP_BUFFER_SIZE] = {0};
  if (flags->h) {
    value = (short)value;
  } else if (!flags->l) {
    value = (int)value;
  }
  s21_ltoa(value, temp, 10);
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void u_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  long int value = va_arg(*args, long int);
  char temp[TEMP_BUFFER_SIZE] = {0};
  if (flags->h) {
    value = (unsigned short)value;
  } else if (!flags->l) {
    value = (unsigned int)value;
  }
  s21_utoa(value, temp);
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void f_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  char temp[TEMP_BUFFER_SIZE] = {0};
  double value = va_arg(*args, double);
  if (isnan(value)) {
    s21_strncpy(temp, "nan", 4);
  } else if (isinf(value)) {
    s21_strncpy(temp, value > 0 ? "inf" : "-inf", value > 0 ? 4 : 5);
  } else {
    s21_lftoa(value, temp, flags->precision, flags->sharp);
  }
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void lf_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  char temp[TEMP_BUFFER_SIZE] = {0};
  long double value = va_arg(*args, long double);
  if (isnan(value) || isinf(value)) {
    if (signbit(value)) {
      s21_strncpy(temp, "-nan", 5);  // Если знак отрицательный
    } else {
      s21_strncpy(temp, "nan", 4);  // Если положительный
    }
  } else {
    s21_lftoa(value, temp, flags->precision, flags->sharp);
  }
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void p_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  void *adress = va_arg(*args, void *);
  char temp[TEMP_BUFFER_SIZE] = {0};
  s21_ptoa(temp, adress);
  process_flags(temp, flags, 0);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void x_mod(char *str, va_list *args, int *jump, flag_t *flags, int is_upper) {
  long int value = va_arg(*args, long int);
  ;
  char temp[TEMP_BUFFER_SIZE] = {0};
  if (flags->h) {
    value = (short)value;
  } else if (!flags->l) {
    value = (int)value;
  }
  s21_ltoa(value, temp, 16);
  if (flags->h && s21_strlen(temp) > 4) {
    s21_strncpy(temp, temp + 4, 5);
  }
  if (flags->sharp) {
    char temp2[TEMP_BUFFER_SIZE] = {0};
    temp2[0] = '0';
    temp2[1] = 'x';
    s21_strncpy(temp2 + 2, temp, s21_strlen(temp));
    s21_strncpy(temp, temp2, s21_strlen(temp2));
  }
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  if (is_upper) {
    char *upper_str = s21_to_upper(temp);
    s21_strncpy(temp, upper_str, len);
    free(upper_str);
  }
  s21_strncpy(str, temp, len);
  *jump = len;
}

void o_mod(char *str, va_list *args, int *jump, flag_t *flags) {
  long int value = va_arg(*args, long int);
  char temp[TEMP_BUFFER_SIZE] = {0};
  if (flags->h) {
    value = (short)value;
  } else if (!flags->l) {
    value = (int)value;
  }
  s21_ltoa(value, temp, 8);
  if (flags->h && s21_strlen(temp) > 6) {
    s21_strncpy(temp, temp + 5, 7);
    *temp = '1';
  }
  if (flags->sharp) {
    char temp2[TEMP_BUFFER_SIZE] = {0};
    temp2[0] = '0';
    s21_strncpy(temp2 + 1, temp, s21_strlen(temp));
    s21_strncpy(temp, temp2, s21_strlen(temp2));
  }
  flags->zero = 0;
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void n_mod(int current_len, va_list *args, int *jump) {
  int *value = va_arg(*args, int *);
  *value = current_len;
  *jump = 0;
}

void e_mod(char *str, va_list *args, int *jump, flag_t *flags, int is_upper) {
  double value = va_arg(*args, double);
  char temp[TEMP_BUFFER_SIZE] = {0};

  // Используем точность, указанную в флаге
  int precision = (flags->precision == -1) ? 6 : flags->precision;

  // Форматируем число как экспоненциальное

  // Если формат %E, то дополнительно обрабатываем экспоненциальный регистр
  s21_etoa(value, temp, precision, is_upper);

  // Применяем флаги (ширина, выравнивание и т.д.)
  process_flags(temp, flags, 1);

  // Копируем результат в выходную строку
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void g_mod(char *str, va_list *args, int *jump, flag_t *flags, int is_upper) {
  double value = va_arg(*args, double);
  char temp[TEMP_BUFFER_SIZE] = {0};
  int int_value = (int)value, num_count = 0, reminder = 1, num_count2 = 0,
      tempc = -1;
  while (int_value > 0) {
    int_value /= 10;
    num_count++;
  }
  if (num_count > 6) {
    reminder = s21_pow(10, num_count - 6);
    num_count2 = 6;
  }
  int int_value2 = (int)(value / reminder);
  while (int_value2 > 0) {
    if (int_value2 % 10 != 0 && tempc == -1) {
      tempc = num_count2;
    }
    num_count2++;
    int_value2 /= 10;
  }
  int int_value3 = (int)value;
  double fractional_part = value - int_value3 + 1;
  fractional_part *= s21_pow(10, 6 - num_count);
  int i = (int)(fractional_part + 0.5) - s21_pow(10, 6 - num_count);
  int counter = 0;
  int final_precision = 6 - num_count;
  if (i == 0) {
    final_precision = 0;
  } else if (i > 0) {
    while (i % 10 == 0) {
      counter++;
      i /= 10;
    }
    final_precision = 6 - num_count - counter;
  }
  if (num_count > 6) {
    s21_etoa(value, temp, num_count2 - tempc - 1, is_upper);
  } else {
    s21_lftoa(value, temp, final_precision, flags->sharp);
  }
  process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  if (is_upper) {
    char *upper_str = s21_to_upper(temp);
    s21_strncpy(temp, upper_str, len);
    free(upper_str);
  }
  s21_strncpy(str, temp, len);
  *jump = len;
}

void prc_mod(char *str, int *jump, const flag_t *flags) {
  if (flags->align_left) {
  }
  char temp[TEMP_BUFFER_SIZE] = {0};
  s21_strncpy(temp, "%", 2);
  // process_flags(temp, flags, 1);
  s21_size_t len = s21_strlen(temp);
  s21_strncpy(str, temp, len);
  *jump = len;
}

void parse_width_or_precision(const char *str, flag_t *flags, va_list *args,
                              s21_size_t len, s21_size_t *i) {
  if (str[*i] == '*') {
    flags->width = va_arg(*args, int);
  } else if (str[*i] >= '1' && str[*i] <= '9') {
    char temp[16] = {};
    s21_size_t j = 0;
    while (*i < len && str[*i] >= '0' && str[*i] <= '9') {
      temp[j++] = str[(*i)++];
    }
    flags->width = s21_atof(temp);
    (*i)--;  // Компенсируем последний проход str[i++], НУЖНОЕ
  } else if (str[*i] == '.') {
    (*i)++;  // Сразу смотри чо там дальше по точности
    if (str[*i] == '*') {  // если звезда, то всем ..
      flags->precision = va_arg(*args, int);
    } else if (str[*i] >= '1' && str[*i] <= '9') {
      char temp[16] = {};
      s21_size_t j = 0;
      while (*i < len && str[*i] >= '0' && str[*i] <= '9') {
        temp[j++] = str[(*i)++];
      }
      flags->precision = s21_atof(temp);
      (*i)--;  // Опять же компенсируем :)
    } else {
      flags->precision = 0;
    }
  }
}

void parse_flags(flag_t *flags, const char *str, s21_size_t len,
                 va_list *args) {
  s21_size_t i = 0;
  while (i < len) {
    switch (str[i]) {
      case '-':
        flags->align_left = 1;
        break;
      case '+':
        flags->show_sign = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '#':
        flags->sharp = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'L':
        flags->L = 1;
        break;
      default:
        parse_width_or_precision(str, flags, args, len, &i);
    }
    i++;
  }
  if (flags->show_sign) {
    flags->space = 0;
  }
  if (flags->align_left) {
    flags->zero = 0;
  }
}

char *parse_modification(char *str, char *next, va_list *args, int *jump,
                         int current_len) {
  const char *mods = "cdieEfgGosuxXpn%";
  s21_size_t find = s21_strcspn(next, mods);
  flag_t flags = {0};
  flags.precision = -1;
  if (next[find] != '\0') {
    if (find > 0) {
      parse_flags(&flags, next, find, args);
    }
    if (next[find] == 's') {
      s_mod(str, args, jump, &flags);
    } else if (next[find] == 'c') {
      c_mod(str, args, jump, &flags);
    } else if (next[find] == 'd' || next[find] == 'i') {
      d_i_mod(str, args, jump, &flags);
    } else if (next[find] == 'u') {
      u_mod(str, args, jump, &flags);
    } else if (next[find] == 'f') {
      if (flags.L) {
        lf_mod(str, args, jump, &flags);
      } else {
        f_mod(str, args, jump, &flags);
      }
    } else if (next[find] == 'p') {
      p_mod(str, args, jump, &flags);
    } else if (next[find] == 'x' || next[find] == 'X') {
      x_mod(str, args, jump, &flags, next[find] == 'X');
    } else if (next[find] == 'o') {
      o_mod(str, args, jump, &flags);
    } else if (next[find] == 'n') {
      n_mod(current_len, args, jump);
    } else if (next[find] == 'e') {
      e_mod(str, args, jump, &flags, 0);
    } else if (next[find] == 'E') {
      e_mod(str, args, jump, &flags, 1);
    } else if (next[find] == 'g' || next[find] == 'G') {
      g_mod(str, args, jump, &flags, next[find] == 'G');
    } else if (next[find] == '%') {
      prc_mod(str, jump, &flags);
    }
    str = next + find + 1;
  } else {
    *str = '%';
    *jump = 1;
    str = next;
  }
  return str;
}

int s21_sprintf(char *str, const char *format, ...) {
  int current_len = 0;
  va_list args;
  va_start(args, format);
  s21_size_t format_len = s21_strlen(format);
  char *fmt = malloc((format_len + 1) * sizeof(char));
  s21_strncpy(fmt, format, format_len + 1);

  char *next = fmt;
  int jump = 0;
  while (*next != '\0') {
    s21_size_t literal_len = s21_strcspn(next, "%");
    s21_strncpy(str, next, literal_len);
    str += literal_len;
    current_len += literal_len;
    next += literal_len;

    if (*next != '\0') {
      next = parse_modification(str, next + 1, &args, &jump, current_len);
      str += jump;
      current_len += jump;
    }
  }

  va_end(args);
  *str = '\0';
  free(fmt);
  return current_len;
}

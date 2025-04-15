#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/s21_atof.h"
#include "core/s21_etoa.h"
#include "core/s21_ltoa.h"
#include "core/s21_utoa.h"
#include "s21_string.h"

typedef struct TestCases {
  Suite *suite;
  TCase *tcase;
  SRunner *runner;
} TestCases;

START_TEST(s21_memchr_test) {
  char test1[] = "123456";
  char test2 = '4';
  char test3 = '7';
  char test4[] = "hello/\0";
  char test5[] = "h";
  char test6 = 'h';
  char test7 = ' ';
  char test8 = '/';
  char test9 = '\0';

  ck_assert_ptr_eq(s21_memchr(test1, test2, 6), memchr(test1, test2, 6));
  ck_assert_ptr_eq(s21_memchr(test1, test3, 6), memchr(test1, test3, 6));
  ck_assert_ptr_eq(s21_memchr(test4, test6, 6), memchr(test4, test6, 6));
  ck_assert_ptr_eq(s21_memchr(test5, test7, 1), memchr(test5, test7, 1));
  ck_assert_ptr_eq(s21_memchr(test4, test8, 6), memchr(test4, test8, 6));
  ck_assert_ptr_eq(s21_memchr(test4, test9, 6), memchr(test4, test9, 6));
}
END_TEST

START_TEST(s21_memcmp_test) {
  const char str[] = "just a text :)";
  const char not_str[] = "its not a str :(";
  const char not_str_two[] = "yahooooooooooooooo";
  s21_size_t len = 14;

  ck_assert_int_eq(s21_memcmp(str, str, len) == 0, memcmp(str, str, len) == 0);
  ck_assert_int_eq(s21_memcmp(str, not_str, len) > 0,
                   memcmp(str, not_str, len) > 0);
  ck_assert_int_eq(s21_memcmp(str, not_str_two, len) < 0,
                   memcmp(str, not_str_two, len) < 0);
}
END_TEST

START_TEST(s21_memset_test) {
  char str[] = "test test";
  char str_two[] = "test test";
  s21_size_t len = 9;

  char *res = s21_memset(str, 'a', len);
  char *res_two = memset(str_two, 'a', len);

  ck_assert_ptr_eq(res, str);
  ck_assert_ptr_eq(res_two, str_two);
  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_memcpy_test) {
  char str[] = "test protest";
  char str_two[] = "test protest";
  const char insert[] = "hello";
  s21_size_t len = 5;

  char *res = s21_memcpy(str, insert, len);
  char *res_two = memcpy(str_two, insert, len);

  ck_assert_ptr_eq(res, str);
  ck_assert_ptr_eq(res_two, str_two);
  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strncat_test_1) {
  char str[100] = "Hello ";
  char str_two[100] = "Hello ";
  const char insert[] = "World";
  s21_size_t len = 5;

  char *res = s21_strncat(str, insert, len);
  char *res_two = strncat(str_two, insert, len);

  ck_assert_ptr_eq(res, str);
  ck_assert_ptr_eq(res_two, str_two);
  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strncat_test_2) {
  char str[100] = "Hello ";
  char str_two[100] = "Hello ";
  const char insert[] = "Great World";
  s21_size_t len = 5;

  char *res = s21_strncat(str, insert, len);
  char *res_two = strncat(str_two, insert, len);

  ck_assert_ptr_eq(res, str);
  ck_assert_ptr_eq(res_two, str_two);
  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strchr_test) {
  const char str[] = "Hello World";

  ck_assert_ptr_eq(s21_strchr(str, 'H'), strchr(str, 'H'));
  ck_assert_ptr_eq(s21_strchr(str, ' '), strchr(str, ' '));
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));
}
END_TEST

START_TEST(s21_strncmp_test) {
  const char str[] = "just a text :)";
  const char not_str[] = "its not a str :(";
  const char not_str_two[] = "yahooooooooooooooo";
  s21_size_t len = 7;

  ck_assert_int_eq(s21_strncmp(str, str, len) == 0,
                   strncmp(str, str, len) == 0);
  ck_assert_int_eq(s21_strncmp(str, not_str, len) > 0,
                   strncmp(str, not_str, len) > 0);
  ck_assert_int_eq(s21_strncmp(str, not_str_two, len) < 0,
                   strncmp(str, not_str_two, len) < 0);
}
END_TEST

START_TEST(s21_strncpy_test) {
  char str[] = "test protest";
  char str_two[] = "test protest";
  const char insert[] = "hello";
  s21_size_t len = 5;

  char *res = s21_strncpy(str, insert, len);
  char *res_two = strncpy(str_two, insert, len);

  ck_assert_ptr_eq(res, str);
  ck_assert_ptr_eq(res_two, str_two);
  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strcspn_test) {
  const char str[] = "Hello everyone";

  ck_assert_uint_eq(s21_strcspn(str, "e"), strcspn(str, "e"));
  ck_assert_uint_eq(s21_strcspn(str, "v"), strcspn(str, "v"));
  ck_assert_uint_eq(s21_strcspn(str, ""), strcspn(str, ""));
  ck_assert_uint_eq(s21_strcspn(str, "llo"), strcspn(str, "llo"));
}
END_TEST

START_TEST(s21_strerror_test_1) {
  char *res = s21_strerror(10);
  char *res_two = strerror(10);

  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strerror_test_2) {
  char *res = s21_strerror(1000);
  char *res_two = strerror(1000);

  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strerror_test_3) {
  char *res = s21_strerror(-100);
  char *res_two = strerror(-100);

  ck_assert_str_eq(res, res_two);
}
END_TEST

START_TEST(s21_strlen_test) {
  const char str[] = "Hello World";

  ck_assert_uint_eq(s21_strlen(str), strlen(str));

  ck_assert_uint_eq(s21_strlen(s21_NULL), 0);
}
END_TEST

START_TEST(s21_strpbrk_test) {
  const char str[] = "Hello World";

  ck_assert_ptr_eq(s21_strpbrk(str, "Wo"), strpbrk(str, "Wo"));
  ck_assert_ptr_eq(s21_strpbrk(str, ""), strpbrk(str, ""));
  ck_assert_ptr_eq(s21_strpbrk(str, "H"), strpbrk(str, "H"));
  ck_assert_ptr_eq(s21_strpbrk(str, " "), strpbrk(str, " "));
}
END_TEST

START_TEST(s21_strrchr_test) {
  const char str[] = "Hello World";

  ck_assert_ptr_eq(s21_strrchr(str, 'H'), strrchr(str, 'H'));
  ck_assert_ptr_eq(s21_strrchr(str, ' '), strrchr(str, ' '));
  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

START_TEST(s21_strstr_test) {
  const char str[] = "Hello World";

  ck_assert_ptr_eq(s21_strstr(str, ""), strstr(str, ""));
  ck_assert_ptr_eq(s21_strstr(str, "World"), strstr(str, "World"));
  ck_assert_ptr_eq(s21_strstr(str, "He"), strstr(str, "He"));
  ck_assert_ptr_eq(s21_strstr(str, "test"), strstr(str, "test"));
}
END_TEST

START_TEST(s21_strtok_test_1) {
  char str[] = "test1|test2|test3|test4-test5|-test6";
  char str_two[] = "test1|test2|test3|test4-test5|-test6";

  char *token = s21_strtok(str, "|-");
  char *token_two = strtok(str_two, "|-");
  while (token != s21_NULL && token_two != NULL) {
    ck_assert_str_eq(token, token_two);
    token = s21_strtok(s21_NULL, "|-");
    token_two = strtok(NULL, "|-");
  }
}
END_TEST

START_TEST(s21_strtok_test_2) {
  char str[] = "test1";
  char str_two[] = "test1";

  char *token = s21_strtok(str, "|-");
  char *token_two = strtok(str_two, "|-");
  while (token != s21_NULL && token_two != NULL) {
    ck_assert_str_eq(token, token_two);
    token = s21_strtok(s21_NULL, "|-");
    token_two = strtok(NULL, "|-");
  }
}
END_TEST

START_TEST(s21_to_upper_test_1) {
  const char str[] = "TeSt upper%%123!\n|";
  char *upper = s21_to_upper(str);

  ck_assert_str_eq(upper, "TEST UPPER%%123!\n|");

  free(upper);
}
END_TEST

START_TEST(s21_to_upper_test_2) {
  char *upper = s21_to_upper(s21_NULL);

  ck_assert_ptr_eq(upper, s21_NULL);
}
END_TEST

START_TEST(s21_to_lower_test_1) {
  const char str[] = "TeSt LOWER%%!";
  char *lower = s21_to_lower(str);

  ck_assert_str_eq(lower, "test lower%%!");

  free(lower);
}
END_TEST

START_TEST(s21_to_lower_test_2) {
  char *lower = s21_to_lower(s21_NULL);

  ck_assert_ptr_eq(lower, s21_NULL);
}
END_TEST

START_TEST(s21_insert_test_1) {
  const char str[] = "Hello World";
  const char insert[] = " fucking";

  char *new_str = s21_insert(str, insert, 6);

  ck_assert_str_eq(new_str, "Hello fucking World");

  free(new_str);
}
END_TEST

START_TEST(s21_insert_test_2) {
  const char str[] = "Hello World";

  char *new_str = s21_insert(str, s21_NULL, 6);

  ck_assert_ptr_eq(new_str, s21_NULL);

  free(new_str);
}
END_TEST

START_TEST(s21_insert_test_3) {
  const char str[] = "Hello World";

  char *new_str = s21_insert(s21_NULL, str, 6);

  ck_assert_ptr_eq(new_str, s21_NULL);

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_1) {
  const char str[] = "$Hello World$ ";
  const char trim[] = " $";

  char *new_str = s21_trim(str, trim);

  ck_assert_str_eq(new_str, "Hello World");

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_2) {
  const char str[] = "Hello World$ ";
  const char trim[] = " $";

  char *new_str = s21_trim(str, trim);

  ck_assert_str_eq(new_str, "Hello World");

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_3) {
  const char str[] = "$Hello World";
  const char trim[] = " $";

  char *new_str = s21_trim(str, trim);

  ck_assert_str_eq(new_str, "Hello World");

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_4) {
  const char trim[] = " $";

  char *new_str = s21_trim(s21_NULL, trim);

  ck_assert_ptr_eq(new_str, s21_NULL);

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_5) {
  const char str[] = "$Hello World";

  char *new_str = s21_trim(str, s21_NULL);

  ck_assert_str_eq(new_str, "$Hello World");

  free(new_str);
}
END_TEST

START_TEST(s21_trim_test_6) {
  const char str[] = "\n\r\t";

  char *new_str = s21_trim(str, s21_NULL);

  ck_assert_str_eq(new_str, "");

  free(new_str);
}
END_TEST

START_TEST(s21_sprintf_test_1) {
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%s:%s", "Hello", s21_NULL);
    int res_two = sprintf(str_two, "%s:%s", "Hello", NULL);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%50s", "Hello");
    int res_two = sprintf(str_two, "%50s", "Hello");

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%-50s", "Hello");
    int res_two = sprintf(str_two, "%-50s", "Hello");

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%c", 'c');
    int res_two = sprintf(str_two, "%c", 'c');

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
}
END_TEST

START_TEST(s21_sprintf_test_2) {
  char str[100] = {0};
  char str_two[100] = {0};

  int res = s21_sprintf(str, "%d:%i", 123, -321);
  int res_two = sprintf(str_two, "%d:%i", 123, -321);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%010d", 123);
  res_two = sprintf(str_two, "%010d", 123);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%#10d", 123);
  res_two = sprintf(str_two, "%#10d", 123);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%+*d", 10, 123);
  res_two = sprintf(str_two, "%+*d", 10, 123);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%.20d", 123456);
  res_two = sprintf(str_two, "%.20d", 123456);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%.*d", 20, -123456);
  res_two = sprintf(str_two, "%.*d", 20, -123456);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
}
END_TEST

START_TEST(s21_sprintf_test_3) {
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%u %hu", -123, 123456);
    int res_two = sprintf(str_two, "%u %hu", -123, 123456);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%.10s", "test");
    int res_two = sprintf(str_two, "%.10s", "test");

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%.3s", "test");
    int res_two = sprintf(str_two, "%.3s", "test");

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "% 010d %+015d", 123456, 654321);
    int res_two = sprintf(str_two, "% 010d %+015d", 123456, 654321);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
}
END_TEST

START_TEST(s21_sprintf_test_4) {
  char str[100] = {0};
  char str_two[100] = {0};
  int res = s21_sprintf(str, "%f %f", -12.345678, INFINITY);
  int res_two = sprintf(str_two, "%f %f", -12.345678, INFINITY);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%+.5f %f", 12.345678, NAN);
  res_two = sprintf(str_two, "%+.5f %f", 12.345678, NAN);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "% f", -12.345678);
  res_two = sprintf(str_two, "% f", -12.345678);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%#.0f", -12.345678);
  res_two = sprintf(str_two, "%#.0f", -12.345678);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%10.20f", -12.345678);
  res_two = sprintf(str_two, "%10.20f", -12.345678);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  long double lgnum = 12.345678;
  res = s21_sprintf(str, "%Lf %Lf %Lf", lgnum, NAN, INFINITY);
  res_two = sprintf(str_two, "%Lf %Lf %Lf", lgnum, NAN, INFINITY);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%lf", -12.345678);
  res_two = sprintf(str_two, "%lf", -12.345678);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%hf", -12.345678);
  res_two = sprintf(str_two, "%hf", -12.345678);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
  res = s21_sprintf(str, "%f %f", s21_pow(10, 1000), s21_pow(-10, 1000));
  res_two = sprintf(str_two, "%f %f", s21_pow(10, 1000), s21_pow(-10, 1000));
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
}
END_TEST

START_TEST(s21_sprintf_test_5) {
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%-.1f", -12.345678);
    int res_two = sprintf(str_two, "%-.1f", -12.345678);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};
    char test[] = "Hello World";

    int res = s21_sprintf(str, "%p", test);
    int res_two = sprintf(str_two, "%p", test);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%p", s21_NULL);
    int res_two = sprintf(str_two, "%p", NULL);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
  {
    char str[100] = {0};
    char str_two[100] = {0};

    int res = s21_sprintf(str, "%hd %ld", 10000000, 12345678);
    int res_two = sprintf(str_two, "%hd %ld", 10000000, 12345678);

    ck_assert_int_eq(res, res_two);
    ck_assert_str_eq(str, str_two);
  }
}
END_TEST

START_TEST(s21_sprintf_test_6) {
  char str[100] = {0};
  char str_two[100] = {0};

  int res = s21_sprintf(str, "%x:%X:%hx", 123, 321, 1234567);
  int res_two = sprintf(str_two, "%x:%X:%hx", 123, 321, 1234567);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%#x:%#X:%lx:%hx", 123, 321, 111, 4444);
  res_two = sprintf(str_two, "%#x:%#X:%lx:%hx", 123, 321, 111, 4444);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%hx:%ho:%lo", 12345, 12345, 12345);
  res_two = sprintf(str_two, "%hx:%ho:%lo", 12345, 12345, 12345);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%o %ho", 123321, 1234567);
  res_two = sprintf(str_two, "%o %ho", 123321, 1234567);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%#o", 123321);
  res_two = sprintf(str_two, "%#o", 123321);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  int len = 0;
  int len_two = 0;
  res = s21_sprintf(str, "%o %n", 123321, &len);
  res_two = sprintf(str_two, "%o %n", 123321, &len_two);
  ck_assert_int_eq(res, res_two);
  ck_assert_int_eq(len, len_two);
  ck_assert_str_eq(str, str_two);
}
END_TEST

START_TEST(s21_sprintf_test_7) {
  char str[100] = {0};
  char str_two[100] = {0};

  int res = s21_sprintf(str, "%e:%E", 123.321, 999.9999999);
  int res_two = sprintf(str_two, "%e:%E", 123.321, 999.9999999);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%g:%G", 123.321, 999.9999999);
  res_two = sprintf(str_two, "%g:%G", 123.321, 999.9999999);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%g:%G", 1234567.321, 100);
  res_two = sprintf(str_two, "%g:%G", 1234567.321, 100);
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%%");
  res_two = sprintf(str_two, "%%");
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "%я");
  res_two = sprintf(str_two, "%я");
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);

  res = s21_sprintf(str, "Test");
  res_two = sprintf(str_two, "Test");
  ck_assert_int_eq(res, res_two);
  ck_assert_str_eq(str, str_two);
}
END_TEST

START_TEST(s21_other_test) {
  double test = s21_atof("-123");
  double test_two = atof("-123");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("+123");
  test_two = atof("+123");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("    +123");
  test_two = atof("    +123");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("+123abc");
  test_two = atof("+123abc");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("+123abc");
  test_two = atof("+123abc");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("123.456abc7");
  test_two = atof("123.456abc7");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("1.0e-1");
  test_two = atof("1.0e-1");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("1.8E+1");
  test_two = atof("1.8E+1");
  ck_assert_double_eq(test, test_two);

  test = s21_atof("1.8E+abc1");
  test_two = atof("1.8E+abc1");
  ck_assert_double_eq(test, test_two);

  char str[100] = {0};
  s21_etoa(1.0, str, -1, 0);
  s21_etoa(-1000, str, -1, 0);
  s21_etoa(0.0, str, -1, 0);
  s21_etoa(0.75, str, 0, 0);

  s21_utoa(0, str);

  s21_ltoa(-100000000, str, 16);
}
END_TEST

TestCases init_test_cases(void) {
  TestCases tc;
  tc.suite = suite_create("s21_string");
  tc.tcase = tcase_create("s21_string");
  tc.runner = srunner_create(tc.suite);
  suite_add_tcase(tc.suite, tc.tcase);
  return tc;
}

void add_tests_to_case(TCase *tc) {
  tcase_add_test(tc, s21_memchr_test);
  tcase_add_test(tc, s21_memcmp_test);
  tcase_add_test(tc, s21_memset_test);
  tcase_add_test(tc, s21_memcpy_test);
  tcase_add_test(tc, s21_strncat_test_1);
  tcase_add_test(tc, s21_strncat_test_2);
  tcase_add_test(tc, s21_strchr_test);
  tcase_add_test(tc, s21_strncmp_test);
  tcase_add_test(tc, s21_strncpy_test);
  tcase_add_test(tc, s21_strcspn_test);
  tcase_add_test(tc, s21_strerror_test_1);
  tcase_add_test(tc, s21_strerror_test_2);
  tcase_add_test(tc, s21_strerror_test_3);
  tcase_add_test(tc, s21_strlen_test);
  tcase_add_test(tc, s21_strpbrk_test);
  tcase_add_test(tc, s21_strrchr_test);
  tcase_add_test(tc, s21_strstr_test);
  tcase_add_test(tc, s21_strtok_test_1);
  tcase_add_test(tc, s21_strtok_test_2);
  tcase_add_test(tc, s21_to_upper_test_1);
  tcase_add_test(tc, s21_to_upper_test_2);
  tcase_add_test(tc, s21_to_lower_test_1);
  tcase_add_test(tc, s21_to_lower_test_2);
  tcase_add_test(tc, s21_insert_test_1);
  tcase_add_test(tc, s21_insert_test_2);
  tcase_add_test(tc, s21_insert_test_3);
  tcase_add_test(tc, s21_trim_test_1);
  tcase_add_test(tc, s21_trim_test_2);
  tcase_add_test(tc, s21_trim_test_3);
  tcase_add_test(tc, s21_trim_test_4);
  tcase_add_test(tc, s21_trim_test_5);
  tcase_add_test(tc, s21_trim_test_6);
  tcase_add_test(tc, s21_sprintf_test_1);
  tcase_add_test(tc, s21_sprintf_test_2);
  tcase_add_test(tc, s21_sprintf_test_3);
  tcase_add_test(tc, s21_sprintf_test_4);
  tcase_add_test(tc, s21_sprintf_test_5);
  tcase_add_test(tc, s21_sprintf_test_6);
  tcase_add_test(tc, s21_sprintf_test_7);
  tcase_add_test(tc, s21_other_test);
}

int run_tests(SRunner *runner) {
  int failed_tests;
  srunner_run_all(runner, CK_NORMAL);
  failed_tests = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed_tests;
}

int main(void) {
  TestCases tc = init_test_cases();
  add_tests_to_case(tc.tcase);
  int failed_tests = run_tests(tc.runner);
  return failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
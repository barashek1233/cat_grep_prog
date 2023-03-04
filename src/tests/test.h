#ifndef SRC_TEST_ME_H
#define SRC_TEST_ME_H

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

Suite *test_memchr(void);
Suite *test_memcmp(void);
Suite *test_memcpy(void);
Suite *test_memmove(void);
Suite *test_memset(void);
Suite *test_strcat(void);
Suite *test_strncat(void);
Suite *s21_strchr_suite(void);
Suite *s21_string_strlen_suite(void);
Suite *s21_math_pow_suite();
Suite *s21_strrchr_suite();
Suite *s21_strspn_suite();
Suite *s21_string_strcmp_suite();
Suite *s21_strncmp_suite();
Suite *s21_strstr_suite();
Suite *s21_strtok_suite();
Suite *s21_strerror_suite();
Suite *s21_strcpy_suite();
Suite *s21_strncpy_suite();
Suite *s21_string_strcspn_suite();
Suite *suite_sprintf(void);
Suite *suite_sscanf(void);
Suite *test_to_lower(void);
Suite *test_to_upper(void);
Suite *test_trim(void);

#endif  // SRC_TESTS_ME_H

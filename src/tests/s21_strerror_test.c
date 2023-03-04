#include "test.h"

#ifdef __linux__
#define MAX 133
#elif __APPLE__
#define MAX 106
#endif

START_TEST(test_s21_string_strerror_usual) {
  for (int i = 0; i <= MAX; i++) {
    ck_assert_pstr_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_s21_string_strerror_unusual) {
  for (int i = MAX; i <= 2 * MAX; i++) {
    ck_assert_pstr_eq(s21_strerror(i), strerror(i));
    ck_assert_pstr_eq(s21_strerror(-i), strerror(-i));
  }
}
END_TEST

Suite *s21_strerror_suite() {
  Suite *s;
  TCase *tc_strerror_usual, *tc_strerror_unusual;

  s = suite_create("\033[45m-=S21_STRERROR=-\033[0m");

  tc_strerror_usual = tcase_create("strerror_usual");
  tcase_add_test(tc_strerror_usual, test_s21_string_strerror_usual);
  suite_add_tcase(s, tc_strerror_usual);

  tc_strerror_unusual = tcase_create("strerror_unusual");
  tcase_add_test(tc_strerror_unusual, test_s21_string_strerror_unusual);
  suite_add_tcase(s, tc_strerror_unusual);

  return s;
}
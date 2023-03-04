#include "test.h"

char *s21_strrchr(const char *str, int c);

START_TEST(test_s21_string_strrchr_usual1) {
  char *str = "abobus";
  ck_assert_pstr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(test_s21_string_strrchr_usual2) {
  char *str =
      "ffffffffffffffffffffffffffffffffffffffffffffssssssssssssssssssss";
  ck_assert_pstr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(empty_str) {
  char *str = "";
  ck_assert_pstr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(test_s21_string_strrchr_usual3) {
  char *str = "aaabib";
  ck_assert_pstr_eq(s21_strrchr(str, 's'), strrchr(str, 's'));
}
END_TEST

START_TEST(terminate_null) {
  char *str = "abibus";
  ck_assert_pstr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));
}
END_TEST

Suite *s21_strrchr_suite() {
  Suite *s;
  TCase *tc_strrchr_normal = tcase_create("strrchr_normal");

  s = suite_create("\033[45m-=S21_STRRCHR=-\033[0m");
  tcase_add_test(tc_strrchr_normal, test_s21_string_strrchr_usual1);
  tcase_add_test(tc_strrchr_normal, test_s21_string_strrchr_usual2);
  tcase_add_test(tc_strrchr_normal, test_s21_string_strrchr_usual3);
  tcase_add_test(tc_strrchr_normal, empty_str);
  tcase_add_test(tc_strrchr_normal, terminate_null);
  suite_add_tcase(s, tc_strrchr_normal);
  return s;
}
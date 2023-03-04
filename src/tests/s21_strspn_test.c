#include "test.h"

START_TEST(s21_test_strspn_usual1) {
  char *str = "abobus";
  char *sym = "boooooooooooooooooob";
  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

START_TEST(s21_test_strspn_usual2) {
  char *str = "privet";
  char *sym = "privet";
  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

START_TEST(s21_test_strspn_usual3) {
  char *str = "abooooooooooooooooooooobus";
  char *sym = "o";
  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

START_TEST(s21_test_strspn_usual4) {
  char *str = "abobus";
  char *sym = "basuo";
  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

START_TEST(s21_test_strspn_unusual1) {
  char *str = "\0";
  char *sym = "\0";
  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

START_TEST(s21_test_strspn_unusual3) {
  char *str = "";
  char *sym = "";

  ck_assert_int_eq(s21_strspn(str, sym), strspn(str, sym));
}
END_TEST

Suite *s21_strspn_suite() {
  Suite *s;
  TCase *tc1_1 = tcase_create("strspn_normale");

  s = suite_create("\033[45m-=S21_STRSPN=-\033[0m");
  tcase_add_test(tc1_1, s21_test_strspn_usual1);
  tcase_add_test(tc1_1, s21_test_strspn_usual2);
  tcase_add_test(tc1_1, s21_test_strspn_usual3);
  tcase_add_test(tc1_1, s21_test_strspn_usual4);
  tcase_add_test(tc1_1, s21_test_strspn_unusual1);
  tcase_add_test(tc1_1, s21_test_strspn_unusual3);
  suite_add_tcase(s, tc1_1);
  return s;
}
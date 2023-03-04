#include "test.h"

START_TEST(test_s21_string_strcspn_normal) {
  char str1[30] = "wHello world! Hello School 21!";
  char str2[30] = "Ok, I oul like to...";
  char str3[30] = "\0";
  char example[10] = "!";
  ck_assert_int_eq(strcspn(str1, example), s21_strcspn(str1, example));
  ck_assert_int_eq(strcspn(str2, example), s21_strcspn(str2, example));
  ck_assert_int_eq(strcspn(str3, example), s21_strcspn(str3, example));
}
END_TEST

START_TEST(test_s21_string_strcspn_broke) {
  char str1[30] = "01";
  char str2[30] = "\0";
  char example[10] = "1";
  ck_assert_int_eq(strcspn(str1, example), s21_strcspn(str1, example));
  ck_assert_int_eq(strcspn(str2, example), s21_strcspn(str2, example));
}
END_TEST

Suite *s21_string_strcspn_suite() {
  Suite *s;
  TCase *tc_strcspn_normal, *tc_strcspn_broke;

  s = suite_create("\033[45m-=S21_STRCSPN=-\033[0m");

  tc_strcspn_normal = tcase_create("strcspn_normal");
  tcase_add_test(tc_strcspn_normal, test_s21_string_strcspn_normal);
  suite_add_tcase(s, tc_strcspn_normal);

  tc_strcspn_broke = tcase_create("strcspn_broke");
  tcase_add_test(tc_strcspn_broke, test_s21_string_strcspn_broke);
  suite_add_tcase(s, tc_strcspn_broke);

  return s;
}
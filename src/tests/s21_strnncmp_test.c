#include "test.h"

START_TEST(s21_strncmp_test_usual) {
  char str1[] = "word123231313", str2[] = "word12";
  ck_assert_int_eq(strncmp(str1, str2, 0), s21_strncmp(str1, str2, 0));
  // ck_assert_int_eq(strncmp(str1, str2, -1), s21_strncmp(str1, str2, -1));
  ck_assert_int_eq(strncmp(str1, str2, 6), s21_strncmp(str1, str2, 6));
}
END_TEST

START_TEST(s21_strncmp_test_unusual) {
  char str3[] = "word123231313", str4[] = "word12";
  char str5[] = "", str6[] = "";
  ck_assert_int_eq(strncmp(str3, str4, 15), s21_strncmp(str3, str4, 15));
  ck_assert_int_eq(strncmp(str3, str4, 30), s21_strncmp(str3, str4, 30));
  ck_assert_int_eq(strncmp(str6, str5, 100), s21_strncmp(str5, str6, 100));
}
END_TEST

Suite *s21_strncmp_suite() {
  Suite *s;
  TCase *tc_strncmp_usual, *tc_strncmp_unusual;

  s = suite_create("\033[45m-=S21_STRNCMP=-\033[0m");

  tc_strncmp_usual = tcase_create("s21_strncmp_test_usual");
  tcase_add_test(tc_strncmp_usual, s21_strncmp_test_usual);
  suite_add_tcase(s, tc_strncmp_usual);

  tc_strncmp_unusual = tcase_create("s21_strncmp_test_usual");
  tcase_add_test(tc_strncmp_unusual, s21_strncmp_test_unusual);
  suite_add_tcase(s, tc_strncmp_unusual);

  return s;
}
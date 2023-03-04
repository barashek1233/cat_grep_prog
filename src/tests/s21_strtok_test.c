#include "test.h"

START_TEST(test_s21_string_strtok_usual) {
  char str1[] = "dir1/di.r2/d.ir3/di.r4";
  char str2[] = "dir1/di.r2/d.ir3/di.r4";
  char delim1[] = "/.";
  char *p1 = strtok(str1, delim1);
  char *p2 = s21_strtok(str2, delim1);
  while (p1 != S21_NULL && p2 != S21_NULL) {
    p1 = strtok(S21_NULL, delim1);
    p2 = s21_strtok(S21_NULL, delim1);
    ck_assert_pstr_eq(p1, p2);
  }

  char str3[] = "Lorem ipsum dolor sit amet";
  char str4[] = "Lorem ipsum dolor sit amet";
  char delim[] = " ";
  char *p3 = strtok(str3, delim);
  char *p4 = s21_strtok(str4, delim);
  while (p3 != S21_NULL && p4 != S21_NULL) {
    p3 = strtok(S21_NULL, delim);
    p4 = s21_strtok(S21_NULL, delim);
    ck_assert_pstr_eq(p1, p2);
  }
}
END_TEST

START_TEST(test_s21_string_strtok_unusual) {
  char str1[] = "dir1/di.r2/d.ir3/di.r4";
  char delim[] = "&";
  ck_assert_ptr_null(s21_strtok(S21_NULL, delim));
  ck_assert_ptr_null(s21_strtok(S21_NULL, S21_NULL));
  ck_assert_ptr_eq(s21_strtok(str1, ""), strtok(str1, ""));
}
END_TEST

Suite *s21_strtok_suite() {
  Suite *s;
  TCase *tc_strtok_usual, *tc_strtok_unusual;

  s = suite_create("\033[45m-=S21_STRTOK=-\033[0m");

  tc_strtok_usual = tcase_create("strtok_usual");
  tcase_add_test(tc_strtok_usual, test_s21_string_strtok_usual);
  suite_add_tcase(s, tc_strtok_usual);

  tc_strtok_unusual = tcase_create("strtok_unusual");
  tcase_add_test(tc_strtok_unusual, test_s21_string_strtok_unusual);
  suite_add_tcase(s, tc_strtok_unusual);

  return s;
}
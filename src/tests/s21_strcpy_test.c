#include "test.h"

START_TEST(test_s21_string_strcpy_usual) {
  char *src = "Hello, world!";
  char dst[14];
  ck_assert_pstr_eq(s21_strcpy(dst, src), strcpy(dst, src));
}
END_TEST

START_TEST(test_s21_string_strcpy_unusual) {
  char src[6] = {'H', 'E', 'L', 'L', 'O', '\0'};
  char dst[6];
  ck_assert_pstr_eq(s21_strcpy(dst, src), strcpy(dst, src));

  char src_e[6] = {};
  char dst_e[6];
  ck_assert_pstr_eq(s21_strcpy(dst_e, src_e), strcpy(dst_e, src_e));
}
END_TEST

Suite *s21_strcpy_suite() {
  Suite *s;
  TCase *tc_strcpy_usual, *tc_strcpy_unusual;

  s = suite_create("\033[45m-=S21_STRCPY=-\033[0m");

  tc_strcpy_usual = tcase_create("strcpy_usual");
  tcase_add_test(tc_strcpy_usual, test_s21_string_strcpy_usual);
  suite_add_tcase(s, tc_strcpy_usual);

  tc_strcpy_unusual = tcase_create("strcpy_unusual");
  tcase_add_test(tc_strcpy_unusual, test_s21_string_strcpy_unusual);
  suite_add_tcase(s, tc_strcpy_unusual);

  return s;
}
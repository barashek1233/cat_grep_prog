#include "test.h"

int main(void) {
  int failed = 0;
  Suite *s21_string_test[] = {test_memchr(),
                              test_memcmp(),
                              test_memcpy(),
                              test_memmove(),
                              test_memset(),
                              test_strcat(),
                              test_strncat(),
                              s21_strchr_suite(),
                              s21_string_strlen_suite(),
                              s21_math_pow_suite(),
                              s21_strrchr_suite(),
                              s21_strspn_suite(),
                              s21_string_strcmp_suite(),
                              s21_strncmp_suite(),
                              s21_strstr_suite(),
                              s21_strtok_suite(),
                              s21_strerror_suite(),
                              s21_strcpy_suite(),
                              s21_strncpy_suite(),
                              s21_string_strcspn_suite(),
                              suite_sprintf(),
                              suite_sscanf(),
                              test_to_lower(),
                              test_to_upper(),
                              test_trim(),
                              NULL};

  for (int i = 0; s21_string_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_string_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
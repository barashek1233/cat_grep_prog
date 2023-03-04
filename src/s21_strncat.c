//  char *strncat(char *dest, const char *src, size_t n)
//  Добавляет строку, на которую указывает src, в конец строки, на которую
//  указывает dest, длиной до n символов.
#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t lenDest;

  lenDest = s21_strlen(dest);
  for (s21_size_t i = 0; i < n; i++) {
    dest[lenDest + i] = src[i];
  }
  return dest;
}

// int main() {
//   char str1[10] = "ab";
//   char str2[10] = "cd";
//   char *str3, *str4;
//   str4 = strncat(str1, str2, 3);
//   str3 = s21_strncat(str1, str2, 3);
//   printf("%s\n", str3);
//   printf("%s\n", str4);
// }
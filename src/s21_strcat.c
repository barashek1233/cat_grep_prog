#include "s21_string.h"

//  char *strcat(char *dest, const char *src)
//  Добавляет строку, на которую указывает src, в конец строки, на которую
//  указывает dest.
char *s21_strcat(char *dest, const char *src) {
  s21_strcpy(dest + s21_strlen(dest), src);
  return dest;
}

// int main() {
//   char str1[10] = "ab";
//   char str2[10] = "cd";
//   char *str3;
//   str3 = s21_strcat(str1, str2);
//   printf("%s", str3);
// }
#include "s21_string.h"

// char *strchr(const char *str, int c)
// ыполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.

// char *s21_strchr(const char *str, int c) {
//   char* ret = S21_NULL;
//   for (s21_size_t i = 0; i < strlen(str); i++) {
//     if (str[i] == (char)c) {
//       ret = (char*)&str[i];
//     }
//   }
//   return ret;
// }

// int main() {
//   char str[10] = "abcdefg";
//   char* sim;
//   sim = s21_strchr(str, 'c');
//   printf("%s\n", sim);
// }

char *s21_strchr(const char *str, int c) {
  char *symb = S21_NULL;
  while (*str != c && *str) str++;
  if (*str || (*str == '\0' && c == '\0')) {
    symb = (char *)str;
  }
  return symb;
}
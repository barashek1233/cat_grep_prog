#include "s21_string.h"

void* s21_memset(void* str, int c, s21_size_t n) {
  char* s21_str = (char*)str;
  while (n--) {
    *s21_str++ = (char)c;
  }
  return str;
}

// int main () {
//   char str[10] = "sssssss";
//   printf("%s\n", str);
//   s21_memset(str, 'a', 7);
//   printf("%s\n", str);
// }
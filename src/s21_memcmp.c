#include "s21_string.h"

/*
  int memcmp(const void *str1, const void *str2, size_t n)
  Сравнивает первые n байтов str1 и str2.
*/

// int main() {
//   char str1[10] = "abcdefg";
//   char str2[10] = "abadefg";
//   int s21_i, i;
//   s21_i = s21_memcmp(str1, str2, 6);
//   i = memcmp(str1, str2, 6);
//   printf("%d = %d\n", s21_i, i);
// }

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  char* s1 = (char*)str1;
  char* s2 = (char*)str2;
  int ret = 0;
  while (n--) {
    if (*s1 != *s2) {
      ret = (int)*s1 - (int)*s2;
      break;
    }
    s1++;
    s2++;
  }
  return ret;
}
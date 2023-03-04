#include "s21_string.h"

// int main () {
//   char s21str1[10] = "abcd";
//   char s21str2[10] = "dcbass";
//   char str1[10] = "abcd";
//   char str2[10] = "dcbass";
//   s21_memcpy(s21str1, s21str2, 4);
//   s21_memcpy(str1, str2, 4);
//   printf("%s = %s\n", s21str1, str1);
// }

/*
  void *memcpy(void *dest, const void *src, size_t n)
  Копирует n символов из src в dest.
*/

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *dest_ret = (char *)dest;
  char *src_ret = (char *)src;
  while (n--) {
    *dest_ret++ = *src_ret++;
  }
  return dest;
}
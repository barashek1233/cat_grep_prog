#include "s21_string.h"

void* s21_memmove(void* dest, const void* src, s21_size_t n) {
  char* s21dest = (char*)dest;
  char* s21src = (char*)src;
  int i;

  i = s21dest - s21src;
  if (i >= (int)n) {
    dest = s21_memcpy(dest, src, n);
  } else {
    s21dest += n - 1;
    s21src += n - 1;
    while (n--) *s21dest-- = *s21src--;
  }
  return dest;
}
// int main() {
//   char str[10] = "qwertyuio";
//   printf("%s\n", str);
//   s21_memmove(&str[5], &str[2], 4);
//   printf("%s\n", str);
// }
#include "s21_string.h"

// int main() {
//   char str[100];
//   char sym = 'a';
//   for (int i = 0; i < 20; i++) {
//     str[i] = sym;
//     sym++;
//   }
//   printf("%s\n", str);
//   char *str2 = s21_memchr(str, 'b', 10);
//   for (int i = 0; i < 5; i++) printf("%c", str2[i]);
//   printf("\n");
// }

//  void *memchr(const void *str, int c, size_t n)

// void *s21_memchr(const void *str, int c, s21_size_t n) {  //  str - указатель
// на массив с - символ n - в каком количестве байт искать
//   char *strret = (char*)str;
//   char *strreturn = NULL;
//   for (s21_size_t i = 0; i <= n; i++) {
//     if (strret[i] == (char)c) {
//       strreturn = &strret[i];
//     }
//   }
//   return strreturn;
// }

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *str_1 = (unsigned char *)str;
  void *adress = S21_NULL;
  for (s21_size_t i = 0; i < n;
       i++) {  // в оригинальной функции нет проверки str_1[i] != '\0' &&
    if (str_1[i] == c) {
      adress = (void *)str + sizeof(char) * i;
      break;
    }
  }
  return adress;
}
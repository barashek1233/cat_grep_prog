#include <string.h>  //Пока не будут доделаны остальные функции

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  int i = 0;
  void *temporary;
  if (str == S21_NULL) {
    temporary = S21_NULL;
  } else {
    char *strUpper = (char *)malloc(sizeof(char) * (s21_strlen(str) + 1));
    for (; str[i] != '\0'; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        strUpper[i] = str[i] - 32;
      } else {
        strUpper[i] = str[i];
      }
    }
    strUpper[i++] = '\0';
    temporary = strUpper;
  }
  return temporary;  // Think about NULL
}

void *s21_to_lower(const char *str) {
  int i = 0;
  void *temporary = S21_NULL;
  if (str == S21_NULL) {  //  бесполезный иф
    temporary = S21_NULL;
  } else {
    char *strLower = (char *)malloc(sizeof(char) * (s21_strlen(str) + 1));
    if (strLower != S21_NULL) {
      for (; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90) {
          strLower[i] = str[i] + 32;
        } else {
          strLower[i] = str[i];
        }
      }
      strLower[i++] = '\0';
      temporary = strLower;
    }
  }
  return temporary;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  // проверка на NULL вначале перед выделением памяти!
  void *temporary;
  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src)) {
    temporary = S21_NULL;
  } else {
    char *resultString =
        (char *)malloc(sizeof(char) * (s21_strlen(src) + s21_strlen(str) + 3));
    size_t i = start_index, indexForLast = start_index;
    s21_memcpy(resultString, src, start_index);
    for (int j = 0; str[j] != '\0'; j++, i++) {
      resultString[i] = str[j];
    }
    for (; i < (s21_strlen(src) + s21_strlen(str)) || src[indexForLast] != '\0';
         i++, indexForLast++) {
      resultString[i] = src[indexForLast];
    }
    resultString[i] = '\0';
    temporary = resultString;
  }
  return temporary;  // Think about NULL
}

// void *s21_trim(const char *src, const char *trim_chars) {
//   // FIXME:  пустая строка trimchars - пробел
//   void *temporary;
//   if (src == S21_NULL) {
//     temporary = S21_NULL;
//   } else {
//     char *resultString = (char *)malloc(sizeof(char) * (s21_strlen(src) +
//     1)); strcpy(resultString, src);  //ИЗМЕНИТЬ! if (trim_chars != S21_NULL)
//     {
//       size_t j = 0;
//       for (; j < s21_strlen(trim_chars) && trim_chars[j] != '\0'; j++) {
//         for (; trim_chars[j] != '\0' && s21_strlen(resultString) >= 1; j++) {
//           while (trim_chars[j] == resultString[0]) {
//             s21_memmove(&resultString[0], &resultString[1],
//                         s21_strlen(resultString) - 1);
//             resultString[s21_strlen(resultString) - 1] = '\0';
//             j = 0;  //если нашли совпадение и удалили
//           }
//         }
//         if (s21_strlen(resultString) > 1) {
//           j = 0;
//         }
//         for (; trim_chars[j] != '\0' && s21_strlen(resultString) >= 1; j++) {
//           while (trim_chars[j] == resultString[s21_strlen(resultString) - 1])
//           {
//             resultString[s21_strlen(resultString) - 1] = '\0';
//             j = 0;  //если нашли совпадение и удалили
//           }
//         }
//       }
//     }
//     temporary = resultString;
//   }
//   return temporary;  // free
// }

void *s21_trim(const char *src, const char *trim_chars) {
  char *st_res = S21_NULL;
  if (src != S21_NULL) {
    st_res = calloc((s21_strlen(src) + 2), sizeof(char));
    char *res = st_res;
    int flag = 1;
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_trim;
    if (trim_chars != S21_NULL) {
      len_trim = s21_strlen(trim_chars);
    } else {
      len_trim = 0;
    }
    for (s21_size_t i = 0; i < len_src; i++) {
      for (s21_size_t j = 0; j < len_trim && flag; j++) {
        if (src[i] == trim_chars[j]) {
          flag = 0;
        }
      }
      if (flag == 1) {
        for (; i < len_src; i++) {
          *res++ = src[i];
        }
      } else {
        flag = 1;
      }
    }
    flag = 1;
    if (!*st_res) {
      return st_res;
    }
    for (s21_size_t i = len_src - 1; (int)i >= 0; i--) {
      for (s21_size_t j = 0; j < len_trim && flag; j++) {
        if (src[i] == trim_chars[j]) {
          flag = 0;
          *--res = '\0';
        }
      }
      if (flag == 1) {
        for (; (int)i >= 0; i--)
          ;
      } else {
        flag = 1;
      }
    }
  }
  return st_res;
}

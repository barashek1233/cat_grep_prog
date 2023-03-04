#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  int i = 0, flagWass21_NULL = 0;
  static char *last;
  char *pointer = S21_NULL;
  if (str == S21_NULL) flagWass21_NULL = 1;
  if (str != S21_NULL && last != S21_NULL) last = S21_NULL;
  if (!(str == S21_NULL && last == S21_NULL)) {
    if (str == S21_NULL && last != S21_NULL) {
      str = last;
    }
    int skipsDone = 0;
    while (!skipsDone && str[i] != '\0') {
      int j = 0, skipFlag = 0;
      while (delim[j] != '\0') {
        if (str[i] == delim[j]) {
          skipFlag = 1;
          break;
        }
        j++;
      }
      if (skipFlag) {
        i++;
      } else {
        skipsDone = 1;
      }
    }
    if (str[i] != '\0') pointer = &str[i];
    while (str[i] != '\0') {
      int j = 0, stopFlag = 0;
      while (delim[j] != '\0') {
        if (str[i] == delim[j]) {
          str[i] = '\0';
          last = &str[i + 1];
          stopFlag = 1;
          break;
        }
        j++;
      }
      if (stopFlag) break;
      i++;
      if (!stopFlag && str[i] == '\0') {
        last = S21_NULL;
      }
    }
  }
  if (last != S21_NULL && !flagWass21_NULL) {
    if (*last == '\0') last = S21_NULL;
  }
  if (pointer == S21_NULL) last = S21_NULL;
  return pointer;
}

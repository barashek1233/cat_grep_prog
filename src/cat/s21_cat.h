#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  int b;  //  нумерует только непустые строки
  int e;  //  отображает символы конца строки как $ + V
  int n;  //  нумерует все выходные строки (проверитьработу с флагом b)
  int s;  //  сжимает несколько смежных непустых строк
  int t;  //  отображает табы как ^| + v
  int v;  //  не док конца понятно как работает
} flags;

void readFile(int argc, char **argv, flags myFlags);
int parsing(int argc, char **argv, flags *myFlags);

#endif  // SRC_CAT_S21_CAT_H_

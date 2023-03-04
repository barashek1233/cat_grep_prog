#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    int checkFail;
    flags myFlags = {0};
    checkFail = parsing(argc, argv, &myFlags);
    if (checkFail > -1) {
      readFile(argc, argv, myFlags);
    }
  } else {
    printf("argc < 1");
  }
}

void readFile(int argc, char **argv, flags myFlags) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      FILE *mf = fopen(argv[i], "rt");
      if (mf != NULL) {
        int counter = 1, newLine = 1, secondNewLine = 2;
        char ch;
        ch = fgetc(mf);
        while (ch != EOF) {
          if (myFlags.s && ch == '\n' && newLine == 1) {
            secondNewLine = secondNewLine - 1;
          } else {
            secondNewLine = 2;
          }
          if (myFlags.n && newLine == 1 && myFlags.b != 1 &&
              secondNewLine > 0) {
            printf("%6d\t", counter);
            counter++;
          }
          if (myFlags.b && newLine == 1 && ch != '\n' && secondNewLine > 0) {
            printf("%6d\t", counter);
            counter++;
          }
          if (myFlags.e && ch == '\n' && secondNewLine > 0) printf("$");
          if (myFlags.v && 32 > (int)ch && (int)ch != 9 && (int)ch != 10) {
            ch = ch + 64;
            printf("^");
          } else if (myFlags.v && (int)ch == 127) {
            ch = '?';
            printf("^");
          }
          if (myFlags.t == 1 && ch == '\t') {
            ch = 'I';
            printf("^");
          }
          if (ch == '\n') {
            newLine = 1;
          } else {
            newLine = 0;
          }
          if (secondNewLine > 0) printf("%c", ch);
          ch = fgetc(mf);
        }
      }
      fclose(mf);
    }
  }
}

int parsing(int argc, char **argv, flags *myFlags) {
  int error = 0;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      if (!strcmp("--number-nonblank", argv[i])) {
        myFlags->b = 1;
        error = 1;
      } else if (!strcmp("--number", argv[i])) {
        myFlags->n = 1;
        error = 1;
      } else if (!strcmp("--squeeze-blank", argv[i])) {
        myFlags->s = 1;
        error = 1;
      }
    } else if (argv[i][0] == '-' && argv[i][1] != '-' && error != -1) {
      int lenStr = strlen(argv[i]);
      for (int sim = 1; sim < lenStr; sim++) {
        if (argv[i][sim] == 'b') {
          myFlags->b = 1;
          error = 1;
        } else if (argv[i][sim] == 'e') {
          myFlags->e = 1;
          myFlags->v = 1;
          error = 1;
        } else if (argv[i][sim] == 'n') {
          myFlags->n = 1;
          error = 1;
        } else if (argv[i][sim] == 's') {
          myFlags->s = 1;
          error = 1;
        } else if (argv[i][sim] == 't') {
          myFlags->t = 1;
          myFlags->v = 1;
          error = 1;
        } else if (argv[i][sim] == 'v') {
          myFlags->v = 1;
          error = 1;
        } else if (argv[i][sim] == 'E') {
          myFlags->e = 1;
        } else if (argv[i][sim] == 'T') {
          myFlags->t = 1;
        } else {
          error = -1;
        }
      }
    }
  }
  return error;
}

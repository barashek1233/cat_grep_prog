#include "s21_grep.h"

int main(int argc, char **argv) {
  flags res = parserStr(argc, argv);
  readFile(&res);

  return 0;
}

void openFileWithPtrn(flags *res, int *countPatterns, char *fileName) {
  char pattern[N_LENGTH];
  int count = *countPatterns;
  if (strlen(fileName)) {
    FILE *f;

    f = fopen(fileName, "r");
    if (f == NULL) {
      if (!res->s) perror("grep");
    } else {
      while (!feof(f)) {
        fscanf(f, "%s", pattern);
        strcpy(res->pattern[count++], pattern);
      }
      fclose(f);
    }
  }
  *countPatterns = count;
}

flags parserStr(int argc, char **argv) {
  flags result = {0};
  const char *shortOptions = "e:ivclnhsf:o";
  int rez;
  int countPatterns = 0;
  int count = 0;

  while ((rez = getopt(argc, argv, shortOptions)) != -1) {
    switch (rez) {
      case 'e':
        result.e = 1;
        strcpy(result.pattern[countPatterns++], optarg);
        break;
      case 'i':
        result.i = 1;
        break;
      case 'v':
        result.v = 1;
        break;
      case 'c':
        result.c = 1;
        break;
      case 'l':
        result.l = 1;
        break;
      case 'n':
        result.n = 1;
        break;
      case 'h':
        result.h = 1;
        break;
      case 's':
        result.s = 1;
        break;
      case 'f':
        result.f = 1;
        openFileWithPtrn(&result, &countPatterns, optarg);
        break;
      case 'o':
        result.o = 1;
        break;
    }
  }
  while (optind < argc) {
    if (!result.e && !countPatterns) {
      strcpy(result.pattern[countPatterns++], argv[optind++]);
    } else {
      strcpy(result.nameFile[count++], argv[optind++]);
    }
  }

  return result;
}

void readFile(flags *res) {
  int matches[N_LENGTH];
  if (strlen(res->nameFile[0])) {
    FILE *mf;
    int i = 0;
    while (strlen(res->nameFile[i])) {
      char *fileName = res->nameFile[i++];
      mf = fopen(fileName, "r");
      if (mf == NULL) {
        if (!res->s) perror("grep");
      } else {
        output(mf, matches, res);
        printMatches(mf, matches, res, fileName);
        fclose(mf);
      }
      memset(matches, 0, sizeof(int) * N_LENGTH);
    }
  }
}

int find(char *str, char *pattern, int i) {
  regex_t reg;
  int er;
  int ret = 0;

  if (i) {
    er = regcomp(&reg, pattern, REG_ICASE);
  } else {
    er = regcomp(&reg, pattern, REG_EXTENDED);
  }

  if (!er) {
    er = regexec(&reg, str, 0, NULL, 0);

    if (!er) {
      ret = 1;
    }
  } else {
    char buffer[100];
    regerror(er, &reg, buffer, 100);
    printf("regcomp() failed with '%s'\n", buffer);
  }
  regfree(&reg);
  return ret;
}

void output(FILE *fp, int matches[N_LENGTH], flags *res) {
  char str[S_LENGTH];
  int count = 0;
  int countStr = 1;
  int match = 0;

  while (fgets(str, S_LENGTH, fp)) {
    int i = 0;
    while (strlen(res->pattern[i])) {
      if (res->v) {
        if (find(str, res->pattern[i++], res->i)) {
          if (match) matches[--count] = 0;
          break;
        } else {
          if (!match) matches[count++] = countStr;
          match = 1;
        }
      } else {
        if (find(str, res->pattern[i++], res->i)) {
          if (match) matches[--count] = 0;
          matches[count++] = countStr;
          match = 1;
        }
      }
    }
    match = 0;
    countStr++;
  }
  matches[count++] = 0;
}

void printNumOfStr(int n, int countStr) {
  if (n) {
    printf("%d:", countStr);
  }
}

void printFileName(char *file_1, char *fileName, int h) {
  if (strlen(file_1) && !h) {
    printf("%s:", fileName);
  }
}

void findO(char *str, char *pattern, int i) {
  regmatch_t matches[2];
  regex_t reg;
  int start;
  int end;
  int er;

  if (i) {
    er = regcomp(&reg, pattern, REG_ICASE);
  } else {
    er = regcomp(&reg, pattern, REG_EXTENDED);
  }

  while (1) {
    er = regexec(&reg, str, 2, matches, 0);

    if (er) break;

    start = matches->rm_so;
    end = matches->rm_eo;

    printf("%.*s\n", (end - start), (str + start));
    str = str + end;
  }

  regfree(&reg);
}

void printMatches(FILE *fp, int matches[N_LENGTH], flags *res,
                   char *fileName) {
  fseek(fp, 0, SEEK_SET);

  char str[S_LENGTH];
  int countStr = 1;

  if (res->c || res->v) res->o = 0;

  if (res->c) {
    int i = 0;
    if (res->l && matches[0]) {
      i++;
      printFileName(res->nameFile[1], fileName, res->h);
      printf("%d\n", i);
    } else {
      while (matches[i]) i++;
      printFileName(res->nameFile[1], fileName, res->h);
      printf("%d\n", i);
    }
  } else if (!res->l) {
    int i = 0;
    while (!feof(fp) && matches[i]) {
      fgets(str, S_LENGTH, fp);
      if (countStr == matches[i]) {
        printFileName(res->nameFile[1], fileName, res->h);
        printNumOfStr(res->n, countStr);

        if (res->o) {
          int j = 0;
          while (strlen(res->pattern[j])) {
            findO(str, res->pattern[j++], res->i);
            if ((strcmp(res->pattern[i], res->pattern[i + 1]) < 0) &&
                (strlen(res->pattern[i + 1]))) {
              break;
            }
          }
        } else {
          feof(fp) ? printf("%s\n", str) : printf("%s", str);
        }

        i++;
      }
      countStr++;
    }
  }
  if (res->l && matches[0]) printf("%s\n", fileName);
}
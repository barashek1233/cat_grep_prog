#ifndef SRC_S21_GREP_H
#define SRC_S21_GREP_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NMAX 10
#define N_LENGTH 100
#define S_LENGTH 4096

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  char pattern[NMAX][N_LENGTH];
  char nameFile[NMAX][N_LENGTH];
} flags;

void openFileWithPtrn(flags *res, int *countPatterns, char *fileName);
flags parserStr(int argc, char **argv);
void readFile(flags *res);
int find(char *str, char *pattern, int i);
void output(FILE *fp, int matches[N_LENGTH], flags *res);
void printFileName(char *file_1, char *fileName, int h);
void findO(char *str, char *pattern, int i);
void printNumOfStr(int n, int countStr);
void printMatches(FILE *fp, int matches[N_LENGTH], flags *res, char *fileName);

#endif
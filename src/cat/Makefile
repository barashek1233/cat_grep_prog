CFLAGS=gcc -Werror -Wextra -Wall

all: build

build: s21_cat

s21_cat:
	$(CFLAGS) -c s21_cat.c
	$(CFLAGS) s21_cat.o -o s21_cat

check:
	clang-format -style=Google -n *.c

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat
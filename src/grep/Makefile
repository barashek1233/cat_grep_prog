CFLAGS=gcc -Werror -Wextra -Wall

all: build

build: s21_grep

s21_grep:
	$(CFLAGS) -c s21_grep.c
	$(CFLAGS) s21_grep.o -o s21_grep

test:
	sh my_test_grep.sh

style: 
	cp ../../materials/linters/.clang-format ./
	echo =COPY DONE!=
	clang-format -n *.c *.h
	echo =CHECK COMPLETED=
	rm -rf .clang-format
	echo =REMOVE DONE!=

style-fix: 
	cp ../../materials/linters/.clang-format ./
	echo =COPY DONE!=
	clang-format -i *.c *.h
	echo =CHECK COMPLETED=
	rm -rf .clang-format
	echo =REMOVE DONE!=

clean:
	rm -rf s21_grep.log
	rm -rf test_history.txt
	rm -rf log2.txt
	rm -rf grep_err.txt
	rm -rf grep_res.txt
	rm -rf my_err.txt
	rm -rf my_res.txt
	rm -rf *.o
	rm -rf  s21_grep
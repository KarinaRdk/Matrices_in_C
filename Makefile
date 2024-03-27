CC= gcc 
CFLAG= -Wall -Werror -Wextra  -std=c11 -g
CHECKFLAG= -lcheck

ifeq ($(shell uname),Linux)
		CHECKFLAG += -lsubunit -lrt -lm -lpthread
endif

all: s21_matrix.a


rebuild: clean s21_matrix.a

s21_matrix.o: s21_matrix.c
	$(CC) $(CFLAG) $(COVER) -c $^ -o $@

s21_matrix.a: s21_matrix.o
	ar rcs $@ $^
	rm -rf $^

test_build: s21_matrix.a
	$(CC) $(CFLAG) $(COVER) s21_test.c $^ $(CHECKFLAG) -o s21_test

test: test_build
	./s21_test || true


test_gcov: coverlib covertest

coverlib: COVER= -fprofile-arcs -ftest-coverage
coverlib: rebuild
covertest: COVER= -fprofile-arcs
covertest: test

gcov_report: test_gcov
	lcov -c -d ./ -o s21_test.info
	genhtml -o ./report s21_test.info
	open ./report/index.html

paola: rebuild
	$(CC) -Wall -g paola.c s21_matrix.a -o $@
	./$@
	rm -rf paola

clean:
	rm -rf *.o *.a s21_test.info s21_test *.gcda *gcno report *.gcov


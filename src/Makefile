NAME = s21_matrix_oop.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
SRCS =	matrix/*.cpp
TEST_SRCS =	tests/tests.cpp
TEST_FLAGS = -lgtest --coverage
TEST_FLAGS = #-lcheck -lm -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs
UNAME_S = $(shell uname -s)

ifeq ($(UNAME_S), Linux)

endif

all: $(NAME) test gcov_report

$(NAME):
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc $(NAME) *.o
	ranlib $(NAME)
	rm *.o

test:
	make rebuild
	$(CC) $(CFLAGS) -c $(TEST_SRCS)
	$(CC) $(CFLAGS) *.o $(NAME) $(TEST_FLAGS)  -o test
	./test

gcov_report:
	$(CC) $(CFLAGS) -c $(TEST_SRCS)
	$(CC)  $(CFLAGS) $(GCOV_FLAGS) -c $(SRCS)
	$(CC)  $(CFLAGS) $(GCOV_FLAGS) *.o $(TEST_FLAGS_LINUX) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style: 
	clang-format --style=google *.c *.h tests/*.c -n

correct_style: 
	clang-format --style=google *.c *.h tests/*.c -i

clean:
	rm -rf *.o *.a test test_linux *.gcno *.gcda *.info report

rebuild : clean $(NAME)

install_gtest:
	sudo apt install googletest
	sudo apt install libgtest-dev

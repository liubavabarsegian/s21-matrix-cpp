NAME = s21_matrix_oop.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++ -lm
SRCS =	matrix/s21_matrix_oop.cpp
TEST_SRCS =	tests/tests.cpp
TEST_FLAGS = -lgtest -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs
SRCS_DIR = matrix
TESTS_DIR = tests

all: $(NAME) test gcov_report

$(NAME):
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rc $(NAME) *.o
	ranlib $(NAME)
	rm *.o

test:
	make rebuild
	g++ $(CFLAGS) -c $(TEST_SRCS)
	g++ $(CFLAGS) *.o $(NAME) $(TEST_FLAGS)  -o test
	./test

gcov_report:
	g++ $(CFLAGS) -c $(TEST_SRCS)
	g++  $(CFLAGS) $(GCOV_FLAGS) -c $(SRCS)
	g++  $(CFLAGS) $(GCOV_FLAGS) *.o $(TEST_FLAGS) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

style: 
	clang-format --style=google $(SRCS_DIR)/*.cpp $(SRCS_DIR)/*.hpp $(TESTS_DIR)/*.cpp -n

correct_style: 
	clang-format --style=google $(SRCS_DIR)/*.cpp $(SRCS_DIR)/*.hpp $(TESTS_DIR)/*.cpp -i

clean:
	rm -rf *.o *.a test test_linux *.gcno *.gcda *.info report

rebuild : clean $(NAME)

install_gtest:
	sudo apt install googletest
	sudo apt install libgtest-dev

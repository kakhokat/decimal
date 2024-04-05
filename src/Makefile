CC = gcc
CFLAGS = -Werror -Wall -Wextra -std=c11
TARGET = s21_decimal
TARGET_DIR = functions
SRCS = *.c shared/*.c 
OBJS = $(SRCS:.c=.o)
TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/*.c
TEST_OBJS = $(TEST_SRCS:.c=.o)

GCOV_FLAGS = -ftest-coverage -fprofile-arcs -fPIC	

UNAME_S 		:= $(shell uname -s)
CHECKFLAGS= -D_THREAD_SAFE -I/opt/homebrew/Cellar/check/0.15.2/include
OPEN_CMD = open
ADD_LIB = 

ifeq ($(UNAME_S),Linux)
	CHECKFLAGS= -lcheck
	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lm -lpthread -lrt -lsubunit
	OS = LINUX
endif


.PHONY: all clean test_compile test build rebuild gcov_report clang cpp_check valgrind

all: rebuild
rebuild: clean s21_decimal.a

s21_decimal.a : $(wildcard $(SRCS))
	@$(CC) $(CFLAGS) -c $+
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -rf *.o

test_compile: rebuild
	$(CC) $(CFLAGS) $(CHECKFLAGS) -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck $(TEST_DIR)/*.c $(TARGET).a -o test $(ADD_LIB)

test: test_compile
	./test
	rm -rf *.o test *.a $(TEST_DIR)/*.o *.gcda *.gcno *.info report *.out coverage

gcov_report: clean
	$(CC) $(GCOV_FLAGS) $(CHECKFLAGS) -L/opt/homebrew/Cellar/check/0.15.2/lib -lcheck $(SRCS) $(TEST_SRCS) $(ADD_LIB) -o coverage
	./coverage
	lcov -t "coverage" -o coverage.info --no-external -c -d .
	genhtml -o report coverage.info
	$(OPEN_CMD) report/index.html

clean:
	rm -rf *.o test *.a $(TEST_DIR)/*.o *.gcda *.gcno *.info report *.out coverage

clang:
	clang-format -i --style=Google $(SRCS) $(TEST_DIR)/*.[ch] 

cpp_check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRCS) $(TARGET).h shared/*.h $(TEST_DIR)/*.h $(TEST_SRCS)

valgrind: test_compile
	valgrind --tool=memcheck --leak-check=yes -s ./test

leaks: test_compile
	leaks -atExit -- ./test | grep LEAK:

CFLAGS = -Wall -Werror -Wextra -std=c11
GCOV = -fprofile-arcs -ftest-coverage
CC = gcc
LIBS = -lcheck
RM = rm -rf
SRCS = s21_3dviewer.c baseCube.c
OBJS = $(SRCS:.c=.o)
OS := $(shell uname -s)

ifeq ($(OS), Linux)
 	CFLAGS += -D OS_LINUX
 	ADD_LIB = -lcheck -lm -lrt -lpthread
 	TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm
endif

ifeq ($(OS), Darwin)
	CFLAGS += -D OS_MAC
 	ADD_LIB =
 	TEST_FLAGS =-lcheck
endif

all: 3dviewer

3dviewer: 3dviewer.a
	$(CC) test.c -lcheck -L. 3dviewer.a -o 3dviewer.out

3dviewer.a:
	$(CC) -c $(CFLAGS) $(SRCS)
	ar rcs 3dviewer.a $(OBJS)
	ranlib 3dviewer.a

test:
	gcc -I/opt/homebrew/Cellar/check/0.15.2/include -L/opt/homebrew/Cellar/check/0.15.2/lib -Wall -Wextra -Werror -std=c11 test.c 3dviewer.a -o test -lcheck
	# $(CC) test.c -lcheck -L. 3dviewer.a -o test
	./test

gcov_report:
	$(CC) test.c $(SRCS) -o ./test -lcheck -lgcov -coverage
	./test
	lcov -t "./gcov" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov


clean:
	$(RM) *.a *.o *.info *.gcno *.gcda *.gcov test report 3dviewer.out a.out a.out.clang-format

valgrind_check: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

lik: test
	CK_FORK=no leaks -atExit -- ./test

style_check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *.h 
	clang-format -n 3DViewer/*.cpp 3DViewer/*.h

style_change:
	clang-format -i *.c *.h 
	clang-format -i 3DViewer/*.cpp 3DViewer/*.h

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
	touch README.md

rebuild:
	$(MAKE) clean
	$(MAKE) all

install:
	@make clean
	@mkdir build
	@cd 3dviewer && qmake && make && make clean && rm Makefile && cd ../ && mv 3dviewer/3dviewer.app build
	@cp -R build/3dviewer.app ~/Desktop/3dviewer.app

uninstall:
	@rm -rf build*
	@echo "Uninstall completed successfully"

dvi:
	@open README.md

dist:
	@rm -rf Dist_3dviewer/
	@mkdir Dist_3dviewer/
	@mkdir Dist_3dviewer/src
	@mv ./build/3dviewer.app Dist_3dviewer/src/
	@tar cvzf Dist_3dviewer.tgz Dist_3dviewer/
	@rm -rf Dist_3dviewer/

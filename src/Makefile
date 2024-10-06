DIST_DIR = misc/dist
CC = gcc
CFLAGS = -c 	 -Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11

HEADERS=$(wildcard brick_game/tetris/*/*.h gui/cli/*.h)
UNAME_S := $(shell uname -s)
BIN = brick_game/tetris/bin
MAIN = $(wildcard brick_game/tetris/*.c)
TEST = $(wildcard tests/*.c)
BACK = $(wildcard brick_game/tetris/src/*.c )
FRONT = $(wildcard gui/cli/*.c)
GCOV_FOLDER = gcov_report


OBJ = brick_game/tetris/obj

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = firefox
	ADD_LIB =  -lm -lrt -lpthread -D_GNU_SOURCE -lncurses 
	TEST_LIB = -lcheck -lsubunit -lm
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lncurses
	TEST_LIB = -lcheck 
endif

# all, install, uninstall, clean, dvi, dist, test, gcov_report

all: clean install #dvi

install: style tetris
	mkdir $(BIN)
	$(CC) $(OBJ)/*.o -o $(BIN)/tetris -lncurses

uninstall:
	rm $(BIN)/tetris

clean: style
	clear
	rm -rf *.o $(BIN) $(TETRIS_LIB) $(OBJ) *.out *.o tests/test $(GCOV_FOLDER) report $(DIST_DIR) dist


dvi: misc/docs/doc.tex misc/docs/doc_eng.tex
	test -f misc/doc.pdf || ( latex misc/docs/doc.tex && mv doc.pdf misc/ ) 
	test -f misc/doc_eng.pdf || ( latex misc/docs/doc_eng.tex && mv doc_eng.pdf misc/)

	$(OPEN_CMD) misc/doc.pdf misc/doc_eng.pdf

dist: all
	mkdir dist
	cp -r brick_game gui Makefile misc dist/
	mv dist $(DIST_DIR)
	tar -czf tetris-1.0.tar.gz $(DIST_DIR)	
	mv tetris-1.0.tar.gz $(DIST_DIR)

test: style clean
	gcc $(LDFLAGS) -Ddebug_bro -DTEST_BRO $(BACK) $(FRONT) $(TEST) $(TEST_LIB) -o tests/test  && ./tests/test 

gcov_report: style clean
	mkdir $(GCOV_FOLDER)
	gcc --coverage $(LDFLAGS) -Ddebug_bro -DTEST_BRO  $(BACK) $(TEST) $(TEST_LIB) -o $(GCOV_FOLDER)/gcov_test
	chmod +x $(GCOV_FOLDER)/gcov_test
	$(GCOV_FOLDER)/gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	$(OPEN_CMD) ./report/index.html
	rm -rf gcov*

create_file:
	test -f highscore.txt || ( touch highscore.txt && echo 0 >> highscore.txt )

deb_tetris: create_file
	mkdir $(OBJ)
	$(CC) $(CFLAGS) -Ddebug_bro $(MAIN) $(BACK) $(FRONT) $(ADD_LIB)
	mv *.o $(OBJ)

tetris: create_file
	mkdir $(OBJ)
	$(CC) $(CFLAGS)  $(MAIN) $(BACK) $(FRONT) $(ADD_LIB)
	mv *.o $(OBJ)


debug: style deb_tetris
	mkdir $(BIN)
	$(CC) -Ddebug_bro $(OBJ)/*.o -o $(BIN)/tetris 
	

run: 
	$(BIN)/tetris 

sanitize:
	gcc  $(BACK) $(FRONT) -g -fsanitize=address -o $(BIN)/tetris $(ADD_LIB) && $(BIN)/tetris 



rebuild: clean all
redebug: clean debug

style_test:
	clang-format --style=Google -n $(MAIN) $(BACK) $(FRONT) $(TEST) $(HEADERS)
style:
	@ clang-format --style=Google -i $(MAIN) $(BACK) $(FRONT) $(TEST) $(HEADERS)

valg: rebuild
	valgrind --tool=memcheck --leak-check=yes  ./$(BIN)/tetris	

valg_f: rebuild
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --suppressions=ncurses_supp.supp ./$(BIN)/tetris	

stvalg: redebug
	valgrind --tool=memcheck --leak-check=yes ./$(BIN)/tetris


# Собираем docker image с тегом 'v1' на основании dockerfile и создаем контейнер
docker_build:
	docker build -t vault:v1 .
	docker create -it --name tetris vault:v1

# Запускаем контейнер
docker_start:
	docker start -i tetris

docker_delete:
	docker rm tetris
	docker image rm vault:v1


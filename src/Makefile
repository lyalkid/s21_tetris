CC = gcc
CFLAGS = -c #	 -Wall -Werror -Wextra -std=c11
LDFLAGS = #-Wall -Werror -Wextra -std=c11

HEADERS=$(wildcard brick_game/tetris/*/*.h gui/cli/*.h)
UNAME_S := $(shell uname -s)
BIN = brick_game/tetris/bin
MAIN = $(wildcard brick_game/tetris/*.c)
BACK = $(wildcard brick_game/tetris/src/*.c )
FRONT = $(wildcard gui/cli/*.c)
OBJ = brick_game/tetris/obj

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB =  -lm -lrt -lpthread -D_GNU_SOURCE -lncurses #-lcheck -lsubunit
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lncurses
endif

all: intstall

intstall: style tetris
	mkdir $(BIN)
	$(CC) $(OBJ)/*.o -o $(BIN)/tetris -lncurses


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


clean:
	clear
	rm -rf *.o $(BIN) $(TETRIS_LIB) $(OBJ) *.out *.o


rebuild: clean all
redebug: clean debug

style_test:
	clang-format --style=Google -n $(MAIN) $(BACK) $(FRONT)  $(HEADERS)
style:
	clang-format --style=Google -i $(MAIN) $(BACK) $(FRONT)  $(HEADERS)

valg: rebuild
	valgrind --tool=memcheck --leak-check=yes ./$(BIN)/tetris	


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


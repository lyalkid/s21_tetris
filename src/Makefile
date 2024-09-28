CC = gcc
CFLAGS = -c  -Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11

HEADERS=$(wildcard brick_game/tetris/inc/*.h gui/cli/*.h)
UNAME_S := $(shell uname -s)
BIN = brick_game/tetris/bin
BACK = $(wildcard brick_game/tetris/*.c brick_game/tetris/src/*.c)
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

tetris:
	mkdir $(OBJ)
	$(CC) $(CFLAGS)  $(BACK) $(FRONT) $(ADD_LIB)
	mv *.o $(OBJ)

run: clean intstall
	$(BIN)/tetris 

sanitize:
	gcc  $(BACK) $(FRONT) -g -fsanitize=address -o $(BIN)/tetris $(ADD_LIB) && $(BIN)/tetris 


clean:
	clear
	rm -rf *.o $(BIN) $(TETRIS_LIB) $(OBJ) *.out *.o


rebuild: clean all

style_test:
	clang-format --style=Google -n $(BACK) $(FRONT) $(HEADERS)
style:
	clang-format --style=Google -i $(BACK) $(FRONT) $(HEADERS)

valgrind:
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


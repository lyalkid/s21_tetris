TETRIS_LIB = brick_game/tetris/lib/tetris.a
CC = gcc
CFLAGS = -c  #-Wall -Werror -Wextra -std=c11
LDFLAGS = #-Wall -Werror -Wextra -std=c11
SOURCE=$(wildcard brick_game/tetris/*.c brick_game/tetris/src/*.c gui/cli/*.c)
HEADERS=$(wildcard brick_game/tetris/inc/*.h gui/cli/*.h)
UNAME_S := $(shell uname -s)
BIN = brick_game/tetris/bin


ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB =  -lm -lrt -lpthread -D_GNU_SOURCE -lncurses #-lcheck -lsubunit
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = -lncurses
endif

all: s21_tetris.a

run: style s21_tetris.a
	gcc  $(TETRIS_LIB) -o $(BIN)/tetris $(ADD_LIB) && $(BIN)/tetris 

sanitize:
	gcc  $(SOURCE) -g -fsanitize=address -o $(BIN)/tetris $(ADD_LIB) && $(BIN)/tetris 

s21_tetris.a: $(SOURCE)
	$(CC) $(CFLAGS)  $(SOURCE) $(ADD_LIB)
	ar rc $(TETRIS_LIB) *.o 
	ranlib $(TETRIS_LIB)
	-rm -rf *.o


clean:
	clear
	rm -rf *.o $(BIN)/tetris $(TETRIS_LIB) *.out


rebuild: clean run

style_test:
	clang-format --style=Google -n $(SOURCE) $(HEADERS)
style:
	clang-format --style=Google -i $(SOURCE) $(HEADERS)

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


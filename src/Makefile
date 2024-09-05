TETRIS_LIB = tetris.a
CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11
LDFLAGS = -Wall -Werror -Wextra -std=c11
SOURCE=$(wildcard tetris_src/*.c)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB =
endif



all: s21_tetris.a

run: s21_tetris.a
	gcc tetris_bro.c $(TETRIS_LIB) -o tetris && ./tetris 

s21_tetris.a: ${SOURCE}
	$(CC) $(CFLAGS) $(ADD_LIB) $(SOURCE)
	ar rc $(TETRIS_LIB) *.o
	ranlib $(TETRIS_LIB)
	-rm -rf *.o


clean:
	rm -rf *.o tetris *.a *.out


style_test:
	clang-format --style=Google -n *.c */*.h */*.c
style:
	clang-format --style=Google -i *.c */*.h */*.c

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


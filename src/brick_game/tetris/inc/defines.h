#ifndef BRICK_GAME_DEFINES_H_
#define BRICK_GAME_DEFINES_H_

enum status { ERROR, OK_BRO };

enum figures { T = 1, J, L, I, S, Z, O };
enum degrees { COMPLETE, RIGHT, STRAIGHT, REFLEX };
#define NONE_ACTION 8

#define MY_ROWS 20
#define MY_COLS 10

#define scale_field 2
#define scale 2
#define FIELD_Y MY_ROWS + 2
#define FIELD_X MY_COLS* scale_field + 2

#define NEXT_FIELD 10
#define INFO_FIELD 10

#define INFO_X INFO_FIELD* scale + 2
#define INFO_Y INFO_FIELD + 2

#define NEXT_X NEXT_FIELD* scale + 2
#define NEXT_Y NEXT_FIELD

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#define TIME 2000000

#define TETR_L "###\n  #"d

#define ESCAPE 27
#define ENTER_KEY 10
#define SPACE 32

#endif
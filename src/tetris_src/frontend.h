#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 20
#define COLS 10

enum figures { T, J, L, I, S, Z, O };
enum degrees { COMPLETE, RIGHT, STRAIGHT, REFLEX };

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int coordinates[8];
  int type;
  int rotate;

  int center_x;
  int center_y;
} TetraMino_bro;

typedef struct {
  int coordinates[200];
  int moves[100];  // смещения фигуры до того, пока она встанет
  int figura;  // значение из enum figures
  int rotate;  // всего положений 4
} Current_figure;

typedef struct {
  int **field;
  int **next;
  TetraMino_bro tetraMinoBro;
  //    int top;   // текущая верхняя позиция
  //    int size;  //  текущий размер поля
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void render(GameInfo_t board);

int get_random();
int get_highScore();
void start_initialization(GameInfo_t *gameInfo, int type);
void get_next(GameInfo_t *gameInfo, int type);
void move_tetramino(GameInfo_t *gameInfo, char key);
void tetramino_into_next(GameInfo_t *gameInfo, TetraMino_bro tetraminoBro);
void get_TetraMino(TetraMino_bro *tetraMinoBro);
void rotate_90_degrees(GameInfo_t *gameInfo);
void rotate_Tetramino(GameInfo_t *gameInfo);

void get_tetra_two(TetraMino_bro *tetraminoBro);
void get_tetra_four(TetraMino_bro *tetraMinoBro);

// void copy_tetramino(TetraMino_bro *src, TetraMino_bro *dst);
void setCoordinates(int *coordinates, const int *values);
void tetra_to_next(TetraMino_bro tetraMinoBro, int **next);
int get_min(int a, int b);

int get_max(int a, int b);
int is_rotate_possible(TetraMino_bro tetraMinoBro, int rotate);
#endif  // FRONTEND_H
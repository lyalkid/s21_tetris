#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 20
#define COLS 10

enum figures { Z, REVERSE_Z, L, REVERSE_L, SQUARE, T, I };

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

typedef struct{
  int coordinates[200];
  int moves[100]; // смещения фигуры до того, пока она встанет
  int figura; // значение из enum figures
  int rotate; // всего положений 4
}Current_figure;


typedef struct {
  int **field;
  int **next;
  Current_figure figura;
  int top;   // текущая верхняя позиция
  int size;  //  текущий размер поля
  int score;
  int high_score;
  int level;
  int speed;
  int pause;

} GameInfo_t;

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void render(GameInfo_t board);
void initBoard(GameInfo_t *board);
int get_random();
int get_highScore();
void get_next(GameInfo_t *gameInfo, int type);
void get_start(GameInfo_t *gameInfo, int type);
#endif  // FRONTEND_H
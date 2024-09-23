#ifndef OBJECTS_H_
#define OBJECTS_H_
#include <stdbool.h>
#include <string.h>

enum status { ERROR, OK_BRO };

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
  Action,
  NONE_ACTION
} UserAction_t;

typedef enum {
  MAIN_MENU,  // getch
  START,      // getch
  SPAWN,
  MOVE,  // getch
  SHIFT,
  ATTACHING,
  CHECK_DESTROY,
  CHECK_GAME_OVER,
  DESTROY,
  PAUSE,      // getch
  GAME_OVER,  // getch
  EXIT_BRO
} State_t;

typedef struct {
  int type;
  int rotate;
  int center_x;
  int center_y;
  int coordinates[8];
} TetraMino_bro;

typedef struct {
  // TODO убрать эту фигуру из этой структуры
  // TetraMino_bro tetraMinoBro;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int **field;
  int **next;
} GameInfo_t;

// TODO сделать так чтобы после каждой игровой сессии данные сохранялись в csv
// или в txt файл
// TODO сделать реализацию с этой структурой, чтобы можно было участвовать в
// рейтинге
// typedef struct {
//  int high_score;
//  char *unique_name;
//} UserInfo_t;

typedef struct {
  struct timeval before;
  struct timeval after;
  suseconds_t timer;
  bool game_is_running;
  bool time_to_shift;
  State_t state;
  UserAction_t userAction;
  TetraMino_bro tetraMinoBro;
  GameInfo_t gameInfo;

} Game_Objects_t;

#endif  // OBJECTS_H_
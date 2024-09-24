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
  int next_type;
  int rotate;
  int center_x;
  int center_y;
  int coordinates[8];
} TetraMino_bro;

typedef struct {
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int **field;
  int **next;
} GameInfo_t;


typedef struct {
  struct timeval before;
  struct timeval after;
  suseconds_t timer; // через какое время делать shift
  bool game_is_running; // флаг для game_loop()
  bool time_to_shift; // показывает нужно ли делать shift
  State_t state;
  UserAction_t userAction;
  TetraMino_bro tetraMinoBro;
  GameInfo_t gameInfo;

} Game_Objects_t;

#endif  // OBJECTS_H_
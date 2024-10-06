#ifndef OBJECTS_H_
#define OBJECTS_H_
#include <stdbool.h>
#include <string.h>

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,

} UserAction_t;

typedef enum {
  MAIN_MENU,  // getch
  START,      // getch
  SPAWN,
  MOVE,  // getch
  SHIFT,
  ATTACHING,
  PAUSE,      // getch
  GAME_OVER,  // getch
  EXIT_BRO,
  STATIC
} State;

typedef struct {
  int count[7];
  int pieses[7];
} Bag;

typedef struct {
  int type;
  int next_type;
  int rotate;
  int center_x;
  int center_y;
  int coordinates[8];
  Bag meshok;
  int** tmp_current_figure_on_field;
} TetraMino_bro;

typedef struct {
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int** field;
  int** next;
} GameInfo_t;

typedef struct {
  struct timeval before;
  struct timeval after;
  suseconds_t delay_to_shift;  // через какое время делать shift
  bool time_to_shift;  // показывает нужно ли делать shift
} Shift_timer;

typedef struct {
  int yMax;
  int xMax;
#ifndef debug_bro
  WINDOW* game_win;
  WINDOW* info_win;
  WINDOW* next_win;
#endif
} View_bro;

typedef struct {
  Shift_timer timer;
  bool game_is_running;  // флаг для game_loop()
  // bool was_move;
  State state;
  UserAction_t userAction;
  TetraMino_bro tetraMinoBro;
  GameInfo_t gameInfo;

#ifndef debug_bro
  View_bro views;
#endif
} Game_Objects_t;

#endif  // OBJECTS_H_
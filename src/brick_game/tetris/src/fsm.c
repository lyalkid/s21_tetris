#include "../inc/fsm.h"

#include "../../../gui/cli/frontend.h"
#include "../inc/backend.h"
/*typedef enum {
  MAIN_MENU,  // getch
  START,      // getch
  SPAWN,
  MOVE,  // getch
  SHIFT,
  ATTACHING,
  CHECK_DESTROY,
  CHECK_GAME_OVER,
  PAUSE,      // getch
  GAME_OVER,  // getch
  EXIT_BRO
} State_t;
 * */

void main_fsm(Game_Objects_t* game_params) {
  switch (game_params->state) {
    case MAIN_MENU:
      main_menu(game_params);
      break;
    case START:
      onStart_state(game_params);
      break;
    case SPAWN:
      onSpawn(game_params);
      break;
    case MOVE:
      onMoving(game_params);
      break;
    case SHIFT:
      onShifting(game_params);
      break;
    case ATTACHING:
      onAttaching(game_params);
      break;
    case CHECK_DESTROY:
      onCheck_destroy(game_params);
      break;
    case DESTROY:
      onDestroy_state(game_params);
      break;
    case CHECK_GAME_OVER:
      onCheck_game_over(game_params);
      break;
    case GAME_OVER:
      onGame_over(game_params);
      break;
    case PAUSE:
      onPause_state(game_params);
      break;
    case EXIT_BRO:
      onExit_state(game_params);
      break;
    default:
      onStart_state(game_params);
      break;
  }
}

void main_menu(Game_Objects_t* params) {
  // print_main_menu(params);
  //  char key = getch();
  char key = getchar();
  switch (key) {
    case 'n':
      //        *params = (Game_Objects_t)init_empty_game_objects();
      params->state = START;
      break;
    case 'q':
      params->state = EXIT_BRO;
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
  }
}

void onStart_state(Game_Objects_t* params) {
  switch (params->state) {
    case START:
      params->state = SPAWN;
      break;
    default:
      params->state = START;
      break;
  }
}

void onSpawn(Game_Objects_t* params) {
  switch (params->state) {
    case SPAWN:
      params->state = MOVE;
      break;
    default:
      break;
  }
}
void onMoving(Game_Objects_t* params) {
  switch (params->state) {}
}
void onShifting(Game_Objects_t* params) {
  switch (params->state) {}
}
void onAttaching(Game_Objects_t* params) {
  switch (params->state) {}
}

void onGame_over(Game_Objects_t* params) {
  switch (params->state) {}
}

void onExit_state(Game_Objects_t* params) {
  switch (params->state) {}
}
void onCheck_destroy(Game_Objects_t* params) {
  switch (params->state) {}
}
void onDestroy_state(Game_Objects_t* params) {
  switch (params->state) {}
}
void onCheck_game_over(Game_Objects_t* params) {
  switch (params->state) {}
}
void onPause_state(Game_Objects_t* params) {
  switch (params->state) {}
}

// void userInput(UserAction_t action, bool hold) {}

GameInfo_t updateCurrentState();
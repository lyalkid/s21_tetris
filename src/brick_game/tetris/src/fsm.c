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
  int key = getch();
  UserAction_t signal = getSignal(key);
  //  char key = getchar();
  switch (signal) {
    case Start:
      params->userAction = Start;
      //        *params = (Game_Objects_t)init_empty_game_objects();
      params->state = START;
      break;
    case Terminate:
      if (params->state == MAIN_MENU) params->state = EXIT_BRO;

      //      exit(EXIT_SUCCESS);
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
      params->tetraMinoBro = get_new_tetraMino(get_random());
      params->state = MOVE;
      break;
    default:
      break;
  }
}
void onMoving(Game_Objects_t* params) {
  char key = getch();
  if (params->state == MOVE &&
      can_i_move(params->tetraMinoBro, params->gameInfo.field, key) == OK_BRO) {
    move_tetramino(&params->tetraMinoBro, params->gameInfo.next, key);
  }
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

UserAction_t getSignal(int user_input) {
  UserAction_t sig = -1;
  if (user_input == KEY_UP || user_input == 119) {
    sig = Action;
  } else if (user_input == KEY_DOWN || user_input == 115) {
    sig = Down;
  } else if (user_input == KEY_LEFT || user_input == 97) {
    sig = Left;
  } else if (user_input == KEY_RIGHT || user_input == 100) {
    sig = Right;
  } else if (user_input == ESCAPE || user_input == 'q') {
    sig = Terminate;
  } else if (user_input == ENTER_KEY || user_input == 'n') {
    sig = Start;
  } else if (user_input == SPACE) {
    sig = Pause;
  }
  return sig;
}

// void userInput(UserAction_t action) {
//
// }

GameInfo_t updateCurrentState() {
  Game_Objects_t* current_params = get_game_instance();
  return current_params->gameInfo;
};
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
      // main_fsm(game_params); !!! нельзя делать здесь, так как будет
      // бесконечный цикл
      break;
    case START:
      onStart_state(game_params);
      main_fsm(game_params);
      break;
    case SPAWN:
      onSpawn(game_params);
      main_fsm(game_params);
      break;
    case MOVE:
      onMoving(game_params);
      if (game_params->time_to_shift == true) {
        game_params->state = SHIFT;
        game_params->userAction = Down;
        main_fsm(game_params);
      } else if (game_params->state == ATTACHING) {
        main_fsm(game_params);
      }
      break;
    case SHIFT:
      // if (game_params->time_to_shift == true) game_params->state = MOVE;
      onShifting(game_params);

      main_fsm(game_params);
      break;
    case ATTACHING:
      onAttaching(game_params);
      main_fsm(game_params);
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
  switch (params->userAction) {
    case Start:
      params->state = START;

      break;
    case Terminate:
      if (params->state == MAIN_MENU) params->state = EXIT_BRO;

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
      tetra_to_next(params->tetraMinoBro, params->gameInfo.next);
      int is_all_ok =
          is_all_ok_bro(params->gameInfo.field, params->gameInfo.next);
      if (is_all_ok == OK_BRO)
        params->state = MOVE;
      else
        params->state = GAME_OVER;
      break;
    default:
      break;
  }
}
void onMoving(Game_Objects_t* params) {
  if (params->userAction != Start && params->userAction != Pause &&
      params->userAction != Terminate)
    main_move(params);
}
void onShifting(Game_Objects_t* params) {
  if (params->time_to_shift == true) {
    main_move(params);
    gettimeofday(&params->before, NULL);
    params->time_to_shift = false;
  }
  params->state = MOVE;
}
void onAttaching(Game_Objects_t* params) {
  switch (params->state) {
    case ATTACHING:
      next_to_field(params->gameInfo.next, params->gameInfo.field);

      // TODO не забыть менять скорость
      game_mechanics(params);

      params->state = SPAWN;
      break;

    default:
      break;
  }
}

void onGame_over(Game_Objects_t* params) { render_simple(params); }

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
  UserAction_t sig = NONE_ACTION;
  if (user_input == 'f') {
    sig = Up;
  } else if (user_input == KEY_UP || user_input == 119) {
    sig = Action;
  } else if (user_input == KEY_DOWN || user_input == 115) {
    sig = Down;
  } else if (user_input == KEY_LEFT || user_input == 97) {
    sig = Left;
  } else if (user_input == KEY_RIGHT || user_input == 100) {
    sig = Right;
  } else if (user_input == ESCAPE || user_input == 'q') {
    sig = Terminate;
  } else if (user_input == ENTER_KEY || user_input == 'n' ||
             user_input == '\n') {
    sig = Start;
  } else if (user_input == SPACE) {
    sig = Pause;
  }
  return sig;
}
void main_move(Game_Objects_t* params) {
  if (params->userAction == Up) {
    params->userAction = Down;
    while (params->state != ATTACHING) {
      move_brother(params);
    }
    params->state = MOVE;
  } else {
    move_brother(params);
  }

  if (params->userAction != Start || params->userAction != Pause ||
      params->userAction != Terminate)
    params->userAction = NONE_ACTION;
}
void move_brother(Game_Objects_t* params) {
  int is_move_possible = can_i_move(params->tetraMinoBro,
                                    params->gameInfo.field, params->userAction);

  if (is_it_board(params->gameInfo.next) == ERROR ||
      (params->userAction == Down && is_move_possible == ERROR)) {
    params->state = ATTACHING;
  } else if ((params->state == MOVE || params->state == SHIFT) &&
             is_move_possible == OK_BRO) {
    move_tetramino(&params->tetraMinoBro, params->gameInfo.next,
                   params->userAction);
    tetra_to_next(params->tetraMinoBro, params->gameInfo.next);
  }
}

// void userInput(UserAction_t action) {
//
// }

GameInfo_t updateCurrentState() {
  Game_Objects_t* current_params = get_game_instance();
  return current_params->gameInfo;
};
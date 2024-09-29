#include "fsm_debug.h"

#include "../inc/backend.h"
#include "front_debug.h"

#ifdef debug_bro
void main_fsm(Game_Objects_t* params) {
  int is_all_ok = OK_BRO;
  switch (params->state) {
    case MAIN_MENU:

      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

      main_menu(params);

      // main_fsm(params, win); !!! нельзя делать здесь, так как будет
      // бесконечный цикл
      break;
    case START:
      // nodelay(stdscr, true);

      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

      onStart_state(params);
      main_fsm(params);
      break;
    case SPAWN:

      is_all_ok = onSpawn(params);

      if (is_all_ok == OK_BRO) {
        params->state = MOVE;
        draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

      } else {
        params->state = GAME_OVER;
      }
      // main_fsm(params);
      break;
    case MOVE:
      onMoving(params);
      if (params->state == MOVE)
        draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

      break;
    case SHIFT:
      if (onShifting(params) != ATTACHING) params->state = MOVE;
      break;
    case ATTACHING:
      onAttaching(params);
      break;
    case GAME_OVER:
      onGame_over(params);
      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

      if (params->userAction == Start) main_fsm(params);
      break;
    case PAUSE:
      onPause_state(params);
      break;
    case EXIT_BRO:
      onExit_state(params);
      break;
    default:
      onStart_state(params);
      break;
  }
}

void main_menu(Game_Objects_t* params) {
  switch (params->userAction) {
    case Start:
      params->state = START;
      params->gameInfo = init_empty_gameInfo();

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
      *params = init_empty_game_objects();
      params->state = SPAWN;
      break;
    default:
      params->state = START;
      break;
  }
}

int onSpawn(Game_Objects_t* params) {
  int is_all_ok = OK_BRO;
  switch (params->state) {
    case SPAWN:
      get_new_tetraMino(&params->tetraMinoBro);
      tetra_to_array(params->tetraMinoBro,
                     params->tetraMinoBro.tmp_current_figure_on_field);

      is_all_ok =
          is_all_ok_bro(params->gameInfo.field,
                        params->tetraMinoBro.tmp_current_figure_on_field);

      break;
    default:
      break;
  }
  return is_all_ok;
}
void onMoving(Game_Objects_t* params) {
  if (params->userAction == Terminate) {
    params->state = MAIN_MENU;
    reset_game(&params->gameInfo, &params->tetraMinoBro);
  } else {
    if (is_it_legal_mv(params->userAction) == OK_BRO) onMoving_legal(params);
    if (is_it_illegal_mv(params->userAction) == OK_BRO) {
      onMoving_down(params);
    }
    if (params->time_to_shift == true) {
      params->state = SHIFT;
      main_fsm(params);
    }
  }
}

void onMoving_legal(Game_Objects_t* params) {
  int is_mv_possible = can_i_move(params->tetraMinoBro, params->gameInfo.field,
                                  params->userAction);
  if ((params->userAction == Left || params->userAction == Right ||
       params->userAction == Action) &&
      is_mv_possible == OK_BRO) {
    move_tetraMino(&params->tetraMinoBro, params->userAction);
    tetra_to_array(params->tetraMinoBro,
                   params->tetraMinoBro.tmp_current_figure_on_field);
  }
  if (is_it_legal_mv(params->userAction) == OK_BRO)
    params->userAction = NONE_ACTION;
}

void onMoving_down(Game_Objects_t* params) {
  move_down_tetraMino(&params->tetraMinoBro);
  if (check_collision(params->tetraMinoBro, params->gameInfo.field) == ERROR) {
    params->state = ATTACHING;
  } else {
    tetra_to_array(params->tetraMinoBro,
                   params->tetraMinoBro.tmp_current_figure_on_field);
  };
  if (is_it_illegal_mv(params->userAction) == OK_BRO)
    params->userAction = NONE_ACTION;
}

State_t onShifting(Game_Objects_t* params) {
  if (params->time_to_shift == true) {
    params->userAction = Down;
    onMoving_down(params);
    params->time_to_shift = false;
    gettimeofday(&params->before, NULL);
  }
  return params->state;
}
void onAttaching(Game_Objects_t* params) {
  switch (params->state) {
    case ATTACHING:
      move_up_tetraMino(&params->tetraMinoBro);
      tetra_to_array(params->tetraMinoBro,
                     params->tetraMinoBro.tmp_current_figure_on_field);
      next_to_field(params->tetraMinoBro.tmp_current_figure_on_field,
                    params->gameInfo.field);

      // TODO не забыть менять скорость
      game_mechanics(params);

      params->state = SPAWN;
      break;

    default:
      break;
  }
}

void onGame_over(Game_Objects_t* params) {
  int current_score = params->gameInfo.score;
  int h_score_in_file = get_highScore();
  if (current_score > h_score_in_file) write_high_score(current_score);
  if (params->userAction == Start) {
    params->state = START;
    reset_game(&params->gameInfo, &params->tetraMinoBro);
  }
}

void onExit_state(Game_Objects_t* params) {
  params->game_is_running = false;
  deleteGame(&params->gameInfo, &params->tetraMinoBro);
}

void onPause_state(Game_Objects_t* params) {
  while (params->userAction != Start && params->userAction != Terminate) {
    params->userAction = getSignal(getchar());
  }
}
void pause_bro(Game_Objects_t* params, State_t prev) {
  params->state = PAUSE;
  draw_simple(params->state, params->gameInfo, params->tetraMinoBro);

  main_fsm(params);
  if (params->userAction != Terminate) {
    params->state = prev;
  } else {
    params->state = MAIN_MENU;
    params->userAction = NONE_ACTION;
    reset_game(&params->gameInfo, &params->tetraMinoBro);
  }
}

UserAction_t getSignal(int user_input) {
  UserAction_t sig = NONE_ACTION;
  if (user_input == 'f') {
    sig = Up;
  } else if (user_input == 119) {
    sig = Action;
  } else if (user_input == 115) {
    sig = Down;
  } else if (user_input == 97) {
    sig = Left;
  } else if (user_input == 100) {
    sig = Right;
  } else if (user_input == ESCAPE || user_input == 'q') {
    sig = Terminate;
  } else if (user_input == ENTER_KEY || user_input == 'n' ||
             user_input == '\n') {
    sig = Start;
  } else if (user_input == SPACE || user_input == 'g') {
    sig = Pause;
  }
  return sig;
}

GameInfo_t updateCurrentState() {
  Game_Objects_t* current_params = get_game_instance();
  return current_params->gameInfo;
};
#endif
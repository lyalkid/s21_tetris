#include "../inc/fsm_main.h"

#include "../../../gui/cli/frontend.h"

void main_game_fsm(Game_Objects_t* params, State* prev) {
  if (params->state == MAIN_MENU) {
    if (params->userAction == Start) {
      *prev = START;
      params->state = START;
      reset_game(&params->gameInfo, &params->tetraMinoBro);
      params->timer.time_to_shift = TIME;
    } else if (params->userAction == Terminate) {
      params->game_is_running = false;
      deleteGame(&params->gameInfo, &params->tetraMinoBro);
    }
  }

  else if (params->state == PAUSE || params->state == GAME_OVER) {
    if (params->userAction == Start) {
      params->state = START;
    } else if (params->userAction == Terminate) {
      reset_game(&params->gameInfo, &params->tetraMinoBro);
      params->state = MAIN_MENU;
      params->userAction = NONE_ACTION;
    }
  }
}

void fsm_game_session(Game_Objects_t* params) {
  int is_all_ok = OK_BRO;
  switch (params->state) {
    case START:
      onStart(params);

      break;
    case SPAWN:
      /* code */
      is_all_ok = onSpawn(params);

      is_game_over(params, is_all_ok);
      break;
    case MOVE:
      /* code */
      onMove(params);
      if (params->state != ATTACHING) params->state = SHIFT;
      params->userAction = NONE_ACTION;
      break;
    case SHIFT:
      params->userAction = Down;
      if (onShifting(params) != ATTACHING) {
        params->state = MOVE;
      }
      params->userAction = NONE_ACTION;
      break;

    case ATTACHING:
      onAttaching(params);
      break;

    default:

      break;
  }
}

void onStart(Game_Objects_t* params) {
  if (params->gameInfo.field != NULL &&
      params->tetraMinoBro.tmp_current_figure_on_field != NULL) {
    reset_game(&params->gameInfo, &params->tetraMinoBro);
  }

  params->state = SPAWN;
  params->userAction = NONE_ACTION;
}
int onSpawn(Game_Objects_t* params) {
  int is_all_ok = OK_BRO;

  get_new_tetraMino(&params->tetraMinoBro);

  tetra_to_array(params->tetraMinoBro,
                 params->tetraMinoBro.tmp_current_figure_on_field);

  is_all_ok = is_all_ok_bro(params->gameInfo.field,
                            params->tetraMinoBro.tmp_current_figure_on_field);

  return is_all_ok;
}
void is_game_over(Game_Objects_t* params, int status) {
  if (status == OK_BRO) {
    params->state = MOVE;

  } else {
    params->state = GAME_OVER;
    if (params->gameInfo.score > params->gameInfo.high_score)
      write_high_score(params->gameInfo.score);
  }
}

void onMove(Game_Objects_t* params) {
  if (is_it_movement(params->userAction) == OK_BRO) {
    onMoving(params);
  } else if (params->userAction == Down) {
    onMoving_down(params);
  } else if (params->userAction == Up) {
    onMoving_pro_down(params);
  }
  params->userAction = NONE_ACTION;
}

void onMoving(Game_Objects_t* params) {
  int is_mv_possible = can_i_move(params->tetraMinoBro, params->gameInfo.field,
                                  params->userAction);
  if ((params->userAction == Left || params->userAction == Right ||
       params->userAction == Action) &&
      is_mv_possible == OK_BRO) {
    move_tetraMino(&params->tetraMinoBro, params->userAction);
    tetra_to_array(params->tetraMinoBro,
                   params->tetraMinoBro.tmp_current_figure_on_field);
  }
  if (is_it_movement(params->userAction) == OK_BRO) {
    params->userAction = NONE_ACTION;
  }
}

void onMoving_down(Game_Objects_t* params) {
  move_down_tetraMino(&params->tetraMinoBro);
  if (check_collision(params->tetraMinoBro, params->gameInfo.field) == ERROR) {
    params->state = ATTACHING;
    params->tetraMinoBro.center_y--;
  }
  tetra_to_array(params->tetraMinoBro,
                 params->tetraMinoBro.tmp_current_figure_on_field);

  if (params->userAction == Down) {
    params->userAction = NONE_ACTION;
  }
}

void onMoving_pro_down(Game_Objects_t* params) {
  while (params->state != ATTACHING) {
    params->userAction = Down;
    onMoving_down(params);
  }

  params->userAction = NONE_ACTION;
}

State onShifting(Game_Objects_t* params) {
  if (params->timer.time_to_shift == true) {
    params->userAction = Down;
    onMove(params);
    params->timer.time_to_shift = false;
    gettimeofday(&params->timer.before, NULL);
  }
  return params->state;
}

void onAttaching(Game_Objects_t* params) {
  next_to_field(params->tetraMinoBro.tmp_current_figure_on_field,
                params->gameInfo.field);

  game_mechanics(params);

  params->state = SPAWN;
}

void userInput(UserAction_t action, bool hold) {
  Game_Objects_t* params = get_instanse();
  params->userAction = action;
  if (hold)
    hold = true;
  else
    hold = false;
}

GameInfo_t updateCurrentState() {
  // game session
  Game_Objects_t* params = get_instanse();

  return params->gameInfo;
}

Game_Objects_t* get_instanse() {
  static Game_Objects_t* data;
  if (data == NULL) {
    data = (Game_Objects_t*)(malloc(sizeof(Game_Objects_t)));
  }
  return data;
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
  } else if (user_input == ESCAPE || user_input == 'q' || user_input == 'Q') {
    sig = Terminate;
  } else if (user_input == 'n' || user_input == 'N') {
    sig = Start;
  } else if (user_input == SPACE || user_input == 'p' || user_input == 'P') {
    sig = Pause;
  }
  return sig;
}

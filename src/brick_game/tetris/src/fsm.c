#include "../inc/fsm.h"

#include "../../../gui/cli/frontend.h"
#include "../inc/backend.h"

void main_fsm(Game_Objects_t* params) {
  int is_all_ok = OK_BRO;
  // printw_state(params->state);
  switch (params->state) {
    case MAIN_MENU:
#ifndef debug_bro
      draw_main(params);
#else
      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif
      main_menu(params);

      // main_fsm(params, win); !!! нельзя делать здесь, так как будет
      // бесконечный цикл
      break;
    case START:
#ifndef debug_bro
      draw_main(params);
#else
      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif
      onStart_state(params);
      main_fsm(params);
      break;
    case SPAWN:
      // params->game_is_running = false;
      // printw_state(params->state);
      is_all_ok = onSpawn(params);
      if (is_all_ok == OK_BRO) {
        params->state = MOVE;

        main_fsm(params);
      } else {
        params->state = GAME_OVER;
        if (params->gameInfo.score > params->gameInfo.high_score)
          write_high_score(params->gameInfo.high_score);
      }

      break;
    case MOVE:
      onMoving(params);

      if (params->state == ATTACHING) {
        main_fsm(params);
      } else if (params->timer.time_to_shift == true &&
                 params->state != ATTACHING) {
        params->state = SHIFT;
        main_fsm(params);
      }

#ifndef debug_bro
      draw_main(params);
#else
      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif

      break;
    case SHIFT:
      params->userAction = Down;
      if (params->state != ATTACHING && onShifting(params) != ATTACHING) {
        params->state = MOVE;
        main_fsm(params);
      }
      break;
    case ATTACHING:
      onAttaching(params);
      break;
    case GAME_OVER:
      onGame_over(params);
#ifndef debug_bro
      draw_main(params);
#else
      draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif

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
      params->gameInfo = init_empty_gameInfo();
      params->state = SPAWN;
      params->userAction = NONE_ACTION;
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
    params->userAction = NONE_ACTION;

  } else {
    params->was_move = true;
    if (is_it_legal_mv(params->userAction) == OK_BRO) {
      onMoving_legal(params);
    } else if (params->userAction == Down) {
      onMoving_down(params);
    } else if (params->userAction == Up) {
      onMoving_pro_down(params);
    } else {
      params->was_move = false;
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
    params->tetraMinoBro.center_y--;
  }
  tetra_to_array(params->tetraMinoBro,
                 params->tetraMinoBro.tmp_current_figure_on_field);
#ifdef debug_bro
  printf("field\n");
  out(params->gameInfo.field, MY_ROWS, MY_COLS);
  printf("\nnext\n");
  out(params->tetraMinoBro.tmp_current_figure_on_field, MY_ROWS, MY_COLS);
#endif
  if (params->userAction == Down) {
    params->userAction = NONE_ACTION;
  }
}

void onMoving_pro_down(Game_Objects_t* params) {
  while (params->state != ATTACHING) {
    params->userAction = Down;
    onMoving_down(params);
  }
#ifdef debug_bro
  printf("field\n");
  out(params->gameInfo.field, MY_ROWS, MY_COLS);
  printf("\nnext\n");
  out(params->tetraMinoBro.tmp_current_figure_on_field, MY_ROWS, MY_COLS);
#endif
  params->userAction = NONE_ACTION;
}

State onShifting(Game_Objects_t* params) {
  if (params->timer.time_to_shift == true) {
    params->userAction = Down;
    onMoving(params);
    params->timer.time_to_shift = false;
    gettimeofday(&params->timer.before, NULL);
  }
  return params->state;
}
void onAttaching(Game_Objects_t* params) {
#ifdef debug_bro
  printf("field\n");
  out(params->gameInfo.field, MY_ROWS, MY_COLS);
#endif
  next_to_field(params->tetraMinoBro.tmp_current_figure_on_field,
                params->gameInfo.field);
#ifdef debug_bro
  printf("field\n");
  out(params->gameInfo.field, MY_ROWS, MY_COLS);
#endif
  // TODO не забыть менять скорость
  game_mechanics(params);

  params->state = SPAWN;
}

void onGame_over(Game_Objects_t* params) {
  UserAction_t useract = params->userAction;

  if (useract == Start || useract == Terminate) {
    params->state = useract == Start ? START : EXIT_BRO;
    reset_game(&params->gameInfo, &params->tetraMinoBro);
    params->userAction = NONE_ACTION;
    main_fsm(params);
  }
}

void onExit_state(Game_Objects_t* params) {
  params->game_is_running = false;
  deleteGame(&params->gameInfo, &params->tetraMinoBro);
}

void onPause_state(Game_Objects_t* params) {
  while (params->userAction != Start && params->userAction != Terminate) {
#ifndef debug_bro
    params->userAction = getSignal(getch());
    timeout(100000000);

    timeout(1);
#else
    params->userAction = getSignal(getchar());

#endif
  }
}
void pause_bro(Game_Objects_t* params, State prev) {
  params->state = PAUSE;
#ifndef debug_bro
  draw_main(params);
#else
  draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif
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

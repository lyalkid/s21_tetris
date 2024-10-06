

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"
#include "inc/fsm_main.h"

void game_loop();
void game_session(Game_Objects_t* params, State* prev);
int main() {
  srand(time(0));
  get_random(1);
  Game_Objects_t* params = get_instanse();
  *params = init_empty_game_objects();
#ifndef debug_bro
  init_bro_ncurses(&params->views);
  game_loop();
  terminate_ncurses_bro(&params->views);
  exit(0);
#else
  game_loop();
#endif
  return 0;
}

void game_loop() {
  Game_Objects_t* params = get_instanse();
  // *params = init_empty_game_objects();
  State prev = START;
  while (params->game_is_running) {
#ifndef debug_bro
    draw_static(params);
#else
    draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif
    while (params->userAction != Start && params->userAction != Terminate) {
#ifndef debug_bro
      params->userAction = getSignal(getch());
      timeout(100000000);
      timeout(1);
#else
      params->userAction = getSignal('n');
#endif
    }
    main_game_fsm(params, &prev);
    if (params->game_is_running == false) {
      break;
    }
    game_session(params, &prev);
  }
  free(params);
}

void game_session(Game_Objects_t* params, State* prev) {
  bool session_is_running = false;
  if (params->state == START) {
    session_is_running = true;
    params->state = *prev;
  }
  char key = -1;
  while (params->state != PAUSE && params->state != GAME_OVER &&
         params->state != MAIN_MENU) {
    fsm_game_session(params);
    if (params->state == MOVE) {
#ifndef debug_bro
      key = getch();
#else
      key = 'f';
#endif
      if (key != -1) userInput(getSignal(key), session_is_running);
      if (params->userAction == Pause) {
        *prev = params->state;
        params->state = PAUSE;
        session_is_running = false;
      }
      if (params->userAction == Terminate) {
        params->state = MAIN_MENU;
        params->userAction = NONE_ACTION;
      }
    }
    countTime(params);

#ifndef debug_bro
    draw_main(params);
#else
    draw_simple(params->state, params->gameInfo, params->tetraMinoBro);
#endif
  }
  if (params->state == GAME_OVER) {
    if (params->gameInfo.score > params->gameInfo.high_score)
      params->gameInfo.high_score = params->gameInfo.score;
    write_high_score(params->gameInfo.high_score);
  }
}

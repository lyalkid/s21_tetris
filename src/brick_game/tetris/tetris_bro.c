

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"
#include "inc/fsm.h"

void game_loop(Game_Objects_t* params);
int main() {
  srand(time(0));
  get_random();
  Game_Objects_t* params = malloc(sizeof(Game_Objects_t));
  *params = init_empty_game_objects();
#ifndef debug_bro

  init_bro_ncurses(&params->views);

  game_loop(params);
  terminate_ncurses_bro(&params->views);
#else
  game_loop(params);
#endif
  return 0;
}
void game_loop(Game_Objects_t* params) {
  // gettimeofday(&params->timer.before, NULL);
  char key = 'n';

  while (params->game_is_running == true) {
    main_fsm(params);

    if (params->state == MOVE || params->state == MAIN_MENU ||
        params->state == GAME_OVER) {
#ifndef debug_bro
      key = getch();
#else
      key = getchar();
#endif

      if (key != -1) params->userAction = getSignal(key);
      if (params->userAction == Pause) {
        pause_bro(params, params->state);
      }
    }

    gettimeofday(&params->timer.after, NULL);

    if (is_time_to_shift(params->timer.before, params->timer.after,
                         params->timer.delay_to_shift)) {
      params->timer.time_to_shift = true;
    }
  }
}
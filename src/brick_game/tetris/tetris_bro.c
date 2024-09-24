

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"
#include "inc/fsm.h"

void game_loop();

int main() {
  srand(time(0));
  get_random();
  game_loop();
#if curses_bro
  terminate_ncurses_bro();
#endif
  return 0;
}

void game_loop() {
#if curses_bro
  init_bro_ncurses();
#endif

  Game_Objects_t* gameObjects = get_game_instance();
  *gameObjects = init_empty_game_objects();
  gettimeofday(&gameObjects->before, NULL);
  char key = 'n';

  while (gameObjects->game_is_running == true) {
    //    render_simple(gameObjects);

    main_fsm(gameObjects);
#if deb
    printf("next\n");
    out(gameObjects->gameInfo.next);
    printf("field\n");
    out(gameObjects->gameInfo.field);
#endif
    // gettimeofday(&gameObjects->before, NULL);
    render_simple(gameObjects);

    if (gameObjects->state == MOVE || gameObjects->state == MAIN_MENU ||
        gameObjects->state == GAME_OVER) {
#if curses_bro
      key = getch();
#else
      printf("you can exit\n");
      key = getchar();

#endif
      if (key != -1) gameObjects->userAction = getSignal(key);
      if (gameObjects->userAction == Pause) {
        pause_bro(gameObjects, gameObjects->state);
      }
    }

    gettimeofday(&gameObjects->after, NULL);

    if (is_time_to_shift(gameObjects->before, gameObjects->after,
                         gameObjects->timer)) {
      gameObjects->time_to_shift = true;
      //          main_fsm(gameObjects);
    }

#if deb
    printf("next\n");
    out(gameObjects->gameInfo.next);
    printf("field\n");
    out(gameObjects->gameInfo.field);
#endif
    if (gameObjects->state == EXIT_BRO || key == 'q') {
      gameObjects->game_is_running = false;
    }
  }
  // nanosleep(&ts, NULL);
  // endwin();
}
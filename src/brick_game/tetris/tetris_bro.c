

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"
#include "inc/fsm.h"

void game_loop(WINDOW* game_field, WINDOW* info_game, WINDOW* next_tetraMino);

int main() {
  WINDOW *game_field, *info_game, *next_tetraMino;
  srand(time(0));
  get_random();
  init_bro_ncurses();

  game_field = newwin(FIELD_Y, FIELD_X, 0, 0);
  info_game = newwin(INFO_Y, INFO_X, 0, FIELD_X);
  next_tetraMino = newwin(NEXT_Y, NEXT_X, INFO_Y, FIELD_X);
  refresh();
  box(game_field, 0, 0);
  box(info_game, 0, 0);
  box(next_tetraMino, 0, 0);

  // wgetch(game_field);
  wrefresh(game_field);
  wrefresh(info_game);
  wrefresh(next_tetraMino);
  refresh();

  game_loop(game_field, info_game, next_tetraMino);
  terminate_ncurses_bro(game_field, info_game, next_tetraMino);
  return 0;
}

void game_loop(WINDOW* game_field, WINDOW* info_game, WINDOW* next_tetraMino) {
  Game_Objects_t* gameObjects = get_game_instance();
  *gameObjects = init_empty_game_objects();
  gettimeofday(&gameObjects->before, NULL);
  char key = 'n';

  while (gameObjects->game_is_running == true) {
    main_fsm(gameObjects, game_field, info_game, next_tetraMino);

    if (gameObjects->state == MOVE || gameObjects->state == MAIN_MENU ||
        gameObjects->state == GAME_OVER) {
      key = getch();

      if (key != -1) gameObjects->userAction = getSignal(key);
      if (gameObjects->userAction == Pause) {
        pause_bro(gameObjects, gameObjects->state, game_field, info_game,
                  next_tetraMino);
      }
    }

    gettimeofday(&gameObjects->after, NULL);

    if (is_time_to_shift(gameObjects->before, gameObjects->after,
                         gameObjects->timer)) {
      gameObjects->time_to_shift = true;
    }
  }
}

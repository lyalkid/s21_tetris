

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"
#include "inc/fsm.h"

void gay_loop();

void game_loop();

int main() {
  srand(time(0));
  get_random();
  game_loop();

  return 0;
}

void game_loop() {
  Game_Objects_t* gameObjects = get_game_instance();
  *gameObjects = init_empty_game_objects();
  // char key = 0;
  while (gameObjects->game_is_running == true) {
    render_simple(gameObjects);
    main_fsm(gameObjects);
    char k;
    if (gameObjects->state == MOVE || gameObjects->state == PAUSE ||
        gameObjects->state == START || gameObjects->state == GAME_OVER) {
      k = getchar();
    }
    if (k == 'q') {
      gameObjects->game_is_running = false;
    }
#if deb
    printf("next\n");
    out(gameObjects->gameInfo.next);
    printf("field\n");
    out(gameObjects->gameInfo.field);
#endif
  }
}

void gay_loop() {
  Game_Objects_t gameObjects = init_empty_game_objects();
  int random_type = get_random();

  start_initialization(&gameObjects.gameInfo, random_type);

  int flag = 1;

  int cont = 0;
  char key = 's';
  int is_move_possible = -1;
  while (flag) {
    is_move_possible = can_i_move(gameObjects.gameInfo.tetraMinoBro,
                                  gameObjects.gameInfo.field, key);
#if deb
    printf("next\n");
    out(game_info.next);
    printf("field\n");
    out(game_info.field);
#endif
    if (is_it_board(gameObjects.gameInfo.next) == ERROR ||
        (key == 's' && is_move_possible == ERROR)) {
      next_to_field(gameObjects.gameInfo.next, gameObjects.gameInfo.field);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      gameObjects.gameInfo.tetraMinoBro =
          (TetraMino_bro)get_new_tetraMino(get_random());
      tetra_to_next(gameObjects.gameInfo.tetraMinoBro,
                    gameObjects.gameInfo.next);

    } else if (is_move_possible == OK_BRO) {
      move_tetramino(&gameObjects.gameInfo.tetraMinoBro,
                     gameObjects.gameInfo.next, key);

      tetra_to_next(gameObjects.gameInfo.tetraMinoBro,
                    gameObjects.gameInfo.next);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      //  prev = is_move_possible;
      scan_bro(gameObjects.gameInfo.field, MY_ROWS, COLS);

#if !deb
      system("clear");
#endif
      printf("\n");

      render_simple(&gameObjects);
    }
    key = getchar();
    if (key == 'q') flag = 0;

    printf("%c %d\n ", key, ++cont);
  }
  printf("\n");
}

// TODO написать сдвиг
// TODO написать соединение
// TODO написать game over
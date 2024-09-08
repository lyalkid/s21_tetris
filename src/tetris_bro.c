
#include "tetris_src/backend.h"
#include "tetris_src/frontend.h"

void game_loop();
int move(GameInfo_t* current);
int main() {
  srand(time(0));

  game_loop();

  return 0;
}

void game_loop() {
  GameInfo_t game_info = {0};
  int random_type = get_random();
  // for (int i = 0; i < 7; i++) {
  start_initialization(&game_info, random_type);
  render(game_info);

  // render(game_info);

  //  int tmp = get_random();
  //  printf("%d\n", tmp);
  //
  //  tmp = get_random();
  //  printf("%d\n", tmp);

  int cont = 0;
  char key = 's';
  int status = 1;
  int is_move_possible = -1;
  int prev = OK;
  while (key != 'q') {
    is_move_possible = can_i_move(game_info.tetraMinoBro, game_info.field, key);
#if deb
    printf("next\n");
    out(game_info.next);
    printf("field\n");
    out(game_info.field);
#endif
    if (is_move_possible == OK) {
      move_tetramino(&game_info.tetraMinoBro, game_info.next, key);

      tetra_to_next(game_info.tetraMinoBro, game_info.next);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      prev = is_move_possible;
        scan_bro(game_info.field, ROWS, COLS);

      render(game_info);
    } else if (key == 's' && is_move_possible == ERROR) {
      next_to_field(game_info.next, game_info.field);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      game_info.tetraMinoBro = (TetraMino_bro)get_new_tetraMino(get_random());
      tetra_to_next(game_info.tetraMinoBro, game_info.next);
    }

    key = getchar();
    printf("%c %d\n ", key, ++cont);
    system("clear");
  }
  printf("\n");
  // }
}

// TODO написать сдвиг
// TODO написать соединение
// TODO написать game over
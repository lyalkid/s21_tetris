#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../gui/cli/frontend.h"
#include "inc/backend.h"

void game_loop();

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
  // render_simple(game_info);

  //        int time = TIME;
  // render_simple(game_info);
  int flag = 1;
  //  int tmp = get_random();
  //  printf("%d\n", tmp);
  //
  //  tmp = get_random();
  //  printf("%d\n", tmp);

  int cont = 0;
  char key = 's';
  // int status = 1;
  int is_move_possible = -1;
  // int prev = OK_BRO;
  while (flag) {
    is_move_possible = can_i_move(game_info.tetraMinoBro, game_info.field, key);
#if deb
    printf("next\n");
    out(game_info.next);
    printf("field\n");
    out(game_info.field);
#endif
    if (is_it_board(game_info.next) == ERROR ||
        (key == 's' && is_move_possible == ERROR)) {
      next_to_field(game_info.next, game_info.field);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      game_info.tetraMinoBro = (TetraMino_bro)get_new_tetraMino(get_random());
      tetra_to_next(game_info.tetraMinoBro, game_info.next);

    } else if (is_move_possible == OK_BRO) {
      move_tetramino(&game_info.tetraMinoBro, game_info.next, key);

      tetra_to_next(game_info.tetraMinoBro, game_info.next);
#if deb
      printf("next\n");
      out(game_info.next);
      printf("field\n");
      out(game_info.field);
#endif
      //  prev = is_move_possible;
      scan_bro(game_info.field, ROWS, COLS);

#if !deb
      system("clear");
#endif
      printf("\n");

      render_simple(game_info);
    }
    //  render_simple(game_info);
    key = getchar();
    //    usleep(time);
    if (key == 'q') flag = 0;

    printf("%c %d\n ", key, ++cont);
    // system("clear");
  }
  printf("\n");
  // }
}

// TODO написать сдвиг
// TODO написать соединение
// TODO написать game over

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
  // random_type =  get_random();
  for (int i = 0; i < 7; i++) {
    start_initialization(&game_info, i);
    render(game_info);

    //  int tmp = get_random();
    //  printf("%d\n", tmp);
    //
    //  tmp = get_random();
    //  printf("%d\n", tmp);

    int cont = 0;
    char c = ' ';
    while (c != 'q') {
      // render(game_info);

      //    printf("%d ", get_random());
      // int tmp = get_random();
      //    get_next(&figure, tmp);
      // printf("%d\n", tmp);
      tetra_to_next(game_info.tetraMinoBro, game_info.next);
      // game_info.field = game_info.next;

      render(game_info);
      move_tetramino(&game_info, c);

      printf("%c\n", c);

      c = getchar();
      system("clear");
    }
    printf("\n");
  }
}

// TODO написать сдвиг
// TODO написать соединение
// TODO написать game over
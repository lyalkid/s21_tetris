
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
  start_initialization(&game_info, Z);

  //  int tmp = get_random();
  //  printf("%d\n", tmp);
  //
  //  tmp = get_random();
  //  printf("%d\n", tmp);

  int cont = 0;
  char c = getchar();
  while (c != 'q') {
    //    printf("%d ", get_random());
    // int tmp = get_random();
    //    get_next(&figure, tmp);
    // printf("%d\n", tmp);
    move_tetramino(&game_info, c);
    game_info.field = game_info.next;

    render(game_info);
    printf("%c\n", c);

    c = getchar();
    system("clear");
  }
  printf("\n");
}

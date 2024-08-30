
#include "tetris_src/frontend.h"
void game_loop();
int move(GameInfo_t* current);
int main() {
  srand(time(0));

  game_loop();

  return 0;
}

void game_loop() {
  GameInfo_t figure = {0};
  initBoard(&figure);
  //     printf("%d\n", tmp);

  int tmp = get_random();
  printf("%d\n", tmp);

  tmp = get_random();
  printf("%d\n", tmp);

  get_start(&figure, L);
  int cont = 0;
  char c = getchar();
  while (c != 'q') {
    //    printf("%d ", get_random());
    // int tmp = get_random();
    //    get_next(&figure, tmp);
    // printf("%d\n", tmp);
    move_tetramino(&figure, c);
    figure.field = figure.next;

    render(figure);
    printf("%c\n", c);
    c = getchar();
    system("clear");
  }
  printf("\n");
}

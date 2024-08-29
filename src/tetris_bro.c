
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
  get_start(&figure, get_random());
  int cont = 0;
  while (cont++ != 10) {
    //    printf("%d ", get_random());
    int tmp = get_random();
    get_next(&figure, tmp);
    printf("%d\n", tmp);
    int c;
    figure.field = figure.next;

    render(figure);
    printf("\n");
  }
  printf("\n");
}

int move(GameInfo_t* current) {
  int yest_eshe_mesto_znakvoprosa_ = 0;

  while () {
  }
}

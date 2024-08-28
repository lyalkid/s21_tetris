
#include "frontend.h"
void game_loop();
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

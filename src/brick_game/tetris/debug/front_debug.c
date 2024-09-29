#include "front_debug.h"

void show_game_field(int** field, int** next, int score, int level) {
    for (int j = 0; j < MY_COLS; j++) {
        printf("%d ", j );
    }
    printf("\n");
    for (int j = 0; j < MY_COLS; j++) {
    printf("##");
  }
  printf("\n");
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = field[i][j] + next[i][j];
      if (res == 1) {
        printf("[]");
      } else if (res > 1) {
        printf("@@");
      } else {
        printf("  ");
      }
    }
    printf("| %d\n", i);
  }
  for (int j = 0; j < MY_COLS; j++) {
    printf("##");
  }
  printf("\n");
  printf("score: %d\n", score);
  printf("level: %d\n", level);
};

void draw_simple(State_t state, GameInfo_t gameInfo,
                 TetraMino_bro tetraMinoBro) {
  system("clear");
  switch (state) {
    case MAIN_MENU:
      printf(
          "HELLO\n press ENTER or N to start a new game\n press ESCAPE or Q to "
          "exit\n");
      break;
    case GAME_OVER:
      printf(
          "GAME IS OVER :(\n press ENTER or N to start a new game\n press "
          "ESCAPE or Q to exit\n");
      break;
    case PAUSE:
      printf(
          "PAUSE\n press ENTER or N to continue\n press ESCAPE or Q to exit "
          "into main menu\n");
      break;
    default:
      show_game_field(gameInfo.field, tetraMinoBro.tmp_current_figure_on_field,
                      gameInfo.score, gameInfo.level);
      break;
  }
}

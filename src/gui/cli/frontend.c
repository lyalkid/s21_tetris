#include "frontend.h"

// void render_gui(GameInfo_t board) {
//   for (int j = 0; j < MY_COLS; j++) {
//     printw("##");
//   }
//   printw("\n");
//   for (int i = 0; i < MY_ROWS; i++) {
//     for (int j = 0; j < MY_COLS; j++) {
//       int res = board.field[i][j] + board.next[i][j];
//       if (res == 1) {
//         printw("[]");
//       } else if (res > 1) {
//         printw("@@");
//       }

//       else {
//         printw("  ");
//       }
//     }
//     printw("|\n");
//   }
//   for (int j = 0; j < MY_COLS; j++) {
//     printw("##");
//   }
//   printw("\n");
// }

void render_simple(Game_Objects_t* gameObjects) {
  system("clear");
  switch (gameObjects->state) {
    case MAIN_MENU:
      print_main_menu(gameObjects);
      break;
    default:
      show_game_field(gameObjects->gameInfo.field, gameObjects->gameInfo.next);
      break;
  }
}

void print_main_menu(Game_Objects_t* gameObjects) {
  printf("press N to start a new game\n");
  printf("press Q to exit from tetris\n");
}

// TODO добавить отображение количества очков
void show_game_field(int** field, int** next) {
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
};

#include "frontend.h"

// void render_gui(GameInfo_t board) {
//   for (int j = 0; j < COLS; j++) {
//     printw("##");
//   }
//   printw("\n");
//   for (int i = 0; i < ROWS; i++) {
//     for (int j = 0; j < COLS; j++) {
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
//   for (int j = 0; j < COLS; j++) {
//     printw("##");
//   }
//   printw("\n");
// }

void render_simple(GameInfo_t board) {
  for (int j = 0; j < COLS; j++) {
    printf("##");
  }
  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int res = board.field[i][j] + board.next[i][j];
      if (res == 1) {
        printf("[]");
      } else if (res > 1) {
        printf("@@");
      }

      else {
        printf("  ");
      }
    }
    printf("| %d\n", i);
  }
  for (int j = 0; j < COLS; j++) {
    printf("##");
  }
  printf("\n");
}

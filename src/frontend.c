#include "frontend.h"
void render() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if ((i == 2 || i == 3 || i == 1) && ( j == 4)) {
        printf("[]");
      } else {
        printf("@@");
      }
    }
    printf("\n");
  }
}
#include "frontend.h"

void init_bro_ncurses() {
  initscr();
  echo();
  nodelay(stdscr, TRUE);
  //  keypad(stdscr, TRUE);
  curs_set(0);
  timeout(1);
}

void terminate_ncurses_bro() { endwin(); }

void render_gui(int** field, int** next) {
  for (int j = 0; j < MY_COLS; j++) {
    printw("##");
    // refresh();
  }
  // refresh();

  printw("\n");
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = field[i][j] + next[i][j];
      if (res == 1) {
        printw("[]");
        //   refresh();

      } else if (res > 1) {
        printw("@@");
        // refresh();

      } else {
        printw("  ");
        // refresh();
      }
    }
    printw("|\n");
    //    refresh();
  }
  // refresh();

  for (int j = 0; j < MY_COLS; j++) {
    printw("##");
    // refresh();
  }
  printw("\n");
  // refresh();
  printw("score: %d\n", 100);
  refresh();
}

void render_simple(Game_Objects_t* gameObjects) {
  //  system("clear");
  clear();
  switch (gameObjects->state) {
    case MAIN_MENU:
      print_main_menu(gameObjects);
      break;
    default:
      render_gui(gameObjects->gameInfo.field, gameObjects->gameInfo.next);
      // show_game_field(gameObjects->gameInfo.field,
      // gameObjects->gameInfo.next);
      break;
  }
}

void print_main_menu(Game_Objects_t* gameObjects) {
  printw("press N to start a new game\n");
  // refresh();

  printw("press Q to exit from tetris\n");
  refresh();
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
        printf("");
      }
    }
    printf("| %d\n", i);
  }
  for (int j = 0; j < MY_COLS; j++) {
    printf("##");
  }
  printf("\n");
};

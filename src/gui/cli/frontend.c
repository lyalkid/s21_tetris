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

void render_gui(int** field, int** next, int score) {
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
  printw("score: %d\n", score);
  refresh();
}

void render_simple(Game_Objects_t* gameObjects) {
#if curses_bro
  clear();
#else
  system("clear");
#endif
  switch (gameObjects->state) {
    case MAIN_MENU:
      print_main_menu(gameObjects);
      break;
    default:
#if curses_bro
      render_gui(gameObjects->gameInfo.field, gameObjects->gameInfo.next,
                 gameObjects->gameInfo.score);
#else
      show_game_field(gameObjects->gameInfo.field, gameObjects->gameInfo.next,
                      gameObjects->gameInfo.score, gameObjects->gameInfo.level);
#endif
      break;
  }
}

void print_main_menu(Game_Objects_t* gameObjects) {
#if curses_bro

  printw("press N to start a new game\n");
  refresh();

  printw("press Q to exit from tetris\n");
  refresh();
#else
  printf("press N to start a new game\n");
  // refresh();

  printf("press Q to exit from tetris\n");
  //  refresh();
#endif
}

// TODO добавить отображение количества очков
void show_game_field(int** field, int** next, int score, int level) {
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

#include "frontend.h"
void draw_main(Game_Objects_t* gameObjects, WINDOW* game_field,
               WINDOW* info_field, WINDOW* next_field) {
  switch (gameObjects->state) {
    case MAIN_MENU:

      print_main_menu(gameObjects, game_field);
      wrefresh(info_field);
      wrefresh(next_field);

      break;
    case GAME_OVER:
      clear();
      game_over(gameObjects->gameInfo.score, gameObjects->gameInfo.level);
      break;

    default:
      // nodelay(stdscr, TRUE);
      // clear();
      render_game_win(game_field, gameObjects->gameInfo.field,
                      gameObjects->tetraMinoBro.tmp_current_figure_on_field);
      box(info_field, 0, 0);
      box(next_field, 0, 0);
      wrefresh(info_field);
      wrefresh(next_field);
      break;
  }
}

void init_bro_ncurses() {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  // keypad(stdscr, TRUE);
  curs_set(0);
  // timeout(12);
}

void terminate_ncurses_bro(WINDOW* game_field, WINDOW* info_game,
                           WINDOW* next_tetraMino) {
  delwin(game_field);
  delwin(info_game);
  delwin(next_tetraMino);

  endwin();
}

void render_game_win(WINDOW* win, int** field, int** next) {
  //  wclear(win);
  //  printw("clear\n");
  //  getch();
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = field[i][j] + next[i][j];
      if (res == 1) {
        mvwprintw(win, i + 1, j * 2 + 1, "0 ");
        //   refresh();

      } else if (res > 1) {
        mvwprintw(win, i + 1, j * 2 + 1, "# ");

        // refresh();

      } else {
        mvwprintw(win, i + 1, j * 2 + 1, ". ");

        // refresh();
      }
    }
    // printw("|\n");
    //    refresh();
  }
  // refresh();
  box(win, 0, 0);
  wrefresh(win);
  refresh();
}

// void render_gui(int** field, int** next, int score, int level) {
//   for (int j = 0; j < MY_COLS; j++) {
//     printw("##");
//     // refresh();
//   }
//   // refresh();

//   printw("\n");
//   for (int i = 0; i < MY_ROWS; i++) {
//     for (int j = 0; j < MY_COLS; j++) {
//       int res = field[i][j] + next[i][j];
//       if (res == 1) {
//         printw("0 ");
//         //   refresh();

//       } else if (res > 1) {
//         printw("# ");
//         // refresh();

//       } else {
//         printw(". ");
//         // refresh();
//       }
//     }
//     printw("|\n");
//     //    refresh();
//   }
//   // refresh();

//   for (int j = 0; j < MY_COLS; j++) {
//     printw("##");
//     // refresh();
//   }
//   printw("\n");
//   // refresh();
//   printw("score: %d\n", score);
//   printw("level: %d\n", level);

//   //  refresh();
// }

void print_main_menu(Game_Objects_t* gameObjects, WINDOW* game_field) {
  mvwprintw(game_field, 1, 1, "HELLO BRO");
  wrefresh(game_field);
}

void game_over(int score, int level) {
  for (int j = 0; j < MY_COLS; j++) {
    printw("##");
  }
  printw("\n");
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = 0;

      if (i == MY_ROWS / 2 && j == MY_COLS / 2) {
        printw("Game Over");
        i += 9;
      } else {
        printw("  ");
      }
    }
    printw("| %d\n", i);
  }
  for (int j = 0; j < MY_COLS; j++) {
    printw("##");
  }
  printw("\n");
  printw("score: %d\n", score);
  printw("level: %d\n", level);
  refresh();
}

// int main() {
//   WINDOW *game_field, *info_game, *next_tetraMino;
//   init_bro_ncurses(game_field, info_game, next_tetraMino);

//   sleep(2);
//   Game_Objects_t* game_f;
//   print_main_menu(game_f, game_field);
//   wgetch(game_field);
//   // terminate_ncurses_bro(game_field, info_game, next_tetraMino);
// }

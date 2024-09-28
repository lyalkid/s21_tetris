#include "frontend.h"
void draw_main(Game_Objects_t* gameObjects, WINDOW* game_field,
               WINDOW* info_field, WINDOW* next_field) {
  // printw_state(gameObjects->state);
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

    case PAUSE:

      render_pause(game_field);
      break;
    case SPAWN:

      render_next_win(next_field,
                      get_new_tetraMino(gameObjects->tetraMinoBro.next_type));

      break;
    default:
      render_game_win(game_field, gameObjects->gameInfo.field,
                      gameObjects->tetraMinoBro.tmp_current_figure_on_field);

      render_info_win(info_field, gameObjects->gameInfo.high_score,
                      gameObjects->gameInfo.score, gameObjects->gameInfo.level,
                      gameObjects->gameInfo.speed);

      break;
  }
}

void printw_state(State_t state) {
  switch (state) {
    case MAIN_MENU:
      mvprintw(FIELD_Y + 1, 0, "MAIN_MENU\n");
      refresh();
      break;

    case START:
      mvprintw(FIELD_Y + 1, 0, "START\n");
      refresh();

      break;
    case SPAWN:
      mvprintw(FIELD_Y + 1, 0, "SPAWN\n");
      refresh();

      break;
    case MOVE:

      mvprintw(FIELD_Y + 1, 0, "MOVE\n");
      refresh();

      break;
    case SHIFT:
      mvprintw(FIELD_Y + 1, 0, "SHIFT\n");
      refresh();

      break;
    case ATTACHING:
      mvprintw(FIELD_Y + 1, 0, "ATTACHING\n");
      refresh();

      break;
    case PAUSE:
      mvprintw(FIELD_Y + 1, 0, "PAUSE\n");
      refresh();

      break;
    case GAME_OVER:
      mvprintw(FIELD_Y + 1, 0, "GAME_OVER\n");
      refresh();

      break;

    default:
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
  werase(win);

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

void render_next_win(WINDOW* next_win, TetraMino_bro tetraMinoBro) {
  werase(next_win);

  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i] + tetraMinoBro.center_x + 4;
    int y = tetraMinoBro.coordinates[i + 1] + tetraMinoBro.center_y + 4;
    if (x < 1 || x > NEXT_X || y > NEXT_Y || y < 1) {
      mvwprintw(next_win, 1, 1,
                "smth wrong\n x:%d\n y:%d\n center_x:%d\n center_y:%d\n", x, y,
                tetraMinoBro.center_x, tetraMinoBro.center_y);
      //      break;
    } else {
      mvwprintw(next_win, y, x, "0 ");
    }
  }
  box(next_win, 0, 0);
  //  mvprintw(NEXT_X, NEXT_Y, "%d, %d", NEXT_Y, NEXT_X);

  wrefresh(next_win);
  refresh();
}
void render_info_win(WINDOW* info_win, int h_score, int score, int level,
                     int speed) {
  box(info_win, 0, 0);
  wrefresh(info_win);
  refresh();
}

void render_pause(WINDOW* game_win) {
  werase(game_win);
  mvwprintw(game_win, MY_ROWS / 2, MY_COLS / 2, "PAUSE BRO");
  box(game_win, 0, 0);
  wrefresh(game_win);
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
  werase(game_field);
  mvwprintw(game_field, 1, 1, "HELLO BRO");
  box(game_field, 0, 0);
  wrefresh(game_field);
  refresh();
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

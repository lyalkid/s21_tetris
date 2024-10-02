#include "frontend.h"

void show_game_field(int** field, int** next, int score, int level) {
  for (int j = 0; j < MY_COLS; j++) {
    printf("%d ", j);
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
#ifdef debug_bro
  printf("field\n");
  out(field, MY_ROWS, MY_COLS);
  printf("next\n");
  out(next, MY_ROWS, MY_COLS);
#endif
};

void draw_simple(State state, GameInfo_t gameInfo, TetraMino_bro tetraMinoBro) {
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

#ifndef debug_bro
#define curses_macro 1
void init_bro_ncurses(View_bro* views) {
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);
  // timeout(12);

  // views->main_menu_win = newwin(MAIN_W_SIZE, MAIN_W_SIZE, 2, 0);
  views->game_win = newwin(FIELD_Y, FIELD_X, 0, 0);
  views->info_win = newwin(INFO_Y, INFO_X, 0, FIELD_X);
  views->next_win = newwin(NEXT_Y, NEXT_X, INFO_Y, FIELD_X);
  // views->pause_win =  newwin();

  refresh();
  // box(views->game_win, 0, 0);
  // box(views->info_win, 0, 0);
  // box(views->next_win, 0, 0);

  // wrefresh(views->game_win);
  // wrefresh(views->info_win);
  // wrefresh(views->next_win);
  // wrefresh(views->main_menu_win);

  refresh();
}

void terminate_ncurses_bro(View_bro* views) {
  delwin(views->game_win);
  delwin(views->info_win);
  delwin(views->next_win);
  // delwin(views->game_over_win);
  // delwin(views->main_menu_win);
  // delwin(views->pause_win);
  endwin();
}
void draw_main(Game_Objects_t* params) {
  switch (params->state) {
    case MAIN_MENU:

      print_main_menu(params->views.game_win);
      wrefresh(params->views.info_win);
      wrefresh(params->views.next_win);

      break;
    case GAME_OVER:
      game_over(params->views.game_win);
      werase(params->views.next_win);
      wrefresh(params->views.next_win);
      break;

    case PAUSE:

      render_pause(params->views.game_win);
      break;
    case SPAWN:
      render_next_win(params->views.next_win, params->tetraMinoBro.next_type,
                      params);

      break;
    default:
      render_game_win(params->views.game_win, params->gameInfo.field,
                      params->tetraMinoBro.tmp_current_figure_on_field);

      render_info_win(params->views.info_win, params->gameInfo.high_score,
                      params->gameInfo.score, params->gameInfo.level);

      break;
  }
}

void render_game_win(WINDOW* win, int** field, int** next) {
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

void render_next_win(WINDOW* next_win, int type, Game_Objects_t* params) {
  werase(next_win);
  int coordinates[8] = {};
  get_TetraMino(coordinates, COMPLETE, type);
  for (int i = 0; i < 8; i += 2) {
    int x = coordinates[i] + 1 + 4;
    int y = coordinates[i + 1] + 4 + 4;
    if (x < 1 || x > NEXT_X || y > NEXT_Y || y < 1) {
      mvwprintw(next_win, 1, 1,
                "smth wrong\n x:%d\n y:%d\n center_x:%d\n center_y:%d\n", x, y,
                1, 4);
      //      break;
    } else {
      mvwprintw(next_win, y, x, "0 ");
    }
  }

  //  mvprintw(NEXT_X, NEXT_Y, "%d, %d", NEXT_Y, NEXT_X);

  wrefresh(next_win);
  refresh();
}
void render_info_win(WINDOW* info_win, int h_score, int score, int level) {
  werase(info_win);
  mvwprintw(info_win, 1, 1, "high_score:%d", h_score > score ? h_score : score);
  mvwprintw(info_win, 2, 1, "score:%d", score);
  mvwprintw(info_win, 3, 1, "level:%d", level);

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

void print_main_menu(WINDOW* main_menu_win) {
  werase(main_menu_win);
  mvwprintw(main_menu_win, 1, MY_COLS / 2, "HELLO BRO");
  mvwprintw(main_menu_win, MY_ROWS / 2 + 1, 1, "W,A,S,D - to move");
  mvwprintw(main_menu_win, MY_ROWS / 2 + 2, 1, "G - PAUSE");
  mvwprintw(main_menu_win, MY_ROWS / 2 + 3, 1,
            "Q or ESCAPE -\n exit session/game ");
  mvwprintw(main_menu_win, MY_ROWS / 2 + 5, 1,
            "N or ENTER - \n start/resume game ");

  box(main_menu_win, 0, 0);
  wrefresh(main_menu_win);
  refresh();
}

void game_over(WINDOW* game_win) {
  werase(game_win);
  mvwprintw(game_win, MY_ROWS / 2, MY_COLS / 2, "IT's");
  mvwprintw(game_win, MY_ROWS / 2, MY_COLS / 2, "GAME OVER");
  mvwprintw(game_win, MY_ROWS / 2, MY_COLS / 2, "BRO");

  box(game_win, 0, 0);
  wrefresh(game_win);
  refresh();
}

void printw_state(State state) {
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
#else
#define curses_macro 0
#endif
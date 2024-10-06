#include "frontend.h"

#include "../../brick_game/tetris/inc/fsm_main.h"
void draw_simple(State state, GameInfo_t gameInfo, TetraMino_bro tetraMinoBro) {
  // system("clear");
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
      // system("clear");
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
      if (res != 0)
        printf("%d ", res);
      else
        printf("  ");
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

#ifndef debug_bro
#define curses_macro 1
void init_bro_ncurses(View_bro* views) {
  initscr();
  cbreak();
  noecho();
  int h = 0, w = 0;

  init_bro_colors();
  getmaxyx(stdscr, h, w);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  curs_set(0);

  views->game_win =
      newwin(FIELD_Y, FIELD_X, (h - FIELD_Y) / 2, (w - FIELD_X) / 2);
  views->info_win = newwin(INFO_Y - 2, INFO_X, 0 + (h - FIELD_Y) / 2,
                           FIELD_X + (w - FIELD_X) / 2);
  views->next_win = newwin(NEXT_Y + 2, NEXT_X, INFO_Y - 2 + (h - FIELD_Y) / 2,
                           FIELD_X + (w - FIELD_X) / 2);

  refresh();
  box(views->game_win, 0, 0);
  box(views->info_win, 0, 0);
  box(views->next_win, 0, 0);

  wrefresh(views->game_win);
  wrefresh(views->info_win);
  wrefresh(views->next_win);

  refresh();
}

void init_bro_colors() {
  start_color();
  init_pair(9, COLOR_BLACK, COLOR_BLACK);
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_CYAN);
  init_pair(3, COLOR_BLACK, COLOR_BLUE);
  init_pair(4, COLOR_BLACK, COLOR_YELLOW);
  init_pair(5, COLOR_BLACK, COLOR_WHITE);
  init_pair(6, COLOR_BLACK, COLOR_GREEN);
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
}

void terminate_ncurses_bro(View_bro* views) {
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран

  refresh();
  delwin(views->game_win);
  delwin(views->info_win);
  delwin(views->next_win);
  clearok(stdscr, TRUE);  // Устанавливаем флаг перерисовки экрана
  clear();  // Очищаем экран

  refresh();
  endwin();
}

void draw_static(Game_Objects_t* params) {
  switch (params->state) {
    case MAIN_MENU:
      // clear();
      // printw("main menu\n");
      print_main_menu(params->views.game_win);
      werase(params->views.info_win);
      werase(params->views.next_win);
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
    default:
      break;
  }
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
  mvwprintw(game_win, MY_ROWS / 2 + 1, MY_COLS / 2, "GAME OVER");
  mvwprintw(game_win, MY_ROWS / 2 + 2, MY_COLS / 2, "BRO");

  box(game_win, 0, 0);
  wrefresh(game_win);
  refresh();
}
void render_pause(WINDOW* game_win) {
  werase(game_win);
  mvwprintw(game_win, MY_ROWS / 2, MY_COLS / 2, "PAUSE BRO");
  box(game_win, 0, 0);
  wrefresh(game_win);
  refresh();
}
void draw_main(Game_Objects_t* params) {
  GameInfo_t current_state = updateCurrentState();
  render_game_win(params->views.game_win, current_state.field,
                  params->tetraMinoBro.tmp_current_figure_on_field);
  render_next_win(params->views.next_win, params->tetraMinoBro.next_type);

  render_info_win(params->views.info_win, current_state.high_score,
                  current_state.score, current_state.level,
                  params->tetraMinoBro.meshok.count);
}

void render_game_win(WINDOW* win, int** field, int** next) {
  werase(win);

  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = field[i][j] + next[i][j];
      if ((res != 0 && field[i][j] == 0) || field[i][j] != 0) {
        wattron(win, COLOR_PAIR(res));

        mvwprintw(win, i + 1, j * scale_field + 1, "  ");

        wattroff(win, COLOR_PAIR(res));

      } else {
        mvwprintw(win, i + 1, j * scale_field + 1, "[]");
      }
    }
  }

  box(win, 0, 0);
  wrefresh(win);
  refresh();
}

void render_next_win(WINDOW* next_win, int type) {
  werase(next_win);

  mvwprintw(next_win, 1, 4 * 2, "NEXT");
  mvwprintw(next_win, 2, 3 * 2, "TETRAMINO:");

  int coordinates[8] = {};
  get_TetraMino(coordinates, COMPLETE, type);

  for (int i = 0; i < 8; i += 2) {
    int x = coordinates[i];
    int y = coordinates[i + 1] + 5;
    if (x < 1 || x > NEXT_X || y > NEXT_Y || y < 1) {
      mvwprintw(next_win, 1, 1, "smth wrong\n x:%d\n y:%d\n", x, y);
      //      break;
    } else {
      wattron(next_win, COLOR_PAIR(type));
      mvwprintw(next_win, y, x * 2 + 1, "  ");
      wattroff(next_win, COLOR_PAIR(type));
    }
  }

  box(next_win, 0, 0);
  wrefresh(next_win);
  refresh();
}
void render_info_win(WINDOW* info_win, int h_score, int score, int level,
                     int count[]) {
  werase(info_win);

  int stat_w = 7 * 2, stat_h = 1;
  wattron(info_win, COLOR_PAIR(4));
  mvwprintw(info_win, 1, 2, "high_score:");
  mvwprintw(info_win, 2, 2, "%d", h_score > score ? h_score : score);
  wattroff(info_win, COLOR_PAIR(4));
  wattron(info_win, COLOR_PAIR(6));

  mvwprintw(info_win, 4, 2, "score:");
  mvwprintw(info_win, 5, 2, "%d", score);
  wattroff(info_win, COLOR_PAIR(6));
  wattron(info_win, COLOR_PAIR(7));

  mvwprintw(info_win, 7, 2, "level:");

  mvwprintw(info_win, 8, 2, "%d", level);
  wattroff(info_win, COLOR_PAIR(7));

  mvwprintw(info_win, stat_h, stat_w, "STATS:");
  for (int i = 0; i < 7; i++) {
    mvwprintw(info_win, stat_h + i + 1, stat_w, "%c:%d", piece(i + 1),
              count[i]);
  }
  box(info_win, 0, 0);
  wrefresh(info_win);
  refresh();
}

char piece(int type) {
  char r = '0';
  switch (type) {
    case T:
      r = 'T';
      break;

    case O:
      r = 'O';
      break;

    case S:
      r = 'S';
      break;

    case Z:
      r = 'Z';
      break;

    case L:
      r = 'L';
      break;

    case J:
      r = 'J';
      break;
    case I:
      r = 'I';
      break;
  }
  return r;
}

#else
#define curses_macro 0
#endif
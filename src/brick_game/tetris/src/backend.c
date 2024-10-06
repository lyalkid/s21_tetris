#include "../inc/backend.h"

int** malloc_array(int rows, int cols) {
  int** field = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    field[i] = calloc(cols, sizeof(int));
  }
  return field;
}

void free_array(int** field, int rows) {
  for (int i = 0; i < rows; i++) {
    if (field[i] != NULL) {
      free(field[i]);
    }
  }
  if (field != NULL) free(field);
}

void null_array(int** field, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      field[i][j] = 0;
    }
  }
}

int can_i_move(TetraMino_bro tetraMino, int** field, UserAction_t key) {
  int** next = malloc_array(MY_ROWS, MY_COLS);
  int** tmp_next = malloc_array(MY_ROWS, MY_COLS);

  int** tmp_field = malloc_array(MY_ROWS, MY_COLS);
  tetra_to_array(tetraMino, next);
  move_tetraMino(&tetraMino, key);
  tetra_to_array(tetraMino, next);

  bin_array_bro(next, tmp_next, MY_ROWS, MY_COLS);

  bin_array_bro(field, tmp_field, MY_ROWS, MY_COLS);
  int is_all_ok = is_all_ok_bro(tmp_field, tmp_next);
  free_array(tmp_next, MY_ROWS);
  free_array(tmp_field, MY_ROWS);
  free_array(next, MY_ROWS);

  return is_all_ok;
}

void bin_array_bro(int** src, int** dist, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (src[i][j] == 0)
        dist[i][j] = 0;
      else
        dist[i][j] = 1;
    }
  }
}

int is_all_ok_bro(int** field, int** next) {
  int** tmp_next = malloc_array(MY_ROWS, MY_COLS);

  int** tmp_field = malloc_array(MY_ROWS, MY_COLS);
  bin_array_bro(next, tmp_next, MY_ROWS, MY_COLS);

  bin_array_bro(field, tmp_field, MY_ROWS, MY_COLS);
  int is_all_ok = OK_BRO;

  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int n_tmp = tmp_next[i][j];
      //      if (i == 15) {
      //        int c;
      //      }
      int f_tmp = tmp_field[i][j];
      int res = n_tmp + f_tmp;
      if (res > 1) {
        is_all_ok = ERROR;
        break;
      }
    }
    if (is_all_ok == ERROR) break;
  }
  free_array(tmp_field, MY_ROWS);
  free_array(tmp_next, MY_ROWS);

  return is_all_ok;
}

int scan_bro(int** field, int rows, int cols) {
  // TODO должен возвращать количество строк, которые удалились, чтобы
  // увеличивать очки
  int count = 0;
  int full_scan = 0;
  while (full_scan != 2) {
    int flag = 1;
    for (int i = rows - 1; i >= 0; i--) {
      int destroy = to_be_destroyed(field[i], cols);
      if (destroy == YES) {
        destruction(field, cols, i);
        count++;
        flag = 0;
      }
    }
    if (flag == 1) full_scan++;
  }
  return count;
}

int calc_score(int lines) {
  int res = 0;
  if (lines != 0) {
    switch (lines) {
      case 1:
        res = 100;
        break;
      case 2:
        res = 300;
        break;
      case 3:
        res = 700;
        break;
      default:
        res = 1500;
        break;
    }
  }
  return res;
}

void game_mechanics(Game_Objects_t* params) {
  int lines = scan_bro(params->gameInfo.field, MY_ROWS, MY_COLS);
  int prev_level = params->gameInfo.level;
  params->gameInfo.score += calc_score(lines);
  params->gameInfo.level = calc_level(params->gameInfo.score);
  if (prev_level < params->gameInfo.level) {
    params->gameInfo.speed++;
    params->timer.delay_to_shift = TIME / params->gameInfo.speed;
  }
}

int calc_level(int current_score) {
  int res = current_score / 600;
  return res > 10 ? 10 : res;
}
int to_be_destroyed(const int a[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (a[i] != 0) sum++;
  }
  return sum == size ? YES : NO;
}

void destruction(int** field, int cols, int row_not_bro) {
  for (int i = 0; i < cols; i++) {
    field[row_not_bro][i] = 0;
  }
  for (int j = 0; j < cols; j++) {
    for (int i = row_not_bro; i > 0; i--) {
      //        int tmp_a = field[i][j];
      int tmp_b = field[i - 1][j];
      field[i][j] = tmp_b;
    }
  }
}

// from front

void get_TetraMino(int coordinates[], int rotate, int type) {
  if (type >= T && type <= L) {
    get_tetra_four(coordinates, rotate, type);
  } else if (type >= I && type <= Z) {
    get_tetra_two(coordinates, rotate, type);
  } else if (type == O) {
    int coord[] = {4, 0, 5, 0, 4, 1, 5, 1};
    setCoordinates(coordinates, coord);
  } else {
    int coord[] = {0, 0, 0, 0, 0, 0, 0, 0};
    setCoordinates(coordinates, coord);
  }
}

void get_tetra_two(int coordinates[], int rotate, int type) {
  if (rotate % 2 == 1 && type == Z) {
    int coord[] = {4, 2, 4, 1, 5, 1, 5, 0};
    setCoordinates(coordinates, coord);

    /* ..#
     * .##
     * .#.
     *
     * */
  } else if (type == Z) {
    int coord[] = {3, 0, 4, 0, 4, 1, 5, 1};
    setCoordinates(coordinates, coord);

    /* ...
     * ##.
     * .##
     *
     * */
  } else if (rotate % 2 == 1 && type == S) {
    int coord[] = {4, 0, 4, 1, 5, 1, 5, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .##
     * ..#
     *
     * */

  } else if (type == S) {
    int coord[] = {4, 0, 5, 0, 3, 1, 4, 1};
    setCoordinates(coordinates, coord);

    /* ...
     * .##
     * ##.
     *
     * */

  } else if (rotate % 2 == 1 && type == I) {
    int coord[] = {5, 2, 5, 1, 5, 0, 5, 3};
    setCoordinates(coordinates, coord);

    /* ..#.
     * ..#.
     * ..#.
     * ..#.
     *
     * */
  } else if (type == I) {
    int coord[] = {3, 0, 4, 0, 5, 0, 6, 0};
    setCoordinates(coordinates, coord);

    /* ....
     * ....
     * ####
     * ....
     *
     * */
  }
}
void get_tetra_four(int coordinates[], int rotate, int type) {
  // TODO если это Т то поднять наверх

  // TODO ПРОВЕРИТЬ на коректность в соответвии со специф tetris rotate system
  if (type == T && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 4, 2};
    setCoordinates(coordinates, coord);

    /* ...
     * ###
     * .#.
     *
     * */
  } else if (type == T && rotate == RIGHT) {
    int coord[] = {3, 1, 4, 1, 4, 0, 4, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * ##.
     * .#.
     *
     * */

  } else if (type == T && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 4, 0};

    setCoordinates(coordinates, coord);

    /* .#.
     * ###
     * ...
     *
     * */
  } else if (type == T && rotate == REFLEX) {
    int coord[] = {5, 1, 4, 1, 4, 0, 4, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .##
     * .#.
     *
     * */
  }

  else if (type == L && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 5, 0};
    setCoordinates(coordinates, coord);
    /* ..#
     * ###
     * ...
     *
     * */

  } else if (type == L && rotate == RIGHT) {
    int coord[] = {4, 0, 4, 1, 4, 2, 5, 2};
    setCoordinates(coordinates, coord);
    /* .#.
     * .#.
     * .##
     *
     * */

  } else if (type == L && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 3, 2};
    setCoordinates(coordinates, coord);
    /*
     * ...
     * ###
     * #..
     *
     * */

  } else if (type == L && rotate == REFLEX) {
    int coord[] = {4, 0, 4, 1, 4, 2, 3, 0};
    setCoordinates(coordinates, coord);
    /* ##.
     * .#.
     * .#.
     *
     * */

  } else if (type == J && rotate == COMPLETE) {
    int coord[] = {3, 1, 4, 1, 5, 1, 3, 0};
    setCoordinates(coordinates, coord);
    /*
     * #..
     * ###
     * ...
     *
     * */

  } else if (type == J && rotate == RIGHT) {
    int coord[] = {4, 0, 4, 1, 4, 2, 5, 0};
    setCoordinates(coordinates, coord);

    /* .##
     * .#.
     * .#.
     *
     * */
  } else if (type == J && rotate == STRAIGHT) {
    int coord[] = {3, 1, 4, 1, 5, 1, 5, 2};
    setCoordinates(coordinates, coord);
    /*
     * ...
     * ###
     * ..#
     *
     * */

  } else if (type == J && rotate == REFLEX) {
    int coord[] = {4, 0, 4, 1, 4, 2, 3, 2};
    setCoordinates(coordinates, coord);

    /* .#.
     * .#.
     * ##.
     *
     * */
  }
}

void setCoordinates(int* coordinates, const int* values) {
  for (int i = 0; i < 8; i++) {
    coordinates[i] = values[i];
  }
}
void get_new_tetraMino(TetraMino_bro* tetraMinoBro) {
  int current = tetraMinoBro->type;
  int next = tetraMinoBro->next_type;
  init_bag(&tetraMinoBro->meshok);
  sort(tetraMinoBro->meshok.pieses, 7);

  //  printw("\nfdfdfdfdf");

  if (current == 0) {
    current = tetraMinoBro->type = get_random(7);
    tetraMinoBro->next_type = get_random(7);

  } else {
    int tmp = 1;
    int flag = 1;
    while (flag) {
      //      printw("\nfdfdfdfdf");
      tmp = get_random(get_real_len_of_number(tetraMinoBro->meshok.pieses, 7));
      int tmp_q = tetraMinoBro->meshok.pieses[tmp - 1];
      if (tmp_q != 0) {
        tetraMinoBro->next_type = tetraMinoBro->meshok.pieses[tmp - 1];
        current = tetraMinoBro->type = next;
        flag = 0;
        break;
      }
      //      for (int i = 0; i < 7; i++) {
      //        if (tetraMinoBro->meshok.pieses[i] == 1) flag = 0;
      //      }
    }
  }
  tetraMinoBro->meshok.count[current - 1]++;
  tetraMinoBro->meshok.pieses[find(tetraMinoBro->meshok.pieses, 7, current)] =
      0;

  tetraMinoBro->rotate = COMPLETE;
  tetraMinoBro->center_x = 0;
  tetraMinoBro->center_y = 0;
  null_array(tetraMinoBro->tmp_current_figure_on_field, MY_ROWS, MY_COLS);
  get_TetraMino(tetraMinoBro->coordinates, tetraMinoBro->rotate,
                tetraMinoBro->type);
}

int find(const int array[], int size, int i) {
  int res = 0;
  for (int k = 0; k < size; k++) {
    if (array[k] == i) {
      res = k;
      break;
    }
  }
  return res;
}
// получает длину числа без ведущих нулей
int get_real_len_of_number(const int a[], int size) {
  int i = 0;
  int count = 0;
  for (i = size - 1; i >= 0; i--) {
    if (a[i] == 0) {
      count++;
    } else {
      break;
    }
  }

  return size - count;
}

void move_tetraMino(TetraMino_bro* tetraMinoBro, UserAction_t key) {
  // TODO уменьшить размер строк

  int min_x =
      get_min(
          get_min(tetraMinoBro->coordinates[0], tetraMinoBro->coordinates[2]),
          get_min(tetraMinoBro->coordinates[4], tetraMinoBro->coordinates[6])) +
      tetraMinoBro->center_x;

  int max_x =
      get_max(
          get_max(tetraMinoBro->coordinates[0], tetraMinoBro->coordinates[2]),
          get_max(tetraMinoBro->coordinates[4], tetraMinoBro->coordinates[6])) +
      tetraMinoBro->center_x;
  switch (key) {
    case Left:
      if ((min_x - 1) >= 0) tetraMinoBro->center_x -= 1;
      break;

    case Right:
      if ((max_x + 1 < MY_COLS)) tetraMinoBro->center_x += 1;
      break;
    case Action:
      rotate_TetraMino(tetraMinoBro);
      break;
    default:
      break;
  }
}

void move_down_tetraMino(TetraMino_bro* tetraMinoBro) {
  tetraMinoBro->center_y += 1;
}

void move_up_tetraMino(TetraMino_bro* tetraMinoBro) {
  if (tetraMinoBro->center_y >= MY_ROWS - 1) tetraMinoBro->center_y -= 1;
}

int check_collision(TetraMino_bro tetraMinoBro, int** field) {
  int is_all_ok = OK_BRO;
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i] + tetraMinoBro.center_x;
    int y = tetraMinoBro.coordinates[i + 1] + tetraMinoBro.center_y;
    if (x < 0 || x >= MY_COLS || y < 0 || y >= MY_ROWS) {
      is_all_ok = ERROR;
      break;
    }
  }
  if (is_all_ok == OK_BRO) {
    int** tmp_next = malloc_array(MY_ROWS, MY_COLS);
    tetra_to_array(tetraMinoBro, tmp_next);
    is_all_ok = is_all_ok_bro(field, tmp_next);
    free_array(tmp_next, MY_ROWS);
  }

  return is_all_ok;
}

void rotate_TetraMino(TetraMino_bro* tetraMinoBro) {
  int rotate = (tetraMinoBro->rotate + 1) % 4;

  if (is_rotate_possible(*tetraMinoBro, rotate)) {
    tetraMinoBro->rotate = rotate;
    get_TetraMino(tetraMinoBro->coordinates, tetraMinoBro->rotate,
                  tetraMinoBro->type);
  }
}
void tetra_to_array(TetraMino_bro tetraMinoBro, int** next) {
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      next[i][j] = 0;
    }
  }
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i] + tetraMinoBro.center_x;
    int y = tetraMinoBro.coordinates[i + 1] + tetraMinoBro.center_y;
    next[y][x] = tetraMinoBro.type;
  }
}

int get_min(int a, int b) { return a > b ? b : a; }

int get_max(int a, int b) { return a < b ? b : a; }

int is_rotate_possible(TetraMino_bro tetraMinoBro, int rotate) {
  int possible = 1;
  tetraMinoBro.rotate = rotate;
  get_TetraMino(tetraMinoBro.coordinates, tetraMinoBro.rotate,
                tetraMinoBro.type);
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i] + tetraMinoBro.center_x;
    int y = tetraMinoBro.coordinates[i + 1] + tetraMinoBro.center_y;
    if (x < 0 || x >= MY_COLS || y >= MY_ROWS || y < 0) {
      possible = 0;
      break;
    }
  }
  return possible;
}

int get_random(int size) { return ((rand() % size) + 1); }

int get_highScore() {
  int h_score = 0;
  // return 100;
  char* filename = "highscore.txt";
  int size = 1000;
  // буфер для считавания данных из файла
  char buffer[size];
  // чтение из файла
  FILE* fp = fopen(filename, "r");
  if (fp) {
    // пока не дойдем до конца, считываем по 256 байт
    fgets(buffer, size, fp);
    h_score = atoi(buffer);
    fclose(fp);
  }
  return h_score;
};

void write_high_score(int h_score) {
  char* filename = "highscore.txt";

  int size = 1000;
  char buffer[size];

  FILE* fp = fopen(filename, "w");
  if (fp) {
    sprintf(buffer, "%d", h_score);
    fputs(buffer, fp);
    fclose(fp);
  }
}

int next_to_field(int** next, int** field) {
  int is_all_ok = is_all_ok_bro(field, next);
  if (is_all_ok) {
    for (int i = 0; i < MY_ROWS; i++) {
      for (int j = 0; j < MY_COLS; j++) {
        int n_tmp = next[i][j];
        int f_tmp = field[i][j];
        int res = n_tmp + f_tmp;
        field[i][j] = res;
      }
    }
  }
  return is_all_ok;
}

TetraMino_bro init_empty_tetraMino() {
  TetraMino_bro tetraMinoBro = (TetraMino_bro){0};
  tetraMinoBro.type = 0;
  tetraMinoBro.next_type = 0;

  tetraMinoBro.rotate = 0;
  tetraMinoBro.center_x = 0;
  tetraMinoBro.center_y = 0;
  for (int i = 0; i < 8; i++) {
    tetraMinoBro.coordinates[i] = 0;
  }

  tetraMinoBro.tmp_current_figure_on_field = malloc_array(MY_ROWS, MY_COLS);

  return tetraMinoBro;
}

GameInfo_t init_empty_gameInfo() {
  GameInfo_t gameInfo = {0};
  gameInfo.score = 0;
  gameInfo.high_score = get_highScore();
  gameInfo.level = 0;
  gameInfo.pause = 0;
  gameInfo.speed = 0;
  gameInfo.field = malloc_array(MY_ROWS, MY_COLS);
  gameInfo.next = malloc_array(NEXT_FIELD, NEXT_FIELD);
  //    malloc(sizeof(int*) * (MY_ROWS));
  //
  //          malloc(sizeof(int*) * (NEXT_FIELD));
  //  for (int i = 0; i < MY_ROWS; i++) {
  //    gameInfo.field[i] = calloc(MY_COLS, sizeof(int));
  //  }
  //  for (int i = 0; i < NEXT_FIELD; i++) {
  //    gameInfo.next[i] = calloc(NEXT_FIELD, sizeof(int));
  //  }
  return gameInfo;
}
void deleteGame(GameInfo_t* gameInfo, TetraMino_bro* tetraMino) {
  gameInfo->level = 0;
  gameInfo->speed = 0;
  gameInfo->score = 0;
  free_array(gameInfo->field, MY_ROWS);
  free_array(gameInfo->next, NEXT_FIELD);
  free_array(tetraMino->tmp_current_figure_on_field, MY_ROWS);
}
void reset_game(GameInfo_t* gameInfo, TetraMino_bro* tetraMino) {
  gameInfo->level = 0;
  gameInfo->speed = 0;
  gameInfo->score = 0;
  null_array(gameInfo->field, MY_ROWS, MY_COLS);
  null_array(gameInfo->next, NEXT_FIELD, NEXT_FIELD);
  null_array(tetraMino->tmp_current_figure_on_field, MY_ROWS, MY_COLS);
  tetraMino->type = 0;
  init_array(tetraMino->meshok.count, 7);
  init_array(tetraMino->meshok.pieses, 7);

  get_TetraMino(tetraMino->coordinates, tetraMino->rotate, 0);
}
void init_array(int array[], int size) {
  for (int i = 0; i < size; i++) {
    array[i] = 0;
  }
}
Game_Objects_t init_empty_game_objects() {
  Game_Objects_t gameObjects = {0};
  /*
   Shift_timer timer;
   bool game_is_running;  // флаг для game_loop()
   State state;
   UserAction_t userAction;
   TetraMino_bro tetraMinoBro;
   GameInfo_t gameInfo;
 #ifndef debug_bro
   View_bro views;
 #endif
  */

  gameObjects.timer = init_shift_timer();
  gameObjects.game_is_running = true;
  gameObjects.state = MAIN_MENU;
  gameObjects.userAction = NONE_ACTION;
  gameObjects.tetraMinoBro = init_empty_tetraMino();
  gameObjects.gameInfo = init_empty_gameInfo();

#ifndef debug_bro
  gameObjects.views = init_view();
#endif
  return gameObjects;
}

void init_bag(Bag* bag) {
  int sum = 0;
  int tmp = T;
  for (int i = 0; i < 7; i++) {
    sum += bag->pieses[i];
  }
  if (sum == 0) {
    for (int i = 0; i < 7; i++) {
      bag->pieses[i] = tmp++;
    }
  }
}

void sort(int array[], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      int tmp_a = array[i];
      int tmp_b = array[j];
      if (tmp_a < tmp_b) {
        array[j] = tmp_a;
        array[i] = tmp_b;
      }
    }
  }
}

#ifndef debug_bro

View_bro init_view() {
  View_bro views = {0};
  getmaxyx(stdscr, views.yMax, views.xMax);
  delwin(views.game_win);
  return views;
}

#endif

Shift_timer init_shift_timer() {
  Shift_timer sh_timer = {0};
  gettimeofday(&sh_timer.before, NULL);
  gettimeofday(&sh_timer.after, NULL);
  sh_timer.delay_to_shift = TIME;
  sh_timer.time_to_shift = false;
  return sh_timer;
}

// Game_Objects_t* get_game_instance() {
//   static Game_Objects_t gameObjects;
//   gameObjects.game_is_running = true;
//   return &gameObjects;
// };

int is_time_to_shift(struct timeval before, struct timeval after,
                     suseconds_t timer) {
  int res = ((suseconds_t)(after.tv_sec * 1000000 + after.tv_usec) -
             ((suseconds_t)before.tv_sec * 1000000 + before.tv_usec));

  return res > timer;
}

int is_it_movement(UserAction_t userAction) {
  int res = OK_BRO;
  if (!(userAction == Left || userAction == Right || userAction == Action))
    res = ERROR;
  return res;
}
int is_it_down_mv(UserAction_t userAction) {
  int res = OK_BRO;
  if (userAction == Down) {
    res = ERROR;
  }
  return res;
}

void countTime(Game_Objects_t* params) {
  gettimeofday(&params->timer.after, NULL);

  if (is_time_to_shift(params->timer.before, params->timer.after,
                       params->timer.delay_to_shift)) {
    params->timer.time_to_shift = true;
  }
}
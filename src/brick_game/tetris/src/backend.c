#include "../inc/backend.h"
void out(int** tmp_next) {
  for (int j = 0; j < MY_COLS; j++) {
    printf("%d", j);
  }
  printf("\n");
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int res = tmp_next[i][j];
      if (res == 1) {
        printf("*");
      } else if (res > 1) {
        printf("@");
      } else {
        printf("`");
      }
    }
    printf("% d\n", i);
  }
}

int** malloc_array(int rows, int cols) {
  int** field = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    field[i] = calloc(cols, sizeof(int));
  }
  return field;
}

void free_array(int** field, int rows) {
  for (int i = 0; i < rows; i++) {
    free(field[i]);
  }
  free(field);
}

int can_i_move(TetraMino_bro tetraMino, int** field, char key) {
  int** tmp_next = malloc_array(MY_ROWS, MY_COLS);
  tetra_to_next(tetraMino, tmp_next);
#if deb
  out(tmp_next);
#endif
  move_tetramino(&tetraMino, tmp_next, key);
  tetra_to_next(tetraMino, tmp_next);

#if deb
  out(tmp_next);
#endif
#if deb
  out(field);
#endif
  int is_all_ok = is_all_ok_bro(field, tmp_next);

  // tetra_to_next(tetraMino, tmp_next);

  /*
   * нужно подвинуть tetramino , перевести в tmp_next, чекнуть нет ли коллизий.
   * если все ок, то вернуть OK_BRO, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, MY_ROWS);
  return is_all_ok;
}

int can_i_rotate(TetraMino_bro tetraMino, int** field) {
  int** tmp_next = malloc_array(MY_ROWS, MY_COLS);
  tetra_to_next(tetraMino, tmp_next);
#if deb
  out(tmp_next);
#endif
  rotate_TetraMino(&tetraMino);
  tetra_to_next(tetraMino, tmp_next);

#if deb
  out(tmp_next);
#endif
#if deb
  out(field);
#endif
  int is_all_ok = is_all_ok_bro(field, tmp_next);

  // tetra_to_next(tetraMino, tmp_next);

  /*
   * нужно подвинуть tetramino , перевести в tmp_next, чекнуть нет ли коллизий.
   * если все ок, то вернуть OK_BRO, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, MY_ROWS);
  return is_all_ok;
}
int is_all_ok_bro(int** field, int** next) {
  int is_all_ok = OK_BRO;

  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int n_tmp = next[i][j];
      //      if (i == 15) {
      //        int c;
      //      }
      int f_tmp = field[i][j];
      int res = n_tmp + f_tmp;
      if (res > 1) {
        is_all_ok = ERROR;
        break;
      }
    }
    if (is_all_ok == ERROR) break;
  }
  return is_all_ok;
}

// Проверка, что фигура встретилась с границей
int is_it_board(int** next) {
  int is_all_ok = OK_BRO;
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      int n_tmp = next[i][j];
      //      if (i == 15) {
      //        int c;
      //      }
      if (n_tmp == 1 && i == 19) {
        is_all_ok = ERROR;
        break;
      }
    }
    if (is_all_ok == ERROR) break;
  }
  return is_all_ok;
}
void scan_bro(int** field, int rows, int cols) {
  // TODO должен возвращать количество строк, которые удалились, чтобы
  // увеличивать очки
  int full_scan = 0;
  while (full_scan != 2) {
    int flag = 1;
    for (int i = rows - 1; i >= 0; i--) {
      int destroy = to_be_destroyed(field[i], cols);
      if (destroy == YES) {
        destruction(field, cols, i);
        flag = 0;
      }
    }
    if (flag == 1) full_scan++;
  }
}

int to_be_destroyed(const int a[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    if (a[i] == 1) sum++;
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

void get_TetraMino(TetraMino_bro* tetraMinoBro) {
  if (tetraMinoBro->type >= T && tetraMinoBro->type <= L) {
    get_tetra_four(tetraMinoBro);
  } else if (tetraMinoBro->type >= I && tetraMinoBro->type <= Z) {
    get_tetra_two(tetraMinoBro);
  } else if (tetraMinoBro->type == O) {
    int coord[] = {0, 0, 1, 0, 0, -1, 1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);
  }
}

void get_tetra_two(TetraMino_bro* tetraMinoBro) {
  if (tetraMinoBro->rotate % 2 == 1 && tetraMinoBro->type == Z) {
    int coord[] = {0, 0, 1, 0, 1, -1, 0, 1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ..#
     * .##
     * .#.
     *
     * */
  } else if (tetraMinoBro->type == Z) {
    int coord[] = {0, 0, 1, 0, 0, -1, -1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ...
     * ##.
     * .##
     *
     * */
  } else if (tetraMinoBro->rotate % 2 == 1 && tetraMinoBro->type == S) {
    int coord[] = {0, 0, 1, 0, 1, 1, 0, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * .##
     * ..#
     *
     * */

  } else if (tetraMinoBro->type == S) {
    int coord[] = {0, 18, -1, 18, 0, 17, 1, 17};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ...
     * .##
     * ##.
     *
     * */

  } else if (tetraMinoBro->rotate % 2 == 1 && tetraMinoBro->type == I) {
    int coord[] = {1, -1, 1, 0, 1, 1, 1, 2};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ..#.
     * ..#.
     * ..#.
     * ..#.
     *
     * */
  } else if (tetraMinoBro->type == I) {
    int coord[] = {-1, -1, 0, -1, 1, -1, 2, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ....
     * ....
     * ####
     * ....
     *
     * */
  }
}
void get_tetra_four(TetraMino_bro* tetraMinoBro) {
  // TODO если это Т то поднять наверх

  // TODO ПРОВЕРИТЬ на коректность в соответвии со специф tetris rotate system
  if (tetraMinoBro->type == T && tetraMinoBro->rotate == COMPLETE) {
    int coord[] = {0, 0, 1, 0, -1, 0, 0, 1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ...
     * ###
     * .#.
     *
     * */
  } else if (tetraMinoBro->type == T && tetraMinoBro->rotate == RIGHT) {
    int coord[] = {0, 0, 0, -1, 0, 1, -1, 0};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * ##.
     * .#.
     *
     * */
  } else if (tetraMinoBro->type == T && tetraMinoBro->rotate == STRAIGHT) {
    int coord[] = {0, 0, 1, 0, -1, 0, 0, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * ###
     * ...
     *
     * */
  } else if (tetraMinoBro->type == T && tetraMinoBro->rotate == REFLEX) {
    int coord[] = {0, 0, 0, -1, 0, 1, 1, 0};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * .##
     * .#.
     *
     * */
  }

  else if (tetraMinoBro->type == L && tetraMinoBro->rotate == COMPLETE) {
    int coord[] = {0, -1, -1, -1, 1, -1, -1, 0};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ###
     * #..
     * ...
     *
     * */
  } else if (tetraMinoBro->type == L && tetraMinoBro->rotate == RIGHT) {
    int coord[] = {0, 0, 0, -1, 0, 1, -1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ##.
     * .#.
     * .#.
     *
     * */
  } else if (tetraMinoBro->type == L && tetraMinoBro->rotate == STRAIGHT) {
    int coord[] = {0, 0, -1, 0, 1, 0, 1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ..#
     * ###
     * ...
     *
     * */
  } else if (tetraMinoBro->type == L && tetraMinoBro->rotate == REFLEX) {
    int coord[] = {0, 0, 0, -1, 0, 1, 1, 1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * .#.
     * .##
     *
     * */
  } else if (tetraMinoBro->type == J && tetraMinoBro->rotate == COMPLETE) {
    int coord[] = {0, -1, -1, -1, 1, -1, 1, 0};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ###
     * ..#
     * ...
     *
     * */
  } else if (tetraMinoBro->type == J && tetraMinoBro->rotate == RIGHT) {
    int coord[] = {0, 0, 0, -1, 0, 1, -1, 1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .#.
     * .#.
     * ##.
     *
     * */
  } else if (tetraMinoBro->type == J && tetraMinoBro->rotate == STRAIGHT) {
    int coord[] = {0, 0, -1, 0, 1, 0, -1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* #..
     * ###
     * ...
     *
     * */
  } else if (tetraMinoBro->type == J && tetraMinoBro->rotate == REFLEX) {
    int coord[] = {0, 0, 0, -1, 0, 1, 1, -1};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* .##
     * .#.
     * .#.
     *
     * */
  }
}

void setCoordinates(int* coordinates, const int* values) {
  for (int i = 0; i < 8; i++) {
    coordinates[i] = values[i];
  }
}
TetraMino_bro get_new_tetraMino(int type) {
  TetraMino_bro tetraMinoBro = {0};
  tetraMinoBro.type = type;
  tetraMinoBro.rotate = COMPLETE;
  tetraMinoBro.center_x = 4;
  tetraMinoBro.center_y = 1;
  get_TetraMino(&tetraMinoBro);
  return tetraMinoBro;
}

void move_tetramino(TetraMino_bro* tetraMinoBro, int** next, char key) {
  int dx = 0, dy = 0;
  // TODO уменьшить размер строк
  // int min_y =
  //     get_min(
  //         get_min(tetraMinoBro->coordinates[1],
  //         tetraMinoBro->coordinates[3]),
  //         get_min(tetraMinoBro->coordinates[5],
  //         tetraMinoBro->coordinates[7])) +
  //     tetraMinoBro->center_y;

  int min_x =
      get_min(
          get_min(tetraMinoBro->coordinates[0], tetraMinoBro->coordinates[2]),
          get_min(tetraMinoBro->coordinates[4], tetraMinoBro->coordinates[6])) +
      tetraMinoBro->center_x;
  int max_y =
      get_max(
          get_max(tetraMinoBro->coordinates[1], tetraMinoBro->coordinates[3]),
          get_max(tetraMinoBro->coordinates[5], tetraMinoBro->coordinates[7])) +
      tetraMinoBro->center_y;

  int max_x =
      get_max(
          get_max(tetraMinoBro->coordinates[0], tetraMinoBro->coordinates[2]),
          get_max(tetraMinoBro->coordinates[4], tetraMinoBro->coordinates[6])) +
      tetraMinoBro->center_x;
  switch (key) {
    // case 'w':
    //   if ((min_y - 1) >= 0) dy -= 1;
    //   break;
    case 'a':
      if ((min_x - 1) >= 0) dx -= 1;
      break;
    case 's':
      if ((max_y + 1) < MY_ROWS) dy += 1;
      break;
    case 'd':
      if ((max_x + 1 < MY_COLS)) dx += 1;
      break;
    case 'h':
      rotate_TetraMino(tetraMinoBro);
      break;
    default:
      break;
  }
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro->coordinates[i];
    int y = tetraMinoBro->coordinates[i + 1];
    if (x >= 0 && x < MY_COLS && y >= 0 && y < MY_ROWS) next[y][x] = 0;
  }

  tetraMinoBro->center_x += dx;
  tetraMinoBro->center_y += dy;
  // if(dx == 0 && dy == 0) *can_i_move = ERROR;
  //   for (int i = 0; i < 8; i += 2) {
  //     int x = gameInfo->tetraMinoBro->coordinates[i];
  //     int y = gameInfo->tetraMinoBro->coordinates[i + 1];
  //     if (x >= 0 && x < MY_COLS && y >= 0 && y < MY_ROWS)
  //     gameInfo->next[y][x] = 1;
  //   }
}

void rotate_TetraMino(TetraMino_bro* tetraMinoBro) {
  int rotate = (tetraMinoBro->rotate + 1) % 4;
  // char v = getchar();
  if (is_rotate_possible(*tetraMinoBro, rotate)) {
    tetraMinoBro->rotate = rotate;
    get_TetraMino(tetraMinoBro);
  }
}
void tetra_to_next(TetraMino_bro tetraMinoBro, int** next) {
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      next[i][j] = 0;
    }
  }
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i] + tetraMinoBro.center_x;
    int y = tetraMinoBro.coordinates[i + 1] + tetraMinoBro.center_y;
    next[y][x] = 1;
  }
}

int get_min(int a, int b) { return a > b ? b : a; }

int get_max(int a, int b) { return a < b ? b : a; }

int is_rotate_possible(TetraMino_bro tetraMinoBro, int rotate) {
  int possible = 1;
  tetraMinoBro.rotate = rotate;
  get_TetraMino(&tetraMinoBro);
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

void start_initialization(GameInfo_t* gameInfo, int type) {
  GameInfo_t gameInfo1 = {0};
  *gameInfo = gameInfo1;
  gameInfo->field = malloc(sizeof(int*) * (MY_ROWS));
  gameInfo->next = malloc(sizeof(int*) * (MY_ROWS));

  for (int i = 0; i < MY_ROWS; i++) {
    gameInfo->field[i] = calloc(MY_COLS, sizeof(int));
    gameInfo->next[i] = calloc(MY_COLS, sizeof(int));
  }
  for (int i = 0; i < MY_COLS; i++) {
    gameInfo->field[MY_ROWS][i] = 1;
  }
  gameInfo->score = 0;
  gameInfo->high_score = get_highScore();
  gameInfo->level = 0;
  gameInfo->pause = 0;
  gameInfo->speed = 0;
  TetraMino_bro tetraMinoBro = get_new_tetraMino(type);
  // get_TetraMino(&tetraMinoBro);
  gameInfo->tetraMinoBro = tetraMinoBro;
  tetra_to_next(gameInfo->tetraMinoBro, gameInfo->next);
  // next_to_field(gameInfo->next, gameInfo->field);
}

int get_random() { return ((rand() % 7)); }

int get_highScore() {
  return 100;
  //    char* filename = "highscore.txt";
  //    char c;
  //    FILE* fp = fopen(filename, "r");
  //
  //    if(fp)
  //    {
  //        // считываем посимвольно из файла
  //        while((c=getc(fp))!= EOF)
  //        {
  //            printf("%c", c);
  //        }
  //        fclose(fp);
  //    }
};
//

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
int is_down_possible(TetraMino_bro tetraMinoBro, int** field, int** next) {
  int possible = 1;
  for (int i = 1; i < 8; i += 2) {
    tetraMinoBro.coordinates[i] += 1;
  }
  tetra_to_next(tetraMinoBro, next);
  possible = is_all_ok_bro(field, next);
  if (possible) {
    next_to_field(next, field);
  } else {
    for (int i = 1; i < 8; i += 2) {
      tetraMinoBro.coordinates[i] -= 1;
    }
    tetra_to_next(tetraMinoBro, next);
  };
  return possible;
}

TetraMino_bro init_empty_tetraMino() {
  TetraMino_bro tetraMinoBro = (TetraMino_bro){0};
  tetraMinoBro.type = get_random();
  tetraMinoBro.rotate = 0;
  tetraMinoBro.center_x = 0;
  tetraMinoBro.center_y = 0;
  for (int i = 0; i < 8; i++) {
    tetraMinoBro.coordinates[i] = 0;
  }
  return tetraMinoBro;
}

GameInfo_t init_empty_gameInfo() {
  GameInfo_t gameInfo = {0};
  gameInfo.score = 0;
  gameInfo.high_score = get_highScore();
  gameInfo.level = 0;
  gameInfo.pause = 0;
  gameInfo.speed = 0;
  gameInfo.field = malloc(sizeof(int*) * (MY_ROWS));
  gameInfo.next = malloc(sizeof(int*) * (MY_ROWS));
  for (int i = 0; i < MY_ROWS; i++) {
    gameInfo.field[i] = calloc(MY_COLS, sizeof(int));
    gameInfo.next[i] = calloc(MY_COLS, sizeof(int));
  }

  return gameInfo;
}

Game_Objects_t init_empty_game_objects() {
  Game_Objects_t gameObjects = {0};
  gameObjects.tetraMinoBro = init_empty_tetraMino();
  gameObjects.gameInfo = init_empty_gameInfo();
  // gameObjects.userAction = -1;
  gameObjects.game_is_running = true;
  gameObjects.state = MAIN_MENU;
  return gameObjects;
}

Game_Objects_t* get_game_instance() {
  static Game_Objects_t gameObjects;
  //    gameObjects.game_is_running = true;
  return &gameObjects;
};

// TODO сделать логирование игрового поля
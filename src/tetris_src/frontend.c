#include "frontend.h"
void render(GameInfo_t board) {
  for (int j = 0; j < COLS; j++) {
    printf("%d", j);
  }
  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board.next[i][j] == 1) {
        printf("*");
      } else {
        printf("`");
      }
    }
    printf("% d\n", i);
  }
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
void start_initialization(GameInfo_t* gameInfo, int type) {
  GameInfo_t gameInfo1 = {0};
  *gameInfo = gameInfo1;
  gameInfo->field = malloc(sizeof(int*) * ROWS);
  gameInfo->next = malloc(sizeof(int*) * ROWS);

  for (int i = 0; i < ROWS; i++) {
    gameInfo->field[i] = calloc(COLS, sizeof(int));
    gameInfo->next[i] = calloc(COLS, sizeof(int));
  }
  gameInfo->score = 0;
  gameInfo->high_score = get_highScore();
  gameInfo->level = 0;
  gameInfo->pause = 0;
  gameInfo->speed = 0;
  TetraMino_bro tetraMinoBro = {0};
  tetraMinoBro.type = type;
  tetraMinoBro.rotate = COMPLETE;
  tetraMinoBro.center_x = 4;
  tetraMinoBro.center_y = 1;
  get_TetraMino(&tetraMinoBro);
  gameInfo->tetraMinoBro = tetraMinoBro;
}

void get_TetraMino(TetraMino_bro* tetraMinoBro) {
  if (tetraMinoBro->type >= T && tetraMinoBro->type <= L) {
    get_tetra_four(tetraMinoBro);
  } else if (tetraMinoBro->type >= I && tetraMinoBro->type <= Z) {
    get_tetra_two(tetraMinoBro);
  } else {
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
    int coord[] = {0, 0, -1, 0, 0, -1, 1, -1};
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
  } else if (tetraMinoBro->type == L && tetraMinoBro->rotate == STRAIGHT) {
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

void move_tetramino(GameInfo_t* gameInfo, char key) {
  int dx = 0, dy = 0;
  // TODO уменьшить размер строк
  int min_y = get_min(get_min(gameInfo->tetraMinoBro.coordinates[1],
                              gameInfo->tetraMinoBro.coordinates[3]),
                      get_min(gameInfo->tetraMinoBro.coordinates[5],
                              gameInfo->tetraMinoBro.coordinates[7])) +
              gameInfo->tetraMinoBro.center_y;

  int min_x = get_min(get_min(gameInfo->tetraMinoBro.coordinates[0],
                              gameInfo->tetraMinoBro.coordinates[2]),
                      get_min(gameInfo->tetraMinoBro.coordinates[4],
                              gameInfo->tetraMinoBro.coordinates[6])) +
              gameInfo->tetraMinoBro.center_x;
  int max_y = get_max(get_max(gameInfo->tetraMinoBro.coordinates[1],
                              gameInfo->tetraMinoBro.coordinates[3]),
                      get_max(gameInfo->tetraMinoBro.coordinates[5],
                              gameInfo->tetraMinoBro.coordinates[7])) +
              gameInfo->tetraMinoBro.center_y;

  int max_x = get_max(get_max(gameInfo->tetraMinoBro.coordinates[0],
                              gameInfo->tetraMinoBro.coordinates[2]),
                      get_max(gameInfo->tetraMinoBro.coordinates[4],
                              gameInfo->tetraMinoBro.coordinates[6])) +
              gameInfo->tetraMinoBro.center_x;
  switch (key) {
    case 'w':
      if ((min_y - 1) >= 0) dy -= 1;
      break;
    case 'a':
      if ((min_x - 1) >= 0) dx -= 1;
      break;
    case 's':
      if ((max_y + 1) < 20) dy += 1;
      break;
    case 'd':
      if ((max_x + 1 < 10)) dx += 1;
      break;
    case 'h':
      rotate_Tetramino(gameInfo);
      break;
    default:
      break;
  }
  for (int i = 0; i < 8; i += 2) {
    int x = gameInfo->tetraMinoBro.coordinates[i];
    int y = gameInfo->tetraMinoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 0;
  }

  gameInfo->tetraMinoBro.center_x += dx;
  gameInfo->tetraMinoBro.center_y += dy;

  //  for (int i = 0; i < 8; i += 2) {
  //    int x = gameInfo->tetraMinoBro.coordinates[i];
  //    int y = gameInfo->tetraMinoBro.coordinates[i + 1];
  //    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 1;
  //  }
}

void rotate_Tetramino(GameInfo_t* gameInfo) {
  int rotate = (gameInfo->tetraMinoBro.rotate + 1) % 4;
  // char v = getchar();
  if (is_rotate_possible(gameInfo->tetraMinoBro, rotate)) {
    gameInfo->tetraMinoBro.rotate = rotate;
    get_TetraMino(&(gameInfo->tetraMinoBro));
  }
}

void setCoordinates(int* coordinates, const int* values) {
  for (int i = 0; i < 8; i++) {
    coordinates[i] = values[i];
  }
}
// void get_next(GameInfo_t* gameInfo, int type) {
//   // TODO не забыть чистить память
//
//   TetraMino_bro tetraMinoBro = {{0}};
//
//   get_Tetramino(&tetraMinoBro, type);
//   gameInfo->tetraMinoBro = tetraMinoBro;
//   tetramino_into_next(gameInfo, tetraMinoBro);
// }

void tetra_to_next(TetraMino_bro tetraMinoBro, int** next) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
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
    if (x < 0 || x >= COLS || y >= ROWS || y < 0) {
      possible = 0;
      break;
    }
  }
  return possible;
}
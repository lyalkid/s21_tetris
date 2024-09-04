#include "frontend.h"
void render(GameInfo_t board) {
  for (int j = 0; j < COLS; j++) {
    printf("%d", j);
  }
  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board.field[i][j] == 1) {
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
  if (tetraMinoBro->type == T && tetraMinoBro->rotate == COMPLETE) {
    int coord[] = {0, -1, 1, -1, -1, -1, 0, 0};
    setCoordinates(tetraMinoBro->coordinates, coord);

    /* ###
     * .#.
     * ...
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
  int dx = gameInfo->tetraMinoBro.center_x,
      dy = gameInfo->tetraMinoBro.center_y;
  switch (key) {
    case 'w':
      dy -= 1;
      break;
    case 'a':
      dx -= 1;
      break;
    case 's':
      dy += 1;
      break;
    case 'd':
      dx += 1;
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
  for (int i = 0; i < 8; i += 2) {
    gameInfo->tetraMinoBro.coordinates[i] += dx;
    gameInfo->tetraMinoBro.coordinates[i + 1] += dy;
  }
  for (int i = 0; i < 8; i += 2) {
    int x = gameInfo->tetraMinoBro.coordinates[i];
    int y = gameInfo->tetraMinoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 1;
  }
  // tetramino_into_next(gameInfo, gameInfo->tetraMinoBro);
}

void tetramino_into_next(GameInfo_t* gameInfo, TetraMino_bro tetraMinoBro) {
  for (int i = 0; i < 8; i += 2) {
    int x = tetraMinoBro.coordinates[i];
    int y = tetraMinoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 1;
  }
}

void rotate_Tetramino(GameInfo_t* gameInfo) {
  int type_tetramino = gameInfo->tetraMinoBro.type;
  if (type_tetramino == Z || type_tetramino == S) {
    get_tetra_two(&(gameInfo->tetraMinoBro));
    // rotate_90_degrees(gameInfo);
  }
}

void rotate_90_degrees(GameInfo_t* gameInfo) {
  for (int i = 0; i < 8; i += 2) {
    int x = gameInfo->tetraMinoBro.coordinates[i];
    int y = gameInfo->tetraMinoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->field[y][x] = 0;
  }
  int centerX = gameInfo->tetraMinoBro.coordinates[0];
  int centerY = gameInfo->tetraMinoBro.coordinates[1];

  for (int i = 0; i < 4; ++i) {
    int x = gameInfo->tetraMinoBro.coordinates[2 * i];
    int y = gameInfo->tetraMinoBro.coordinates[2 * i + 1];

    // Сдвиг в начало координат
    int translatedX = x - centerX;
    int translatedY = y - centerY;

    // Поворот на 90 градусов по часовой стрелке
    int rotatedX = translatedY;
    int rotatedY = -translatedX;

    // Возврат на место
    gameInfo->tetraMinoBro.coordinates[2 * i] = rotatedX + centerX;
    gameInfo->tetraMinoBro.coordinates[2 * i + 1] = rotatedY + centerY;
  }
}

void copy_tetramino(TetraMino_bro* src, TetraMino_bro* dst) {
  *dst = (TetraMino_bro){{0}};
  dst->type = src->type;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dst->coordinates[i * j + j] = src->coordinates[i * j + j];
    }
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
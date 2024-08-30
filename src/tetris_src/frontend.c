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

void initBoard(GameInfo_t* board) {
  board->tetraminoBro = (Tetramino_bro){{0}};
  board->size = 0;
  board->top = 20;
  board->score = 0, board->high_score = get_highScore(), board->level = 0,
  board->pause = 0, board->speed = 0;
  board->field = malloc(sizeof(int*) * ROWS);
  board->next = malloc(sizeof(int*) * ROWS);

  for (int i = 0; i < ROWS; i++) {
    board->field[i] = calloc(COLS, sizeof(int));
    board->next[i] = calloc(COLS, sizeof(int));
  }

  // TODO не забыть чистить память
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
void get_start(GameInfo_t* gameInfo, int type) {
  get_next(gameInfo, type);
  gameInfo->field = gameInfo->next;
}

void get_next(GameInfo_t* gameInfo, int type) {
  // TODO не забыть чистить память

  Tetramino_bro tetraminoBro = {{0}};
  get_Tetramino(&tetraminoBro, type);
  gameInfo->tetraminoBro = tetraminoBro;
  tetramino_into_next(gameInfo, tetraminoBro);
}

void get_Tetramino(Tetramino_bro* tetraminoBro, int type) {
  switch (type) {
    case T:
      *tetraminoBro = (Tetramino_bro){{4, 1, 3, 1, 5, 1, 4, 0}};
      break;
    case O:
      *tetraminoBro = (Tetramino_bro){{4, 1, 4, 0, 5, 1, 5, 0}};
      break;
    case J:
      *tetraminoBro = (Tetramino_bro){{3,1,3,0, 4, 1, 5,1/*0, 0, -1, 0, 0, -1, 0, -2*/}};
      break;
    case L:
      *tetraminoBro = (Tetramino_bro){{5,1,5,0, 4, 1, 3,1/*0, 0, 1, 0, 0, -1, 0, -2*/}};
      break;
    case I:
      *tetraminoBro = (Tetramino_bro){{/*0, 0, 0, 1, 0, -1, 0, -2*/}};
      break;
    case S:
      *tetraminoBro = (Tetramino_bro){{4, 1, 3, 1, 4, 0, 5, 0}};
      break;
    case Z:
      *tetraminoBro = (Tetramino_bro){{4, 1, 5, 1, 4, 0, 3, 0}};
      break;
    default:
      break;
  }
}
void move_tetramino(GameInfo_t* gameInfo, char key) {
  int dx = 0, dy = 0;
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
  }
  for (int i = 0; i < 8; i += 2) {
    int x = gameInfo->tetraminoBro.coordinates[i];
    int y = gameInfo->tetraminoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 0;
  }
  for (int i = 0; i < 8; i += 2) {
    gameInfo->tetraminoBro.coordinates[i] += dx;
    gameInfo->tetraminoBro.coordinates[i + 1] += dy;
  }
  for (int i = 0; i < 8; i += 2) {
    int x = gameInfo->tetraminoBro.coordinates[i];
    int y = gameInfo->tetraminoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 1;
  }
  // tetramino_into_next(gameInfo, gameInfo->tetraminoBro);
}

void tetramino_into_next(GameInfo_t* gameInfo, Tetramino_bro tetraminoBro) {
  for (int i = 0; i < 8; i += 2) {
    int x = tetraminoBro.coordinates[i];
    int y = tetraminoBro.coordinates[i + 1];
    if (x >= 0 && x < COLS && y >= 0 && y < ROWS) gameInfo->next[y][x] = 1;
  }
}

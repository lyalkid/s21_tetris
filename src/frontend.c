#include "frontend.h"
void render(GameInfo_t board) {
  for (int j = 0; j < COLS; j++) {
    printf("%d ", j);
  }
  printf("\n");
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board.field[i][j] == 1) {
        printf("[]");
      } else {
        printf("@@");
      }
    }
    printf("% d\n", i);
  }
}

void initBoard(GameInfo_t* board) {
  board->size = 0;
  board->top = 20;
  board->score = 0, board->high_score = get_highScore(), board->level = 0,
  board->pause = 0, board->speed = 0;
  board->field = malloc(sizeof(int*) * ROWS);
  for (int i = 0; i < ROWS; i++) {
    board->field[i] = calloc(COLS, sizeof(int));
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

void get_next(GameInfo_t* gameInfo, int type) {
  // TODO не забыть чистить память
  gameInfo->next = malloc(sizeof(int*) * ROWS);
  for (int i = 0; i < ROWS; i++) {
    gameInfo->next[i] = calloc(COLS, sizeof(int));
  }
  switch (type) {
    case Z:
      gameInfo->next[1][4] = 1, gameInfo->next[1][3] = 1;
      gameInfo->next[0][4] = 1, gameInfo->next[0][5] = 1;
      break;
    case REVERSE_Z:
      gameInfo->next[1][4] = 1, gameInfo->next[1][5] = 1;
      gameInfo->next[0][4] = 1, gameInfo->next[0][3] = 1;
      break;
    case SQUARE:
      gameInfo->next[1][4] = 1, gameInfo->next[1][5] = 1;
      gameInfo->next[0][4] = 1, gameInfo->next[0][5] = 1;
      break;
    case L:
      gameInfo->next[1][3] = 1, gameInfo->next[0][3] = 1;
      gameInfo->next[1][4] = 1, gameInfo->next[1][5] = 1;
      break;
    case REVERSE_L:
      gameInfo->next[1][3] = 1, gameInfo->next[0][5] = 1;
      gameInfo->next[1][4] = 1, gameInfo->next[1][5] = 1;
      break;
    case T:
      gameInfo->next[1][3] = 1, gameInfo->next[0][4] = 1;
      gameInfo->next[1][4] = 1, gameInfo->next[1][5] = 1;
      break;
    case I:
      gameInfo->next[0][3] = 1;
      gameInfo->next[0][4] = 1;
      gameInfo->next[0][5] = 1;
      gameInfo->next[0][6] = 1;

    default:
      break;
  }
}
void get_start(GameInfo_t* gameInfo, int type){
    get_next(gameInfo, type);
    gameInfo ->field = gameInfo->next;
}

void moving_down(GameInfo_t *gameInfo){

}
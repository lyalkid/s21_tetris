#include "backend.h"

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
  int** tmp_next = malloc_array(ROWS + 1, COLS);
  move_tetramino(&tetraMino, tmp_next, key);
  /*
   * нужно подвинуть tetramino , перевести в tmp_next, чекнуть нет ли коллизий.
   * если все ок, то вернуть OK, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, ROWS + 1);
}
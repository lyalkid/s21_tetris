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
    int is_all_ok = is_all_ok_bro(field, tmp_next);

    move_tetramino(&tetraMino, tmp_next, key, &is_all_ok);
  tetra_to_next(tetraMino, tmp_next);

  /*
   * нужно подвинуть tetramino , перевести в tmp_next, чекнуть нет ли коллизий.
   * если все ок, то вернуть OK, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, ROWS + 1);
  return is_all_ok;
}
int is_all_ok_bro(int** field, int** next) {
  int is_all_ok = OK;
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      int n_tmp = next[i][j];

      int f_tmp = field[i][j];
      int res = n_tmp + f_tmp;
      if (res> 1) {
        is_all_ok = ERROR;
        break;
      }

    }
    if (is_all_ok == ERROR) break;
  }
  return is_all_ok;
}
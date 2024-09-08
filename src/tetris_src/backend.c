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
  int** tmp_next = malloc_array(ROWS_EXTENDED, COLS);
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
   * если все ок, то вернуть OK, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, ROWS_EXTENDED);
  return is_all_ok;
}

int can_i_rotate(TetraMino_bro tetraMino, int** field) {
  int** tmp_next = malloc_array(ROWS_EXTENDED, COLS);
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
   * если все ок, то вернуть OK, если не ок, то вернуть ERROR
   * */
  free_array(tmp_next, ROWS_EXTENDED);
  return is_all_ok;
}
int is_all_ok_bro(int** field, int** next) {
  int is_all_ok = OK;
  for (int i = 0; i < ROWS_EXTENDED; i++) {
    for (int j = 0; j < COLS; j++) {
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

// void scan_bro(int** field, int rows, int cols) {
//     int full_scan = 0;
//     while(full_scan != 2) {
//         for(int i = rows-1; i >= 0; i--){
//             int destroy = to_be_destroyed(field[i], cols);
//             if(destroy == YES){
//                 destruction(field, rows, cols, i);
//             }
//         }
//         full_scan++;
//     }
// }
//
// int to_be_destroyed(int a[], int size){
//
//     int sum = 0;
//     for(int i = 0; i < size; i++){
//         if(a[i] == 1) sum++;
//     }
//     return sum == size ? YES : NO;
// }
//
// void destruction(int** field, int rows, int cols, int row_not_bro){
//     for(int i = 0; i< cols; i++){
//         field[row_not_bro][i] =0;
//     }
//     for(int i = row_not_bro ; i >0; i--){
//         int tmp[cols];
//     }
// }
//
// void copy_array(int from[], int to[], int size_from, int size_to) {
//     int *pA = from;
//     int *pB = to;
//     for (int i = 0; i < size_from; i++) {
//         *(pB + i) = *(pA + i);
//     }
//     if (size_to > size_from) {
//         for (int i = size_from; i < size_to; i++) {
//             to[i] = 0;
//         }
//     }
// }
// void init_array(int a[], int n) {
//     for (int i = 0; i < n; i++) {
//         a[i] = 0;
//     }
// }
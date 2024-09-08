#ifndef BACKEND_H
#define BACKEND_H
#include "frontend.h"

enum answer { YES, NO };

int can_i_move(TetraMino_bro tetraMino, int** field, char key);
int can_i_shift();
int can_i_rotate(TetraMino_bro tetraMino, int** field);
int** malloc_array(int rows, int cols);
void free_array(int** field, int rows);

void scan_bro(int** field, int rows, int cols);
int to_be_destroyed(int a[], int size);
void copy_array(int from[], int to[], int size_from, int size_to);
void init_array(int a[], int n);
void destruction(int** field,  int cols, int row_not_bro);
#endif  // BACKEND_H
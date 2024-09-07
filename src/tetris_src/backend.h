#ifndef BACKEND_H
#define BACKEND_H
#include "frontend.h"

int can_i_move(TetraMino_bro tetraMino, int** field, char key);
int can_i_shift();
int** malloc_array(int rows, int cols);
void free_array(int** field, int rows);

#endif  // BACKEND_H
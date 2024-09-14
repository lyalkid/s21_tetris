#ifndef BACKEND_H_
#define BACKEND_H_
#include <stdlib.h>
#include <stdbool.h>
#include "objects.h"
#include "defines.h"

// HEAD OF OLD BACKEND
enum answer { YES, NO };

int can_i_move(TetraMino_bro tetraMino, int** field, char key);
int can_i_shift();
int can_i_rotate(TetraMino_bro tetraMino, int** field);
int** malloc_array(int rows, int cols);
void free_array(int** field, int rows);

void scan_bro(int** field, int rows, int cols);
int to_be_destroyed(const int a[], int size);
void copy_array(int from[], int to[], int size_from, int size_to);
void init_array(int a[], int n);
void destruction(int** field, int cols, int row_not_bro);
int is_all_ok_bro(int **field, int **next);

// END OF OLD BACKEND


// from front
void get_TetraMino(TetraMino_bro *tetraMinoBro);
void get_tetra_two(TetraMino_bro *tetraminoBro);
void get_tetra_four(TetraMino_bro *tetraMinoBro);
TetraMino_bro get_new_tetraMino(int type);
void setCoordinates(int *coordinates, const int *values);

void tetra_to_next(TetraMino_bro tetraMinoBro, int **next);
int get_min(int a, int b);

int get_max(int a, int b);
int is_rotate_possible(TetraMino_bro tetraMinoBro, int rotate);


void move_tetramino(TetraMino_bro *tetraMinoBro, int **next, char key);
void rotate_TetraMino(TetraMino_bro *tetraMinoBro);


int get_random();
int get_highScore();
void start_initialization(GameInfo_t *gameInfo, int type);
int next_to_field(int **next, int **field);


int is_down_possible(TetraMino_bro tetraMinoBro, int **field, int **next);

//

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();
#endif // BACKEND_H_

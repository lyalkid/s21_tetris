#ifndef BACKEND_H_
#define BACKEND_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

// HEAD OF OLD BACKEND
enum answer { YES, NO };
void out(int **tmp_next);
int can_i_move(TetraMino_bro tetraMino, int **field, char key);
int can_i_shift();
int can_i_rotate(TetraMino_bro tetraMino, int **field);
int **malloc_array(int rows, int cols);
void free_array(int **field, int rows);

void scan_bro(int **field, int rows, int cols);
int to_be_destroyed(const int a[], int size);

void destruction(int **field, int cols, int row_not_bro);
int is_all_ok_bro(int **field, int **next);
int is_it_board(int **next);

TetraMino_bro init_empty_tetraMino();
GameInfo_t init_empty_gameInfo();
Game_Objects_t init_empty_game_objects();

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

Game_Objects_t *get_game_instance();

void shift(GameInfo_t gameInfo, char *key);
int is_down_possible(TetraMino_bro tetraMinoBro, int **field, int **next);

//

#endif  // BACKEND_H_

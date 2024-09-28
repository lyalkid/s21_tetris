#ifndef BACKEND_H_
#define BACKEND_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

enum answer { YES, NO };
int can_i_move(TetraMino_bro tetraMino, int **field, UserAction_t key);
int **malloc_array(int rows, int cols);
void free_array(int **field, int rows);

int scan_bro(int **field, int rows, int cols);
int to_be_destroyed(const int a[], int size);
int calc_score(int lines);
int calc_level(int current_score);
void game_mechanics(Game_Objects_t *params);

void destruction(int **field, int cols, int row_not_bro);
int is_all_ok_bro(int **field, int **next);

TetraMino_bro init_empty_tetraMino();
GameInfo_t init_empty_gameInfo();
void deleteGame(GameInfo_t *gameInfo, TetraMino_bro *tetraMino);
Game_Objects_t init_empty_game_objects();
void get_TetraMino(int coordinates[], int rotate, int type);
void get_tetra_two(int coordinates[], int rotate, int type);
void get_tetra_four(int coordinates[], int rotate, int type);
void get_new_tetraMino(TetraMino_bro *tetraMinoBro);
void setCoordinates(int *coordinates, const int *values);

void tetra_to_array(TetraMino_bro tetraMinoBro, int **next);

int get_min(int a, int b);
int get_max(int a, int b);
int is_rotate_possible(TetraMino_bro tetraMinoBro, int rotate);

void move_tetraMino(TetraMino_bro *tetraMinoBro, UserAction_t key);
void move_down_tetraMino(TetraMino_bro *tetraMinoBro);
void move_up_tetraMino(TetraMino_bro *tetraMinoBro);
int check_collision(TetraMino_bro tetraMinoBro, int **field);

void rotate_TetraMino(TetraMino_bro *tetraMinoBro);

int get_random();
int get_highScore();
void write_high_score(int h_score);
int next_to_field(int **next, int **field);

Game_Objects_t *get_game_instance();

int is_time_to_shift(struct timeval before, struct timeval after,
                     suseconds_t timer);
int is_it_legal_mv(UserAction_t userAction);

int is_it_illegal_mv(UserAction_t userAction);

#endif  // BACKEND_H_

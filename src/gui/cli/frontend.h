#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdio.h>

#include "../../brick_game/tetris/inc/backend.h"
#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void show_game_field(int** field, int** next, int score, int level);

void draw_simple(State state, GameInfo_t gameInfo, TetraMino_bro tetraMinoBro);

void init_bro_ncurses(View_bro* views);
void init_bro_colors();
void terminate_ncurses_bro(View_bro* views);

void render_game_win(WINDOW* win, int** field, int** next);

void render_next_win(WINDOW* next_win, int type);
void render_info_win(WINDOW* info_win, int h_score, int score, int level,
                     int count[]);
char piece(int type);

void render_pause(WINDOW* game_field);

void draw_static(Game_Objects_t* params);
void draw_main(Game_Objects_t* params);
void game_over(WINDOW* game_win);
void print_main_menu(WINDOW* game_field);
void printw_state(State state);
#endif  // FRONTEND_H
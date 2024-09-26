#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdio.h>

#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void init_bro_ncurses();
void terminate_ncurses_bro(WINDOW* game_field, WINDOW* info_game,
                           WINDOW* next_tetraMino);
void render_gui(int** field, int** next, int score, int level);
void render_game_win(WINDOW* win, int** field, int** next);
void draw_main(Game_Objects_t* gameObjects, WINDOW* game_field,
               WINDOW* info_field, WINDOW* next_field);
void game_over(int score, int level);
void print_main_menu(Game_Objects_t* gameObjects, WINDOW* game_field);
#endif  // FRONTEND_H
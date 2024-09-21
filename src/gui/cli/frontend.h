#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdio.h>

#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void init_bro_ncurses();
void terminate_ncurses_bro();
void render_gui(int** field, int** next, int score);
void render_simple(Game_Objects_t* gameObjects);
void show_game_field(int** field, int** next, int score, int level);
void print_main_menu(Game_Objects_t* gameObjects);
#endif  // FRONTEND_H
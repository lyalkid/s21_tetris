#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdio.h>

#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void render_gui(GameInfo_t board);
void render_simple(Game_Objects_t* gameObjects);
void show_game_field(int** field, int** next);
void print_main_menu(Game_Objects_t* gameObjects);
#endif  // FRONTEND_H
#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define TIME 50000

#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void render_gui(GameInfo_t board);
void render_simple(GameInfo_t board);

#endif  // FRONTEND_H
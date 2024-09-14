#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../brick_game/tetris/inc/defines.h"
#include "../../brick_game/tetris/inc/objects.h"

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

void render(GameInfo_t board);

void out(int **tmp_next);
#endif  // FRONTEND_H
#ifndef FRONT_DEBUG_H_
#define FRONT_DEBUG_H_
#include "../inc/defines.h"
#include "../inc/objects.h"

void show_game_field(int** field, int** next, int score, int level);

void draw_simple(State_t state, GameInfo_t gameInfo,
                 TetraMino_bro tetraMinoBro);

#endif  // FRONT_DEBUG_H_
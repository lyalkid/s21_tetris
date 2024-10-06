#ifndef FSM_MAIN_H_
#define FSM_MAIN_H_

#include "backend.h"

void main_game_fsm(Game_Objects_t* params, State* prev);
void onStatic(Game_Objects_t* params);

void fsm_game_session(Game_Objects_t* params);
void onStart(Game_Objects_t* params);
int onSpawn(Game_Objects_t* params);
void is_game_over(Game_Objects_t* params, int status);
void onMove(Game_Objects_t* params);
void onMoving(Game_Objects_t* params);
void onMoving_down(Game_Objects_t* params);
void onMoving_pro_down(Game_Objects_t* params);
State onShifting(Game_Objects_t* params);
void onAttaching(Game_Objects_t* params);

void userInput(UserAction_t action, bool hold);

GameInfo_t updateCurrentState();

Game_Objects_t* get_instanse();

UserAction_t getSignal(int user_input);

#endif  // FSM_MAIN_H_
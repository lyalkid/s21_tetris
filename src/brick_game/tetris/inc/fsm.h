#ifndef FSM_H_
#define FSM_H_
#include "defines.h"
#include "objects.h"

void main_fsm(Game_Objects_t* params);

void main_menu(Game_Objects_t* params);
void onStart_state(Game_Objects_t* params);
void onSpawn(Game_Objects_t* params);
void onMoving(Game_Objects_t* params);
void onShifting(Game_Objects_t* params);
void onAttaching(Game_Objects_t* params);
void onGame_over(Game_Objects_t* params);
void onExit_state(Game_Objects_t* params);
void onCheck_destroy(Game_Objects_t* params);
void onDestroy_state(Game_Objects_t* params);
void onCheck_game_over(Game_Objects_t* params);
void onPause_state(Game_Objects_t* params);
UserAction_t getSignal(int user_input);
void move_brother(Game_Objects_t* params, char key);
void main_move(Game_Objects_t* params, char key);

// void userInput(UserAction_t action);
GameInfo_t updateCurrentState();
#endif  // FSM_H_
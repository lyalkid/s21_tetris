#ifndef FSM_H_
#define FSM_H_
#include "defines.h"
#include "objects.h"

void main_fsm(Game_Objects_t* game_params, WINDOW* game_field,
              WINDOW* info_field, WINDOW* next_field);

void main_menu(Game_Objects_t* params);
void onStart_state(Game_Objects_t* params);
void onSpawn(Game_Objects_t* params);
void onMoving_legal(Game_Objects_t* params);
void onMoving_down(Game_Objects_t* params);

void onShifting(Game_Objects_t* params);
void onAttaching(Game_Objects_t* params);
void onGame_over(Game_Objects_t* params);
void onExit_state(Game_Objects_t* params);
void onPause_state(Game_Objects_t* params);
UserAction_t getSignal(int user_input);

// void move_brother(Game_Objects_t* params);
// void main_move(Game_Objects_t* params);

// void userInput(UserAction_t action);
GameInfo_t updateCurrentState();
void pause_bro(Game_Objects_t* params, State_t prev, WINDOW* game_field,
               WINDOW* info_field, WINDOW* next_field);

#endif  // FSM_H_
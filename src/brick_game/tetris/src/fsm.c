#include "../inc/fsm.h"

void main_menu(Game_Objects_t* params, char key) {
  *params = init_empty_game_objects();
  switch (key) {
    case 'n':
      params->userAction = Start;
      break;
    case 'q':
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
  }
}

void onStart_state(Game_Objects_t* params) {
  switch (params->userAction) {
    case Start:
      params->userAction = S
  }
}
void onSpawn(Game_Objects_t* params) {}
void onMoving(Game_Objects_t* params) {}
void onShifting(Game_Objects_t* params) {}
void onAttaching(Game_Objects_t* params) {}

void onGame_over(Game_Objects_t* params) {}

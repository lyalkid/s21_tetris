#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/inc/backend.h"
#include "../brick_game/tetris/inc/fsm_main.h"

#define SHOW_FAILED 1

START_TEST(s21_tetris_test_1) {
  Game_Objects_t *params = get_instanse();
  *params = init_empty_game_objects();

  ck_assert_ptr_ne(&params->gameInfo.field, NULL);
  deleteGame(&params->gameInfo, &params->tetraMinoBro);
  free(params);
  ck_assert_ptr_nonnull(params->gameInfo.field);
  ck_assert_ptr_nonnull(params->gameInfo.next);
  ck_assert_ptr_nonnull(params->tetraMinoBro.tmp_current_figure_on_field);
}
END_TEST

START_TEST(s21_tetris_test_2) {
  int coord[8] = {};
  for (int i = 0; i < MY_ROWS; i++) {
    for (int j = 0; j < MY_COLS; j++) {
      for (int r = 0; r < 4; r++) {
        get_TetraMino(coord, r, get_random(7));
      }
    }
  }
  int sum = 0;
  for (int i = 0; i < 8; i++) {
    if (coord[i] == 1) sum++;
  }
  ck_assert_int_ne(sum, 0);
}
END_TEST

START_TEST(s21_tetris_test_3) {
  TetraMino_bro tetraMinoBro = init_empty_tetraMino();
  int count = 1;
  while (count != 8) {
    // printf("cool\n");
    get_new_tetraMino(&tetraMinoBro);
    if (tetraMinoBro.type == count) count++;
  }
  TetraMino_bro tetraMinoBro2 = tetraMinoBro;
  move_tetraMino(&tetraMinoBro, Up);
  move_tetraMino(&tetraMinoBro, Left);
  ck_assert_int_eq(tetraMinoBro.center_x, tetraMinoBro2.center_x - 1);
  move_tetraMino(&tetraMinoBro, Right);
  ck_assert_int_eq(tetraMinoBro.center_x, tetraMinoBro2.center_x);
  get_TetraMino(tetraMinoBro.coordinates, COMPLETE, T);
  get_TetraMino(tetraMinoBro2.coordinates, COMPLETE, T);

  move_tetraMino(&tetraMinoBro, Action);

  ck_assert_int_eq(tetraMinoBro.type, tetraMinoBro2.type);
  ck_assert_int_ne(tetraMinoBro.rotate, tetraMinoBro2.rotate);

  // ck_assert_int_ne(sum, 0);
}
END_TEST

START_TEST(s21_tetris_test_4) {
  write_high_score(0);
  Game_Objects_t *params = get_instanse();
  // UserAction_t actions[5] = {Left, Right, Up, Down, Action};
  params->gameInfo.level = 0;
  int count = 0;
  int border = 15;
  while (count != 1) {
    bool hold = false;
    count++;
    *params = init_empty_game_objects();
    params->state = START;
    fsm_game_session(params);
    for (int i = 0; i < MY_ROWS; i++) {
      for (int j = 0; j < MY_COLS; j++) {
        if (i <= 19 && i > border && j != 9) {
          params->gameInfo.field[i][j] = 1;
        }
      }
    }
    border--;

    while (params->tetraMinoBro.next_type != I) {
      get_new_tetraMino(&params->tetraMinoBro);
    }
    fsm_game_session(params);
    for (int i = 0; i < 3; i++) {
      userInput(getSignal('s'), hold);
      params->timer.time_to_shift = true;

      fsm_game_session(params);
    }
    userInput(getSignal('w'), hold);
    params->state = MOVE;
    fsm_game_session(params);
    for (int i = 0; i < 5; i++) {
      userInput(getSignal('d'), hold);
      params->state = MOVE;
      // params->timer.time_to_shift = true;

      fsm_game_session(params);
    }
    move_up_tetraMino(&params->tetraMinoBro);
    tetra_to_array(params->tetraMinoBro,
                   params->tetraMinoBro.tmp_current_figure_on_field);
    while (params->state != ATTACHING) {
      params->timer.time_to_shift = true;

      fsm_game_session(params);
      userInput(getSignal('f'), hold);
    }
    fsm_game_session(params);
    //  write_high_score(params->gameInfo.score);
    ck_assert_int_eq(params->gameInfo.score, 1500);
    ck_assert_int_eq(params->gameInfo.level, 2);
    while (params->state != GAME_OVER) {
      params->timer.time_to_shift = true;

      fsm_game_session(params);
    }
    ck_assert_int_eq(params->state, GAME_OVER);
  }
}
END_TEST

START_TEST(s21_tetris_test_5) {
  Game_Objects_t *params = get_instanse();
  *params = init_empty_game_objects();
  bool hold = false;
  int count = 0;
  int ckk = 0;

  State prev = START;
  params->game_is_running = true;
  while (params->game_is_running) {
    main_game_fsm(params, &prev);
    while (params->userAction != Start && params->userAction != Terminate) {
      if (ckk <= 1) {
        userInput(getSignal('n'), hold);

        ckk++;
      } else {
        userInput(getSignal('q'), hold);
      }
    }
    main_game_fsm(params, &prev);

    if (params->game_is_running == false) {
      break;
    }
    if (params->state == START) {
      hold = true;
      params->state = prev;
    }

    while (params->state != PAUSE && params->state != GAME_OVER &&
           params->state != MAIN_MENU) {
      fsm_game_session(params);
      if (params->state == MOVE) {
        if (ckk <= 1) {
          params->userAction = Pause;
          prev = params->state;
          params->state = PAUSE;
          params->userAction = NONE_ACTION;
        }
        params->userAction = Terminate;
        if (params->userAction == Terminate) {
          params->state = MAIN_MENU;
          params->userAction = NONE_ACTION;
          ckk++;
        }
      }
      count++;
    }
  }
  ck_assert_int_eq(params->game_is_running, false);
  free(params);
}
END_TEST
Suite *s21_tetris_suite_create() {
  Suite *suite = suite_create("s21_tetris_test");
  TCase *tc_core = tcase_create("tcase_core_s21_tetris_test");

  tcase_add_test(tc_core, s21_tetris_test_1);
  tcase_add_test(tc_core, s21_tetris_test_2);
  tcase_add_test(tc_core, s21_tetris_test_3);
  tcase_add_test(tc_core, s21_tetris_test_4);
  tcase_add_test(tc_core, s21_tetris_test_5);

  suite_add_tcase(suite, tc_core);

  return suite;
}

int main() {
  int failed_count = 0;

  Suite *suite = s21_tetris_suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  return failed_count != 0 && !SHOW_FAILED ? EXIT_FAILURE : EXIT_SUCCESS;
}

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
        get_TetraMino(coord, r, get_random());
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
  int count = 0;
  while (count != 7) {
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

Suite *s21_tetris_suite_create() {
  Suite *suite = suite_create("s21_tetris_test");
  TCase *tc_core = tcase_create("tcase_core_s21_tetris_test");

  tcase_add_test(tc_core, s21_tetris_test_1);
  tcase_add_test(tc_core, s21_tetris_test_2);
  tcase_add_test(tc_core, s21_tetris_test_3);

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

#include "frontend.h"
void render(GameInfo_t board) {
    for (int j = 0; j < COLS; j++) {
        printf("%d", j);
    }
    printf("\n");
    for (int i = 0; i < ROWS_EXTENDED; i++) {
        for (int j = 0; j < COLS; j++) {
            int res = board.field[i][j] + board.next[i][j];
            if (res == 1) {
                printf("[]");
            } else if (res > 1) {
                printf("@@");
            } else {
                printf("  ");
            }
        }
        printf("% d\n", i);
    }
}

void out(int** tmp_next) {
    for (int j = 0; j < COLS; j++) {
        printf("%d", j);
    }
    printf("\n");
    for (int i = 0; i < ROWS_EXTENDED; i++) {
        for (int j = 0; j < COLS; j++) {
            int res = tmp_next[i][j];
            if (res == 1) {
                printf("*");
            } else if (res > 1) {
                printf("@");
            } else {
                printf("`");
            }
        }
        printf("% d\n", i);
    }
}
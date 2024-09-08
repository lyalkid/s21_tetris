#include <stdio.h>
#include <stdlib.h>
int main() {
  int n = 20;
  int m = 10;
  int** b = malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    b[i] = calloc(m, sizeof(int));
  }
  int k = 0;
  int a[] = {0, 0, 0, -1, 0, 1, 1, 1};
  // int a[] = {-1, -1, 0, -1, 1, -1, 2, -1};

  int dx = 4;
  int dy = 1;
  for (int i = 0; i < 8; i += 2) {
    int x = a[i] + dx;
    int y = a[i + 1] + dy;
    if (x >= 0 && x < n && y >= 0 && y < m) b[y][x] = 1;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((b[i][j] == 1)) {
        printf("*");
      } else {
        printf("`");
      }
    }
    printf("\n");
  }
}
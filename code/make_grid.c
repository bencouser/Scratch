#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 8
#define COLS 8
#define BOMB_COUNT 8

void print_grid(int grid[ROWS][COLS], int rows, int cols) {
  // Print the array to verify initialization
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      printf("%d ", grid[i][j]);
    }
    printf("\n");
  }
}

void place_bombs(int grid[ROWS][COLS], int rows, int cols) {
  int random_row;
  int random_col;
  int bombs_placed = 0;

  // Initialise random number generator with time
  srand(time(NULL));

  // Place bombs
  while (bombs_placed <= BOMB_COUNT - 1) {
    random_row = rand() % (ROWS);
    random_col = rand() % (COLS);
    if (grid[random_row][random_col] != 9) {
      grid[random_row][random_col] = 9;
      bombs_placed++;
      // Add 1 to all surrounding cells
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          int new_row = random_row + i;
          int new_col = random_col + j;
          if (new_row >= 0 && new_row < rows && new_col >= 0 &&
              new_col < cols && grid[new_row][new_col] != 9) {
            grid[new_row][new_col]++;
          }
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int grid[ROWS][COLS] = {0};

  // Place bombs
  place_bombs(grid, ROWS, COLS);

  // Print grid
  print_grid(grid, ROWS, COLS);

  return 0;
}

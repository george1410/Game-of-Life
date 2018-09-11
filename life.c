/* Implementation of Conway's Game of Life ('Life') */
/* George McCarron 2018 */
/* Implements rules as stated at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life */

#include <stdio.h>
#include <stdlib.h>

int rows = 20;
int cols = 60;

int getCell(int* grid, int x, int y) {
    return *(grid + y*cols + x);
}

void setCell(int* grid, int x, int y, int val) {
    *(grid + y*cols + x) = val;
}

void printGrid(int* grid) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (getCell(grid, j, i) == 0) {
                printf(" ");
            } else {
                printf("*");
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    int* grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));

    setCell(grid, 1, 1, 1);
    setCell(grid, 1, 2, 1);
    setCell(grid, 1, 3, 1);

    printGrid(grid);

    free(grid);
    return 0;
}

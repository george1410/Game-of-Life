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

int main(int argc, char* argv[]) {
    int* grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));
    
    free(grid);
    return 0;
}

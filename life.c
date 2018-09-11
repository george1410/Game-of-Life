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

void clearScreen() {
    int i;
    for (i = 0; i < 10; i++) {
        printf("\n\n\n\n\n\n\n\n\n\n");
    }
}

int countSurrounding(int* grid, int x, int y) {
    int i, j;
    int count = 0;
    for (i = y-1; i <= y+1; i++) {
        for (j = x-1; j <= x+1; j++) {
            if (i >= 0 && i < cols && j >= 0 && j < rows && !(i == y && j == x) && getCell(grid, i, j) == 1) {
                count++;
            }
        }
    }
    return count;
}

void evolve(int* grid) {
    int* next = (int*) calloc(rows*cols, rows * cols * sizeof(int));
    int i, j;
    int count;
    int val;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            val = getCell(grid, x, y);
            count = countSurrounding(grid, j, i);
            if (val == 1 && count < 2) {
                setCell(next, j, i, 0);
            } else if (val == 1 && count > 3) {
                setCell(next, j, i, 0);
            } else if (val == 1) {
                setCell(next, j, i, 1);
            } else if (val == 0 && count == 3) {
                setCell(next, j, i, 1);
            } else {
                setCell(next, j, i, 0);
            }
        }
    }
    
    memcpy(grid, next, cols*rows*sizeof(*grid));
    free(next);
}

int main(int argc, char* argv[]) {
    int* grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));

    setCell(grid, 1, 1, 1);
    setCell(grid, 1, 2, 1);
    setCell(grid, 1, 3, 1);

    clearScreen();
    printGrid(grid);

    free(grid);
    return 0;
}

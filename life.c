/* Implementation of Conway's Game of Life ('Life') */
/* George McCarron 2018 */
/* Implements rules as stated at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int rows = 20;
int cols = 60;

int getCell(int* grid, int x, int y) {
    return *(grid + y*cols + x);
}

void dead(int* grid, int x, int y) {
    *(grid + y*cols + x) = 0;
}

void alive(int* grid, int x, int y) {
    *(grid + y*cols + x) = 1;
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
            if (i >= 0 && i < cols && j >= 0 && j < rows && !(i == y && j == x) && getCell(grid, j, i) == 1) {
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
            val = getCell(grid, j, i);
            count = countSurrounding(grid, j, i);
            if (val == 1 && count < 2) {
                dead(next, j, i);
            } else if (val == 1 && count > 3) {
                dead(next, j, i);
            } else if (val == 1) {
                alive(next, j, i);
            } else if (val == 0 && count == 3) {
                alive(next, j, i);
            } else {
                dead(next, j, i);
            }
        }
    }
    
    memcpy(grid, next, cols*rows*sizeof(*grid));
    free(next);
}

int main(int argc, char* argv[]) {
    int* grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));
    struct timespec ts = {
        0, 
        500000000L 
    };

    alive(grid, 1, 1);
    alive(grid, 1, 3);
    alive(grid, 2, 3);
    alive(grid, 3, 3);
    alive(grid, 3, 2);

    while (1) {
        clearScreen();
        printGrid(grid);
        evolve(grid);
        nanosleep (&ts, NULL);
    }

    free(grid);
    return 0;
}

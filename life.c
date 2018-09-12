/* Implementation of Conway's Game of Life ('Life') */
/* George McCarron 2018 */
/* Implements rules as stated at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int rows = 20;
int cols = 60;
int* grid;
int* next;

int getCell(int x, int y) {
    return *(grid + y*cols + x);
}

void alive(int x, int y) {
    *(grid + y*cols + x) = 1;
}

void deadN(int x, int y) {
    *(next + y*cols + x) = 0;
}

void aliveN(int x, int y) {
    *(next + y*cols + x) = 1;
}

void printGrid() {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (getCell(j, i) == 0) {
                printf(" ");
            } else {
                printf("*");
            }
        }
    }
}

void clearScreen() {
    int i;
    for (i = 0; i < 10; i++) {
        printf("\n\n\n\n\n\n\n\n\n\n");
    }
}

int countSurrounding(int x, int y) {
    int i, j;
    int count = 0;
    for (i = y-1; i <= y+1; i++) {
        for (j = x-1; j <= x+1; j++) {
            if (i >= 0 && i < cols && j >= 0 && j < rows && !(i == y && j == x) && getCell(j, i) == 1) {
                count++;
            }
        }
    }
    return count;
}

void evolve() {
    next = (int*) calloc(rows*cols, rows * cols * sizeof(int));
    int i, j;
    int count;
    int val;
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            val = getCell(j, i);
            count = countSurrounding(j, i);
            if (val == 1 && count < 2) {
                deadN(j, i);
            } else if (val == 1 && count > 3) {
                deadN(j, i);
            } else if (val == 1) {
                aliveN(j, i);
            } else if (val == 0 && count == 3) {
                aliveN(j, i);
            } else {
                deadN(j, i);
            }
        }
    }
    
    memcpy(grid, next, cols*rows*sizeof(*grid));
    free(next);
}

int main(int argc, char* argv[]) {
    grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));
    struct timespec ts = {
        0, 
        500000000L 
    };

    alive(1, 1);
    alive(1, 3);
    alive(2, 3);
    alive(3, 3);
    alive(3, 2);

    while (1) {
        clearScreen();
        printGrid();
        evolve();
        nanosleep (&ts, NULL);
    }

    free(grid);
    return 0;
}

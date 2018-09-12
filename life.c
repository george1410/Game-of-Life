/* Implementation of Conway's Game of Life ('Life') */
/* George McCarron 2018 */
/* Implements rules as stated at: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>

int rows;
int cols;
int* grid;
int* next;
struct timespec ts = {
        0, 
        200000000L 
};

int getCell(int x, int y) {
    return *(grid + y*cols + x);
}

void initial(int x, int y) {
    *(grid + y*cols + x) = 1;
}

void dead(int x, int y) {
    *(next + y*cols + x) = 0;
}

void alive(int x, int y) {
    *(next + y*cols + x) = 1;
}

void initialise() {
    int i, j;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    rows = w.ws_row - 1;
    cols = w.ws_col / 2;
    grid = (int*) calloc(rows*cols, rows * cols * sizeof(int));

    srand(time(NULL));

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j ++) {
            if (rand() % 2) {
                initial(j, i);
            }
        }
    }
}

void clearScreen() {
    int i;

    for (i = 0; i <= rows; i++) {
        printf("\n");
    }
}

void printGrid() {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (getCell(j, i) == 0) {
                printf("%2s", "");
            } else {
                printf("%2s", "*");
            }
        }
        printf("\n");
    }
}

int countSurrounding(int x, int y) {
    int i, j;
    int count = 0;

    for (i = y-1; i <= y+1; i++) {
        for (j = x-1; j <= x+1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == y && j == x) && getCell(j, i)) {
                count++;
            }
        }
    }
    return count;
}

void evolve() {
    int i, j;
    int count;
    int val;
    
    next = (int*) calloc(rows * cols, rows * cols * sizeof(int));
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            val = getCell(j, i);
            count = countSurrounding(j, i);
           
           // This is where the Game of Life rules are actually implemented
            if ((val && (count == 2 || count == 3)) || (!val && count == 3)) {
                alive(j, i);
            } else {
                dead(j, i);
            }
        }
    }
    memcpy(grid, next, cols * rows * sizeof(*grid));
    free(next);
}

int main(int argc, char* argv[]) {
    initialise();

    while (1) {
        clearScreen();
        printGrid();
        evolve();
        nanosleep (&ts, NULL);
    }    

    free(grid);
    return 0;
}

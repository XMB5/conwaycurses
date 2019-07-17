//
// Created by sam on 7/17/19.
//

#include "logic.h"
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int numNeighborsOn(int y, int x, int height, int width, char (**board)[height][width]) {
    int count = 0;
    for (int ny = max(0, y - 1); ny < height && ny <= y + 1; ny++) {
        for (int nx = max(0, x - 1); nx < width && nx <= x + 1; nx++) {
            if (ny == y && nx == x) continue;
            if ((**board)[ny][nx] == 1) count++;
        }
    }
    return count;
}

void tick(int height, int width, char (**board)[height][width]) {

    char (*boardToBe)[height][width] = malloc(height * width);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int neighbors = numNeighborsOn(y, x, height, width, board);
            if ((**board)[y][x]) {
                //"Any live cell with fewer than two live neighbours dies, as if by underpopulation."
                //"Any live cell with two or three live neighbours lives on to the next generation."
                //"Any live cell with more than three live neighbours dies, as if by overpopulation."
                (*boardToBe)[y][x] = neighbors == 2 || neighbors == 3;
                //printf("y: %d x: %d neighbors: %d -  was 1 will be %d\n", y, x, neighbors, (*boardToBe)[y][x]);
            } else {
                //"Any dead cell with three live neighbours becomes a live cell, as if by reproduction."
                (*boardToBe)[y][x] = neighbors == 3;
            }
        }
    }

    *board = boardToBe;

}
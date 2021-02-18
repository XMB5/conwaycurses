#include <curses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "logic.h"

#define COLOR_SQUARE_OFF 1
#define COLOR_SQUARE_ON 2

int main() {
    srand(time(NULL));
    
    initscr();
    nonl();
    cbreak();
    noecho();
    timeout(0);
    curs_set(0);
    if (!has_colors()) {
        printf("colors not supported, exiting\n");
        return 1;
    }
    start_color();
    init_pair(COLOR_SQUARE_ON, COLOR_WHITE, COLOR_WHITE);
    init_pair(COLOR_SQUARE_OFF, COLOR_BLACK, COLOR_BLACK);

    bkgd(COLOR_PAIR(COLOR_SQUARE_OFF));

    int width, height;
    getmaxyx(stdscr, height, width);
    char (*board)[height][width] = malloc(height * width);
    memset(*board, 0, height * width);
    (*board)[10][40] = 1;
    (*board)[11][40] = 1;
    (*board)[12][40] = 1;
    (*board)[13][40] = 1;
    (*board)[14][40] = 1;

    (*board)[10][44] = 1;
    (*board)[11][44] = 1;
    (*board)[12][44] = 1;
    (*board)[13][44] = 1;
    (*board)[14][44] = 1;

    (*board)[10][42] = 1;
    (*board)[14][42] = 1;


    (*board)[10][11] = 1;

    (*board)[11][12] = 1;

    (*board)[12][10] = 1;
    (*board)[12][11] = 1;
    (*board)[12][12] = 1;

    while(1) {
        int c = getch();
        if (c != ERR) {
            switch (c) {
                case 'q':
                    goto end;
                case 'r':
                    for (int i = 0; i < ((width * height) / 4); i++)
                        (*board)[rand() % height][rand() % width] = 1;
            }
        }
        erase();
        attron(COLOR_PAIR(COLOR_SQUARE_ON));
        for (int y = 0; y < height; y++) {
            char* row = (*board)[y];
            for (int x = 0; x < width; x++) {
                char tile = row[x];
                if (tile) {
                    mvaddch(y, x, ' ');
                }
            }
        }
        refresh();
        tick(height, width, &board);
        usleep(50000);
    }

    end:

    endwin();

    return 0;
}

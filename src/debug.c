#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include "headers.h"

void debug(Player player, Pipes pipes, struct winsize w)
{
    // Get the length of the digits 
    int gapstr_length = snprintf(NULL, 0, "%d", pipes.pipeupendY);
    int gapstr2_length = snprintf(NULL, 0, "%d", pipes.pipedownpeakY);
    int birdstr_length = snprintf(NULL, 0, "%d", player.birdY);
    int counterstr_length = snprintf(NULL, 0, "%d", w.ws_col - pipes.pipeX);
    
    // Allocate enough memory for string of digits + NUL terminator character
    char *gapstr = malloc(gapstr_length + 1), *gapstr2 = malloc(gapstr2_length + 1), *birdstr = malloc(birdstr_length + 1), *counterstr = malloc(counterstr_length + 1);
    
    if (gapstr == NULL || gapstr2 == NULL || birdstr == NULL || counterstr == NULL)
    {
        endwin();
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    
    // Copy integer values to a string and add NUL terminator 
    snprintf(gapstr, gapstr_length + 1, "%d", pipes.pipeupendY);
    snprintf(gapstr2, gapstr2_length + 1, "%d", pipes.pipedownpeakY);
    snprintf(birdstr, birdstr_length + 1, "%d", player.birdY);
    snprintf(counterstr, counterstr_length + 1, "%d", w.ws_col - pipes.pipeX);
    
    // Display string to the screen next to score display
    mvaddstr(0, 3, counterstr);
    mvaddstr(0, 6, gapstr);
    mvaddstr(0, 9, gapstr2);
    mvaddstr(0, 12, birdstr);

    free(gapstr);
    free(gapstr2);
    free(birdstr);
    free(counterstr);
}

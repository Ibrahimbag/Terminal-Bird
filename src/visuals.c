#include <ncurses.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <math.h>
#include "headers.h"

// Print the pipes and the gaps
void printPipe(Pipes *pipes, int pipeX, int *randompipe, struct winsize w)
{
    for (int i = 0; i < w.ws_row; i++)
    {
        if (i == *randompipe)
        {
            mvaddstr(i, w.ws_col - pipeX - 1, "[#]");
            pipes->pipeupendY = i;
            i = i + 4;
            mvaddstr(i, w.ws_col - pipeX - 1, "[#]");
            pipes->pipedownpeakY = i;
        }
        mvaddstr(i, w.ws_col - pipeX, "#");
    }
}

// Controlling of the bird
void printBird(Player *player)
{
    if (player->pressed == ' ')
    {
        player->birdY = player->birdY - 3;
    }
    player->birdY++;
    mvaddstr(player->birdY, 20, "-O>");
}

// Print player's current score in up left corner of the screen 
void printScore(Player *player)
{
    // Get the length of the player's score
    int score_length;
    if ((score_length = floor(log10(abs(player->score))) + 1) == -2147483648) score_length = 1; // floor() function here returns -2147483648 when player->score is 0 so if returned value equals to -2147483648, assign score_length to 1
    
    // Display player's score to screen
    player->score_display = malloc(score_length + 1);
    if (player->score_display == NULL)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    snprintf(player->score_display, score_length + 1, "%d", player->score);
    mvaddstr(0, 0, player->score_display);
}

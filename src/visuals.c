#include "headers.h"
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <sys/ioctl.h>

// Print the pipes and the gaps
void printPipe(Pipes *head, int window_row_size, int window_collumn_size) 
{
    Pipes *ptr = head;
    while (ptr != NULL) 
    {
        for (int i = 0; i < window_row_size; i++) 
        {
            if (i == ptr->pipeupendY) 
            {
                mvaddstr(i, window_collumn_size - ptr->pipeX - 1, "▟██▙");
                i = i + 4;
                mvaddstr(i, window_collumn_size - ptr->pipeX - 1, "▜██▛");
            }
            mvaddstr(i, window_collumn_size - ptr->pipeX, "██");
        }
        ptr = ptr->next;
    }
}

// Controlling of the bird
void printBird(Player *player)
{
    (player->pressed == ' ') ? (player->birdY -= 2) : (player->birdY++);
    mvaddstr(player->birdY, 20, "██");
}

// Print player's current score in up left corner of the screen 
void printScore(Pipes *head, Player *player)
{
    // Get the length of the player's score
    int score_length;
    if ((score_length = floor(log10(abs(player->score))) + 1) == -2147483648) score_length = 1; // floor() function here returns -2147483648 when player->score is 0 so if returned value equals to -2147483648, assign score_length to 1
    
    // Display player's score to screen
    player->score_display = malloc(score_length + 1);
    if (player->score_display == NULL)
    {
        endwin();
        printf("Memory allocation error\n");
        free_list(head);
        exit(EXIT_FAILURE);
    }
    snprintf(player->score_display, score_length + 1, "%d", player->score);
    mvaddstr(0, 0, player->score_display);

    free(player->score_display);
}

void set_color(int color)
{
    init_pair(color, color, -1);
    attrset(COLOR_PAIR(color));
}

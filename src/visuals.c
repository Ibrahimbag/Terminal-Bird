#include "headers.h"
#include <ncurses.h>

// Print the pipes and the gaps
void draw_pipes(Pipes *head, int row_size, int col_size) 
{
    Pipes *ptr = head;
    while (ptr != NULL) 
    {
        for (int i = 0; i < row_size; i++) 
        {
            if (i == ptr->pipe_top_end) 
            {
                attron(COLOR_PAIR(3));
                mvaddstr(i, col_size - ptr->pipe_x - 1, "▟██▙");
                i += 4;
                mvaddstr(i, col_size - ptr->pipe_x - 1, "▜██▛");
                attron(COLOR_PAIR(2));
            }
            mvaddstr(i, col_size - ptr->pipe_x, "  ");
        }
        ptr = ptr->next;
    }
}

// Controlling of the bird
void draw_bird(Player *player)
{
    (player->key == ' ') ? (player->bird_y -= 2) : (player->bird_y++);
    mvaddstr(player->bird_y, 19, "██");
}

// Print player's current score in up left corner of the screen 
void draw_score(Player *player)
{
    attron(A_BOLD);
    mvprintw(0, 0, "%ld", player->score);
}

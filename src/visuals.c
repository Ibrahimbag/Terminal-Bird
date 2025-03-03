#include "configuration.h"
#include "visuals.h"
#include <ncurses.h>

// Controlling of the bird
void draw_bird(Player *player, Pipes *head, int col_size)
{
    Configurations config = configuration();

    int jump_height = config.jump_height;
    if (jump_height < 1 || jump_height > 5)
    {
        jump_height = 2;
    }

    int gravity = config.gravity;
    if (gravity < 1 || gravity > 5)
    {
        gravity = 1;
    }

    if (config.bot)
    {
        // Get the closest pipe next to the bird
        Pipes *closest_pipe = head;
        while (closest_pipe->next != NULL && closest_pipe->pipe_x > col_size - 16)
        {
            closest_pipe = closest_pipe->next;
        }

        // Jump if the pipe is below the bird
        if (player->bird_y > closest_pipe->pipe_bottom_peak - 2)
        {
            player->bird_y -= jump_height;
        }
        else
        {
            player->bird_y += gravity;
        }
    }
    else
    {
        (player->key == config.jump) ? (player->bird_y -= jump_height) : (player->bird_y += gravity);
    }

    attron(COLOR_PAIR(1));
    mvaddstr(player->bird_y, 19, "██");
    attroff(COLOR_PAIR(1));
}

// Print the pipes and the gaps
void draw_pipes(Pipes *head, int row_size, int col_size) 
{
    attron(COLOR_PAIR(2));
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
    attroff(COLOR_PAIR(2));
}

// Print player's current score in up left corner of the screen 
void draw_score(Player *player)
{
    attron(A_BOLD);
    mvprintw(0, 0, "%ld", player->score);
    attroff(A_BOLD);
}

#include "headers.h"
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int window_height, window_width;
static Player player;
static Pipes *head = NULL;

int get_random_position(void);
void game(void);
bool check_for_exit(void);
bool check_terminal_resolution(void);

int main(void)
{
    // Initialize random seed
    srand((unsigned int) time(NULL));
    
    // Initialize ncurses
    setlocale(LC_ALL, "");
    WINDOW *win = initscr();
    noecho();
    curs_set(false);
    nodelay(win, true);
    if (has_colors() == true)
    {
        start_color();
        use_default_colors();
    }

    // Color pairs to be used
    init_pair(1, COLOR_YELLOW, -1); // Bird
    init_pair(2, -1, COLOR_GREEN); // Rest of the pipes exclude the bottom of upper pipe, top of lower pipe.
    init_pair(3, COLOR_GREEN, -1); // Bottom of upper pipe, top of lower pipe.

    // Get the size of the screen
    getmaxyx(win, window_height, window_width);

    // Create the first pipe
    head = first_node(head, get_random_position());

    // Start the game
    while (!check_for_exit())
    {
        getmaxyx(win, window_height, window_width);
        player.key = getch();
        game();        
        usleep(70000);
    }
}

int get_random_position(void)
{
    int random_position = rand() % (window_height - 6) + 1;
    return random_position;
}

void game(void)
{
    // if pipe is in specific position, clone a new pipe heading to the left
    if (new_pipe_available(head, window_width)) 
    {
        new_pipe(head, get_random_position());
    }

    // Print the game elements
    erase();
    attroff(A_BOLD);
    attron(COLOR_PAIR(1));
    draw_bird(&player);
    attron(COLOR_PAIR(2));
    draw_pipes(head, window_height, window_width);
    attroff(COLOR_PAIR(2));
    draw_score(&player);
    refresh();

    // Update the position of pipes
    update_pipe_position(head);

    // Free unused pipes that are out of the screen
    free_list(head, GAME_ONGOING);
}

bool check_for_exit(void)
{
    // Check if terminal resolution is too small
    if (check_terminal_resolution())
    {
        endwin();
        fprintf(stderr, "Terminal resolution too small. Minimun is 12x48.\n");
        free_list(head, GAME_OVER);
        exit(EXIT_FAILURE);
    }

    // Check if user wants to quit or has collided
    if (player.key == 'q' || player.key == 'Q' || bird_collided(head, &player, window_height, window_width))
    {
        usleep(400000);
        endwin();
        printf("Score: %ld\n", player.score);
        free_list(head, GAME_OVER);
        exit(EXIT_SUCCESS);
    }
    return false;
}

// Check if user is using small terminal
bool check_terminal_resolution(void)
{
    if (window_height < 12 || window_width < 48)
    {
        return true;
    }
    return false;
}

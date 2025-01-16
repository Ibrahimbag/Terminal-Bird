#include "headers.h"
#include "leaderboard_db.h"
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

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

    // Initialize leaderboard database
    db_execute(CREATE, NULL, -1);

    // Get the window size
    getmaxyx(win, window_height, window_width);

    // Display the main menu
    main_menu(window_height, window_width);

    // Color pairs to be used
    init_pair(1, COLOR_YELLOW, -1); // Bird
    init_pair(2, -1, COLOR_GREEN); // Rest of the pipes exclude the bottom of upper pipe, top of lower pipe.
    init_pair(3, COLOR_GREEN, -1); // Bottom of upper pipe, top of lower pipe.

    // Create the first pipe
    head = first_node(head, get_random_position());

    // Start the game
    struct timespec remaining, request = {0, 70000000}; 
    while (!check_for_exit())
    {
        getmaxyx(win, window_height, window_width);
        player.key = getch();
        game();       
        nanosleep(&request, &remaining);
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
    draw_bird(&player);
    draw_pipes(head, window_height, window_width);
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

    // Check if user wants to quit while game is running
    if (tolower(player.key) == 'q')
    {
        free_list(head, GAME_OVER);
        endwin();
        return true;
    }

    // If bird collided to somewhere, display game over screen
    else if (bird_collided(head, &player, window_height, window_width))
    {
        int ret = game_over_menu(window_height, window_width, player.score);
        free_list(head, GAME_OVER);

        if (ret == GAME_RESTART)
        {
            player.score = 0;
            player.bird_y = window_height / 2;
            head = first_node(head, get_random_position());
            return false;
        }
        else if (ret == GAME_OVER)
        {
            endwin();
            printf("Score: %lu\n", player.score);
            return true;
        }
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

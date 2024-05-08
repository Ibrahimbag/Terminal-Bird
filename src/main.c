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
void update_game(void);
void check_for_exit(void);
bool check_terminal_resolution(void);

int get_random_position(void)
{
    int random_position = rand() % (window_height - 6) + 1;
    return random_position;
}

void update_game(void)
{
    // if pipe is in specific position, clone a new pipe heading to the left
    if (new_pipe_available(head, window_width)) 
    {
        new_pipe(head, get_random_position());
    }

    // Print the game elements
    erase();
    attroff(A_BOLD);
    set_color(COLOR_YELLOW);
    draw_bird(&player);
    set_color(COLOR_GREEN);
    draw_pipes(head, window_height, window_width);
    set_color(COLOR_WHITE);
    draw_score(&player);
    refresh();
    usleep(70000);

    // Update the position of pipes
    update_pipe_position(head);
}

void check_for_exit(void)
{
    // Check if terminal resolution is too small
    if (check_terminal_resolution())
    {
        endwin();
        fprintf(stderr, "Terminal resolution too small. Minimun is 12x48.\n");
        free_list(head);
        exit(EXIT_FAILURE);
    }

    // Check if user wants to quit or has collided
    if (player.key == 'q' || player.key == 'Q' || bird_collided(head, &player, window_height, window_width))
    {
        usleep(400000);
        endwin();
        printf("Score: %d\n", player.score);
        free_list(head);
        exit(EXIT_SUCCESS);
    }
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

    // Get the size of the screen
    getmaxyx(win, window_height, window_width);

    // Create the first pipe
    head = first_node(head, get_random_position());

    // Start the game
    while (true)
    {
        getmaxyx(win, window_height, window_width);
        player.key = getch();
        update_game();
        check_for_exit();
    }
}

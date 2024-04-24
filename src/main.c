#include "headers.h"
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

static struct winsize w;
static Player player;
static Pipes *head = NULL;

int randomnum(void);
void inGame(void);
void endGame(void);
bool checkterminalresolution(void);

int randomnum(void) 
{
    int random = (rand() % w.ws_row) + 1;
    if (random >= w.ws_row - 5) 
    {
        random = random - 6;
    }
    return random;
}

void inGame(void) 
{
    // Create a linked list to track each spawned pipe and everytime a pipe
    // is in specific position, clone a new pipe heading to the left
    if (new_pipe_spawnable(head, w.ws_col)) 
    {
        new_pipe(head, randomnum());
    }

    // print the bird and pipe
    erase();
    set_color(COLOR_WHITE);
    printScore(head, &player);
    set_color(COLOR_YELLOW);
    printBird(&player);
    set_color(COLOR_GREEN);
    printPipe(head, w.ws_row, w.ws_col);

    // Update the position of pipes and delay the game for a while
    pipes_position_update(head);
    usleep(70000);
}

void endGame(void) 
{
    // Check if users terminal resolution is minimun 12x48 pixels
    int ret = checkterminalresolution();
    if (ret == true)
    {
        endwin();
        printf("Minimun terminal resolution required for this game is 12x48\n");
        free_list(head);
        exit(EXIT_FAILURE);
    }

    // Check if user collided with pipes or ground
    if (player.birdY == w.ws_row)
    {
        usleep(400000);
        endwin();
        printf("Game Over. You hit to the ground.\n");
        printf("Score: %d\n", player.score);
        free_list(head);
        exit(EXIT_SUCCESS);
    }

    // Check if the bird has hit the pipes
    if (pipe_collision_detection(head, &player, w.ws_col) == true) 
    {
        usleep(400000);
        endwin();
        printf("Game Over. You hit a pipe.\n");
        printf("Score: %d\n", player.score);
        free_list(head);
        exit(EXIT_SUCCESS);
    }

    // Check if user wants to quit game
    if (player.pressed == 'q' || player.pressed == 'Q')
    {
        endwin();
        printf("Exited from the game!\n");
        printf("Score: %d\n", player.score);
        free_list(head);
        exit(EXIT_SUCCESS);
    }
}

// Check if user is using small terminal
bool checkterminalresolution(void)
{
    if (w.ws_row < 12 || w.ws_col < 48)
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
    curs_set(0);
    keypad(win, true);
    nodelay(win, true);
    if (has_colors() == true)
    {
        start_color();
        use_default_colors();
    }

    // Get the size of the screen
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Create the first pipe
    head = first_node(head, randomnum());

    // Start the game
    while (true)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        player.pressed = wgetch(win);
        inGame(); // Update the game
        endGame();
    }
}

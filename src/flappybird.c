#include <ncurses.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "headers.h"

static struct winsize w;
static Player player;
static Pipes pipes;
static int random2;
static bool debugmode = false;

bool checkterminalresolution(void);
int randomnum(void);
void inGame(int *random);
void endGame(void);

int randomnum(void)
{
    int random = (rand() % w.ws_row) + 1;
    if (random >= w.ws_row - 5)
    {
        random = random - 6;
    }
    return random;
}

void inGame(int *random)
{
    // Update the position of the bird and pipe in each iteration
    erase();
    set_color(COLOR_WHITE);
    printScore(&player);
    set_color(COLOR_YELLOW);
    printBird(&player);
    set_color(COLOR_GREEN);
    printPipe(&pipes, pipes.pipeX, random, w);
    
    // Print the second pipe every time user passes the pipe
    if (w.ws_col - pipes.pipeX <= 20)
    {
        *random = randomnum();
        pipes.previouspipeX = pipes.pipeX;
        pipes.pipeX = 0;
    }
    if (w.ws_col - pipes.previouspipeX <= 20)
    {
        printPipe(&pipes, pipes.previouspipeX, &random2, w);
        pipes.previouspipeX++;
        if (w.ws_col - pipes.previouspipeX == 0)
        {
            random2 = *random;
            pipes.previouspipeX = 0;
        }
    }
    pipes.pipeX++;
    usleep(70000); // 100000
}

void endGame(void)
{
    // Check if users terminal resolution is minimun 12x48 pixels
    int ret = checkterminalresolution();
    if (ret == true)
    {
        endwin();
        printf("Minimun terminal resolution required for this game is 12x48\n");
        exit(EXIT_FAILURE);
    }

    // Check if user collided with pipes or ground
    if (player.birdY == w.ws_row)
    {
        usleep(400000);
        endwin();
        printf("Game Over. You hit to the ground.\n");
        printf("Score: %d\n", player.score);
        exit(EXIT_SUCCESS);
    }

    if (w.ws_col - pipes.pipeX == 20)
    {
        if (player.birdY <= pipes.pipeupendY || player.birdY >= pipes.pipedownpeakY)
        {
            usleep(400000);
            endwin();
            printf("Game Over. You crashed to the wall.\n");
            printf("Score: %d\n", player.score);
            exit(EXIT_SUCCESS);
        }
        player.score++;
    }

    // Check if user wants to quit game
    if (player.pressed == 'q' || player.pressed == 'Q')
    {
        endwin();
        printf("Exited from the game!\n");
        printf("Score: %d\n", player.score);
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

int main(int argc, char *argv[])
{
    // If user used arguments correctly, check if user wants to open debug mode
    if (argc >= 3)
    {
        printf("Incorrect usage of arguments\n");
        printf("Examples:\n");
        printf("./flappybird\n");
        printf("./flappybird debug\n");
        return EXIT_FAILURE;
    }

    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = true;
    }

    // Set up the screen and keypad
    srand((unsigned int) time(NULL));
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
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    // Choose random numbers for first two pipes gaps
    int random = randomnum();
    random2 = random;

    // Here is where the actual game starts
    while (true)
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        player.pressed = wgetch(win);
        inGame(&random);
        if (debugmode == true)
            debug(player, pipes, w);
        endGame();
    }
}

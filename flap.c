#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Player
{
    int birdY;
    int pressed;
    int score;
    char scoredisplay[100];
}
Player;

typedef struct Pipes
{
    int pipeY;
    int previouspipeY;
    int pipeupendX;
    int pipedownpeakX;
}
Pipes;

struct winsize w;

Player player;
Pipes pipes;
int random2;
bool debugmode = false;

bool checkterminalresolution();
int randomnum();
void inGame(int *random);
void debug();
void endGame();
void printPipe(int pipeY, int *randompipe);
void printBird();

int randomnum()
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
    printBird();
    printPipe(pipes.pipeY, random);
    sprintf(player.scoredisplay, "%d", player.score);
    mvaddstr(0, 0, player.scoredisplay);

    // Print the second pipe every time user passes the pipe
    if (w.ws_col - pipes.pipeY <= 20)
    {
        *random = randomnum();
        pipes.previouspipeY = pipes.pipeY;
        pipes.pipeY = 0;
    }
    if (w.ws_col - pipes.previouspipeY <= 20)
    {
        printPipe(pipes.previouspipeY, &random2);
        pipes.previouspipeY++;
        if (w.ws_col - pipes.previouspipeY == 0)
        {
            random2 = *random;
            pipes.previouspipeY = 0;
        }
    }
    pipes.pipeY++;
    usleep(70000); // 100000
}

// This function prints some variables such as gaps[] and player.birdY in top left corner of the screen for easier experience of debugging
void debug()
{
    char gapstr[100], gapstr2[100], birdstr[100], counterstr[100];
    sprintf(gapstr, "%d", pipes.pipeupendX);
    sprintf(gapstr2, "%d", pipes.pipedownpeakX);
    sprintf(birdstr, "%d", player.birdY);
    sprintf(counterstr, "%d", w.ws_col - pipes.pipeY);
    mvaddstr(0, 3, counterstr);
    mvaddstr(0, 6, gapstr);
    mvaddstr(0, 9, gapstr2);
    mvaddstr(0, 12, birdstr);
}

void endGame()
{
    // Check if users terminal resolution is minimun 12x48 pixels
    int ret = checkterminalresolution();
    if (ret == true)
    {
        endwin();
        printf("Minimun terminal resolution required for this game is 12x48\n");
        exit(1);
    }

    // Check if user collided with pipes or ground
    if (player.birdY == w.ws_row)
    {
        usleep(400000);
        endwin();
        printf("Game Over. You hit to the ground.\n");
        printf("Score: %s\n", player.scoredisplay);
        exit(0);
    }

    if (w.ws_col - pipes.pipeY == 20)
    {
        if (player.birdY <= pipes.pipeupendX || player.birdY >= pipes.pipedownpeakX)
        {
            usleep(400000);
            endwin();
            printf("Game Over. You crashed to the wall.\n");
            printf("Score: %s\n", player.scoredisplay);
            exit(0);
        }
        player.score++;
    }

    // Check if user wants to quit game
    if (player.pressed == 'q' || player.pressed == 'Q')
    {
        endwin();
        printf("Exited from the game!\n");
        printf("Score: %s\n", player.scoredisplay);
        exit(0);
    }
}

// Print the pipes and the gaps
void printPipe(int pipeY, int *randompipe)
{
    for (int i = 0; i < w.ws_row; i++)
    {
        if (i == *randompipe)
        {
            mvaddstr(i, w.ws_col - pipeY - 1, "[#]");
            pipes.pipeupendX = i;
            i = i + 4;
            mvaddstr(i, w.ws_col - pipeY - 1, "[#]");
            pipes.pipedownpeakX = i;
        }
        mvaddstr(i, w.ws_col - pipeY, "#");
    }
}

// Controlling of the bird
void printBird()
{
    if (player.pressed == ' ')
    {
        player.birdY = player.birdY - 3;
    }
    player.birdY++;
    mvaddstr(player.birdY, 20, "-O>");
}

// Check if user is using small terminal
bool checkterminalresolution()
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
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "debug") == 0)
    {
        debugmode = true;
    }

    // Set up the screen and keypad
    srand(time(NULL));
    WINDOW *win = initscr();
    noecho();
    curs_set(0);
    keypad(win, true);
    nodelay(win, true);
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
            debug();
        endGame();
    }
}
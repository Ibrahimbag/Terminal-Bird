typedef struct Player
{
    int birdY;
    int pressed;
    int score;
    char *score_display;
}
Player;

typedef struct Pipes
{
    int pipeX;
    int pipeupendY;
    int pipedownpeakY;
    struct Pipes *next;
}
Pipes;

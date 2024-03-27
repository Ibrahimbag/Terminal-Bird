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
    int previouspipeX;
    int pipeupendY;
    int pipedownpeakY;
}
Pipes;

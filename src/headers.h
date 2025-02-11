#ifndef HEADERS_H
#define HEADERS_H

#include <stdbool.h>

// Structs
typedef struct Player_s
{
    int bird_y;
    int key;
    unsigned long score;
} Player;

typedef struct Pipe_s
{
    int pipe_x;
    int pipe_top_end; // bottom of upper pipe
    int pipe_bottom_peak; // top of lower pipe
    struct Pipe_s *next;
} Pipes;

#define GAME_ONGOING 0
#define GAME_OVER 1
#define GAME_RESTART 2

// Functions in visuals.c
void draw_bird(Player *player);
void draw_pipes(Pipes *head, int row_size, int col_size);
void draw_score(Player *player);

// Functions in pipe_nodes.c
Pipes *first_node(Pipes *head, int random);
bool new_pipe_available(Pipes *head, int col_size);
void new_pipe(Pipes *head, int random);
void update_pipe_position(Pipes *head);
bool bird_collided(Pipes *head, Player *player, int row_size, int col_size);
void free_list(Pipes *head, int status);

// menu.c
void main_menu(int yMax, int xMax);
int game_over_menu(int yMax, int xMax, int score);

#endif

#ifndef HEADERS_H
#define HEADERS_H

#include <ncurses.h>

// Structs
typedef struct Player_s
{
    int y;
    int key;
    int score;
} Player;

typedef struct Pipe_s
{
    int pipe_x;
    int pipe_top_end; // bottom of upper pipe
    int pipe_bottom_peak; // top of lower pipe
    struct Pipe_s *next;
} Pipes;

// Functions in visuals.c
void draw_pipes(Pipes *head, int row_size, int col_size);
void draw_bird(Player *player);
void draw_score(Player *player);
void set_color(int color);

// Functions in pipe_nodes.c
Pipes *first_node(Pipes *head, int random);
bool new_pipe_available(Pipes *head, int col_size);
void new_pipe(Pipes *head, int random);
void update_pipe_position(Pipes *head);
bool bird_collided(Pipes *head, Player *player, int row_size, int col_size);
void free_list(Pipes *head);

#endif

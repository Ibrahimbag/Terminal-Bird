#include "objects.h"
#include <stdbool.h>

// visuals.c
void printPipe(Pipes *head, int window_row_size, int window_collumn_size);
void printBird(Player *player);
void printScore(Pipes *head, Player *player);
void set_color(int color);

// pipe_nodes.c
Pipes *first_node(Pipes *head, int random);
void pipes_position_update(Pipes *head);
bool new_pipe_spawnable(Pipes *head, int window_collumn_size);
void new_pipe(Pipes *head, int random);
bool pipe_collision_detection(Pipes *head, Player *player, int window_collumn_size);
void free_list(Pipes *head);

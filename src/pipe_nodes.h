#ifndef PIPE_NODES_H
#define PIPE_NODES_H

#include "common.h"

// Functions in pipe_nodes.c
Pipes *first_node(Pipes *head, int random);
bool new_pipe_available(Pipes *head, int col_size);
void new_pipe(Pipes *head, int random);
void update_pipe_position(Pipes *head);
bool bird_collided(Pipes *head, Player *player, int row_size, int col_size);
void free_list(Pipes **head, int status, int col_size);

#endif

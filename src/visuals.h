#ifndef VISUALS_H
#define VISUALS_H

#include "common.h"

// Functions in visuals.c
bool bird_jump(Player *player, Pipes *head, int col_size);
void draw_bird(Player *player);
void draw_pipes(Pipes *head, int row_size, int col_size);
void draw_score(Player *player);

#endif

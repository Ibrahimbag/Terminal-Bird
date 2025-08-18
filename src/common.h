#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>

// Structs
typedef struct Player_s {
	int bird_y;
	int key;
	unsigned long score;
} Player;

typedef struct Pipe_s {
	int pipe_x;
	int pipe_top_end;     // bottom of upper pipe
	int pipe_bottom_peak; // top of lower pipe
	struct Pipe_s *next;
} Pipes;

// Game macros
#define GAME_ONGOING 0
#define GAME_OVER 1
#define GAME_RESTART 2

#endif

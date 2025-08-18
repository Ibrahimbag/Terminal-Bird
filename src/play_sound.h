#ifndef PLAY_SOUND_H
#define PLAY_SOUND_H

#include <stdbool.h>

bool init_sound(void);
void play_sound(const char *file_path);
void close_sound(void);

#endif
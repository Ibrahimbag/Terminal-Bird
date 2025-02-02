#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <stdbool.h>

typedef struct {
    bool auto_resize;
    int height;
    int width;
    int bird_color;
    int pipe_color;
    float game_speed_multiplier;
    bool show_score;
    int jump_height;
    int gravity;
    char jump;
    char exit;
    char restart;
    int background_color;
    bool menu_shown;
} Configurations;

Configurations configuration(void);

#endif

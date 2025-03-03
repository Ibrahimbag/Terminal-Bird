#define _POSIX_C_SOURCE 1
#include "configuration.h"
#include <cjson/cJSON.h>
#include <limits.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/*  Code copy and pasted from: https://stackoverflow.com/a/3747128 */
static char *get_json_string(void) 
{
    long lSize;
    FILE *fp = NULL;
    char *json_string = NULL;

    // Get the path to the configuration file
    char path[PATH_MAX];
    snprintf(path, sizeof(path), "%s/.Terminal-Bird/configurations.json", getenv("HOME"));

    fp = fopen (path,"r");
    if(!fp)   
        return NULL;

    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );

    /* allocate memory for entire content */
    json_string = calloc( 1, lSize+1 );
    if( !json_string ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

    /* copy the file into the json_string */
    if( 1!=fread( json_string , lSize, 1 , fp) )
    fclose(fp),free(json_string),fputs("entire read fails",stderr),exit(1);

    fclose(fp);

    return json_string;
}

static cJSON *get_item(cJSON *json, char *object_name, char *key_name)
{
    // Get the object
    cJSON *object = cJSON_GetObjectItemCaseSensitive(json, object_name);
    if (object == NULL) 
    {
        endwin();
        printf("Error: %s object not found.\n", object_name);
        cJSON_Delete(json);
        exit(EXIT_FAILURE);
    }

    // Extract key-value pairs from object
    cJSON *item = cJSON_GetObjectItemCaseSensitive(object, key_name);
    if (item == NULL) 
    {
        endwin();
        printf("Error: Key '%s' not found in %s object.\n", key_name, object_name);
        cJSON_Delete(json);
        exit(EXIT_FAILURE);
    }

    return item;
}

static void assign_config(Configurations *config, cJSON *json, char **object_names, char **key_names, size_t array_size)
{
    for (size_t i = 0; i < array_size; i++) 
    {
        cJSON *item = get_item(json, object_names[i], key_names[i]);

        // Return the value based on the type
        switch (i) 
        {
            case 0:
                config->auto_resize = cJSON_IsTrue(item);
                break;
            case 1:
                config->height = item->valueint;
                break;
            case 2:
                config->width = item->valueint;
                break;
            case 3:
                config->bird_color = item->valueint;
                break;
            case 4:
                config->pipe_color = item->valueint;
                break;
            case 5:
                config->game_speed_multiplier = item->valuedouble;
                break;
            case 6:
                config->show_score = cJSON_IsTrue(item);
                break;
            case 7:
                config->jump_height = item->valueint;
                break;
            case 8:
                config->gravity = item->valueint;
                break;
            case 9:
                config->jump = item->valuestring[0];
                break;
            case 10:
                config->exit = item->valuestring[0];
                break;
            case 11:
                config->restart = item->valuestring[0];
                break;
            case 12:
                config->background_color = item->valueint;
                break;
            case 13:
                config->menu_shown = cJSON_IsTrue(item);
                break;
            case 14:
                config->bot = cJSON_IsTrue(item);
                break;
            default:
                break;
        }
    }
}

Configurations configuration(void) 
{
    // Initialize the configurations
    static Configurations config = {true, 24, 80, 3, 2, 1.00, true, 2, 1, ' ', 'q', 'r', -1, true, false};
    char *object_names[] = {
        "Display", "Display", "Display", 
        "Appearance", "Appearance", "General", 
        "General", "General", "General",
        "Keybinds", "Keybinds", "Keybinds",
        "Appearance", "General", "General"
    };
    char *key_names[] = {
        "auto_resize", "height", "width", 
        "bird_color", "pipe_color", "game_speed_multiplier", 
        "show_score", "jump_height", "gravity",
        "jump", "exit", "restart",
        "background_color", "menu_shown", "bot"
    };

    static bool executed = false;
    if (!executed)
    {
        // Get the JSON string
        char *json_string = NULL;
        json_string = get_json_string();
        if (json_string == NULL) 
        { 
            return config;
        }

        // Parse JSON string.
        cJSON *json = cJSON_Parse(json_string);
        if (json == NULL) 
        {
            return config;
        }
        free(json_string);

        // Assign the values from configuration file to the config struct
        size_t array_size = sizeof(object_names) / sizeof(object_names[0]);
        assign_config(&config, json, object_names, key_names, array_size);

        executed = true;
        cJSON_Delete(json);
    }

    return config;
}


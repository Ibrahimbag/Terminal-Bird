#define _POSIX_C_SOURCE 1
#include "configuration.h"
#include <cjson/cJSON.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

/*  Code copy and pasted from: https://stackoverflow.com/a/3747128 */
static char *get_json_string(void) {
	char path[PATH_MAX];
	snprintf(path, sizeof(path), "%s/.Terminal-Bird/configurations.json",
		 getenv("HOME"));

	FILE *fp = fopen(path, "r");
	if (!fp)
		return NULL;

	fseek(fp, 0, SEEK_END);
	long lSize = ftell(fp);
	rewind(fp);

	char *json_string = calloc(1, lSize + 1);
	if (!json_string)
		fclose(fp), fputs("Memory alloc fails", stderr), exit(1);

	if (fread(json_string, lSize, 1, fp) != 1)
		fclose(fp), free(json_string),
		    fputs("Entire read fails", stderr), exit(1);

	fclose(fp);

	return json_string;
}

static cJSON *get_item(cJSON *json, const char *object_name,
		       const char *key_name) {
	cJSON *object = cJSON_GetObjectItemCaseSensitive(json, object_name);
	if (!object)
		cJSON_Delete(json), fputs("object not found", stderr),
		    exit(EXIT_FAILURE);

	cJSON *item = cJSON_GetObjectItemCaseSensitive(object, key_name);
	if (!item)
		cJSON_Delete(json), fputs("key not found", stderr),
		    exit(EXIT_FAILURE);

	return item;
}

static void assign_config(Configurations *config, cJSON *json)
{
	config->game_speed_multiplier = get_item(json, "General", "game_speed_multiplier")->valuedouble;
	config->show_score = cJSON_IsTrue(get_item(json, "General", "show_score"));
	config->menu_shown = cJSON_IsTrue(get_item(json, "General", "menu_shown"));
	config->jump_height = get_item(json, "General", "jump_height")->valueint;
	config->gravity = get_item(json, "General", "gravity")->valueint;
	config->bot = cJSON_IsTrue(get_item(json, "General", "bot"));
	config->sound_on = cJSON_IsTrue(get_item(json, "Sound", "sound_on"));
	config->bird_color = get_item(json, "Appearance", "bird_color")->valueint;
	config->pipe_color = get_item(json, "Appearance", "pipe_color")->valueint;
	config->background_color = get_item(json, "Appearance", "background_color")->valueint;
	config->auto_resize = cJSON_IsTrue(get_item(json, "Display", "auto_resize"));
	config->height = get_item(json, "Display", "height")->valueint;
	config->width = get_item(json, "Display", "width")->valueint;
	config->jump = get_item(json, "Keybinds", "jump")->valuestring[0];
	config->exit = get_item(json, "Keybinds", "exit")->valuestring[0];
	config->restart = get_item(json, "Keybinds", "restart")->valuestring[0];
}

Configurations configuration(void) {
	static Configurations config = {.game_speed_multiplier = 1.00,
					.show_score = true,
					.menu_shown = true,
					.jump_height = 2,
					.gravity = 1,
					.bot = false,
					.sound_on = false,
					.bird_color = 3,
					.pipe_color = 2,
					.background_color = -1,
					.auto_resize = true,
					.height = 24,
					.width = 80,
					.jump = ' ',
					.exit = 'q',
					.restart = 'r'};

	static bool executed = false;
	if (!executed) {
		char *json_string = get_json_string();
		if (!json_string)
			return config;

		cJSON *json = cJSON_Parse(json_string);
		if (!json)
			return config;
		free(json_string);

		assign_config(&config, json);
		cJSON_Delete(json);

		executed = true;
	}

	return config;
}

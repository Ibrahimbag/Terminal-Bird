#include "play_sound.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define FLAP_PATH "%s/.Terminal-Bird/sounds/flap.mp3"
#define HIT_PATH "%s/.Terminal-Bird/sounds/hit.mp3"
#define POINT_PATH "%s/.Terminal-Bird/sounds/point.mp3"
#define MAX_CHANNELS 16

static Mix_Chunk *playing_chunks[MAX_CHANNELS] = {0};

static void free_chunks(void) {
	for (int i = 0; i < MAX_CHANNELS; i++) {
		if (playing_chunks[i]) {
			Mix_FreeChunk(playing_chunks[i]);
			playing_chunks[i] = NULL;
		}
	}
}

bool init_sound(void) {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		fprintf(stderr, "Mix_OpenAudio Error: %s\n", Mix_GetError());
		SDL_Quit();
		return false;
	}

	Mix_AllocateChannels(MAX_CHANNELS);

	char buffer[256];
	snprintf(buffer, sizeof(buffer), FLAP_PATH, getenv("HOME"));
	Mix_Chunk *flap_sound = Mix_LoadWAV(buffer);
	if (!flap_sound) {
		fprintf(stderr, "Failed to load %s: %s\n", FLAP_PATH,
			Mix_GetError());
		return false;
	}

	snprintf(buffer, sizeof(buffer), HIT_PATH, getenv("HOME"));
	Mix_Chunk *hit_sound = Mix_LoadWAV(buffer);
	if (!hit_sound) {
		fprintf(stderr, "Failed to load %s: %s\n", HIT_PATH,
			Mix_GetError());
		return false;
	}

	snprintf(buffer, sizeof(buffer), POINT_PATH, getenv("HOME"));
	Mix_Chunk *point_sound = Mix_LoadWAV(buffer);
	if (!point_sound) {
		fprintf(stderr, "Failed to load %s: %s\n", POINT_PATH,
			Mix_GetError());
		return false;
	}

	playing_chunks[0] = flap_sound;
	playing_chunks[1] = hit_sound;
	playing_chunks[2] = point_sound;

	return true;
}

void play_sound(const char *sound_effect) {
	Mix_Chunk *sound = NULL;
	if (strcmp(sound_effect, "flap") == 0) {
		sound = playing_chunks[0];
	} else if (strcmp(sound_effect, "hit") == 0) {
		sound = playing_chunks[1];
	} else if (strcmp(sound_effect, "point") == 0) {
		sound = playing_chunks[2];
	}

	if (sound) {
		int channel = Mix_PlayChannel(-1, sound, 0);
		if (channel == -1) {
			fprintf(stderr, "Failed to play sound: %s\n",
				Mix_GetError());
			return;
		}
	}
}

void close_sound(void) {
	// Wait for the channels to finish their sounds to avoid segfaults
	while (Mix_Playing(-1) > 0) {
		SDL_Delay(100);
	}

	free_chunks();

	Mix_CloseAudio();
	SDL_Quit();
}

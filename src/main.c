#include "configuration.h"
#include "leaderboard_db.h"
#include "menu.h"
#include "pipe_nodes.h"
#include "play_sound.h"
#include "visuals.h"
#include <ctype.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int window_height, window_width;
static Player player;
static Pipes *head = NULL;
static Configurations config;

static int get_random_position(void);
static void game(void);
static bool check_for_exit(void);
static bool check_terminal_resolution(void);

int main(void) {
	// Exit from the game if user runned it as root
	if (getuid() == 0) {
		fprintf(stderr, "Do not run this game as root.\n");
		exit(EXIT_FAILURE);
	}

	// Initialize random seed
	srand((unsigned int)time(NULL));

	// Initialize leaderboard database
	db_execute(CREATE, NULL, -1);

	// Get all of the configurations
	config = configuration();

	if(config.sound_on && !init_sound()) {
		config.sound_on = false;
	}

	// Initialize ncurses
	setlocale(LC_ALL, "");
	WINDOW *win = initscr();
	noecho();
	curs_set(false);
	nodelay(win, true);
	if (has_colors() == true) {
		start_color();
		use_default_colors();
	}

	// Get the window size
	config.auto_resize
	    ? getmaxyx(win, window_height, window_width)
	    : (window_height = config.height, window_width = config.width);

	// Display the main menu
	if (config.menu_shown)
		main_menu(window_height, window_width);

	// Color pairs to be used
	int bird_color = config.bird_color;
	if (bird_color < COLOR_BLACK || bird_color > COLOR_WHITE) {
		bird_color = COLOR_YELLOW;
	}

	int pipe_color = config.pipe_color;
	if (pipe_color < COLOR_BLACK || pipe_color > COLOR_WHITE) {
		pipe_color = COLOR_GREEN;
	}

	int background_color = config.background_color;

	init_pair(1, bird_color, -1); // Bird
	init_pair(2, -1, pipe_color); // Rest of the pipes exclude the bottom of
				      // upper pipe, top of lower pipe.
	if (!(background_color < COLOR_BLACK) ||
	    !(background_color > COLOR_WHITE)) {
		init_pair(3, pipe_color,
			  background_color); // Bottom of upper pipe, top of
					     // lower pipe.
		init_pair(4, -1, background_color);
	} else {
		init_pair(3, pipe_color,
			  -1); // Bottom of upper pipe, top of lower pipe.
	}

	// Create the first pipe
	head = first_node(head, get_random_position());

	// Start the game
	float game_speed = config.game_speed_multiplier;

	if (game_speed < 0.1 || game_speed > 10) {
		game_speed = 1.00;
	}

	struct timespec remaining, request = {0, 70000000 / game_speed};
	while (!check_for_exit()) {
		if (config.auto_resize)
			getmaxyx(win, window_height, window_width);
		player.key = getch();
		game();
		nanosleep(&request, &remaining);
	}
}

static int get_random_position(void) {
	int random_position = rand() % (window_height - 6) + 1;
	return random_position;
}

static void game(void) {
	// if pipe is in specific position, clone a new pipe heading to the left
	if (new_pipe_available(head, window_width)) {
		new_pipe(head, get_random_position());
	}

	// Print the game elements
	erase();
	bkgd(COLOR_PAIR(4));

	if(bird_jump(&player, head, window_width) && config.sound_on) {
		play_sound("flap");
	}
	draw_bird(&player);
	draw_pipes(head, window_height, window_width);
	bool show_score = config.show_score;
	if (show_score)
		draw_score(&player);

	refresh();

	// Update the position of pipes
	update_pipe_position(head);

	// Free unused pipes that are out of the screen
	free_list(&head, GAME_ONGOING, window_width);
}

static bool check_for_exit(void) {
	// Check if terminal resolution is too small
	if (check_terminal_resolution()) {
		close_sound();
		endwin();
		fprintf(stderr,
			"Terminal resolution too small. Minimun is 12x48.\n");
		free_list(&head, GAME_OVER, -1);
		exit(EXIT_FAILURE);
	}

	unsigned long old_score = player.score;

	// Check if user wants to quit while game is running
	int exit_key = tolower(config.exit);
	if (tolower(player.key) == exit_key) {
		close_sound();
		free_list(&head, GAME_OVER, -1);
		endwin();
		return true;
	}
	// If bird collided to somewhere, display game over screen
	else if (bird_collided(head, &player, window_height, window_width)) {
		if (config.sound_on) {
			play_sound("hit");
		}
		sleep(1);

		int ret = GAME_OVER;
		if (config.menu_shown)
			ret = game_over_menu(window_height, window_width,
					     player.score);
		else
			sleep(3);

		free_list(&head, GAME_OVER, -1);

		if (ret == GAME_RESTART) {
			player.score = 0;
			player.bird_y = window_height / 2;
			head = first_node(head, get_random_position());
			return false;
		} else if (ret == GAME_OVER) {
			endwin();
			close_sound();
			if (!config.menu_shown)
				printf("Score: %lu\n", player.score);
			return true;
		}
	}

	// If player passes the pipe, play point sound
	if (old_score != player.score && config.sound_on) {
		play_sound("point");
	}
	
	return false;
}

// Check if user is using small terminal
static bool check_terminal_resolution(void) {
	if (window_height < 12 || window_width < 48) {
		return true;
	}
	return false;
}

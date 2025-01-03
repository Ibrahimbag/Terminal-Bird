#include "headers.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void main_menu(int yMax, int xMax)
{   
    // Create a window for the menu
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    nodelay(win, true);
    keypad(win, true);

    // Print menu title
    char *menu_title[] = {
        " _____                   _             _ \n",
        "|_   _|__ _ __ _ __ ___ (_)_ __   __ _| |\n",
        "  | |/ _ \\ '__| '_ ` _ \\| | '_ \\ / _` | |\n",
        "  | |  __/ |  | | | | | | | | | | (_| | |\n",
        "  |_ \\___|_| _|_| |_| |_|_|_|_|_|\\__,_|_|\n",
        "            | __ )(_)_ __ __| |          \n",
        "            |  _ \\| | '__/ _` |          \n",
        "            | |_) | | | | (_| |          \n",
        "            |____/|_|_|  \\__,_|          \n",
    };

    size_t n = sizeof(menu_title) / sizeof(menu_title[0]);
    int menu_title_half_width = 40 / 2;

    for (size_t i = 0; i < n; i++) {
        mvwaddstr(win, i + 1, xMax / 2 - menu_title_half_width, menu_title[i]);
    }
    box(win, 0, 0);

    // Define menu items
    char *menu_items[] = {
        "Start",
        "Leaderboard",
        "Options",
        "Exit"
    };

    // Display menu items
    size_t key_id = 0;
    while(true)
    {
        // Get user input
        int key = wgetch(win);

        // Control keys
        if (key == KEY_UP && key_id > 0) 
        {
            key_id--;
        }
        else if (key == KEY_DOWN && key_id < sizeof(menu_items) / sizeof(menu_items[0]) - 1)
        {
            key_id++;
        }

        // Print menu items
        for (size_t i = 0; i < sizeof(menu_items) / sizeof(menu_items[0]); i++)
        {
            if (key_id == i)
            {
                wattron(win, A_REVERSE);
                mvwprintw(win, 13 + i + i, xMax / 2 - 4, "%s", menu_items[i]);
                wattroff(win, A_REVERSE);
            }
            else
            {
                mvwprintw(win, 13 + i + i, xMax / 2 - 4, "%s", menu_items[i]);
            }
        }

        if (key == '\n')
        {
            if (key_id == 0)
            {
                return;
            }
            else if (key_id == 3)
            {            
                endwin();
                exit(EXIT_SUCCESS);
            }
        }
        else if (tolower(key) == 'q')
        {
            endwin();
            exit(EXIT_SUCCESS);
        }
    }
}    

int game_over_menu(int yMax, int xMax)
{
    // Create a window for the game over screen
    WINDOW *win = newwin(yMax / 2, xMax / 2,  yMax / 4, xMax / 4);
    keypad(win, true);

    // Print game over title
    char *game_over_title[] = {
        " ___                    \n",
        "/  _>  ___ ._ _ _  ___  \n",
        "| <_/\\<_> || ' ' |/ ._> \n",
        "`____/<___||_|_|_|\\___. \n",
        "                        \n",
        "  ___                 _ \n",
        " | . | _ _  ___  _ _ | |\n",
        " | | || | |/ ._>| '_>|_/\n",
        " `___'|__/ \\___.|_|  <_>\n",
    };

    size_t n = sizeof(game_over_title) / sizeof(game_over_title[0]);
    int game_over_title_half_width = 23 / 2;

    for (size_t i = 0; i < n; i++) {
        mvwaddstr(win, i + 1, xMax / 4 - game_over_title_half_width, game_over_title[i]);
    }
    box(win, 0, 0);

    // Print game over message
    getmaxyx(win, yMax, xMax);
    mvwaddstr(win, yMax - 2, xMax / 8, "Exit [Q]");
    mvwaddstr(win, yMax - 2, xMax / 2 + xMax / 8, "Restart [R]");

    // Wait for user input
    while(true)
    {
        int key = wgetch(win);

        if (tolower(key) == 'q')
        {
            return GAME_OVER;
        }
        else if (tolower(key) == 'r')
        {
            return GAME_RESTART;
        }
    }
}

#include "headers.h"
#include <ctype.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leaderboard_menu(int yMax, int xMax)
{
    WINDOW *win = newwin(yMax, xMax, 0, 0);

    box(win , 0 , 0);

    char *message = "Leaderboards are not implemented yet.";
    mvwprintw(win, yMax / 2, xMax / 2 - strlen(message) / 2, "%s", message);
    message = "Press any key to return to the main menu.";
    mvwprintw(win, yMax - 2, xMax / 2 - strlen(message) / 2, "%s", message);

    wgetch(win);
    wclear(win);
    wrefresh(win);

    delwin(win);
}

void options_menu(int yMax, int xMax)
{
    WINDOW *win = newwin(yMax, xMax, 0, 0);

    box(win , 0 , 0);

    char *message = "Options are not implemented yet.";
    mvwprintw(win, yMax / 2, xMax / 2 - strlen(message) / 2, "%s", message);
    message = "Press any key to return to the main menu.";
    mvwprintw(win, yMax - 2, xMax / 2 - strlen(message) / 2, "%s", message);

    wgetch(win);
    wclear(win);
    wrefresh(win);

    delwin(win);
}

void main_menu(int yMax, int xMax)
{   
    // Create a window for the menu
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    nodelay(win, true);
    keypad(win, true);

    // Menu title
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

    // Define menu items
    char *menu_items[] = {
        "Start",
        "Leaderboard",
        "Options",
        "Exit"
    };

    // Display menu items
    int key_id = 0;
    while(true)
    {
        // Get user input
        int key = wgetch(win);

        // Control keys
        if (key == KEY_UP) 
        {
            key_id--;
        }
        else if (key == KEY_DOWN)
        {
            key_id++;
        }

        // Wrap key_id within the valid range
        int num_menu_items = sizeof(menu_items) / sizeof(menu_items[0]);
        key_id = (key_id + num_menu_items) % num_menu_items;

        // Print menu title
        box(win, 0, 0);
        for (size_t i = 0; i < n; i++) 
        {
            mvwaddstr(win, i + 1, xMax / 2 - menu_title_half_width, menu_title[i]);
        }

        // Print menu items
        for (int i = 0; i < (int) sizeof(menu_items) / (int) sizeof(menu_items[0]); i++)
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
            switch (key_id)
            {
                case 0:
                    delwin(win);
                    return;
                case 1:
                    leaderboard_menu(yMax, xMax);
                    break;
                case 2:
                    options_menu(yMax, xMax);
                    break;
                default:
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
            delwin(win);
            return GAME_OVER;
        }
        else if (tolower(key) == 'r')
        {
            delwin(win);
            return GAME_RESTART;
        }
    }
}

#include "headers.h"
#include <errno.h>
#include <ncurses.h>
#include <stdlib.h>

Pipes *first_node(Pipes *head, int random)
{
    // Create the first node
    Pipes *starting_node = malloc(sizeof(Pipes));
    if (starting_node == NULL)
    {
        endwin();
        perror("Error");
        free_list(head);
        exit(EXIT_FAILURE);
    }
    starting_node->pipe_x = 3; 
    starting_node->pipe_top_end = random;
    starting_node->pipe_bottom_peak = random + 4;
    starting_node->next = NULL;

    return starting_node;
}

bool new_pipe_available(Pipes *head, int col_size)
{
    Pipes *ptr = head;
    while (ptr != NULL)
    {
        if (col_size - ptr->pipe_x == col_size - 50)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

void new_pipe(Pipes *head, int random)
{
    // Create the next node 
    Pipes *end_node = malloc(sizeof(Pipes));
    if (end_node == NULL)
    {
        endwin();
        perror("Error");
        free_list(head);
        exit(EXIT_FAILURE);
    }
    end_node->pipe_x = 3;
    end_node->pipe_top_end = random;
    end_node->pipe_bottom_peak = random + 4;
    end_node->next = NULL;
    
    // Add the new node to the list
    Pipes *ptr = head;
    while (true) 
    {
        if (ptr->next != NULL) 
        {
            ptr = ptr->next;
        } 
        else 
        {
            ptr->next = end_node;
            break;
        }
    }
}

void update_pipe_position(Pipes *head)
{
    // Move the pipes to the left of the screen
    Pipes *ptr = head;
    while (ptr != NULL)
    {
        ptr->pipe_x++;
        ptr = ptr->next;
    }
}

bool bird_collided(Pipes *head, Player *player, int row_size, int col_size) 
{
    // Check if the bird has hit the ground
    if (player->y == row_size - 1)
    {
        return true;
    }

    // Check if the bird has hit the pipes. If so, return true; else increment player score and return false.
    Pipes *ptr = head;
    while (ptr != NULL) 
    {
        if (col_size - ptr->pipe_x == 20)
        {
            if (player->y <= ptr->pipe_top_end || player->y >= ptr->pipe_bottom_peak) 
            {
                return true;
            }
            player->score++;
        }
        ptr = ptr->next;
    }

    return false;
}

void free_list(Pipes *head) 
{
    Pipes *ptr = head, *next;
    while (ptr != NULL) 
    {
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

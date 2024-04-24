#include "headers.h"
#include <ncurses.h>
#include <stdlib.h>

Pipes *first_node(Pipes *head, int random)
{
    // Create the first node
    Pipes *starting_node = malloc(sizeof(Pipes));
    if (starting_node == NULL)
    {
        endwin();
        printf("Memory allocation error");
        free_list(head);
        exit(EXIT_FAILURE);
    }
    starting_node->pipeX = 3; 
    starting_node->pipeupendY = random;
    starting_node->pipedownpeakY = random + 4;
    starting_node->next = NULL;

    return starting_node;
}

bool new_pipe_spawnable(Pipes *head, int window_collumn_size)
{
    Pipes *ptr = head;
    while (ptr != NULL)
    {
        if (window_collumn_size - ptr->pipeX == window_collumn_size - 50)
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
        printf("Memory allocation error");
        free_list(head);
        exit(EXIT_FAILURE);
    }
    end_node->pipeX = 3;
    end_node->pipeupendY = random;
    end_node->pipedownpeakY = random + 4;
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

void pipes_position_update(Pipes *head)
{
    // Move the pipes to the left of the screen
    Pipes *ptr = head;
    while (ptr != NULL)
    {
        ptr->pipeX++;
        ptr = ptr->next;
    }
}

bool pipe_collision_detection(Pipes *head, Player *player, int window_collumn_size) 
{
    // Check if the bird has hit the pipes. If so, return true; else increment player score and return false.
    Pipes *ptr = head;
    while (ptr != NULL) 
    {
        if (window_collumn_size - ptr->pipeX == 20)
        {
            if (player->birdY <= ptr->pipeupendY || player->birdY >= ptr->pipedownpeakY) 
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

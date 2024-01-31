#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H
#include <threads.h>
#include "../Edge/Edge.h"

// Structure to represent an adjacency list
typedef struct Adjacency_List{
    Edge* head;
} Adjacency_List;

Adjacency_List create_adjacency_list();
void destroy_adjacency_list(Adjacency_List* list);

//Adds new edge on the beginning of the list
void adjacency_list_add_edge(Adjacency_List* list, Edge *edge);
void adjacency_list_remove_edge(Adjacency_List* list, int removed_edge_destination);
void adjacency_list_display(Adjacency_List* list);

//Checks if vertex have connection with dest vertex and returns weight of edge or -1 if connection doesn't exist
int adjacency_list_find_weight_of_edge_to_vertex(Adjacency_List* list, int destination);

#endif // ADJACENCY_LIST_H
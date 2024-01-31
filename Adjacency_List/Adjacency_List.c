#include <stdlib.h>
#include <stdio.h>
#include "Adjacency_List.h"

Adjacency_List create_adjacency_list(){
    Adjacency_List new;
    new.head=NULL;
    return new;
}

void destroy_adjacency_list(Adjacency_List* list){
    while (list->head){
        Edge* current = list->head;
        list->head = list->head->next;
        free(current);
    }
}

void adjacency_list_add_edge(Adjacency_List* list, Edge *edge){
    edge->next = list->head;
    list->head = edge;
}

void adjacency_list_remove_edge(Adjacency_List* list, int removed_edge_destination){
    Edge* temp = list->head;
    Edge* prev = NULL;

    while (temp != NULL){
        if (temp->dest == removed_edge_destination){
            if (prev == NULL) {
                list->head = temp->next;
            }
            else{
                prev->next = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void adjacency_list_display(Adjacency_List* list){
    Edge* edge = list->head;
    while (edge){
        printf("  (%d)[weight = %d]", edge->dest, edge->weight);
        edge = edge->next;
    }
    printf("\n");
}

int adjacency_list_find_weight_of_edge_to_vertex(Adjacency_List *list, int destination) {
    if(list==NULL){
        return -1;
    }
    Edge* edge = list->head;
    while (edge != NULL){
        if (edge->dest == destination)
            return edge->weight;
        edge = edge->next;
    }
    return -1;
}

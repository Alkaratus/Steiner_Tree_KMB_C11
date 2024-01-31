#include <stdlib.h>
#include "Path.h"

Path* path_empty_create(int total_weight){
    Path* path = (Path*) malloc(sizeof(Path));
    path->total_weight = total_weight;
    path->head = NULL;
    return path;
}

void path_destroy(Path* path){
    if (path == NULL)
        return;

    while (path->head){
        Edge* current = path->head;
        path->head = path->head->next;
        free(current);
    }
    free(path);
}
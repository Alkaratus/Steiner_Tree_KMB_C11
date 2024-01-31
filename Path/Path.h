//
// Created by alkaratus on 03.12.23.
//

#ifndef KMB_PTHREADS_PATH_H
#define KMB_PTHREADS_PATH_H
#include "../Edge/Edge.h"

// Structure to represent a path (sequence of edges)
typedef struct Path{
    int total_weight;
    Edge* head;
} Path;

Path* path_empty_create(int total_weight);
void path_destroy(Path* path);

#endif //KMB_PTHREADS_PATH_H

#ifndef KMB_PTHREADS_PATH_TO_SOURCE_H
#define KMB_PTHREADS_PATH_TO_SOURCE_H
#include <stdbool.h>

static const int NO_PREVIOUS_VERTEX=-1;

//Data informing about path to source for vertex in graph
typedef struct Path_To_Source{
    //distance from beginning to vertex
    int distance;

    //index of previous vertex in path to source
    int previous;

    // information confirming this path is the shortest
    bool shortest;
}Path_To_Source;

/// Initialize all distances as infinite (INT_MAX) and shortest_path[] elements as false (0)
Path_To_Source path_to_source_create_empty();

#endif //KMB_PTHREADS_PATH_TO_SOURCE_H

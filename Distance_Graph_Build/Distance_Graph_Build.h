#ifndef KMB_PTHREADS_DISTANCE_GRAPH_BUILD_H
#define KMB_PTHREADS_DISTANCE_GRAPH_BUILD_H

#include "Graph.h"
#include "Steiner_Points.h"

typedef struct Distance_Graph_Build{
    //Pointer to existing graph
    Graph* graph;

    //Pointer to existing distance graph
    Graph* distance_graph;

    //Pointer to steiner points struct
    Steiner_Points* steiner_points;

    //iterator used in creation of distance graph
    int i1, i2;

    mtx_t mutex;

} Distance_Graph_Build;

Distance_Graph_Build *distance_graph_build_create(Graph* graph, Graph* distance_graph, Steiner_Points* steiner_points);
void distance_graph_build_destroy(Distance_Graph_Build *build);

#endif //KMB_PTHREADS_DISTANCE_GRAPH_BUILD_H

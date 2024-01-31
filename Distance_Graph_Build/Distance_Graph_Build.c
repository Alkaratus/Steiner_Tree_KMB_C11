#include "Distance_Graph_Build.h"

Distance_Graph_Build *distance_graph_build_create(Graph* graph, Graph* distance_graph, Steiner_Points* steiner_points){
    Distance_Graph_Build *new= malloc(sizeof(Distance_Graph_Build));
    new->graph=graph;
    new->distance_graph=distance_graph;
    new->steiner_points=steiner_points;
    new->i1=0;
    new->i2=1;
    mtx_init(&new->mutex,0);
    return new;
}

void distance_graph_build_destroy(Distance_Graph_Build *build){
    mtx_destroy(&build->mutex);
    free(build);
}
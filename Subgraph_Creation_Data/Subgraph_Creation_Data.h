//
// Created by alkaratus on 01.01.24.
//

#ifndef KMB_PTHREADS_SUBGRAPH_CREATION_DATA_H
#define KMB_PTHREADS_SUBGRAPH_CREATION_DATA_H

#include <threads.h>
#include "Graph.h"
#include "Matrix.h"
#include "Steiner_Points.h"

typedef struct Subgraph_Creation_Data{
    Graph *graph;

    Graph *subgraph;

    Graph* distance_graph_mst;

    Matrix *already_added_edges;

    Steiner_Points *steiner_points;

    int vertex_index;

    mtx_t index_guard;

    mtx_t matrix_guard;

}Subgraph_Creation_Data;

Subgraph_Creation_Data* subgraph_creation_data_create(Graph *graph,Graph *subgraph,Graph* distance_graph_mst,Matrix *already_added_edges,Steiner_Points *steiner_points);
void subgraph_creation_data_destroy(Subgraph_Creation_Data *data);


#endif //KMB_PTHREADS_SUBGRAPH_CREATION_DATA_H

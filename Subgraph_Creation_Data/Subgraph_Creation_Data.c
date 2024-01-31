//
// Created by alkaratus on 01.01.24.
//

#include "Subgraph_Creation_Data.h"

Subgraph_Creation_Data *
subgraph_creation_data_create(Graph *graph, Graph *subgraph, Graph *distance_graph_mst, Matrix *already_added_edges,
                              Steiner_Points *steiner_points) {
    Subgraph_Creation_Data *new= malloc(sizeof(Subgraph_Creation_Data));
    new->graph=graph;
    new->subgraph=subgraph;
    new->distance_graph_mst=distance_graph_mst;
    new->already_added_edges=already_added_edges;
    new->steiner_points=steiner_points;
    new->vertex_index=0;
    mtx_init(&new->index_guard,0);
    mtx_init(&new->matrix_guard,0);
    return new;
}

void subgraph_creation_data_destroy(Subgraph_Creation_Data *data) {
    mtx_destroy(&data->index_guard);
    mtx_destroy(&data->matrix_guard);
    free(data);
}

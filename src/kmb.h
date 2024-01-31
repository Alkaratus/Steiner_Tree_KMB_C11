#ifndef KMB_H
#define KMB_H

#include "Graph.h"
#include "Matrix.h"
#include "Mst_Node.h"
#include "Path_To_Source.h"
#include "Steiner_Points.h"
#include "Dijkstra_Shortest_Path.h"
#include "Prim_MST.h"

void run_kmb(int vertex_count, int steiner_points_count);

Graph* construct_test_graph();
Graph* construct_graph(int size);

Graph* create_distance_graph(Graph* graph, Steiner_Points* steiner_points);
Graph* create_distance_graph_parallel(Graph* graph, Steiner_Points *steiner_points);
int create_distance_edge_thread(void *arg);

Graph* construct_subgraph_with_distance_graph_mst(Graph* graph, Graph* distance_graph_mst, Steiner_Points* steiner_points);
void add_path_edges_to_graph(Graph *graph,Path* path, Matrix* added_edges);

Graph* construct_subgraph_with_distance_graph_mst_parallel(Graph* graph, Graph* distance_graph_mst, Steiner_Points* steiner_points);
int add_vertex_edges_paths_to_subgraph_thread(void *arg);
void add_path_edges_to_graph_secure(Graph *graph,Path* path, Matrix* added_edges,mtx_t *matrix_guard);

void construct_steiner_tree(Graph* graph, Steiner_Points* steiner_points);



#endif
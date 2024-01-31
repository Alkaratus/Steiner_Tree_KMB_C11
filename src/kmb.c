#include <stdio.h>
#include <time.h>

#include "kmb.h"
#include "Steiner_Points.h"
#include "Matrix.h"
#include "Utilities.h"
#include "Distance_Graph_Build.h"
#include "Subgraph_Creation_Data.h"

const unsigned int NUMBER_OF_THREADS=4;

void run_kmb(int vertex_count, int steiner_points_count){
    printf("C11 threads version of KBM method for determining the Steiner Tree of a graph.\n");
    struct timespec begin,start, end;

    clock_gettime(CLOCK_MONOTONIC, &begin);
    /* Step 0: Construct a graph G */
    clock_gettime(CLOCK_MONOTONIC, &start);
    Graph* graph = construct_graph(vertex_count);
    Steiner_Points* steiner_points = create_steiner_points(steiner_points_count, 1, graph->vertex_count);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 0 time used: %f seconds\n", calculate_time_from_timespec(start, end));


    /* Step 1: Construct the complete undirected distance graph G1 */
    clock_gettime(CLOCK_MONOTONIC, &start);
	Graph* distance_graph = create_distance_graph_parallel(graph, steiner_points);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 1 time used: %f seconds\n", calculate_time_from_timespec(start, end));

    /* Step 2: Find the minimal spanning tree T1 of the distance graph G1 */
    clock_gettime(CLOCK_MONOTONIC, &start);
    Graph* distance_graph_mst =prim_mst(distance_graph);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 2 time used: %f seconds\n", calculate_time_from_timespec(start, end));

    /* Step 3: Construct the subgraph Gs of G by replacing each edge in T1 by its shortest path in G */
    clock_gettime(CLOCK_MONOTONIC, &start);
    Graph* subgraph = construct_subgraph_with_distance_graph_mst_parallel(graph, distance_graph_mst, steiner_points);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 3 time used: %f seconds\n", calculate_time_from_timespec(start, end));

    /* Step 4: Find the minimal spanning tree Ts of Gs */
    clock_gettime(CLOCK_MONOTONIC, &start);
    Graph* steiner_tree = prim_mst(subgraph);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 4 time used: %f seconds\n", calculate_time_from_timespec(start, end));

    /* Step 5: Construct a steiner tree Th out of tree Ts, by deleting all the edges so that all the steiner points are leaves */
    clock_gettime(CLOCK_MONOTONIC, &start);
    construct_steiner_tree(steiner_tree, steiner_points);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nStep 5 time used: %f seconds\n", calculate_time_from_timespec(start, end));

    printf("\nTotal time: %f seconds\n", calculate_time_from_timespec(begin, end));

    // graph_print(graph);
	// graph_print(distance_graph);
    // graph_print(distance_graph_mst);
    // graph_print(subgraph);
    // graph_print(subgraph_mst);
    // graph_print(steiner_tree);

    deallocate_steiner_points_memory(steiner_points);
    graph_destroy(steiner_tree);
    graph_destroy(subgraph);
    graph_destroy(distance_graph);
    graph_destroy(graph);
}

Graph* construct_small_graph(){
    int V = 9; // Number of nodes in the graph
    Graph* graph = graph_create(V);
    graph_add_edge(graph, edge_create(0, 1, 20));
    graph_add_edge(graph, edge_create(0, 8, 2));
    graph_add_edge(graph, edge_create(1, 2, 16));
    graph_add_edge(graph, edge_create(1, 5, 2));
    graph_add_edge(graph, edge_create(2, 4, 4));
    graph_add_edge(graph, edge_create(2, 3, 18));
    graph_add_edge(graph, edge_create(3, 4, 4));
    graph_add_edge(graph, edge_create(4, 5, 2));
    graph_add_edge(graph, edge_create(4, 8, 2));
    graph_add_edge(graph, edge_create(5, 6, 2));
    graph_add_edge(graph, edge_create(6, 7, 1));
    graph_add_edge(graph, edge_create(7, 8, 1));
    return graph;
}

Graph* construct_graph(int size){
    Graph* graph = graph_create(size);

    // Add edges to the graph to ensure connectivity
    // The edges and weights are chosen arbitrarily to connect all nodes
    for (int i = 0; i < size; ++i){
        graph_add_edge(graph, edge_create(i, (i + 1) % size, i + 1));  // Connect each node to the next
    }

    // Add more edges to increase connectivity
    for (int i = 0; i < size; ++i){
        if (i + 2 < size){
            graph_add_edge(graph, edge_create(i, i + 2, (i + 2) % 10 + 1));  // Skip one node
        }
        if (i + 3 < size){
            graph_add_edge(graph, edge_create(i, i + 3, (i + 3) % 10 + 1));  // Skip two nodes
        }
        if (i + 5 < size){
            graph_add_edge(graph, edge_create(i, i + 5, (i + 5) % 10 + 1));  // Skip four nodes
        }
    }
    return graph;
}

Graph* create_distance_graph(Graph* graph, Steiner_Points* steiner_points){
    Graph* distance_graph = graph_create(steiner_points->count);
    for (int i = 0; i < steiner_points->count; ++i){
        for (int j = i + 1; j < steiner_points->count; ++j){
            Path* path = dijkstra_shortest_path(graph, steiner_points->points[i], steiner_points->points[j]);
            graph_add_edge(distance_graph, edge_create(i, j, path->total_weight));
            path_destroy(path);
        }
    }
    return distance_graph;
}

Graph* create_distance_graph_parallel(Graph* graph, Steiner_Points *steiner_points){
    Graph* distance_graph = graph_create(steiner_points->count);
    Distance_Graph_Build *build= distance_graph_build_create(graph,distance_graph,steiner_points);
    thrd_t threads[NUMBER_OF_THREADS];
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        thrd_create(&threads[i],create_distance_edge_thread,build);
    }
    int res;
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        thrd_join(threads[i],&res);
    }
    distance_graph_build_destroy(build);
    return distance_graph;
}

int create_distance_edge_thread(void *arg){
    Distance_Graph_Build *build= (Distance_Graph_Build*)arg;
    while(build->i1<build->steiner_points->count){
        mtx_lock(&build->mutex);
        int src= build->i1, dest=build->i2;
        build->i2++;
        if(build->i2>=build->steiner_points->count){
            build->i1++;
            build->i2=build->i1+1;
        }
        mtx_unlock(&build->mutex);
        if(build->i1<build->steiner_points->count){
            Path* path = dijkstra_shortest_path(build->graph, build->steiner_points->points[src], build->steiner_points->points[dest]);
            int min_distance = path->total_weight;
            path_destroy(path);
            graph_add_edge(build->distance_graph, edge_create(build->i1, build->i2, min_distance));
        }
    }
    return 0;
}

Graph* construct_subgraph_with_distance_graph_mst(Graph* graph, Graph* distance_graph_mst, Steiner_Points* steiner_points){
    if (graph == NULL || distance_graph_mst == NULL || steiner_points == NULL){
        return NULL;
    }
    Graph* subgraph = graph_create(graph->vertex_count);
    Matrix *already_added_edges= matrix_create(graph->vertex_count, graph->vertex_count);
    for (int vertex = 0; vertex < steiner_points->count; ++vertex){
        int path_src = steiner_points->points[vertex];
        Edge* edge = distance_graph_mst->adj_list[vertex].head;
        while (edge){
            int path_dest = steiner_points->points[edge->dest];
            Path* path = dijkstra_shortest_path(graph, path_src, path_dest);
            add_path_edges_to_graph(subgraph,path,already_added_edges);
            path_destroy(path);
            edge = edge->next;
        }
    }
    matrix_destroy(already_added_edges);
    return subgraph;
}

void add_path_edges_to_graph(Graph *graph,Path* path, Matrix* added_edges){
    Edge *edge=path->head;
    while (edge){
        if (!added_edges->values[edge->src][edge->dest]){
            graph_add_edge(graph, edge_create(edge->src, edge->dest, edge->weight));
            added_edges->values[edge->src][edge->dest] = 1;
            added_edges->values[edge->dest][edge->src] = 1;
        }
        edge = edge->next;
    }
}

Graph* construct_subgraph_with_distance_graph_mst_parallel(Graph* graph, Graph* distance_graph_mst, Steiner_Points* steiner_points){
    if (graph == NULL || distance_graph_mst == NULL || steiner_points == NULL){
        return NULL;
    }
    Graph* subgraph = graph_create(graph->vertex_count);
    Matrix *already_added_edges= matrix_create(graph->vertex_count, graph->vertex_count);
    Subgraph_Creation_Data *data= subgraph_creation_data_create(graph,subgraph,distance_graph_mst,already_added_edges,steiner_points);
    thrd_t threads[NUMBER_OF_THREADS];
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        thrd_create(&threads[i],add_vertex_edges_paths_to_subgraph_thread,data);
    }
    int res;
    for(int i=0;i<NUMBER_OF_THREADS;i++){
        thrd_join(threads[i],&res);
    }
    subgraph_creation_data_destroy(data);
    matrix_destroy(already_added_edges);
    return subgraph;
}

int add_vertex_edges_paths_to_subgraph_thread(void *arg){
    Subgraph_Creation_Data *data= (Subgraph_Creation_Data*) arg;
    while(data->vertex_index<data->distance_graph_mst->vertex_count){
        int working_vertex;
        mtx_lock(&data->index_guard);
        working_vertex=data->vertex_index;
        data->vertex_index++;
        mtx_unlock(&data->index_guard);
        if(working_vertex<data->distance_graph_mst->vertex_count) {
            int path_src = data->steiner_points->points[working_vertex];
            Edge* edge = data->distance_graph_mst->adj_list[working_vertex].head;
            while (edge){
                int path_dest = data->steiner_points->points[edge->dest];
                Path* path = dijkstra_shortest_path(data->graph, path_src, path_dest);
                add_path_edges_to_graph_secure(data->subgraph,path,data->already_added_edges,&data->matrix_guard);
                path_destroy(path);
                edge = edge->next;
            }
        }
    }
    return 0;
}

void add_path_edges_to_graph_secure(Graph *graph,Path* path, Matrix* added_edges,mtx_t *matrix_guard){
    Edge *edge=path->head;
    while (edge){
        mtx_lock(matrix_guard);
        if (!added_edges->values[edge->src][edge->dest]){
            graph_add_edge(graph, edge_create(edge->src, edge->dest, edge->weight));
            added_edges->values[edge->src][edge->dest] = 1;
            added_edges->values[edge->dest][edge->src] = 1;
        }
        mtx_unlock(matrix_guard);
        edge = edge->next;
    }
}

void construct_steiner_tree(Graph* graph, Steiner_Points* steiner_points){
    if (graph == NULL || steiner_points->count < 1){
        return;
    }
    if(steiner_points->count > graph->vertex_count){
        return;
    }
    for (int vertex = 0; vertex < graph->vertex_count; ++vertex){
        if (is_leaf(graph, vertex) && !is_steiner_point(steiner_points, vertex)){
            int src = graph->adj_list[vertex].head->src;
            int dest = graph->adj_list[vertex].head->dest;
            remove_edge(graph, src, dest);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Graph.h"
#include "Matrix.h"



Graph* graph_create(int vertex_count){
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->vertex_count = vertex_count;
	graph->adj_list = calloc(vertex_count, sizeof(Adjacency_List));
	return graph;
}

void graph_destroy(Graph* graph){
    for (int i = 0; i < graph->vertex_count; ++i){
        destroy_adjacency_list(&graph->adj_list[i]);
    }
    free(graph->adj_list);
    free(graph);
}

void graph_add_edge(Graph* graph, Edge *edge){
	if (edge->src < 0 || edge->dest < 0 || edge->src > graph->vertex_count - 1 || edge->dest > graph->vertex_count - 1) {
        return;
    }
    adjacency_list_add_edge(&graph->adj_list[edge->src],edge);
    adjacency_list_add_edge(&graph->adj_list[edge->dest], edge_reversed(edge));
}

void remove_edge(Graph* graph, int src, int dest){
	if (graph->adj_list[src].head == NULL || graph->adj_list[dest].head == NULL){
        return;
    }
    adjacency_list_remove_edge(&graph->adj_list[src],dest);
    adjacency_list_remove_edge(&graph->adj_list[dest],src);
}

int graph_first_connected_vertex_index(Graph *graph) {
    int index=0;
    while(index<graph->vertex_count){
        if (graph->adj_list[index].head != NULL){
            return index;
        }
    }
    return -1;
}

void graph_print(Graph* graph){
	printf("\n|--------------------------------GRAPH---------------------------------|\n");
	for (int v = 0; v < graph->vertex_count; ++v){
        printf("Vertex (%d)\n    connects with:", v);
        adjacency_list_display(&graph->adj_list[v]);
	}
	printf("|----------------------------------------------------------------------|\n");
}

int find_weight(Graph* graph, int src, int dest){
    if (graph == NULL){
        return -1;
    }
    return adjacency_list_find_weight_of_edge_to_vertex(&graph->adj_list[src],dest);
}

int is_leaf(Graph* graph, int vertex){
	if (graph->vertex_count < 1 || vertex < 0 || vertex > graph->vertex_count - 1){
        return 0;
    }
	return graph->adj_list[vertex].head != NULL && graph->adj_list[vertex].head->next == NULL;
}
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "Adjacency_List.h"
#include "Path.h"

struct Graph;

typedef Path(*graph_searching_algotithm)(struct Graph* graph,int src,int dest) ;


// Structure to represent a graph. A graph is an array of adjacency lists.
typedef struct Graph{
	int vertex_count;
	Adjacency_List* adj_list;
} Graph;


Graph* graph_create(int vertex_count);
void graph_destroy(Graph* graph);
void graph_add_edge(Graph* graph, Edge *edge);
void remove_edge(Graph* graph, int src, int dest);
///returns graph's first vertex index which is connected with other vertex or returns -1 if no vertices in graph
///are connected to another
int graph_first_connected_vertex_index(Graph *graph);
void graph_print(Graph* graph);
///Function to find weight of an edge from src to dest
int find_weight(Graph* graph, int src, int dest);
int is_leaf(Graph* graph, int vertex);


#endif // GRAPH_H
#include <stdlib.h>
#include "Edge.h"

Edge* edge_create(int src, int dest, int weight){
	Edge* new_edge = (Edge*) malloc(sizeof(Edge));
	new_edge->src = src;
	new_edge->dest = dest;
	new_edge->weight = weight;
	new_edge->next = NULL;
	return new_edge;
}

Edge* edge_reversed(Edge *edge){
	Edge* new_edge = (Edge*) malloc(sizeof(Edge));
	new_edge->src = edge->dest;
	new_edge->dest = edge->src;
	new_edge->weight = edge->weight;
	new_edge->next = NULL;
	return new_edge;
}

void edge_destroy(Edge *edge){
    free(edge);
}

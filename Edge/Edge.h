#ifndef EDGE_H
#define EDGE_H

// Structure to represent an adjacency list node
typedef struct Edge{
    int src;
	int dest;
	int weight;
	struct Edge* next;
} Edge;

Edge* edge_create(int src, int dest, int weight);
Edge* edge_reversed(Edge *edge);
void edge_destroy(Edge *edge);

#endif // EDGE_H

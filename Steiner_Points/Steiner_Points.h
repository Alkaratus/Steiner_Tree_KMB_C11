#ifndef STEINER_POINTS_H
#define STEINER_POINTS_H

typedef struct Steiner_Points{
    int count;
    int* points;
} Steiner_Points;

Steiner_Points* create_steiner_points(int count, int option, int graph_size);

/*
    Function that checks whether a node of given vertex in
    the graph is a steiner point. It returns 1 if so, 0 otherwise.
*/
int is_steiner_point(Steiner_Points* steiner_points, int vertex);

void deallocate_steiner_points_memory(Steiner_Points* steiner_points);

#endif
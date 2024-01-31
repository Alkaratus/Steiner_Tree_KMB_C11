//
// Created by alkaratus on 27.12.23.
//

#ifndef KMB_PTHREADS_DIJKSTRA_SHORTEST_PATH_H
#define KMB_PTHREADS_DIJKSTRA_SHORTEST_PATH_H

#include "Path_To_Source.h"
#include "Graph.h"

///Implementation of Dijkstra's shortest path algorithm from provided source to destination
///returned path structure have to be destroyed by path_destroy function from Path.h
Path* dijkstra_shortest_path(Graph* graph, int src, int dest);




#endif //KMB_PTHREADS_DIJKSTRA_SHORTEST_PATH_H

//
// Created by alkaratus on 27.12.23.
//

#include <limits.h>
#include "Dijkstra_Shortest_Path.h"

///Return index of vertex with minimum distance value, from the set of vertices not yet included in the shortest path
static int min_distance(Path_To_Source paths[], int vertex_count);
///Creates paths array for Dijkstra algorithm array is deleted at end of Dijkstra algorithm function
static Path_To_Source* create_paths(int number_of_vertices, int src);
///Finds shortest way for vertices of provided graph
static void find_shortest_ways_for_vertices(Graph *graph, Path_To_Source paths[]);
///Creates path from destination to source path struct is then returned by Dijkstra algorithm function
static Path* create_path_to_destination(Graph *graph,Path_To_Source paths[],int dest);


Path* dijkstra_shortest_path(Graph* graph, int src, int dest){
    Path_To_Source *paths= create_paths(graph->vertex_count,src);
    if(paths==NULL){
        return NULL;
    }
    find_shortest_ways_for_vertices(graph,paths);
    Path* path = create_path_to_destination(graph,paths,dest);
    free(paths);
    return path;
}

static int min_distance(Path_To_Source paths[], int vertex_count){
    int min = INT_MAX;
    int min_index = -1;
    for (int v = 0; v < vertex_count; ++v){
        if ((!paths[v].shortest) && paths[v].distance <= min){
            min = paths[v].distance;
            min_index = v;
        }
    }
    return min_index;
}

static Path_To_Source* create_paths(int number_of_vertices, int src){
    Path_To_Source *paths= calloc(number_of_vertices,sizeof(Path_To_Source));
    if (paths==NULL){
        return NULL;
    }
    for (int i = 0; i < number_of_vertices; ++i){
        paths[i]=path_to_source_create_empty();
    }
    paths[src].distance = 0;
    return paths;
}

static void find_shortest_ways_for_vertices(Graph *graph, Path_To_Source paths[]){
    for (int count = 0; count < graph->vertex_count - 1; ++count){
        int min_index = min_distance(paths, graph->vertex_count);
        if (min_index == -1 || paths[min_index].shortest || paths[min_index].distance == INT_MAX){
            continue;
        }
        paths[min_index].shortest = true;
        // Update dist value of the adjacent vertices of the picked vertex
        for (Edge* edge = graph->adj_list[min_index].head; edge != NULL; edge = edge->next){
            int v = edge->dest;
            if ((!paths[v].shortest) && paths[min_index].distance + edge->weight < paths[v].distance){
                paths[v].previous = min_index;
                paths[v].distance = paths[min_index].distance + edge->weight;
            }
        }
    }
}

static Path *create_path_to_destination(Graph *graph,Path_To_Source paths[],int dest){
    Path* path = path_empty_create(paths[dest].distance);
    int u = dest;
    Edge** current_edge = &path->head;
    while (paths[u].previous != NO_PREVIOUS_VERTEX){
        int weight = find_weight(graph, paths[u].previous, u);
        Edge* new_edge = edge_create(paths[u].previous, u, weight);
        *current_edge=new_edge;
        current_edge= &((*current_edge)->next);
        u = paths[u].previous;
    }
    return path;
}
//
// Created by alkaratus on 27.12.23.
//
#include <limits.h>
#include "Prim_MST.h"
#include "Mst_Node.h"
#include "Matrix.h"

/// Creates mst nodes array for Prim algorithm
int min_key(Mst_Node nodes[], int vertex_count);
static Mst_Node* create_mst_nodes(Graph *graph);
static void find_minimal_keys_for_nodes(Graph *graph, Mst_Node nodes[]);
static Graph* create_mst_graph(Mst_Node nodes[],int number_of_vertices);


Graph* prim_mst(Graph* graph){
    Mst_Node *mst_nodes= create_mst_nodes(graph);
    if (mst_nodes==NULL){
        return NULL;
    }

    int first_connected_vertex = graph_first_connected_vertex_index(graph);
    if (first_connected_vertex == -1){
        return NULL;
    }

    mst_nodes[first_connected_vertex].key = 0;
    mst_nodes[first_connected_vertex].parent = NO_PARENT_FOR_ROOT;

    find_minimal_keys_for_nodes(graph,mst_nodes);
    Graph* mst=create_mst_graph(mst_nodes,graph->vertex_count);
    free(mst_nodes);
    return mst;
}

int min_key(Mst_Node nodes[], int vertex_count){
    int min = INT_MAX;
    int min_index = -1;
    for (int v = 0; v < vertex_count; ++v){
        if ((!nodes[v].set) && nodes[v].key <= min){
            min = nodes[v].key;
            min_index = v;
        }
    }
    return min_index;
}

static Mst_Node *create_mst_nodes(Graph *graph){
    Mst_Node *mst_nodes= calloc(graph->vertex_count,sizeof(Mst_Node));
    if (mst_nodes==NULL){
        return NULL;
    }
    for (int i = 0; i < graph->vertex_count; ++i){
        mst_nodes[i].key = INT_MAX;
        mst_nodes[i].set = graph->adj_list[i].head == NULL;
        if (mst_nodes[i].set){
            mst_nodes[i].parent = PARENT_CANT_EXIST;
        }
    }
    return mst_nodes;
}

static void find_minimal_keys_for_nodes(Graph *graph, Mst_Node nodes[]){
    for (int count = 0; count < graph->vertex_count - 1; ++count){
        int u = min_key(nodes, graph->vertex_count);
        if (u == -1 || nodes[u].set)
            continue;

        nodes[u].set = true;

        for (Edge* edge = graph->adj_list[u].head; edge != NULL; edge = edge->next){
            int dest = edge->dest;
            if ((!nodes[dest].set) && edge->weight < nodes[dest].key){
                nodes[dest].parent = u;
                nodes[dest].key = edge->weight;
            }
        }
    }
}

static Graph* create_mst_graph(Mst_Node nodes[],int number_of_vertices){
    Graph* mst = graph_create(number_of_vertices);
    for (int i = 0; i < number_of_vertices; ++i){
        if (nodes[i].parent >= 0){
            graph_add_edge(mst, edge_create(nodes[i].parent, i, nodes[i].key));
        }
    }
    return mst;
}
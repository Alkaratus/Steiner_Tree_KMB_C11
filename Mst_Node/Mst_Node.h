#ifndef KMB_PTHREADS_MST_NODE_H
#define KMB_PTHREADS_MST_NODE_H

#include <stdbool.h>

int static const PARENT_CANT_EXIST=-2;
int static const NO_PARENT_FOR_ROOT=-1;

typedef struct Mst_Node{
    int parent;
    int key;
    bool set;
}Mst_Node;

Mst_Node mst_node_create_empty();

#endif //KMB_PTHREADS_MST_NODE_H

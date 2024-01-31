//
// Created by alkaratus on 10.12.23.
//

#include <limits.h>
#include "Mst_Node.h"

Mst_Node mst_node_create_empty() {
    Mst_Node result={
            .key=INT_MAX,
            .set=false
    };
    return result;
}

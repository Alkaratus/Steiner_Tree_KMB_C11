//
// Created by alkaratus on 05.12.23.
//

#include <limits.h>
#include "Path_To_Source.h"



Path_To_Source path_to_source_create_empty() {
    Path_To_Source new;
    new.distance=INT_MAX;
    new.previous=NO_PREVIOUS_VERTEX;
    new.shortest=false;
    return new;
}

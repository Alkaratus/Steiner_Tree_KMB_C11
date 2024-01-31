//
// Created by alkaratus on 27.12.23.
//

#include "Utilities.h"

double calculate_time_from_clocks(clock_t start, clock_t end){
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double calculate_time_from_timespec(struct timespec start, struct timespec end) {
    double elapsed;
    elapsed = (double) (end.tv_sec - start.tv_sec);
    elapsed += (double) (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    return elapsed;
}

//
// Created by alkaratus on 27.12.23.
//

#ifndef KMB_PTHREADS_UTILITIES_H
#define KMB_PTHREADS_UTILITIES_H

#include <time.h>

double calculate_time_from_clocks(clock_t start, clock_t end);

double calculate_time_from_timespec(struct timespec start, struct timespec end);

#endif //KMB_PTHREADS_UTILITIES_H

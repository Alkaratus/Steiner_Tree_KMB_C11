#include "Steiner_Points.h"

#include <stdlib.h>

Steiner_Points* create_steiner_points(int count, int option, int graph_size)
{
	Steiner_Points* steiner_points = (Steiner_Points*) malloc(sizeof(Steiner_Points));
	steiner_points->count = count;
	steiner_points->points = (int*) malloc(count * sizeof(int));

	if (option == 0) // steiner points are points with indices from 0 to (count - 1) 
	{
		for (int i = 0; i < count; ++i)
			steiner_points->points[i] = i;
	}
	else // evenly distributed steiner points
	{
		int interval = graph_size / count;
		for (int i = 0; i < count; ++i)
		{
			steiner_points->points[i] = i * interval;

			if (steiner_points->points[i] >= graph_size)
				steiner_points->points[i] = graph_size - 1;
		}
	}

	return steiner_points;
}

int is_steiner_point(Steiner_Points* steiner_points, int vertex)
{
	if (vertex < 0)
		return 0;

	for (int i = 0; i < steiner_points->count; ++i)
	{
		if (vertex == steiner_points->points[i])
			return 1;
	}	

	return 0;
}

void deallocate_steiner_points_memory(Steiner_Points* steiner_points)
{
	free(steiner_points->points);
	free(steiner_points);
}
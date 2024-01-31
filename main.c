#include <stdio.h>
#include <stdlib.h>
#include "Graph/Graph.h"
#include "src/kmb.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		printf("Wrong number of input parameters!\n");
		printf("	- First one should be the graph size\n");
		printf("	- Second one should be the number of steiner points\n");
		return 1;
	}

	int vertex_count = strtol(argv[1], NULL, 10);
	int steiner_points_count = strtol(argv[2], NULL, 10);

	if (vertex_count < steiner_points_count)
	{
		printf("Number of steiner points can't be greater then the total number of vertices!\n");
		return 1;
	}
	if (vertex_count == 0 || steiner_points_count == 0)
	{
		printf("Number of steiner points or total number of vertices can't be 0!\n");
		return 1;
	}

	run_kmb(vertex_count, steiner_points_count);

	return 0;
}

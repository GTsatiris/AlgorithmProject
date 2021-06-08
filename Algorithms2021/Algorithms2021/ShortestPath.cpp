#include "ShortestPath.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define V 50
#define DISCON_RATIO 0.7

int Graph_10[V][V];
int Graph_25[V][V];
int Graph_50[V][V];
int Graph_100[V][V];

void Initialize();
void PrintAdjacencyMatrix(int graph[V][V]);
void DijkstraAlgorithm(int graph[V][V], int start);
void PrintShortestPath();

void DoDijkstra()
{
	srand((unsigned int)time(NULL));

	cout << endl << "Initializing graphs..." << endl;
	Initialize();

	cout << endl << "******** GRAPH_10 ********" << endl;
	for(int i = 0; i < 5; i++)
	{
		cout << endl << "Try " << i + 1 << ":" << endl;
		DijkstraAlgorithm(Graph_10, 0);
	}

	cout << endl << "******** GRAPH_25 ********" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "Try " << i + 1 << ":" << endl;
		DijkstraAlgorithm(Graph_25, 0);
	}

	cout << endl << "******** GRAPH_50 ********" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "Try " << i + 1 << ":" << endl;
		DijkstraAlgorithm(Graph_50, 0);
	}

	cout << endl << "******** GRAPH_100 ********" << endl;
	for (int i = 0; i < 5; i++)
	{
		cout << endl << "Try " << i + 1 << ":" << endl;
		DijkstraAlgorithm(Graph_100, 0);
	}
}

void Initialize()
{
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			int rand10 = rand() % 10 + 1;
			Graph_10[i][j] = rand10;
			Graph_10[j][i] = rand10;

			int rand25 = rand() % 25 + 1;
			Graph_25[i][j] = rand25;
			Graph_25[j][i] = rand25;

			int rand50 = rand() % 50 + 1;
			Graph_50[i][j] = rand50;
			Graph_50[j][i] = rand50;

			int rand100 = rand() % 100 + 1;
			Graph_100[i][j] = rand100;
			Graph_100[j][i] = rand100;
		}
	}

	int rand_i_idx[(int)(V * DISCON_RATIO)];
	int rand_j_idx[(int)(V * DISCON_RATIO)];
	for (int k = 0; k < (int)(V * DISCON_RATIO); k++)
	{
		rand_i_idx[k] = rand() % V;
		rand_j_idx[k] = rand() % V;

		Graph_10[rand_i_idx[k]][rand_j_idx[k]] = 0;
		Graph_10[rand_j_idx[k]][rand_i_idx[k]] = 0;

		Graph_25[rand_i_idx[k]][rand_j_idx[k]] = 0;
		Graph_25[rand_j_idx[k]][rand_i_idx[k]] = 0;

		Graph_50[rand_i_idx[k]][rand_j_idx[k]] = 0;
		Graph_50[rand_j_idx[k]][rand_i_idx[k]] = 0;

		Graph_100[rand_i_idx[k]][rand_j_idx[k]] = 0;
		Graph_100[rand_j_idx[k]][rand_i_idx[k]] = 0;
	}

	//Vertices don't have edges with themselves
	for (int i = 0; i < V; i++)
	{
		Graph_10[i][i] = 0;
		Graph_25[i][i] = 0;
		Graph_50[i][i] = 0;
		Graph_100[i][i] = 0;
	}
}

int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false &&
			dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// Function to print shortest
// path from source to j
// using parent array
void printPath(int parent[], int j)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}

// A utility function to print 
// the constructed distance
// array
void printSolution(int dist[], int n, int parent[])
{
	int src = 0;
	printf("Vertex\t Distance\tPath");
	for (int i = 1; i < V; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ",
			src, i, dist[i], src);
		printPath(parent, i);
	}
}

void DijkstraAlgorithm(int graph[V][V], int src)
{
	// The output array. dist[i]
	// will hold the shortest
	// distance from src to i
	int dist[V];

	// sptSet[i] will true if vertex
	// i is included / in shortest
	// path tree or shortest distance 
	// from src to i is finalized
	bool sptSet[V];

	// Parent array to store
	// shortest path tree
	int parent[V];

	// Initialize all distances as 
	// INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex 
	// from itself is always 0
	dist[src] = 0;

	// Find shortest path
	// for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance
		// vertex from the set of
		// vertices not yet processed. 
		// u is always equal to src
		// in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex 
		// as processed
		sptSet[u] = true;

		// Update dist value of the 
		// adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is
			// not in sptSet, there is
			// an edge from u to v, and 
			// total weight of path from
			// src to v through u is smaller
			// than current value of
			// dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}

	// print the constructed
	// distance array
	printSolution(dist, V, parent);
}

void PrintAdjacencyMatrix(int graph[V][V])
{
	cout << endl;
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			cout << graph[i][j] << " - ";
		}
		cout << endl;
	}
	cout << endl;
}

// A utility function to print the constructed distance array
void PrintShortestPath()
{

}
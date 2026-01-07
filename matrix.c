#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   int undirected; // 1 for directe or 0 for undirected
   int N; // number of vertices
   int ** E; // number of edges
} *graphPT;

// graph.h
/*
 * Creates a new graph with N vertices.
 *
 * N           : initial number of vertices (labeled 0 to N-1)
 * undirected  : 1 for undirected graph, any other value for directed
 *
 * returns     : pointer to the newly created graph
 */

// Graph creation / destruction
graphPT newGraph(int N, int undirected)
{
    graphPT result = (graphPT) malloc(sizeof(*result));
    result -> undirected = undirected;
    result -> N = N;

    result -> E = (int **) calloc(N, sizeof(int *));

    for(int row = 0; row < N; ++row)
    {
       result -> E[row] = (int*) calloc(N, sizeof(int));
    }
}
void destroyGraph(graphPT g)
{
    if(g == NULL) return;
    
    int size = g ->N;
    for (int row = 0; row < size; ++row)
    {
        free(g -> E[row]);
    }

    free(g -> E);
    free(g);
}

// Basic graph info
int numVertices(graphPT g)
{
    if(g == NULL) return;
    return g->N;
}

int vertexValidity(graphPT g, int vertex)
{
    if(g == NULL) return;
    if(vertex < 0 || vertex)
}
// Edge operations
int edgeExists(graphPT g, int v1, int v2)
{
    if(g == NULL) return; return;
}
int addEdge(graphPT g, int v1, int v2);
int removeEdge(graphPT g, int v1, int v2);

// Vertex operations
int* vertexNeighbors(graphPT g, int v, int* res_size);

// Display helpers
void printGraph(graphPT g);
void printNeighbors(graphPT g, int v);

// Accessors
int** getAdjacencyMatrix(graphPT g);


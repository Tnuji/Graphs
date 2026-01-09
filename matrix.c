#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   int undirected; // 1 for undirected or 0 for directed
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
// Function destroys the created graph.
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

// Counts how many vertices(points) there are.
int numVertices(graphPT g)
{
    if(g == NULL) return;
    return g->N;
}

//Checks whether or not a vertex is valid
int vertexValidity(graphPT g, int vertex)
{
    if(g == NULL) return;
    if(vertex < 0 || vertex >= (g -> N))
    {
        return 0;
    }
    return 1;
}
// Checks whether or not there exists an edge(connection) between two vertices(points)
int edgeExists(graphPT g, int v1, int v2)
{
    if(g == NULL) return 0;
    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! No edge!");
        return 0;
    }

    return g -> E[v1][v2];
}

//Creates an edge (connection) between two points
void addEdge(graphPT g, int v1, int v2)
{
    if(g == NULL) return;
    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! Edge not created.");
        return;
    }
    g -> E[v1][v2] = 1;
    if(g -> undirected == 1)
    {
        g -> E[v2][v1] = 1;
    }
}
//Remove an edge(connection) from the graph
int removeEdge(graphPT g, int v1, int v2)
{
    if(g == NULL) return;
    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! Edge not created.");
        return;
    }
    g -> E[v1][v2] = 0;
    if(g -> undirected == 1)
    {
        g -> E[v2][v1] = 0;
    }
}

// Vertex operations
int* vertexNeighbors(graphPT g, int v, int* res_size)
{
    if(g == NULL) return;
    if(!(vertexValidity(g, v)))
    {
        printf("\nInvalid Vertex! Edge not created.");
        return;
    }

    int count = 0;
    for(int i = 0; i < g -> N; ++i)
    {
        if(g -> E[v][i] == 1)
        {
            ++count;
        }
    }

    res_size = count;
    int *res = malloc(count * sizeof(int));

    int j = 0;
    for(int i = 0; i < g -> N; ++i)
    {
        if(g -> E[v][i] == 1)
        {
            res[j] = i;
            ++j;
        }
    }

    return res;
}

// Display helpers
void printGraph(graphPT g);
void printNeighbors(graphPT g, int v);

// Accessors
int** getAdjacencyMatrix(graphPT g);


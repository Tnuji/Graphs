#include <stdio.h>
#include <stdlib.h>

/* Forward declarations */
typedef struct graph* graphPT;
typedef struct node* nodePT;

/* Graph structure (adjacency list representation) */
typedef struct graph
{
    int undirected;   // 1 = undirected, else is directed
    int N;            // number of vertices
    nodePT* E;        // array of adjacency lists
}graph;

typedef struct node
{
    int data;
    struct node *next;
}node;

/* Linked-list helper */
nodePT delete_by_data(nodePT L, int data)
{
    if (L == NULL) return NULL;

    nodePT curr = L -> next;
    nodePT prev = L;

    if(prev -> data == data)
    {
        prev -> next = NULL;
        free(prev);
        return curr;
    }

    while(curr != NULL)
    {
        if(curr -> data == data)
        {
            prev -> next = curr -> next;
            free(curr);
            
            break;
        }
        else
        {
            prev = curr;
            curr = curr -> next;
        }

        return L;
    }
}

/* Graph creation / destruction */
graphPT newGraph(int N, int undirected)
{
    graphPT result = malloc (sizeof(*result));
    result -> undirected = undirected;
    result -> E = malloc(N * sizeof(nodePT));

    for(int i = 0; i < N; ++i)
    {
        result -> E[i] = NULL;
    }
    
    return result;
}
void destroy_list(nodePT L)
{
    if(L == NULL) return;

    nodePT curr = L;

    while(curr != NULL)
    {
        nodePT next = curr -> next;
        free(curr);
        curr = next;
    }
}
void destroyGraph(graphPT g)
{
    if (g == NULL) return;

    for(int i = 0; i < g -> N; ++i)
    {
        destroy_list(g -> E[i]);
    }

    free(g -> E);
    free(g);
}

/* Graph properties */
int numVertices(graphPT g)
{
    if(g == NULL)return;
    return g->N;
}

/* Vertex operations */
int* vertexNeighbors(graphPT g, int v, int* res_size);

/* Edge operations */
int edgeExists(graphPT g, int v1, int v2);
int addEdge(graphPT g, int v1, int v2);
int removeEdge(graphPT g, int v1, int v2);

/* Printing */
void printGraph(graphPT g);
void printNeighbors(graphPT g, int v);

/* Optional / unsupported */
int** getAdjacencyMatrix(graphPT g);
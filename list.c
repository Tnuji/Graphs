#include <stdio.h>
#include <stdlib.h>

/* Forward declarations */
typedef struct graph* graphPT;
typedef struct node* nodePT;

/* Graph structure (adjacency list representation) */
typedef struct
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
graphPT newGraph(int N, int undirected);
void destroyGraph(graphPT g);

/* Graph properties */
int numVertices(graphPT g);

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
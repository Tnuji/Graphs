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
    }
    return L;
}

/* Graph creation / destruction */
graphPT newGraph(int N, int undirected)
{
    graphPT result = malloc (sizeof(*result));
    result -> undirected = undirected;
    result -> E = malloc(N * sizeof(nodePT));
    result -> N = N;

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
    if(g == NULL) return 0;
    return g->N;
}

//Checks whether or not a vertex is valid
int vertexValidity(graphPT g, int vertex)
{
    if(g == NULL) return 0;
    if(vertex < 0 || vertex >= (g -> N))
    {
        return 0;
    }
    return 1;
}
/* Vertex operations */
int* vertexNeighbors(graphPT g, int v, int* res_size)
{
    if(g == NULL) return NULL;
    if(!(vertexValidity(g, v)))
    {
        printf("\nInvalid Vertex! Edge not created.");
        return NULL;
    }

    int count = 0;
    nodePT curr = g ->E[v];

    while(curr != NULL)
    {
        ++count;
        curr = curr -> next;
    }

    *res_size = count;
    int *res = malloc(count * sizeof(int));

    int j = 0;
    curr = g -> E[v];
    while(curr != NULL)
    {
        res[j] = curr -> data;
        ++j;
        curr = curr -> next;
    }

    return res;
}

/* Edge operations */
int edgeExists(graphPT g, int v1, int v2)
{
    if (g == NULL)return 0;

    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! No edge!");
        return 0;
    }

    nodePT curr = g -> E[v1];
    
    while(curr != NULL)
    {
        if(curr -> data == v2)
        {
            return 1;
        }
        curr = curr -> next;
    }

    return 0;

}

void addEdge(graphPT g, int v1, int v2)
{
    if(g == NULL) return;
    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! No edge!");
        return;
    }

    nodePT node1 = malloc(sizeof(*node1));
    node1 -> data = v2;
    if(g -> E[v1] == NULL)
    {
        g -> E[v1] = node1;
        node1 -> next = NULL;
    }
    else
    {
        nodePT holder  = g ->E[v1];
        g -> E[v1] = node1;
        node1 -> next = holder;
    }

    if(g -> undirected == 1)
    {
        nodePT node2 = malloc(sizeof(*node2));
        node2 -> data = v1;
        if(g -> E[v2] == NULL)
        {
            g -> E[v2] = node2;
            node2 -> next = NULL;
        }
        else
        {
            nodePT holder  = g ->E[v2];
            g -> E[v2] = node2;
            node2 -> next = holder;
        } 
    }

}
void removeEdge(graphPT g, int v1, int v2)
{
    if(g == NULL) return;
    if(!(vertexValidity(g, v1)) || ! (vertexValidity(g, v2)))
    {
        printf("\nInvalid Vertex! No edge!");
        return;
    }

    if(edgeExists(g,v1,v2))
    {
        nodePT curr = g -> E[v1];
        if(curr -> data == v2)
        {
            g -> E[v1] = curr -> next;
            free(curr);
            return;
        }
        while(curr -> next != NULL)
        {
            
            if(curr -> next -> data == v2)
            {
                nodePT holder = curr -> next;
                curr -> next = curr -> next -> next;
                free(holder);
                break;
            }

            curr  = curr -> next;
        }

        if(g -> undirected == 1)
        {
            curr = g -> E[v2];
            if(curr -> data == v1)
            {
                g -> E[v2] = curr -> next;
                free(curr);
                return;
            }
            while(curr -> next != NULL)
            {
            
                if(curr -> next -> data == v1)
                {
                    nodePT holder = curr -> next;
                    curr -> next = curr -> next -> next;
                    free(holder);
                    return;
                }

                curr  = curr -> next;
            }
        }
    }
}

/* Printing */
void printNeighbors(graphPT g, int v)
{
    if(g == NULL) return;

    if(!(vertexValidity(g,v)))
    {
        printf("\nInvalid Vertex!");
        return;
    }

    int neighbors_size;
    int *neighbors  = vertexNeighbors(g, v, &neighbors_size);

    printf("\nVertex %d neighbors: ", v);
    for(int i = 0; i < neighbors_size; ++i)
    {
        printf("%d", neighbors[i]);
        if(i != neighbors_size - 1)
        {
            printf(", ");
        }
    
    }

    free(neighbors);
}

void printGraph(graphPT g)
{
    if(g == NULL) return;

    for(int v = 0; v < g -> N; ++v)
    {
        printNeighbors(g,v);
        printf("\n");
    }

    printf("\n");


}

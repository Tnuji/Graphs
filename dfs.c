#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define NIL -1

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

void dfs_list(graphPT G)
{
    int color[G -> N];
    int pred[G -> N];

    for(int i = 0; i < G -> N; ++i)
    {
        color[i] = WHITE;
        pred[i] = NIL;
    }
    for(int i = 0; i < G -> N; ++i)
    {
        if(color[i] == WHITE)
        {
            dfs_visit_list(G, i, color, pred);
        }
    }
    
}
void dfs_visit_list(graphPT G, int u, int color[], int pred[])
{
    color[u] = GRAY;
    nodePT curr = G -> E[u];
    
    if(curr != NULL)
    {
        while(curr != NULL)
        {
            if(color[curr -> data] == WHITE)
            {
                pred[curr ->data] = u;
                dfs_visit(G,curr -> data, color, pred);
            }
            else if(color[curr -> data] == GRAY)
            {
                printf("Cycle found");
            }
            curr = curr -> next;
        }
    }

    color[u] = BLACK;
    printf("%d ", u);
}

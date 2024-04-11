#include <stdio.h>

typedef struct node
{
    char *vertex;
    int weight;
    struct node *next;
    int id;
} Node;

typedef struct vertex
{ 
    char *vertex;
    Node *edges;
    
} Vertex;

typedef struct graph
{
    int V;
    Vertex *array;
} Graph;

void initGraph(Graph * g, int numberOfVertices);
Node *generateNode(Graph g,char *vertex, int weight);
void addVertex(Graph *g, char *vertex);
int checkVertex(Graph g, char *vertex);
void addEdge(Graph *g, char *vertex1, char *vertex2, int weight);


void dfs(Graph g, char * visited, char vertex);
void bfs(Graph g, char * visited, char vertex);

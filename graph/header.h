#include"../sphere.c"
typedef struct node
{
    char *vertex;
    int weight;
    struct node *next;
    int id;
} Node;

typedef struct coord{
    GLfloat x,y,z;
}coord;

typedef struct vertex
{ 
    char *vertex;
    Node *edges;
    coord loc;
    
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
int count(Graph g);

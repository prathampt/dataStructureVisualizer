#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    int numVertices;
    Node** adjLists; 

    int numEdges;
    int* edges; 
} Graph;


Node* createNode(int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; ++i) {
        graph->adjLists[i] = NULL;
    }
    graph->numEdges = 0;
    graph->edges = NULL;
    return graph;
}


void addEdge(Graph* graph, int src, int dest, int weight) {
  
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;

    graph->numEdges++;
    graph->edges = realloc(graph->edges, graph->numEdges * 3 * sizeof(int));
    graph->edges[(graph->numEdges - 1) * 3] = src;
    graph->edges[(graph->numEdges - 1) * 3 + 1] = dest;
    graph->edges[(graph->numEdges - 1) * 3 + 2] = weight;
}


void BFS(Graph* graph, int startVertex) {

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }


    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;


    visited[startVertex] = 1;
    queue[rear++] = startVertex;

 
    while (front < rear) {

        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

  
        Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue);
}


void DFSUtil(Graph* graph, int v, int* visited) {
  
    visited[v] = 1;
    printf("%d ", v);

    Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void DFS(Graph* graph, int startVertex) {

    int* visited = (int*)malloc(graph->numVertices * sizeof(int));
    for (int i = 0; i < graph->numVertices; ++i) {
        visited[i] = 0;
    }

  
    DFSUtil(graph, startVertex, visited);

    free(visited);
}


typedef struct {
    int src;
    int dest;
    int weight;
} Edge;


int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

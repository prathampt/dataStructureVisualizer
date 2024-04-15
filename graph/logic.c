#include "header.h"
#include "queue/logic.c"
#include "../sphere.c"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Constants
#define PI 3.14159

Graph globalGraph;

coord *fibonacci_sphere(int samples)
{
    coord *points = (coord *)malloc(samples * sizeof(coord));
    float phi = PI * (sqrt(5.0) - 1.0);

    for (int i = 0; i < samples; i++)
    {
        float y = (1.0 - (i / (double)(samples - 1)) * 2.0) * 3.0;
        float radius = sqrt(10 - y * y);

        float theta = phi * i;
        float x = cos(theta) * radius;
        float z = sin(theta) * radius;

        points[i].x = x;
        points[i].y = y;
        points[i].z = z;
    }

    return points;
}

int count(Graph *g)
{
    int cnt = 0;
    int i = 0;
    while (g->array[i].vertex != NULL)
    {
        cnt += 1;
        i += 1;
    }
    return cnt;
}
void initGraph(Graph *g, int numberOfVertices)
{
    g->V = numberOfVertices;

    g->array = (Vertex *)malloc(sizeof(Vertex) * numberOfVertices);

    for (int i = 0; i < numberOfVertices; i++)
    {
        g->array[i].loc.x = i;
        g->array[i].loc.y = i;
        g->array[i].loc.z = i;

        g->array[i].vertex = NULL;
    }

    return;
}

Node *generateNode(Graph g, char *vertex, int weight, int id)
{
    char *str = (char *)malloc(sizeof(char) * strlen(vertex));
    strcpy(str, vertex);
    Node *nn = (Node *)malloc(sizeof(Node));

    if (!nn)
        return NULL;
    nn->vertex = str;
    nn->weight = weight;
    nn->next = NULL;
    nn->id=id;
    return nn;
}

void addVertex(Graph *g, char *vertex)
{

    if (checkVertex(*g, vertex) != -1)
        return;

    int length = count(&globalGraph);
    coord *arr;

    if (length != 0)
    {
        arr = fibonacci_sphere(length + 1);
    }
    else
    {
        arr = malloc(sizeof(coord));
        arr->x = 0.0;
        arr->y = 0.0;
        arr->z = 0.0;
    }
    for (int i = 0; i < g->V; i++)
    {
        coord temp = arr[i];
        g->array[i].loc.x = temp.x;
        g->array[i].loc.y = temp.y;
        g->array[i].loc.z = temp.z;

        if (g->array[i].vertex == NULL)
        {
            g->array[i].vertex = malloc(strlen(vertex) + 1);
            strcpy(g->array[i].vertex, vertex);

            return;
        }
    }

    free(arr);

    printf("Can add only %d nodes as mentioned earlier in Graph init function!\n", g->V);

    return;
}

int checkVertex(Graph g, char *vertex)
{

    for (int i = 0; i < g.V; i++)
    {
        if (g.array[i].vertex != NULL && strcmp(g.array[i].vertex, vertex) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addEdge(Graph *g, char *vertex1, char *vertex2, int weight)
{
    if (checkVertex(*g, vertex1) == -1)
        addVertex(g, vertex1);
    if (checkVertex(*g, vertex2) == -1)
        addVertex(g, vertex2);

    int id1 = -1, id2 = -1;
    for (int i = 0; i < g->V; i++)
    {
        if (strcmp(g->array[i].vertex, vertex1) == 0)
        {
            id1 = i;
        }
        else if (strcmp(g->array[i].vertex, vertex2) == 0)
        {
            Node *t = g->array[i].edges;
            id2 = i;
        }
        if (id1!=-1 && id2!=-1){

            Node *t = g->array[i].edges;
            g->array[id1].edges = generateNode(*g, vertex2, weight, id2);
            g->array[id1].edges->next = t;
            t = g->array[i].edges;
            g->array[id2].edges = generateNode(*g, vertex2, weight, id1);
            g->array[id2].edges->next = t;
            break;
        }
    }

    coord c1 = g->array[id1].loc;
    coord c2 = g->array[id2].loc;

    return;
}

void func(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    int length = count(&globalGraph);

    GLfloat Color[3];

    for (int i = 0; i < length; i++)
    {
        Vertex v = globalGraph.array[i];
        coord loc = v.loc;
        generateColor(Color, i, length);
        drawSphere(0.6f, 30, 30, Color, loc.x, loc.y, loc.z, v.vertex);
        Node *t = v.edges;
        GLfloat whiteColor[3] = {0.0f, 1.0f, 1.0f};
        while (t)
        {
            if (t->id != i)
            {
                coord loc1 = globalGraph.array[checkVertex(globalGraph, t->vertex)].loc;
                drawLine(loc.x, loc.y, loc.z, loc1.x, loc1.y, loc1.z, whiteColor);
                loc1.x += loc.x;
                loc1.y += loc.y;
                loc1.z += loc.z;

                loc1.x /= 2;
                loc1.y /= 2;
                loc1.z /= 2;

                char text[20];
                sprintf(text, "%d", t->weight);
                drawText(loc1.x, loc1.y, loc1.z, text);
            }
            t = t->next;
        }
    }

    glutSwapBuffers();

    return;
}

void generateColor(float *color, int index, int totalNodes)
{
    float hue = (float)index / totalNodes; // Varying hue based on node index
    float saturation = 1.0f;               // Full saturation for vibrant colors
    float lightness = 0.5f;                // Medium lightness for balanced colors

    // Convert HSL to RGB
    float c = (1.0f - fabs(2.0f * lightness - 1.0f)) * saturation;
    float x = c * (1.0f - fabs(fmod(6.0f * hue, 2.0f) - 1.0f));
    float m = lightness - 0.5f * c;
    float r, g, b;

    if (hue < 1.0f / 6.0f)
    {
        r = c;
        g = x;
        b = 0.0f;
    }
    else if (hue < 2.0f / 6.0f)
    {
        r = x;
        g = c;
        b = 0.0f;
    }
    else if (hue < 3.0f / 6.0f)
    {
        r = 0.0f;
        g = c;
        b = x;
    }
    else if (hue < 4.0f / 6.0f)
    {
        r = 0.0f;
        g = x;
        b = c;
    }
    else if (hue < 5.0f / 6.0f)
    {
        r = x;
        g = 0.0f;
        b = c;
    }
    else
    {
        r = c;
        g = 0.0f;
        b = x;
    }

    color[0] = r + m;
    color[1] = g + m;
    color[2] = b + m;
}

int start(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Spheres with Connection Line");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glutDisplayFunc(func);
    glutReshapeFunc(reshape);
    glutMotionFunc(mouseMovement);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(keyboard);

    initGL();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    glutMainLoop();

    return 0;
}

void insertNode(Graph *g, char *s)
{
    addVertex(g, s);
    printf("node successfully added\n");
}

int search(Graph g, char *s)
{
    int result = checkVertex(g, s);
    if (result != -1)
    {
        return 1;
    }
    return 0;
}
void removeEdgeByID(Graph *g, int id1, int id2) {
    Node *ptr1 = g->array[id1].edges;
    if (ptr1==NULL)
        return;
    if (ptr1->id == id2) {
        g->array[id1].edges = ptr1->next;
        free(ptr1);
        return;
    }
    while (ptr1->next && ptr1->next->id != id2) {
        ptr1 = ptr1->next;
    }
    if (ptr1->next) {
        Node *toFree = ptr1->next;
        ptr1->next = ptr1->next->next;
        free(toFree);
    }

    Node *ptr2 = g->array[id2].edges;
    if (!ptr2)
        return;
    if (ptr2->id == id1) {
        g->array[id2].edges = ptr2->next;
        free(ptr2);
        return;
    }
    while (ptr2->next && ptr2->next->id != id1) {
        ptr2 = ptr2->next;
    }
    if (ptr2->next) {
        Node *toFree = ptr2->next;
        ptr2->next = ptr2->next->next;
        free(toFree);
    }
}
void displayGraph(Graph g) {
    int i, cnt=count(&g);

    for (i = 0; i < cnt; i++) {
        Node *temp = g.array[i].edges;
        printf("Adjacency list of vertex %s:", g.array[i].vertex);
        while (temp) {
            printf("%s(%d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}


void removeEdge(Graph *g, char *vertex1, char *vertex2) {
    int id1 = -1, id2 = -1;
    for (int i = 0; i < g->V; i++) {
        if (strcmp(g->array[i].vertex, vertex1) == 0)
            id1 = i;
        if (strcmp(g->array[i].vertex, vertex2) == 0)
            id2 = i;
        if (id1 != -1 && id2 != -1) {
            removeEdgeByID(g, id1, id2);
            return;
        }
    }
}

void removeVertex(Graph *g, char *vertex) {
    int isRemove = 0;
    for (int i = 0; i < g->V; i++) {
        if (strcmp(g->array[i].vertex, vertex) == 0) {
            Node *ptr = g->array[i].edges;
            while (ptr) {
                Node *ahead = ptr->next;
                removeEdgeByID(g, i, ptr->id);
                ptr = ahead;
            }
            isRemove = 1;
            free(g->array[i].vertex);
            g->array[i].vertex = NULL;
            g->array[i].edges = NULL;
            for (int j = i; j < g->V - 1; j++) {
                g->array[j] = g->array[j + 1];
            }
            i--;
            break;
        }
    }
    if (isRemove == 0)
        printf("Enter the valid name which exists in graph\n");
}
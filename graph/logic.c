#include"header.h"
#include"queue/logic.c"
#include"../sphere.c"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Constants
#define PI 3.14159265358979323846

Graph globalGraph;

coord* fibonacci_sphere(int samples) {
    coord* points = (coord*)malloc(samples * sizeof(coord));
    float phi = PI * (sqrt(5.0) - 1.0);

    for (int i = 0; i < samples; i++) {
        float y = 1.0 - (i / (double)(samples - 1)) * 2.0;
        float radius = sqrt(1 - y * y);

        float theta = phi * i;
        float x = cos(theta) * radius;
        float z = sin(theta) * radius;

        points[i].x = x;
        points[i].y = y;
        points[i].z = z;
    }

    return points;
}

int count(Graph *g){
    int cnt=0;
    int i=0;
    while (g->array[i].vertex!=NULL)
    {
        cnt+=1;
        i+=1;
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

Node *generateNode(Graph g,char* vertex, int weight)
{
    char *str=(char *)malloc(sizeof(char)*strlen(vertex));
    strcpy(str, vertex);
    Node *nn = (Node *)malloc(sizeof(Node));

    if (!nn)
        return NULL;

    nn->vertex = str;
    nn->weight = weight;
    nn->next = NULL;
    for (int i = 0; i < g.V; i++)
    {
        if (g.array[i].vertex!=NULL){
            if(strcmp(g.array[i].vertex, vertex)==0){
                nn->id=i;
                return nn;
            }
        }
    }
    return NULL;
}

void addVertex(Graph *g, char *vertex)
{

    if (checkVertex(*g, vertex) != -1)
        return;

    int length = count(&globalGraph);
    coord* arr;

    if(length != 0){
        arr = fibonacci_sphere(length+1);
    }
    else{
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
            g->array[i].vertex = malloc(strlen(vertex)+1);
            strcpy(g->array[i].vertex,vertex);

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

    int id1 = -1,id2 = -1, found1=0, found2=0;
    for (int i = 0; i < g->V; i++)
    {
        if (!found1 && strcmp(g->array[i].vertex, vertex1)==0)
        {

            Node *t = g->array[i].edges;
            g->array[i].edges = generateNode(*g, vertex2, weight);
            g->array[i].edges->next = t;
            id1 = i;
            found1=1;
            break;
        }
        else if (!found2 && strcmp(g->array[i].vertex ,vertex2)==0)
        {
            Node *t = g->array[i].edges;
            g->array[i].edges = generateNode(*g, vertex1, weight);
            g->array[i].edges->next = t;
            id2 = i;
            found2=1;
            break;
        }
        if(found1 && found2) break;
    }


    coord c1 = g->array[id1].loc;
    coord c2 = g->array[id2].loc;

    return;
}


void func(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis


    GLfloat redColor[3] = {1.0f, 0.0f, 0.0f};
    int length = count(&globalGraph);
    for(int i = 0;i < length;i++){
        Vertex v = globalGraph.array[i];
        coord loc = v.loc;
        drawSphere(0.2f, 30, 30, redColor, loc.x, loc.y, loc.z, v.vertex);
        Node* t = v.edges;
        GLfloat whiteColor[3] = {0.0f,1.0f,1.0f};
        while(t){
            if(t->id != i){
                coord loc1 = globalGraph.array[checkVertex(globalGraph,t->vertex)].loc;
                drawLine(loc.x, loc.y, loc.z, loc1.x, loc1.y, loc1.z, whiteColor);
                loc1.x += loc.x;
                loc1.y += loc.y;
                loc1.z += loc.z;

                loc1.x /= 2;
                loc1.y /= 2;
                loc1.z /= 2;

                char text[20];
                sprintf(text, "%d", t->weight);
                drawText(loc1.x,loc1.y,loc1.z,text);
            }
            t = t->next;
        }
    }

    glutSwapBuffers();



    return;
}

int start(int argc, char **argv){
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

    glutMainLoop();

    return 0;
}

void insertNode(Graph* g,char* s){
    addVertex(g,s);
    printf("node successfully added\n");
}

int search(Graph g,char* s){
    int result = checkVertex(g, s);
    if(result != -1){
        return 1;
    }
    return 0;
}


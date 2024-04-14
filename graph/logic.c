#include"header.h"
#include"queue/logic.c"
#include"../sphere.c"
#include <GL/gl.h>
#include <wctype.h>
// Constants
Graph globalGraph;

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
}

void addVertex(Graph *g, char *vertex)
{

    if (checkVertex(*g, vertex) != -1)
        return;

    for (int i = 0; i < g->V; i++)
    {
        if (g->array[i].vertex == NULL)
        {
            GLfloat redColor[3] = {1.0f, 0.0f, 0.0f};
            g->array[i].vertex = malloc(strlen(vertex)+1);
            strcpy(g->array[i].vertex,vertex);
            coord temp = get_loc(&globalGraph,i);
            g->array[i].loc.x = temp.x;
            g->array[i].loc.y = temp.y;
            g->array[i].loc.z = temp.z;
            drawSphere(0.2f, 30, 30, redColor, g->array[i].loc.x, g->array[i].loc.y,g->array[i].loc.z, g->array[i].vertex);

            return;
        }
    }

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
    GLfloat whiteColor[3] = {1.0f,1.0f,1.0f};
    drawLine(c1.x, c1.y, c1.z, c2.x, c2.y, c2.z, whiteColor);

    return;
}





// void dfs(Graph g, char *visited, char vertex)
// {
//     visited[vertex - 'A'] = 1;

//     Node *e = g.array[checkVertex(g, vertex)].edges;

//     while (e)
//     {
//         if (!visited[e->vertex - 'A'])
//         {
//             printf("%c ", e->vertex);
//             dfs(g, visited, e->vertex);
//         }
//         e = e->next;
//     }

//     return;
// }

// void bfs(Graph g, char *vertex){
//     Queue q;
//     initQ(&q, g.V);
//     enQueue(&q, vertex);
//     int visited[g.V];
//     visited[]

//     while (!isEmpty(q))
//     {
//         Node *e = g.array[checkVertex(g, vertex)].edges;

//         while (e)
//         {
//             if (!visited[e->vertex - 'A']){
//                 enQueue(&q, e->vertex);
//                 visited[e->vertex - 'A'] = 1;
//             }
//             e = e->next;
//         }
//         printf("%c ", deQueue(&q));
//         if (q.front) vertex = q.front->data;
//     }

//     return;
// }
// void DisplayGraph(Graph *g)
// {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();
//     gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position
//     glRotatef(angleX, 1.0f, 0.0f, 0.0f);                              // Rotate around X axis
//     glRotatef(angleY, 0.0f, 1.0f, 0.0f);                              // Rotate around Y axis
//     GLfloat greenColor[3] = {0.0f, 1.0f, 0.0f};
//     GLfloat lineColor[3] = {1.0f, 1.0f, 1.0f}; // White color
//
//     int x = 0.0f, y = 2.0f, z = 0.0f;
//     int rho = 1;
//     float theta, phi;
//
//     Queue *q = (Queue *)malloc(sizeof(Queue));
//     if (q == NULL)
//     {
//         printf("Memory allocation failed for the queue.");
//         return;
//     }
//     initQ(q, 2 * g->V);
//     int visited[g->V];
//     for (int i = 0; i < g->V; i++)
//     {
//         visited[i] = 0;
//     }
//     visited[0] = 1;
//     Enqueue(q, 0, 0, 2, 0);
//     while (q->front <= q->rear && q->front != -1 && q->rear != -1)
//     {
//         int ele = Dequeue(q);
//         drawSphere(0.6f, 30, 30, greenColor, x, y, z, &ele);
//         Vertex ver = g->array[ele];
//         Node* ptr=ver.edges;
//         int cnt = 0;
//         for (; ptr; ptr = ptr->next)
//             cnt += 1;
//         int i = 0;
//         for (; ptr; ptr = ptr->next)
//         {
//             if (visited[ptr->id] == 0)
//             {
//                 visited[ptr->id] = 1;
//                 if (i == 0)
//                 {
//                     Enqueue(q, ptr->id, x, y, z + rho);
//                     i += 1;
//                 }
//                 else if (i == 1)
//                 {
//                     Enqueue(q, ptr->id, x, y, z - rho);
//                     i++;
//                 }
//                 else
//                 {
//                     
//                 }
//             }
//
//             i += 1;
//         }
//     }
//     free(q);
// }
//

void func(void){
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

     glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
     glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis


    glutSwapBuffers();



    return;
}

int start(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("OpenGL Spheres with Connection Line");

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

#include "fib_sphere.c"
// Constants
Graph globalGraph;
int count(Graph g)
{
    int cnt = 0;
    int i = 0;
    while (g.array[i].vertex != NULL)
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

Node *generateNode(Graph g, char *vertex, int weight)
{
    char *str = (char *)malloc(sizeof(char) * strlen(vertex));
    strcpy(str, vertex);
    Node *nn = (Node *)malloc(sizeof(Node));

    if (!nn)
        return NULL;

    nn->vertex = str;
    nn->weight = weight;
    nn->next = NULL;
    for (int i = 0; i < g.V; i++)
    {
        if (g.array[i].vertex != NULL)
        {
            if (strcmp(g.array[i].vertex, vertex) == 0)
            {
                nn->id = i;
                return nn;
            }
        }
    }
}

void addVertex(Graph *g, char *vertex)
{

    if (checkVertex(*g, vertex) != -1)
        return;
    int x=0;
    coord *points;
    for (int i = 0; i < g->V; i++)
    {
        if (g->array[i].vertex == NULL)
        {
            points=fibonacci_sphere(x);
            break;
        }
        else
        {
            x+=1;
        }
    }
    for (int i = 0; i < x; i++)
    {
        g->array[i].loc.x=points[i].x;
        g->array[i].loc.y=points[i].y;
        g->array[i].loc.z=points[i].z;
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

    int id1 = -1, id2 = -1, found1 = 0, found2 = 0;
    for (int i = 0; i < g->V; i++)
    {
        if (!found1 && strcmp(g->array[i].vertex, vertex1) == 0)
        {

            Node *t = g->array[i].edges;
            g->array[i].edges = generateNode(*g, vertex2, weight);
            g->array[i].edges->next = t;
            id1 = i;
            found1 = 1;
            break;
        }
        else if (!found2 && strcmp(g->array[i].vertex, vertex2) == 0)
        {
            Node *t = g->array[i].edges;
            g->array[i].edges = generateNode(*g, vertex1, weight);
            g->array[i].edges->next = t;
            id2 = i;
            found2 = 1;
            break;
        }
        if (found1 && found2)
            break;
    }
    if (found1 && found2)
    {
        coord c1 = g->array[id1].loc;
        coord c2 = g->array[id2].loc;
        GLfloat whiteColor[3] = {1.0f, 1.0f, 1.0f};
    }
    else
    {
        printf("self loop not allowed!!\n");
    }

    return;
}

void func(void)
{
    Graph *g = &globalGraph;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);                              // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);                              // Rotate around Y axis
    GLfloat redColor[3] = {1.0f, 0.0f, 0.0f};
    GLfloat white[3] = {0.0f, 0.0f, 0.0f};

    for (int i = 0; i < g->V; i++)
    {
        drawSphere(0.2f, 30, 30, redColor, g->array[i].loc.x, g->array[i].loc.y, g->array[i].loc.z, g->array[i].vertex);
    }
    for (int i = 0; i < g->V; i++)
    {
        Node *ptr = g->array->edges;
        while (ptr)
        {
            drawLine(g->array[ptr->id].loc.x, g->array[ptr->id].loc.y, g->array[ptr->id].loc.z, g->array[i].loc.x, g->array[i].loc.y, g->array[i].loc.z, white);
            char str[8];
            sprintf(str, "%d", ptr->weight);
            drawText((g->array[ptr->id].loc.x + g->array[i].loc.x) / 2, (g->array[ptr->id].loc.y + g->array[i].loc.y) / 2, (g->array[ptr->id].loc.z + g->array[i].loc.z) / 2, str);
            ptr = ptr->next;
        }
    }
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


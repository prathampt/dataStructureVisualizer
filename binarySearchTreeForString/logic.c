#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

Tree globalTree;

void initBST(Tree *t)
{
    *t = NULL;
    return;
}

Node *generateNode(char *name)
{
    Node *nn = (Node *)malloc(sizeof(Node));

    if (!nn)
        return NULL;

    nn->name = (char *)malloc(sizeof(char) * strlen(name));
    strcpy(nn->name, name);
    nn->left = NULL;
    nn->right = NULL;

    return nn;
}

void insertNode(Tree *t, char *name)
{
    // Using recursion...
    if (!*t)
    {
        *t = generateNode(name);
        return;
    }

    Node *p = *t;

    if (strcmp(name, p->name) < 0)
    {
        if (p->left == NULL)
        {
            p->left = generateNode(name);
            return;
        }
        insertNode(&p->left, name);
        return;
    }
    if (strcmp(name, p->name) > 0)
    {
        if (p->right == NULL)
        {
            p->right = generateNode(name);
            return;
        }
        insertNode(&p->right, name);
        return;
    }
    printf("The student already Exists!\n");
    return;
}

int count(Tree t)
{
    if (!t)
        return 0;

    return 1 + count(t->left) + count(t->right);
}

int level(Tree t)
{

    if (!t)
        return 0;

    return 1 + MAX(level(t->left), level(t->right));
}

int height(Tree t)
{

    return level(t) - 1;
}

void removeNode(Tree *t, char *name)
{
    if (!*t)
        return;

    Node *p = *t, *q = *t;
    char direction;

    while (strcmp(name, p->name) != 0)
    {
        q = p;
        if (strcmp(name, p->name) < 0)
        {
            p = p->left;
            direction = 'l'; // p is left child of q
        }
        else
        {
            p = p->right;
            direction = 'r'; // p is right child of q
        }
    }

    // Handling the case when the node to be deleted has no child...
    if (p->left == NULL && p->right == NULL)
    {
        if (p == q)
        {
            *t = NULL;
            free(p);
            printf("The tree is empty now...\n");
            return;
        }
        free(p);
        if (direction == 'r')
            q->right = NULL;
        else
            q->left = NULL;
        return;
    }

    // Handling the case when the node has only one child...
    if (p->left == NULL)
    {
        if (p == q)
        {
            *t = p->right;
            printf("The root is replaced by %s\n", p->right->name);
        }
        else
        {
            if (direction == 'r')
                q->right = p->right;
            else
                q->left = p->right;
        }
        free(p);
        return;
    }
    if (p->right == NULL)
    {
        if (p == q)
        {
            *t = p->left;
            printf("The root is replaced by %s\n", p->left->name);
        }
        else
        {
            if (direction == 'r')
                q->right = p->left;
            else
                q->left = p->left;
        }
        free(p);
        return;
    }

    // Handling the case when the node has two childrens...
    // Checking for the smallest number in the right sub tree...
    q = p->right;
    Node *r = p;
    direction = 'r';
    while (q->left)
    {
        r = q;
        direction = 'l';
        q = q->left;
    }
    p->name = q->name;
    if (p == *t)
    {
        printf("The root is replaced by %s\n", q->name);
    }
    if (direction == 'l')
        r->left = q->right;
    else
        r->right = q->right;
    free(q);

    return;
}

int search(Tree t, char *name)
{
    // Using recursion...
    if (!t)
        return 0;

    if (strcmp(name, t->name) == 0)
        return 1;

    if (strcmp(name, t->name) < 0)
        return search(t->left, name);

    if (strcmp(name, t->name) > 0)
        return search(t->right, name);
}

void preorderTraversal(Tree t)
{
    // NLR...
    if (!t)
        return;

    printf("%s\n", t->name);
    preorderTraversal(t->left);
    preorderTraversal(t->right);

    return;
}

void inorderTraversal(Tree t)
{
    // LNR...
    if (!t)
        return;

    inorderTraversal(t->left);
    printf("%s\n", t->name);
    inorderTraversal(t->right);

    return;
}

void postorderTraversal(Tree t)
{
    // LRN...
    if (!t)
        return;

    postorderTraversal(t->left);
    postorderTraversal(t->right);
    printf("%s\n", t->name);

    return;
}

void threeDtree()
{
    int h = height(globalTree);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f + 3.0f * h, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    threeDrecursion(0.0f, 0.75f * h, 0.0f, globalTree, h, 0, count(globalTree));

    glutSwapBuffers();
}

void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, Tree t, int h, int k, int totalNodes)
{

    if (!t)
        return;

    GLfloat Color[3];
    generateColor(Color, k, totalNodes);

    GLfloat lineColor[3] = {1.0f, 1.0f, 1.0f}; // White color

    drawSphere(0.6f, 30, 30, Color, x, y, z, t->name);

    if (t->left)
    {
        threeDrecursion(x - pow(2, h - 1), y - 2, z, t->left, h - 1, k * 2 + 1, totalNodes);
        drawLine(x, y, z, x - pow(2, h - 1), y - 2, z, lineColor);
    }

    if (t->right)
    {
        threeDrecursion(x + pow(2, h - 1), y - 2, z, t->right, h - 1, k * 2 + 2, totalNodes);
        drawLine(x, y, z, x + pow(2, h - 1), y - 2, z, lineColor);
    }
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
    glutCreateWindow("DataStructure Visualizer...");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    glutDisplayFunc(threeDtree);
    glutReshapeFunc(reshape);
    glutMotionFunc(mouseMovement);
    glutMouseFunc(mouseButton);
    glutKeyboardFunc(keyboard);

    initGL();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black

    glutMainLoop();

    return 0;
}

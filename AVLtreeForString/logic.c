#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

AVLtree globalTree;

void init(AVLtree *t)
{
    *t = NULL;
    return;
}

Node *generateNode(char *name)
{
    Node *nn = (Node *)malloc(sizeof(Node));
    if (!nn)
        return NULL;

    nn->balancingFactor = 0;
    nn->left = NULL;
    nn->right = NULL;
    nn->parent = NULL;
    nn->name = (char *)malloc(strlen(name) + 1);
    strcpy(nn->name, name);

    return nn;
}

void balanceFactor(Node *node)
{
    if (!node)
        return;

    node->balancingFactor = level(node->left) - level(node->right);

    while (node->parent)
    {
        node = node->parent;

        int t = level(node->left) - level(node->right);
        node->balancingFactor = t;
    }

    return;
}

void insertNode(AVLtree *t, char *name)
{
    if (!*t)
    {
        *t = generateNode(name);
        balanceFactor(*t);
        return;
    }

    Node *p = *t;
    Node *q = NULL;
    char direction;

    while (p)
    {
        q = p;
        if (strcmp(name, p->name) > 0)
        {
            p = p->right;
            direction = 'r';
        }
        else if (strcmp(name, p->name) < 0)
        {
            p = p->left;
            direction = 'l';
        }
        else
        {
            printf("The element already exists in the tree!\n");
            return;
        }
    }

    p = generateNode(name);

    if (direction == 'r')
        q->right = p;
    else
        q->left = p;

    p->parent = q;

    balanceFactor(p);
    adjustImbalance(t, p->parent);

    return;
}

void removeNode(AVLtree *t, char *name)
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

        if (direction == 'r')
            q->right = NULL;
        else
            q->left = NULL;
        free(p);

        balanceFactor(q);
        adjustImbalance(t, q->parent);

        return;
    }

    // Handling the case when the node has only one child...
    if (p->left == NULL)
    {
        if (p == q)
        {
            *t = p->right;
            p->right->parent = NULL;
            printf("The root is replaced by %s\n", p->right->name);
        }
        else
        {
            if (direction == 'r')
                q->right = p->right;
            else
                q->left = p->right;

            p->right->parent = q;
        }
        free(p);

        balanceFactor(q);
        adjustImbalance(t, q->parent);

        return;
    }
    if (p->right == NULL)
    {
        if (p == q)
        {
            *t = p->left;
            p->left->parent = NULL;
            printf("The root is replaced by %s\n", p->left->name);
        }
        else
        {
            if (direction == 'r')
                q->right = p->left;
            else
                q->left = p->left;

            p->left->parent = q;
        }
        free(p);

        balanceFactor(q);
        adjustImbalance(t, q->parent);

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

    strcpy(p->name, q->name);

    if (p == *t)
    {
        printf("The root is replaced by %s\n", q->name);
    }
    if (direction == 'l')
        r->left = q->right;
    else
        r->right = q->right;

    if (q->right)
        q->right->parent = r;

    free(q);

    balanceFactor(r);
    adjustImbalance(t, r->parent);

    return;
}

void traverse(AVLtree t) // Display name, parent and the balancing factor of each node...
{
    if (!t)
        return;

    traverse(t->left);
    printf("Name: %s\nParent Name: %s\nBalancing Factor: %d\n\n", t->name, (t->parent) ? t->parent->name : "NULL", t->balancingFactor);
    traverse(t->right);

    return;
}

void destroyTree(AVLtree *t)
{
    if (!*t)
        return;

    if (!(*t)->right && !(*t)->left)
    {
        free(*t);
        *t = NULL;
        return;
    }

    if (!(*t)->right)
    {
        destroyTree(&(*t)->left);
        free(*t);
        *t = NULL;
        return;
    }

    if (!(*t)->left)
    {
        destroyTree(&(*t)->right);
        free(*t);
        *t = NULL;
        return;
    }

    destroyTree(&(*t)->left);
    destroyTree(&(*t)->right);
    free(*t);
    *t = NULL;
    return;
}

int count(AVLtree t)
{
    if (!t)
        return 0;

    return 1 + count(t->left) + count(t->right);
}

int level(AVLtree t)
{
    if (!t)
        return 0;

    return 1 + MAX(level(t->left), level(t->right));
}

int height(AVLtree t)
{

    return level(t) - 1;
}

void RL(AVLtree *t, Node *n)
{
    RR(t, n->left);
    LL(t, n);
    return;
}

void LR(AVLtree *t, Node *n)
{
    LL(t, n->right);
    RR(t, n);
    return;
}

void LL(AVLtree *t, Node *n)
{
    Node *temp = n->left;
    n->left = temp->right;
    if (n->left)
        n->left->parent = n;

    temp->right = n;
    temp->parent = n->parent;
    n->parent = temp;

    if (temp->parent)
    {
        if (temp->parent->left == n)
            temp->parent->left = temp;
        else
            temp->parent->right = temp;
    }
    else
        *t = temp;
    balanceFactor(n);
    balanceFactor(temp);

    return;
}

void RR(AVLtree *t, Node *n)
{
    Node *temp = n->right;
    n->right = temp->left;
    if (n->right)
        n->right->parent = n;

    temp->left = n;
    temp->parent = n->parent;
    n->parent = temp;

    if (temp->parent)
    {
        if (temp->parent->right == n)
            temp->parent->right = temp;
        else
            temp->parent->left = temp;
    }
    else
        *t = temp;
    balanceFactor(n);
    balanceFactor(temp);

    return;
}

void adjustImbalance(AVLtree *t, Node *n)
{

    if (!n)
        return;

    int bf = n->balancingFactor;

    while (bf == 0 | bf == 1 | bf == -1)
    {
        n = n->parent;
        if (!n)
            return;
        bf = n->balancingFactor;
    }

    if (bf == 2)
    {
        if (n->left->balancingFactor == -1)
            RL(t, n);
        else
            LL(t, n);
    }
    else if (bf == -2)
    {
        if (n->right->balancingFactor == 1)
            LR(t, n);
        else
            RR(t, n);
    }

    return adjustImbalance(t, n->parent);
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

void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, AVLtree t, int h, int k, int totalNodes)
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


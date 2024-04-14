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

Node *generateNode(int val)
{
    Node *nn = (Node *)malloc(sizeof(Node));

    if (!nn)
        return NULL;

    nn->val = val;
    nn->left = NULL;
    nn->right = NULL;

    return nn;
}

void insertNode(Tree *t, int val)
{
    // Using recursion...
    if (!*t)
    {
        *t = generateNode(val);
        return;
    }

    Node *p = *t;

    if (val < p->val)
    {
        if (p->left == NULL)
        {
            p->left = generateNode(val);
            return;
        }
        insertNode(&p->left, val);
        return;
    }
    if (val > p->val)
    {
        if (p->right == NULL)
        {
            p->right = generateNode(val);
            return;
        }
        insertNode(&p->right, val);
        return;
    }
    printf("Value Already Exists!\n");
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

void removeNode(Tree *t, int val)
{
    if (!*t)
        return;

    Node *p = *t, *q = *t;
    char direction;

    while (val != p->val)
    {
        q = p;
        if (val < p->val)
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
            printf("The root is replaced by %d\n", p->right->val);
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
            printf("The root is replaced by %d\n", p->left->val);
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
    p->val = q->val;
    if (p == *t)
    {
        printf("The root is replaced by %d\n", q->val);
    }
    if (direction == 'l')
        r->left = q->right;
    else
        r->right = q->right;
    free(q);

    return;
}

int search(Tree t, int val)
{
    // Using recursion...
    if (!t)
        return 0;

    if (val == t->val)
        return 1;

    if (val < t->val)
        return search(t->left, val);

    if (val > t->val)
        return search(t->right, val);
}

void preorderTraversal(Tree t)
{
    // NLR...
    if (!t)
        return;

    printf("%d ", t->val);
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
    printf("%d ", t->val);
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
    printf("%d ", t->val);

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

    char * text = (char *) malloc(floor(log10(abs(t->val)) + 1) + 1); // To allocate the memory by the lenght of the int... 
    sprintf(text, "%d", t->val);

    drawSphere(0.6f, 30, 30, Color, x, y, z, text);

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

    free(text);

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

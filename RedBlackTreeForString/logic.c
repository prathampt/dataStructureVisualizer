#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "header.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

RedBlackTree globalTree;

void init(RedBlackTree *t)
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
    nn->color = RED;

    return nn;
}

void insertNode(RedBlackTree *t, char *name) {
    Node *z = generateNode(name);
    Node *y = NULL;
    Node *x = *t;

    while (x != NULL) {
        y = x;
        if (strcmp(name, x->name) < 0)
            x = x->left;
        else if (strcmp(name, x->name) > 0)
            x = x->right;
        else {
            printf("The element already exists in the tree!\n");
            return;
        }
    }

    z->parent = y;
    if (y == NULL)
        *t = z; // Tree was empty
    else if (strcmp(name, y->name) < 0)
        y->left = z;
    else
        y->right = z;

    insertFixup(t, z);
}

void insertFixup(RedBlackTree *t, Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(t, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(t, z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(t, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(t, z->parent->parent);
            }
        }
    }
    (*t)->color = BLACK;
}

void transplant(RedBlackTree *t, Node *u, Node *v) {
    if (u->parent == NULL)
        (*t) = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

Node* minimum(Node* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

void removeNode(RedBlackTree *t, char *name) {
    Node *z = *t;
    while (z != NULL && strcmp(name, z->name) != 0) {
        if (strcmp(name, z->name) < 0)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL) {
        printf("Node to be deleted not found!\n");
        return;
    }

    Node *y = z;
    Color originalColor = y->color;
    Node *x;
    if (z->left == NULL) {
        x = z->right;
        transplant(t, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        transplant(t, z, z->left);
    } else {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z && x)
            x->parent = y;
        else {
            transplant(t, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);

    if (originalColor == BLACK)
        deleteFixup(t, x);
}

void deleteFixup(RedBlackTree *t, Node *x) {
    while (x != *t && x->color == BLACK && x->parent != NULL) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w != NULL) {
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(t, x->parent);
                    w = x->parent->right;
                }
                if (w != NULL && w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w != NULL && w->right->color == BLACK) {
                        if (w->left != NULL)
                            w->left->color = BLACK;
                        if (w != NULL)
                            w->color = RED;
                        rightRotate(t, w);
                        w = x->parent->right;
                    }
                    if (w != NULL) {
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        if (w->right != NULL)
                            w->right->color = BLACK;
                        leftRotate(t, x->parent);
                        x = *t;
                    }
                }
            }
        } else {
            Node *w = x->parent->left;
            if (w != NULL) {
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(t, x->parent);
                    w = x->parent->left;
                }
                if (w != NULL && w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w != NULL && w->left->color == BLACK) {
                        if (w->right != NULL)
                            w->right->color = BLACK;
                        if (w != NULL)
                            w->color = RED;
                        leftRotate(t, w);
                        w = x->parent->left;
                    }
                    if (w != NULL) {
                        w->color = x->parent->color;
                        x->parent->color = BLACK;
                        if (w->left != NULL)
                            w->left->color = BLACK;
                        rightRotate(t, x->parent);
                        x = *t;
                    }
                }
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}


void leftRotate(RedBlackTree *t, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *t = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(RedBlackTree *t, Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *t = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void traverse(RedBlackTree t) {
    if (t == NULL)
        return;

    traverse(t->left);
    printf("Name: %s\nParent Name: %s\nColor: %s\n\n", t->name, (t->parent) ? t->parent->name : "NULL", (t->color == RED) ? "Red" : "Black");
    traverse(t->right);
}

void destroyTree(RedBlackTree *t) {
    if (*t == NULL)
        return;

    destroyTree(&((*t)->left));
    destroyTree(&((*t)->right));
    free((*t)->name);
    free(*t);
    *t = NULL;
}

int count(RedBlackTree t) {
    if (t == NULL)
        return 0;

    return 1 + count(t->left) + count(t->right);
}

int level(RedBlackTree t) {
    if (t == NULL)
        return 0;

    return 1 + MAX(level(t->left), level(t->right));
}

int height(RedBlackTree t) {
    return level(t) - 1;
}

void threeDtree()
{
    int h = height(globalTree);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0f, 0.0f, 5.0f + 3.0f * h, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // Set camera position

    glRotatef(angleX, 1.0f, 0.0f, 0.0f); // Rotate around X axis
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); // Rotate around Y axis

    threeDrecursion(0.0f, 0.75f * h, 0.0f, globalTree, h, count(globalTree));

    glutSwapBuffers();
}

void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, RedBlackTree t, int h, int totalNodes)
{

    if (!t)
        return;

    GLfloat nodeColor[3] = {0.0f, 0.0f, 0.0f};
    
    if (t->color == RED) {
        nodeColor[0] = 1.0;
    }
    

    GLfloat lineColor[3] = {1.0f, 1.0f, 1.0f}; // White color

    drawSphere(0.6f, 30, 30, nodeColor, x, y, z, t->name);

    if (t->left)
    {
        threeDrecursion(x - pow(2, h - 1), y - 2, z, t->left, h - 1, totalNodes);
        drawLine(x, y, z, x - pow(2, h - 1), y - 2, z, lineColor);
    }

    if (t->right)
    {
        threeDrecursion(x + pow(2, h - 1), y - 2, z, t->right, h - 1, totalNodes);
        drawLine(x, y, z, x + pow(2, h - 1), y - 2, z, lineColor);
    }
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
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f); 

    glutMainLoop();

    return 0;
}


#include "../sphere.c"

typedef enum { RED, BLACK } Color;

typedef struct node {
    int balancingFactor;
    char *name;
    Color color;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef Node *RedBlackTree;

void init(RedBlackTree *t);
Node *generateNode(char *name);
void insertNode(RedBlackTree *t, char *name);
void transplant(RedBlackTree *t, Node *u, Node *v);
Node* minimum(Node* x);
void removeNode(RedBlackTree *t, char *name);
void traverse(RedBlackTree t);
void destroyTree(RedBlackTree *t);
int count(RedBlackTree t);
int level(RedBlackTree t);
int height(RedBlackTree t);

void leftRotate(RedBlackTree *t, Node *x);
void rightRotate(RedBlackTree *t, Node *x);
void insertFixup(RedBlackTree *t, Node *z);
void deleteFixup(RedBlackTree *t, Node *x);

void threeDtree();
void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, RedBlackTree t, int h, int totalNodes);
void generateColor(float *color, int index, int totalNodes);
int start(int argc, char **argv);
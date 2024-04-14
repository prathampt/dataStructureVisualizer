#include "../sphere.c"

typedef struct node
{
    int balancingFactor;
    char *name;
    struct node *left;
    struct node *right;
    struct node *parent;
} Node;

typedef Node *AVLtree;

void init(AVLtree *t);
Node *generateNode(char *name);
void insertNode(AVLtree *t, char *name);
void balanceFactor(Node *node);
void removeNode(AVLtree *t, char *name);
void traverse(AVLtree t); // Display name, parent and the balancing factor of each node...
void destroyTree(AVLtree *t);
int count(AVLtree t);
int level(AVLtree t);
int height(AVLtree t);

void RL(AVLtree *t, Node * n);
void LR(AVLtree *t, Node * n);
void LL(AVLtree *t, Node * n);
void RR(AVLtree *t, Node * n);
void adjustImbalance(AVLtree *t, Node *n);

void threeDtree();
void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, AVLtree t, int h, int k, int totalNodes);
void generateColor(float *color, int index, int totalNodes);
int start(int argc, char **argv);
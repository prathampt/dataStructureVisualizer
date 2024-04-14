#include "../sphere.c"

typedef struct node
{
    int val;
    struct node *left;
    struct node *right;
} Node;

typedef Node *Tree;

void initBST(Tree *t);
Node *generateNode(int val);
void insertNode(Tree *t, int val); // Using recursion...

int count(Tree t);
int level(Tree t);
int height(Tree t);

void removeNode(Tree *t, int val);
int search(Tree t, int val); // Using recursion...

void preorderTraversal(Tree t); // Modifying the preorderTraversal.... for displaying the sphere...
void inorderTraversal(Tree t);
void postorderTraversal(Tree t);

void threeDtree();
void threeDrecursion(GLfloat x, GLfloat y, GLfloat z,Tree t, int h, int k, int totalNodes);
void generateColor(float *color, int index, int totalNodes);
int start(int argc, char **argv);
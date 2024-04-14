#include "../sphere.c"

typedef struct node
{
    char *name;
    struct node *left;
    struct node *right;
} Node;

typedef Node *Tree;

void initBST(Tree *t);
Node *generateNode(char *name);
void insertNode(Tree *t, char *name); // Using recursion...

int count(Tree t);
int level(Tree t);
int height(Tree t);

void removeNode(Tree *t, char *name);
int search(Tree t, char *name); // Using recursion...

void preorderTraversal(Tree t); // Modifying the preorderTraversal.... for displaying the sphere...
void inorderTraversal(Tree t);
void postorderTraversal(Tree t);

void threeDtree();
void threeDrecursion(GLfloat x, GLfloat y, GLfloat z, Tree t, int h, int k, int totalNodes);
void generateColor(float *color, int index, int totalNodes);
int start(int argc, char **argv);
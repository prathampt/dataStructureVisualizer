#include "logic.c"

void menu(int argc, char **argv)
{
    int choice;
    init(&globalTree);

    char *name = (char *)malloc(sizeof(char) * 50);
    do
    {
        printf("\n---------------------Red-Black Tree Menu----------------------\n");
        printf("1. Insert a Node\n");
        printf("2. Count Nodes\n");
        printf("3. Traverse Red-Black Tree\n");
        printf("4. Destroy Red-Black Tree\n");
        printf("5. 3D Red-Black Tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter Name: ");
            scanf("%s", name);
            insertNode(&globalTree, name);
            printf("Node inserted.\n");
            break;
        case 2:
            printf("Total nodes in the tree: %d\n", count(globalTree));
            break;
        case 3:
            printf("Inorder Traversal of the Tree: \n");
            traverse(globalTree);
            break;
        case 4:
            destroyTree(&globalTree);
            printf("Red-Black Tree destroyed.\n");
            break;
        case 5:
            start(argc, argv);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 0);

}

int main(int argc, char **argv)
{
    menu(argc, argv);
    return 0;
}
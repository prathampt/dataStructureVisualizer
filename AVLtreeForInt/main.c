#include "logic.c"

void menu(int argc, char **argv)
{
    int choice, val;
    init(&globalTree);

    do
    {
        printf("\n---------------------AVL Tree Menu----------------------\n");
        printf("1. Insert a Node\n");
        printf("2. Count Nodes\n");
        printf("3. Remove a Node\n");
        printf("4. Traverse AVL Tree\n");
        printf("5. Destroy AVL Tree\n");
        printf("6. 3D AVL Tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter Value: ");
            scanf("%d", &val);
            insertNode(&globalTree, val);
            printf("Node inserted.\n");
            break;
        case 2:
            printf("Total nodes in the tree: %d\n", count(globalTree));
            break;
        case 3:
            printf("Enter Value: ");
            scanf("%d", &val);
            removeNode(&globalTree, val);
            printf("Node Deleted.\n");
            break;
        case 4:
            printf("Inorder Traversal of the Tree: \n");
            traverse(globalTree);
            break;
        case 5:
            destroyTree(&globalTree);
            printf("AVL Tree destroyed.\n");
            break;
        case 6:
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
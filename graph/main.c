#include "logic.c"

void menu(int argc, char **argv)
{
    initGraph(&globalGraph,100);

    int choice;
    char *name = (char *)malloc(sizeof(char) * 50);

    do
    {
        printf("\n----- Graph Tree Menu -----\n");
        printf("1. Insert Node\n");
        printf("2. Count Nodes\n");
        printf("3. Remove Node\n");
        printf("4. Search Node\n");
        printf("5. Add Edge between Nodes\n");
        printf("6. 3D tree\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter Name: ");
            scanf("%s", name);
            insertNode(&globalGraph, name);
            printf("Node inserted.\n");
            break;
        case 2:
            printf("Total nodes in the tree: %d\n", count(globalGraph));
            break;
        case 3:
            printf("Enter name number to remove: ");
            scanf("%s", name);
            removeNode(&globalGraph, name);
            printf("Node removed.\n");
            break;
        case 4:
            printf("Enter name number to search: ");
            scanf("%s", name);
            if (search(globalGraph, name) == 1)
                printf("Node found.\n");
            else
                printf("Node not found.\n");
            break;
        case 5:
            printf("Enter the node names to have egde between\n");
            scanf("%s",name);
            char name1[50];
            scanf("%s",name1);
            addEdge(&globalGraph, name, name1, 1);
        case 6:
            start(arg);
            start(argc, argv);
            break;
        case 0:
            printf("This is what we call as 3D Graph!\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}


int main(int argc, char **argv)
{
    menu(argc, argv);
    return 0;
}
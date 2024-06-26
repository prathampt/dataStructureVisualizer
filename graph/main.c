#include "logic.c"

void menu(int argc, char **argv)
{
    initGraph(&globalGraph,100);

    int choice;
    char *name = (char *)malloc(sizeof(char) * 50);

    do
    {
        printf("\n----- Graph Menu -----\n");
        printf("1. Insert Node\n");
        printf("2. Count Nodes\n");
        // printf("3. Remove Node\n");
        printf("3. Search Node\n");
        printf("4. Add Edge between Nodes\n");
        printf("5. 3D tree\n");
        printf("6. To Remove Edge\n");
        printf("7. To Remove Vertex\n");
        printf("8. To Display Adjacency List\n");

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
            printf("Total nodes in the tree: %d\n", count(&globalGraph));
            break;
        case 3:
            printf("Enter name of node to search: ");
            scanf("%s", name);
            if (search(globalGraph, name) == 1)
                printf("Node found.\n");
            else
                printf("Node not found.\n");
            break;
        case 4:
            printf("Enter the node names to have egde between\n");
            scanf("%s",name);
            char name1[50];
            scanf("%s",name1);
            printf("Enter the weight of the edge: ");
            int weight;
            scanf("%d",&weight);
            addEdge(&globalGraph, name, name1, weight);
            break;
        case 5:
            start(argc, argv);
            break;
        case 6:
            char n1[50], n2[50];
            printf("Enter the names to remove edge\n");
            scanf("%s %s", n1,n2);
            removeEdge(&globalGraph, n1, n2);
            break;
        case 7:
            char n[50];
            printf("Enter the names to remove vertex\n");
            scanf("%s", n);
            removeVertex(&globalGraph, n);
            break;
        case 8:
            displayGraph(globalGraph);
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

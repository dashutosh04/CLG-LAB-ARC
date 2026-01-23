
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *link;
};

struct Node *head = NULL;

struct Node *newnode(int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->link = NULL;

    return new_node;
}

void insertnode(int data, int pos)
{
    struct Node *new_node = newnode(data);
    if (pos == 1)
    {
        new_node->link = head;
        head = new_node;
        return;
    }
    else
    {
        struct Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->link;
        }
        new_node->link = temp->link;
        temp->link = new_node;
    }
}

void delnode(int pos)
{
    if (pos == 1)
    {
        head = head->link;
    }
    else
    {
        struct Node *temp = head;
        for (int i = 0; i < pos - 1; i++)
        {
            temp = temp->link;
        }
        if (temp->link == NULL)
        {
            printf("Position out of range.\n");
            return;
        }
        temp->link = temp->link->link;
    }
}

int countnode()
{
    struct Node *temp = head;
    int count = 0;
    while (temp)
    {
        count++;
        temp = temp->link;
    }
    return count;
}

void traverse()
{
    struct Node *temp = head;
    struct Node *visited = NULL;
    while (temp)
    {
        if (visited == temp)
        {
            printf("Circular reference detected.\n");
            return;
        }
        visited = temp;
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main()
{
    int n, data, pos, choice;
    do
    {
        printf("MENU:\n");
        printf("1. Insert the node at a position\n");
        printf("2. Delete a node from specific position\n");
        printf("3. Traversal\n");
        printf("4. Count the node\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &pos);
            insertnode(data, pos);
            break;
        case 2:
            printf("Enter position: ");
            scanf("%d", &pos);
            delnode(pos);
            break;
        case 3:
            printf("The list is: ");
            traverse();
            break;
        case 4:
            printf("Total number of nodes = %d\n", countnode());
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
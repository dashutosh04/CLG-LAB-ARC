/*
4.1 Write a program to create a single linked list of n nodes and perform the following menu-based
operations on it using function:
i. Insert a node at specific position
ii. Deletion of an element from specific position
iii. Count nodes
iv. Traverse the linked list
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

struct Node *newNode(int data)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insertNode(int data, int position)
{
    struct Node *new_node = newNode(data);
    if (position == 1)
    {
        new_node->next = head;
        head = new_node;
    }
    else
    {
        struct Node *temp = head;
        for (int i = 0; i < position - 1; i++)
        {
            temp = temp->next;
        }
        new_node->next = temp->next;
        temp->next = new_node;
    }
}

void deleteNode(int position)
{
    if (!head)
    {
        printf("List is empty\n");
        return;
    }
    if (position == 1)
    {
        head = head->next;
    }
    else
    {
        struct Node *temp = head;
        for (int i = 0; i < position - 1; i++)
        {
            temp = temp->next;
        }
        if (temp->next == NULL)
        {
            printf("Invalid position\n");
            return;
        }
        temp->next = temp->next->next;
    }
}

int countNodes()
{
    struct Node *temp = head;
    int count = 0;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

void traverseList()
{
    struct Node *temp = head;
    struct Node *visited = NULL;
    while (temp)
    {
        if (visited == temp)
        {
            printf("Cycle detected\n");
            break;
        }
        visited = temp;
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    int choice, data, position;

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Delete a node\n");
        printf("3. Count nodes\n");
        printf("4. Traverse the linked list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &position);
            insertNode(data, position);
            break;
        case 2:
            printf("Enter position: ");
            scanf("%d", &position);
            deleteNode(position);
            break;
        case 3:
            printf("Number of nodes: %d\n", countNodes());
            break;
        case 4:
            traverseList();
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}
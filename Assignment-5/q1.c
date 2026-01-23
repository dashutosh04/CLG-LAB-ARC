/*
5.1 Write a program to create a double linked list and perform the following menu-based operations on it:
i. insert an element at specific position
ii. delete an element from specific position
iii. Traverse the list
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *prev, *next;
};

struct Node *head = NULL;

void insert(int data, int pos)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;

    if (pos == 1)
    {
        newNode->next = head;
        if (head != NULL)
        {
            head->prev = newNode;
        }
        head = newNode;
    }
    else
    {
        struct Node *current = head;
        for (int i = 1; i < pos - 1; i++)
        {
            if (current != NULL)
            {
                current = current->next;
            }
            else
            {
                printf("Invalid position.\n");
                return;
            }
        }

        newNode->next = current->next;
        if (current->next != NULL)
        {
            current->next->prev = newNode;
        }
        current->next = newNode;
        newNode->prev = current;
    }
}

void deleteNode(int pos)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    if (pos == 1)
    {
        struct Node *temp = head;
        head = head->next;
        if (head != NULL)
        {
            head->prev = NULL;
        }
        free(temp);
    }
    else
    {
        struct Node *current = head;
        for (int i = 1; i < pos - 1; i++)
        {
            if (current != NULL)
            {
                current = current->next;
            }
            else
            {
                printf("Invalid position.\n");
                return;
            }
        }

        if (current->next != NULL)
        {
            struct Node *temp = current->next;
            current->next = current->next->next;
            if (current->next != NULL)
            {
                current->next->prev = current;
            }
            free(temp);
        }
        else
        {
            printf("Invalid position.\n");
        }
    }
}

void traverse()
{
    struct Node *current = head;
    while (current != NULL)
    {
        printf("%d->", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main()
{
    int n, data, pos, choice;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter element: ");
        scanf("%d", &data);
        insert(data, i + 1);
    }

    do
    {
        printf("MENU:\n");
        printf("1. Insert the node at a position\n");
        printf("2. Delete a node from specific position\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element: ");
            scanf("%d", &data);
            printf("Enter position: ");
            scanf("%d", &pos);
            insert(data, pos);
            break;
        case 2:
            printf("Enter position: ");
            scanf("%d", &pos);
            deleteNode(pos);
            break;
        case 3:
            printf("The list is: ");
            traverse();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
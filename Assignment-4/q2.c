/*
4.2 In addition to 4.1, perform following operations using function on the single linked list:
i. search an element in the list
ii. sort the list in ascending order
iii. reverse the list
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

int searchElement(int data)
{
    struct Node *temp = head;
    int position = 1;
    while (temp)
    {
        if (temp->data == data)
        {
            return position;
        }
        temp = temp->next;
        position++;
    }
    return -1;
}

void sortList()
{
    struct Node *current = head;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        while (next != NULL)
        {
            if (current->data > next->data)
            {
                int temp = current->data;
                current->data = next->data;
                next->data = temp;
            }
            next = next->next;
        }
        current = current->next;
    }
}

void reverseList()
{
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
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
        printf("5. Search for an element\n");
        printf("6. Sort the list\n");
        printf("7. Reverse the list\n");
        printf("8. Exit\n");
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
            printf("Enter data to search: ");
            scanf("%d", &data);
            int position = searchElement(data);
            if (position != -1)
            {
                printf("Element found at position %d\n", position);
            }
            else
            {
                printf("Element not found\n");
            }
            break;
        case 6:
            sortList();
            printf("List sorted in ascending order\n");
            break;
        case 7:
            reverseList();
            printf("List reversed\n");
            break;
        case 8:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}
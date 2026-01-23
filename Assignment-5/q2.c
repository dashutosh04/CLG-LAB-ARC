/*
5.2 Write a program to create a circular linked list and display the elements of the list.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void createLinkedList(int n)
{
    struct Node *temp, *rear;
    for (int i = 1; i <= n; i++)
    {
        temp = (struct Node *)malloc(sizeof(struct Node));
        printf("Enter info of node%d: ", i);
        scanf("%d", &temp->data);
        temp->next = NULL;
        if (head == NULL)
        {
            head = temp;
            rear = temp;
        }
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }
    rear->next = head;
}

void displayLinkedList()
{
    struct Node *temp = head;
    printf("Clinkedlist: ");
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

int main()
{
    int n;
    printf("Enter no.of nodes: ");
    scanf("%d", &n);
    createLinkedList(n);
    displayLinkedList();
    return 0;
}

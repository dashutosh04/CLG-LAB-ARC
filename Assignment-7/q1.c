/*
7.1 Write a menu driven program to create a linear queue using array and perform Enqueue, Dequeue,
Traverse, IsEmpty,  IsFull operations.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int element)
{

    if (rear == MAX - 1)
    {
        printf("Queue is full!\n");
        return;
    }
    else
    {
        if (front == -1)
        {
            front = 0;
        }
        rear++;
        queue[rear] = element;

        printf("%d enqueued into the queue.\n", element);
    }
}

int dequeue()
{
    if (front == -1)
    {
        printf("Queue is empty!\n");
        return -1;
    }
    else
    {
        int dequeued = queue[front];
        if (front == rear)
        {
            front = -1; // Queue is now empty
            rear = -1;  // Queue is now empty
        }
        else
        {
            front++;
        }
        return dequeued;
    }
}

int isEmpty()
{
    if (front == -1)
    {
        return 1; // Queue is empty
    }
    else
    {
        return 0;
    }
}

int isFull()
{
    if (rear == MAX - 1 && front == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void display()
{
    if (front == -1)
    {
        printf("Queue is empty!\n");
    }
    else
    {
        printf("Queue: ");
        for (int i = front; i <= rear; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main()
{
    int choice, element;

    while (1)
    {
        printf("\nMain Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. IsEmpty\n");
        printf("4. IsFull\n");
        printf("5. Traverse\n");
        printf("6. Exit\n");

        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to be enqueued into the queue: ");
            scanf("%d", &element);
            enqueue(element);
            break;
        case 2:
            element = dequeue();
            if (element != -1)
            {
                printf("%d dequeued from Queue\n", element);
            }
            break;
        case 3:
            if (isEmpty())
            {
                printf("Queue empty: True\n");
            }
            else
            {
                printf("Queue empty: False\n");
            }
            break;
        case 4:
            if (isFull())
            {
                printf("Queue full: True\n");
            }
            else
            {
                printf("Queue full: False\n");
            }
            break;
        case 5:
            display();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
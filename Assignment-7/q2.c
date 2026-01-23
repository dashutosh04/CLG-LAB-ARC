/*
7.2 Write a menu driven program to implement linear queue operations such as Enqueue, Dequeue,
IsEmpty, Traverse using single linked list.

*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Queue
{
    struct Node *rear;
    struct Node *front;
};

struct Node *first = NULL;

struct Queue *createQueue()
{
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue *queue, int element)
{

    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->data = element;
    temp->next = NULL;

    if (queue->rear == NULL)
    {
        queue->front = temp;
        queue->rear = temp;
    }
    else
    {
        queue->rear->next = temp;
        queue->rear = temp;
    }
}

int dequeue(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue is empty\n");
        return -1;
    }

    struct Node *temp = queue->front;
    int element = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp);
    return element;
}

int isFull()
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    if (temp == NULL)
    {
        return 1; // if node creation failed
    }
    free(temp); // if the node gets created. so we are freeing it
    return 0;
}

int isEmpty(struct Queue *queue)
{
    if (queue->front == NULL)
    {
        return 1;
    }
    else
        return 0;
}

void display(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node *temp = queue->front;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    struct Queue *queue = createQueue();
    int choice, element;

    while (1)
    {
        printf("\nMain Menu\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Isempty\n");
        printf("4. Isfull\n");
        printf("5. Traverse\n");
        printf("6. Exit\n");

        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to be enqueued into the queue: ");
            scanf("%d", &element);
            enqueue(queue, element);
            break;
        case 2:
            element = dequeue(queue);
            if (element != -1)
            {
                printf("%d Deququed from Queued\n", element);
            }
            break;
        case 3:
            if (isEmpty(queue))
            {
                printf("queue empty: True\n");
            }
            else
            {
                printf("queue empty: False\n");
            }
            break;
        case 4:
            isFull(queue);
            break;
        case 5:
            display(queue);
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

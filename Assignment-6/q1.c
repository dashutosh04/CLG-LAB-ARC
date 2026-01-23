/*
6.1 Write a menu driven program to create a stack using array and perform the following operation using function
a. Push
b. Pop
c. check stack is empty or not
d. check stack is full or not
e. display stack elements
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10

int stack[MAX];
int top = -1;

void push(int element)
{
    if (top == MAX - 1)
    {
        printf("Stack is full!\n");
    }
    else
    {
        top++;
        stack[top] = element;
        printf("%d pushed into the stack.\n", element);
    }
}


int pop()
{
    if (top == -1)
    {
        printf("Stack is empty!\n");
        return -1;
    }
    else
    {
        int popped = stack[top];
        top--;
        return popped;
    }
}


int isEmpty()
{
    return (top < 0);
}

int isFull()
{
    return (top == (MAX - 1));
}

void display()
{
    if (top == -1)
    {
        printf("Stack is empty!\n");
    }
    else
    {
        printf("Stack: ");
        for (int i = top; i >= 0; i--)
        {
            printf("%d ", stack[i]);
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
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. IsEmpty\n");
        printf("4. IsFull\n");
        printf("5. Traverse\n");
        printf("6. Exit\n");

        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter element to be pushed into the stack: ");
            scanf("%d", &element);
            push(element);
            break;
        case 2:
            element = pop();
            if (element != -1)
            {
                printf("%d deleted from Stack\n", element);
            }
            break;
        case 3:
            if (isEmpty())
            {
                printf("Stack empty: True\n");
            }
            else
            {
                printf("Stack empty: False\n");
            }
            break;
        case 4:
            if (isFull())
            {
                printf("Stack full: True\n");
            }
            else
            {
                printf("Stack full: False\n");
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
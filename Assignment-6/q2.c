/*
6.2 Write a menu driven program to create a stack using linked list and perform the following operation using function
a. Push
b. Pop
c. IsEmpty
d. display the stack elements
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *top = NULL;

void push(int element) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = element;
    newNode->next = top;
    top = newNode;
    printf("%d pushed into the stack.\n", element);
}

int pop() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        int popped = top->data;
        struct Node *temp = top;
        top = top->next;
        free(temp);
        return popped;
    }
}

int isEmpty() {
    return top == NULL;
}

void display() {
    if (top == NULL) {
        printf("Stack is empty!\n");
    } else {
        printf("Stack: ");
        struct Node *current = top;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

int main() {
    int choice, element;

    while (1) {
        printf("\nMain Menu\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. IsEmpty\n");
        printf("4. Traverse\n");
        printf("5. Exit\n");

        printf("Enter option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to be pushed into the stack: ");
                scanf("%d", &element);
                push(element);
                break;
            case 2:
                element = pop();
                if (element != -1) {
                    printf("%d deleted from Stack\n", element);
                }
                break;
            case 3:
                if (isEmpty()) {
                    printf("Stack empty: True\n");
                } else {
                    printf("Stack empty: False\n");
                }
                break;
            case 4:
                display();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
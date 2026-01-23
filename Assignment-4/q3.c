/*
4.3 Write a program to represent the polynomial equation of single variable using single linked list 
and perform the addition of two polynomial equations.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int power;
    struct Node *next;
};

struct Node *createNode(int coeff, int pow) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->power = pow;
    newNode->next = NULL;
    return newNode;
}

struct Node *insertNode(struct Node *head, int coeff, int pow) {
    struct Node *newNode = createNode(coeff, pow);
    if (head == NULL) {
        return newNode;
    }
    struct Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

void displayPolynomial(struct Node *head) {
    if (head == NULL) {
        printf("0");
        return;
    }
    while (head != NULL) {
        printf("%dx^%d", head->coefficient, head->power);
        if (head->next != NULL) {
            printf(" + ");
        }
        head = head->next;
    }
}

struct Node *addPolynomials(struct Node *poly1, struct Node *poly2) {
    struct Node *result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->power > poly2->power) {
            result = insertNode(result, poly1->coefficient, poly1->power);
            poly1 = poly1->next;
        } else if (poly1->power < poly2->power) {
            result = insertNode(result, poly2->coefficient, poly2->power);
            poly2 = poly2->next;
        } else {
            result = insertNode(result, poly1->coefficient + poly2->coefficient, poly1->power);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        result = insertNode(result, poly1->coefficient, poly1->power);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        result = insertNode(result, poly2->coefficient, poly2->power);
        poly2 = poly2->next;
    }
    return result;
}

int main() {
    struct Node *poly1 = NULL;
    struct Node *poly2 = NULL;

    int maxPower1, coeff;
    printf("Polynomial-1:\n");
    printf("Enter the Maximum power of x: ");
    scanf("%d", &maxPower1);
    for (int i = maxPower1; i >= 0; i--) {
        printf("Enter the coefficient of degree %d: ", i);
        scanf("%d", &coeff);
        poly1 = insertNode(poly1, coeff, i);
    }
    int maxPower2;
    printf("Polynomial-2:\n");
    printf("Enter the Maximum power of x: ");
    scanf("%d", &maxPower2);
    for (int i = maxPower2; i >= 0; i--) {
        printf("Enter the coefficient of degree %d: ", i);
        scanf("%d", &coeff);
        poly2 = insertNode(poly2, coeff, i);
    }
    
    struct Node *sum = addPolynomials(poly1, poly2);

    printf("Sum: ");
    displayPolynomial(sum);

    return 0;
}
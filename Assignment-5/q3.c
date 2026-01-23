/*
5.3 Write a program to represent the given sparse matrix using header single linked list and
display it.
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int row, col, value;
    struct Node *next;
};

struct HeaderNode
{
    int row;
    struct Node *next;
};

void createSM(struct HeaderNode *header, int rows, int cols, int elements[])
{
    int i, j, k = 0;
    struct Node *newNode;

    for (i = 0; i < rows; i++)
    {
        header[i].row = i;
        header[i].next = NULL;
    }

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (elements[k] != 0)
            {
                newNode = (struct Node *)malloc(sizeof(struct Node));
                newNode->row = i;
                newNode->col = j;
                newNode->value = elements[k];
                newNode->next = header[i].next;
                header[i].next = newNode;
            }
            k++;
        }
    }
}
int countNZ(struct HeaderNode *header, int rows)
{
    int count = 0, i;
    struct Node *temp;

    for (i = 0; i < rows; i++)
    {
        temp = header[i].next;
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
    }

    return count;
}

void deleteSM(struct HeaderNode *header, int rows, int cols)
{
    int i, j;
    struct Node *temp;

    printf("Sparse matrix in 3-tuple format\n");
    printf("%d %d %d\n", rows, cols, countNZ(header, rows));

    for (i = 0; i < rows; i++)
    {
        temp = header[i].next;
        while (temp != NULL)
        {
            printf("%d %d %d\n", i, temp->col, temp->value);
            temp = temp->next;
        }
    }
}

int main()
{
    int rows, cols, elements[100], i, j, k = 0;

    printf("Enter size of the sparse matrix: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter elements of sparse matrix: ");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &elements[k]);
            k++;
        }
    }

    struct HeaderNode header[rows];
    createSM(header, rows, cols, elements);
    deleteSM(header, rows, cols);

    return 0;
}
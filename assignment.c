/*
Sparse Matrix Operations in C
Objective: Write a C program that performs the following operations onsparse matrices:
Addition of Two Sparse Matrices
Multiplication of Two Sparse Matrices
*/

/*
Name - Ashutosh Das
Section - CSE38
Roll No - 2305040
*/

#include <stdio.h>
#include <stdlib.h>

/* Here we are defining the structure for the triplet representation*/

typedef struct
{
    int row, col, value;
} trip;

/* Here we are creating funtion for memory allocation for the sparse matrix*/

trip *createSM(int rows, int cols, int val)
{
    trip *matrix = (trip *)malloc((val + 1) * sizeof(trip));

    matrix[0].row = rows;
    matrix[0].col = cols;
    matrix[0].value = val;

    return matrix;
}

/* Here we are creating function for printing the sparse matrix*/

void printSM(trip *matrix)
{
    printf("Rows: %d, Columns: %d, Non-zero elements: %d\n", matrix[0].row, matrix[0].col, matrix[0].value);
    for (int i = 1; i <= matrix[0].value; i++)
        printf("%d %d %d\n", matrix[i].row, matrix[i].col, matrix[i].value);
}

/* Here we are creating function for addition of two sparse matrices*/

trip *addSM(trip *mat1, trip *mat2)
{
    int i = 1, j = 1, k = 1, m, n, p;

    trip *mat3 = createSM(mat1[0].row, mat1[0].col, mat1[0].value + mat2[0].value);

    while (i <= mat1[0].value && j <= mat2[0].value)
    {
        if (mat1[i].row < mat2[j].row)
        {
            mat3[k] = mat1[i];
            i++;
        }
        else if (mat1[i].row > mat2[j].row)
        {
            mat3[k] = mat2[j];
            j++;
        }
        else if (mat1[i].col < mat2[j].col)
        {
            mat3[k] = mat1[i];
            i++;
        }
        else if (mat1[i].col > mat2[j].col)
        {
            mat3[k] = mat2[j];
            j++;
        }
        else
        {
            mat3[k].row = mat1[i].row;
            mat3[k].col = mat1[i].col;
            mat3[k].value = mat1[i].value + mat2[j].value;
            i++;
            j++;
        }
        k++;
    }
    while (i <= mat1[0].value)
    {
        mat3[k] = mat1[i];
        i++;
        k++;
    }
    while (j <= mat2[0].value)
    {
        mat3[k] = mat2[j];
        j++;
        k++;
    }
    mat3[0].value = k - 1;
    return mat3;
}

/* Here we are creating function for multiplication of two sparse matrices*/
trip *mulSM(trip *mat1, trip *mat2)
{
    int i, j, k, m, n, p, q;

    m = mat1[0].row;
    n = mat1[0].col;
    p = mat2[0].col;
    q = mat1[0].value + mat2[0].value;

    trip *mat3 = createSM(m, p, q);

    int *temp = (int *)malloc(p * sizeof(int));

    for (i = 1; i <= mat3[0].row; i++)
    {
        for (j = 1; j <= mat3[0].col; j++)
            temp[j] = 0;

        for (k = 1; k <= mat1[0].value; k++)
        {
            if (mat1[k].row == i)
            {
                for (j = 1; j <= mat2[0].value; j++)
                {
                    if (mat2[j].col == mat1[k].col)
                        temp[mat2[j].row] += mat1[k].value * mat2[j].value;
                }
            }
        }
        for (j = 1; j <= mat3[0].col; j++)
        {
            if (temp[j] != 0)
            {
                mat3[mat3[0].value + 1].row = i;
                mat3[mat3[0].value + 1].col = j;
                mat3[mat3[0].value + 1].value = temp[j];
                mat3[0].value++;
            }
        }
    }

    free(temp);

    return mat3;
}

/* Main function*/
int main()
{
    int row1, col1, nonzero1;
    int row2, col2, nonzero2;

    /*User inputs*/

    printf("Enter the rows, cols and nonzeros for 1st matrix:\n");
    scanf("%d %d %d", &row1, &col1, &nonzero1);

    printf("Enter the rows, cols and nonzeros for 2nd matrix:\n");
    scanf("%d %d %d", &row2, &col2, &nonzero2);

    trip *matrix1 = createSM(row1, col1, nonzero1);
    trip *matrix2 = createSM(row1, col1, nonzero1);

    printf("Please enter the non zero elements of 1st matrix in row coloumn value format:\n");
    for (int i = 1; i <= nonzero1; i++)
    {
        scanf("%d %d %d", &matrix1[i].row, &matrix1[i].col, &matrix1[i].value);
    }

    printf("Please enter the non zero elements of 2nd matrix in row coloumn value format:\n");
    for (int i = 1; i <= nonzero2; i++)
    {
        scanf("%d %d %d", &matrix2[i].row, &matrix2[i].col, &matrix2[i].value);
    }

    printf("\nMatrix 1:\n");
    printSM(matrix1); // Displaying the  matrix

    printf("\nMatrix 2:\n");
    printSM(matrix2); // Displaying the  matrix

    trip *matrix3 = addSM(matrix1, matrix2); // Addition
    printf("\nAddition Result:\n");
    printSM(matrix3);

    if (col1 != row2)
    {
        printf("\nMatrix multiplication not possible.\n"); // From matrix law
    }
    else
    {
        trip *matrixD = mulSM(matrix1, matrix2); // Multiplying the matrix
        printf("\nMultiplication Result - :\n");
        printSM(matrixD);
        free(matrixD); // Can only be done here as it is in the else block
    }

    /*To free up the used memory*/
    free(matrix1);
    free(matrix2);
    free(matrix3);

    return 0;
}
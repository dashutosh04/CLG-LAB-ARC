/*
WAP to represent the given sparse matrix in 3 tuple format using 2D array.
 */

#include <stdio.h>
#include <stdlib.h>

void convert(int **matrix, int rows, int cols) {
    int count = 0; 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                count++;
            }
        }
    }

    int triple[count + 1][3];
    triple[0][0] = rows;
    triple[0][1] = cols;
    triple[0][2] = count;
    int k = 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                triple[k][0] = i;
                triple[k][1] = j;
                triple[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    printf("Sparse matrix in 3-tuple format:\n");
    for (int i = 0; i <= count; i++) {
        printf("%d %d %d\n", triple[i][0], triple[i][1], triple[i][2]);
    }

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows, cols;

    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    int **matrix = (int **)malloc(rows * sizeof(int *));

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    convert(matrix, rows, cols);

    return 0;
}

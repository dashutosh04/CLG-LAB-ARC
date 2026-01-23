/*
 WAP to perform transpose of a given sparse matrix in 3-tuple format.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Triple;

void transpose_sparse_matrix(Triple *matrix, int rows, int cols, int nnz) {
    Triple *transposed_matrix = (Triple *)malloc(nnz * sizeof(Triple));

    int i, j, k = 0;
    for (i = 0; i < cols; i++) {
        for (j = 0; j < nnz; j++) {
            if (matrix[j].col == i) {
                transposed_matrix[k].row = matrix[j].col;
                transposed_matrix[k].col = matrix[j].row;
                transposed_matrix[k].value = matrix[j].value;
                k++;
            }
        }
    }

    printf("Transpose of sparse matrix:\n");
    printf("R C Element\n");
    for (i = 0; i < nnz; i++) {
        printf("%d %d %d\n", transposed_matrix[i].row, transposed_matrix[i].col, transposed_matrix[i].value);
    }

    free(transposed_matrix);
}

int main() {
    int rows, cols, nnz;

    printf("Enter sparse matrix in 3-tuple format\n");
    scanf("%d %d %d", &rows, &cols, &nnz);

    Triple *matrix = (Triple *)malloc(nnz * sizeof(Triple));

    printf("Enter the elements (row, column, value):\n");
    for (int i = 0; i < nnz; i++) {
        scanf("%d %d %d", &matrix[i].row, &matrix[i].col, &matrix[i].value);
    }

    transpose_sparse_matrix(matrix, rows, cols, nnz);

    free(matrix);

    return 0;
}
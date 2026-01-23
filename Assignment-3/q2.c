/*
WAP to add 2 sparse matrices in 3 tuple format.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row;
    int col;
    int value;
} Triple;

void add_sparse_matrices(Triple *matrix1, int nnz1, Triple *matrix2, int nnz2, Triple **result, int *nnz_result) {
    int i = 0, j = 0, k = 0;

    while (i < nnz1 && j < nnz2) {
        if (matrix1[i].row < matrix2[j].row || (matrix1[i].row == matrix2[j].row && matrix1[i].col < matrix2[j].col)) {
            *result[k] = matrix1[i];
            k++;
            i++;
        } else if (matrix1[i].row > matrix2[j].row || (matrix1[i].row == matrix2[j].row && matrix1[i].col > matrix2[j].col)) {
            *result[k] = matrix2[j];
            k++;
            j++;
        } else {
            *result[k] = matrix1[i];
            (*result)[k].value += matrix2[j].value;
            k++;
            i++;
            j++;
        }
    }

    while (i < nnz1) {
        *result[k] = matrix1[i];
        k++;
        i++;
    }

    while (j < nnz2) {
        *result[k] = matrix2[j];
        k++;
        j++;
    }

    *nnz_result = k;
}

int main() {
    int rows1, cols1, nnz1, rows2, cols2, nnz2;

    printf("Enter sparse matrix-1 in 3-tuple format\n");
    scanf("%d %d %d", &rows1, &cols1, &nnz1);

    Triple *matrix1 = (Triple *)malloc(nnz1 * sizeof(Triple));

    printf("Enter the elements (row, column, value):\n");
    for (int i = 0; i < nnz1; i++) {
        scanf("%d %d %d", &matrix1[i].row, &matrix1[i].col, &matrix1[i].value);
    }

    printf("Enter sparse matrix-2 in 3-tuple format\n");
    scanf("%d %d %d", &rows2, &cols2, &nnz2);

    if (rows1 != rows2 || cols1 != cols2) {
        printf("Error: Matrices must have the same dimensions.\n");
        return 1;
    }

    Triple *matrix2 = (Triple *)malloc(nnz2 * sizeof(Triple));

    printf("Enter the elements (row, column, value):\n");
    for (int i = 0; i < nnz2; i++) {
        scanf("%d %d %d", &matrix2[i].row, &matrix2[i].col, &matrix2[i].value);
    }

    int nnz_result = nnz1 + nnz2;
    Triple *result = (Triple *)malloc(nnz_result * sizeof(Triple));

    add_sparse_matrices(matrix1, nnz1, matrix2, nnz2, result, &nnz_result);

    printf("Resultant Matrix in 3-tuple format\n");
    printf("%d %d %d\n", rows1, cols1, nnz_result);
    for (int i = 0; i < nnz_result; i++) {
        printf("%d %d %d\n", result[i].row, result[i].col, result[i].value);
    }

    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
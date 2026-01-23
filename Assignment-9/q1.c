/*9.1WAP to create an un-directed graph using Adjacency Matrix Method and display the degree of each
vertex*/

#include <stdio.h>


void create_undirected_graph(int adj_matrix[][100], int n) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", adj_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nDegree of each vertex:\n");
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += adj_matrix[i][j];
        }
        printf("Vertex %d: %d\n", i + 1, degree);
    }
}

int main() {
    int n = 4;
    int adj_matrix[100][100] = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };

    create_undirected_graph(adj_matrix, n);

    return 0;
}
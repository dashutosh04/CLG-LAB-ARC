/*9.4 WAP to create a directed graph using Adjacency Matrix Method and display the degree of eachvertex.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int adj_matrix[MAX_VERTICES][MAX_VERTICES];
int num_vertices;

void create_graph() {
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            scanf("%d", &adj_matrix[i][j]);
        }
    }
}

void print_degree() {
    printf("Degree of each vertex:\n");
    for (int i = 0; i < num_vertices; i++) {
        int in_degree = 0, out_degree = 0;
        for (int j = 0; j < num_vertices; j++) {
            in_degree += adj_matrix[j][i];
            out_degree += adj_matrix[i][j];
        }
        printf("Vertex %d: In-degree = %d, Out-degree = %d\n", i, in_degree, out_degree);
    }
}

int main() {
    create_graph();
    print_degree();

    return 0;
}
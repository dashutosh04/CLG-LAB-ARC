/*9.2In addition to 9.1, display DFS traversal sequence of the undirected graph.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int adj_matrix[MAX_VERTICES][MAX_VERTICES];
int num_vertices;
int visited[MAX_VERTICES];

void dfs(int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < num_vertices; i++) {
        if (adj_matrix[vertex][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

void dfs_traversal() {
    for (int i = 0; i < num_vertices; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
}

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
        int degree = 0;
        for (int j = 0; j < num_vertices; j++) {
            degree += adj_matrix[i][j];
        }
        printf("Vertex %d: %d\n", i, degree);
    }
}

int main() {
    create_graph();
    printf("DFS traversal: ");
    dfs_traversal();
    printf("\n");

    return 0;
}
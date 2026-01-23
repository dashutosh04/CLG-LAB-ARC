/*9.3In addition to 9.1, display BFS traversal sequence of the undirected graph.*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int adj_matrix[MAX_VERTICES][MAX_VERTICES];
int num_vertices;
int visited[MAX_VERTICES];

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

void bfs(int start_vertex) {
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    visited[start_vertex] = 1;
    queue[++rear] = start_vertex;

    while (front <= rear) {
        int current_vertex = queue[front++];
        printf("%d ", current_vertex);

        for (int i = 0; i < num_vertices; i++) {
            if (adj_matrix[current_vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

int main() {
    create_graph();

    printf("\nDFS traversal: ");
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
    }
    dfs_traversal();

    printf("\nBFS traversal: ");
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = 0;
    }
    bfs(0); // Assuming 0 as the starting vertex

    return 0;
}
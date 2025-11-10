#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 50
#define NO_PARENT -1

int get_num_nodes(FILE *file)
{
    int n = 0;
    char c;
    rewind(file);
    while ((c = fgetc(file)) != '\n' && c != EOF)
    {
        if (c == ' ' || c == '\t')
        {
            n++;
        }
    }
    rewind(file);
    return n + 1;
}

int min_distance(int dist[], int visited[], int V)
{
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
    {
        if (!visited[v] && dist[v] < min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void print_path(int parent[], int j)
{
    if (parent[j] == NO_PARENT)
    {
        printf("%d", j + 1);
        return;
    }
    print_path(parent, parent[j]);
    printf(" -> %d", j + 1);
}

void print_solution(int dist[], int parent[], int src, int V)
{
    printf("\nShortest paths from source vertex %d:\n\n", src + 1);
    printf("%-15s %-15s %-30s\n", "Destination", "Distance", "Path");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < V; i++)
    {
        if (i == src)
            continue;

        printf("%-15d ", i + 1);
        if (dist[i] == INT_MAX)
        {
            printf("%-15s %-30s\n", "Infinity", "No path exists");
        }
        else
        {
            printf("%-15d ", dist[i]);
            print_path(parent, i);
            printf("\n");
        }
    }
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int src, int V)
{
    int dist[V];
    int visited[V];
    int parent[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
        parent[i] = NO_PARENT;
    }

    dist[src] = 0;

    for (int count = 0; count < V; count++)
    {
        int u = min_distance(dist, visited, V);
        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && graph[u][v] > 0 && dist[u] != INT_MAX)
            {
                int new_dist = dist[u] + graph[u][v];
                if (new_dist < dist[v])
                {
                    dist[v] = new_dist;
                    parent[v] = u;
                }
            }
        }
    }
    print_solution(dist, parent, src, V);
}

int main()
{
    char filename[] = "inDiAdjMat1.dat";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open file '%s'\n", filename);
        return 1;
    }

    int V = get_num_nodes(file);
    if (V <= 1 || V > MAX_NODES)
    {
        printf("Error: Invalid number of vertices (%d) in file '%s'\n", V, filename);
        fclose(file);
        return 1;
    }

    int graph[MAX_NODES][MAX_NODES];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (fscanf(file, "%d", &graph[i][j]) != 1)
            {
                printf("Error reading matrix from file.\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    printf("Graph with %d vertices loaded successfully from '%s'.\n", V, filename);

    int start_node;
    while (1)
    {
        printf("\nEnter the starting vertex (from 1 to %d): ", V);
        if (scanf("%d", &start_node) == 1 && start_node >= 1 && start_node <= V)
        {
            dijkstra(graph, start_node - 1, V);
            break;
        }
        else
        {
            printf("Invalid input. Please enter a number between 1 and %d.\n", V);
            while (getchar() != '\n')
                ;
        }
    }

    return 0;
}
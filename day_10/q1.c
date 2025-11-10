/*
Aim of the program: Given an undirected weighted connected graph G(V, E). Apply
Krushkal’s algorithm to
● Find the minimum spanning tree T(V, E’) and Display the selected edges of G.
● Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have varying
weight. The weight matrix of the graph can be represented from the user’s input in the given
format. The expected output could be the selected edge and the corresponding cost of the edge as
per the sample output.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Edge
{
    int src, dest, weight;
};

struct Subset
{
    int parent;
};

int find(struct Subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void union_sets(struct Subset subsets[], int x, int y)
{
    int x_root = find(subsets, x);
    int y_root = find(subsets, y);
    subsets[x_root].parent = y_root;
}

int compareEdges(const void *a, const void *b)
{
    struct Edge *a_edge = (struct Edge *)a;
    struct Edge *b_edge = (struct Edge *)b;
    return a_edge->weight - b_edge->weight;
}

void printMST(struct Edge result[], int e, int V)
{
    int mst_adj[MAX_VERTICES][MAX_VERTICES] = {0};
    long long total_cost = 0;

    for (int i = 0; i < e; ++i)
    {
        mst_adj[result[i].src][result[i].dest] = result[i].weight;
        mst_adj[result[i].dest][result[i].src] = result[i].weight;
        total_cost += result[i].weight;
    }

    printf("\nCost Adjacency Matrix of MST:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d\t", mst_adj[i][j]);
        }
        printf("\n");
    }

    printf("\nTotal cost of the MST: %lld\n", total_cost);
}

void KruskalMST(int graph[MAX_VERTICES][MAX_VERTICES], int V)
{
    int max_edges = V * (V - 1) / 2;
    struct Edge *edges = (struct Edge *)malloc(max_edges * sizeof(struct Edge));
    int edge_count = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (graph[i][j] != 0)
            {
                edges[edge_count].src = i;
                edges[edge_count].dest = j;
                edges[edge_count].weight = graph[i][j];
                edge_count++;
            }
        }
    }

    qsort(edges, edge_count, sizeof(struct Edge), compareEdges);

    struct Subset *subsets = (struct Subset *)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
    }

    struct Edge *result_mst = (struct Edge *)malloc((V - 1) * sizeof(struct Edge));
    int mst_edges = 0;
    int i = 0;

    while (mst_edges < V - 1 && i < edge_count)
    {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        if (x != y)
        {
            result_mst[mst_edges++] = next_edge;
            union_sets(subsets, x, y);
        }
    }

    printMST(result_mst, mst_edges, V);

    free(edges);
    free(subsets);
    free(result_mst);
}

int main()
{
    int V;
    int graph[MAX_VERTICES][MAX_VERTICES];
    FILE *file;

    file = fopen("inUnAdjMat.dat", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file 'inUnAdjMat.dat'\n");
        return 1;
    }

    if (fscanf(file, "%d", &V) != 1)
    {
        printf("Error: Could not read the number of vertices from the file.\n");
        fclose(file);
        return 1;
    }

    printf("Reading %d x %d adjacency matrix from 'inUnAdjMat.dat'...\n", V, V);
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (fscanf(file, "%d", &graph[i][j]) != 1)
            {
                printf("Error: File does not contain a complete adjacency matrix.\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    printf("\nOriginal Graph Adjacency Matrix:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }

    KruskalMST(graph, V);

    return 0;
}
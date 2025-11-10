/**
6.1 Aim of the program: Given an undirected weighted connected graph G(V, E) and starring
vertex ‘s’. Maintain a Min-Priority Queue ‘Q’ from the vertex set V and apply Prim’s algorithm
to
● Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’.
● Display total cost of the minimum spanning tree T.
Note# Nodes will be numbered consecutively from 1 to n (user input), and edges will have varying
weight. The graph G can be read from an input file “inUnAdjMat.dat” that contains cost adjacency
matrix. The expected output could be displayed as the cost adjacency matrix of the minimum
spanning tree and total cost of the tree.

*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

struct MinHeapNode
{
    int v;
    int key;
};

struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode *newMinHeapNode(int v, int key)
{
    struct MinHeapNode *minHeapNode = (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->key = key;
    return minHeapNode;
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode **)malloc(capacity * sizeof(struct MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b)
{
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
        smallest = right;

    if (smallest != idx)
    {
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode *root = minHeap->array[0];

    struct MinHeapNode *lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

void decreaseKey(struct MinHeap *minHeap, int v, int key)
{
    int i = minHeap->pos[v];

    minHeap->array[i]->key = key;

    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
    {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int V)
{
    int mst_adj[MAX_VERTICES][MAX_VERTICES] = {0};
    long long total_cost = 0;

    // printf("Edges in MST:\n");
    for (int i = 1; i < V; i++)
    {
        if (parent[i] != -1)
        {
            // printf("%d - %d (cost: %d)\n", parent[i], i, graph[i][parent[i]]);
            mst_adj[parent[i]][i] = graph[i][parent[i]];
            mst_adj[i][parent[i]] = graph[i][parent[i]];
            total_cost += graph[i][parent[i]];
        }
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

void PrimMST(int graph[MAX_VERTICES][MAX_VERTICES], int V, int startVertex)
{
    int parent[V];
    int key[V];

    struct MinHeap *minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v)
    {
        parent[v] = -1;
        key[v] = INF;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    key[startVertex] = 0;
    decreaseKey(minHeap, startVertex, key[startVertex]);

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        struct MinHeapNode *minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;

        for (int v = 0; v < V; ++v)
        {

            if (graph[u][v] && isInMinHeap(minHeap, v) && graph[u][v] < key[v])
            {
                key[v] = graph[u][v];
                parent[v] = u;
                decreaseKey(minHeap, v, key[v]);
            }
        }
        free(minHeapNode);
    }

    printMST(parent, graph, V);

    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
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

    int startVertex;
    printf("\nEnter the starting vertex (0 to %d): ", V - 1);
    scanf("%d", &startVertex);

    if (startVertex < 0 || startVertex >= V)
    {
        printf("Invalid starting vertex. Please enter a value between 0 and %d.\n", V - 1);
        return 1;
    }

    PrimMST(graph, V, startVertex);

    return 0;
}

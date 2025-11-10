/*
Huffman coding assigns variable length code words to fixed length input
characters based on their frequencies or probabilities of occurrence. Given a set of characters along
with their frequency of occurrences, write a c program to construct a Huffman tree.
Note#
● Declare a structure SYMBOL having members alphabet and frequency. Create a Min Priority Queue, keyed on frequency attributes.
● Create an array of structures where size=number of alphabets.

Input:
    Enter the number of distinct alphabets: 6
    Enter the alphabets: a b c d e f
    Enter its frequencies: 45 13 12 16 9 5
Output:
    In-order traversal of the tree (Huffman): a c b f e d
*/
#include <stdio.h>
#include <stdlib.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
};

struct HNode
{
    struct SYMBOL data;
    struct HNode *left, *right;
};

struct MinHeap
{
    int size;
    int capacity;
    struct HNode **array;
};

struct HNode *newNode(char alphabet, int frequency)
{
    struct HNode *temp = (struct HNode *)malloc(sizeof(struct HNode));
    temp->left = temp->right = NULL;
    temp->data.alphabet = alphabet;
    temp->data.frequency = frequency;
    return temp;
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct HNode **)malloc(capacity * sizeof(struct HNode *));
    return minHeap;
}

void swapNodes(struct HNode **a, struct HNode **b)
{
    struct HNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->data.frequency < minHeap->array[smallest]->data.frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->data.frequency < minHeap->array[smallest]->data.frequency)
        smallest = right;

    if (smallest != idx)
    {
        swapNodes(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct HNode *extractMin(struct MinHeap *minHeap)
{
    struct HNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct HNode *node)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->data.frequency < minHeap->array[(i - 1) / 2]->data.frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

void buildMinHeap(struct MinHeap *minHeap)
{
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i)
    {
        minHeapify(minHeap, i);
    }
}

int isLeaf(struct HNode *root)
{
    return !(root->left) && !(root->right);
}

struct HNode *buildTree(struct SYMBOL symbols[], int n)
{
    struct HNode *left, *right, *top;

    struct MinHeap *minHeap = createMinHeap(n);

    for (int i = 0; i < n; ++i)
    {
        minHeap->array[i] = newNode(symbols[i].alphabet, symbols[i].frequency);
    }
    minHeap->size = n;
    buildMinHeap(minHeap);

    while (minHeap->size != 1)
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('x', left->data.frequency + right->data.frequency);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void inOrderTraversal(struct HNode *root)
{
    if (!root)
    {
        return;
    }
    inOrderTraversal(root->left);

    if (isLeaf(root))
    {
        printf("%c ", root->data.alphabet);
    }

    inOrderTraversal(root->right);
}

int main()
{
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    struct SYMBOL symbols[n];

    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &symbols[i].alphabet);
    }

    printf("Enter their frequencies: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &symbols[i].frequency);
    }

    struct HNode *root = buildTree(symbols, n);

    printf("\nIn-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");

    free(root);

    return 0;
}

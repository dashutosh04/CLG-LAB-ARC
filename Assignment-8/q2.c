/*
8.2 In addition to the 8.1 perform the following menu driven operations on BST.
i. insert an element to the BST
ii. display the largest element
iii. display the smallest element
iv. height of a node
v. count number of leaf nodes
*/

#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}

struct Node *insert(struct Node *node, int data)
{
    if (node == NULL)
        return (newNode(data));
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

int max(struct Node *node)
{ // Recursive way
    if (node->right == NULL)
    {
        return node->data;
    }
    return max(node->right);
}

int min(struct Node *node)
{ // Recursive way
    if (node->left == NULL)
    {
        return node->data;
    }
    return min(node->left);
}

int height(struct Node* node) {
    if (node == NULL)
        return 0;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    } else {
        return 1 + rightHeight;
    }
}

int countLeafNodes(struct Node* node) {
    if (node == NULL)
        return 0;
    
    if (node->left == NULL && node->right == NULL)
        return 1;
    
    return countLeafNodes(node->left) + countLeafNodes(node->right);
}

int main()
{
    struct Node *root = NULL;
    int choice, data;
    int key;
    while (1)
    {

        printf("\n1. Insert\n2. Largest\n3. Smallest\n4. Height\n5. Count Leaf\n6.Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Largest Element: %d\n", max(root));
            break;
        case 3:
            printf("Smallest Element: %d\n", min(root));
            break;
        case 4:
            printf("Height of the tree: %d\n", height(root));
            break;
        case 5:
            printf("Number of leaf nodes: %d\n", countLeafNodes(root));
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}

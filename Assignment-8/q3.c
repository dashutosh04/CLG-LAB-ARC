/*8.3 In addition to 8.2, perform deletion of an element in the BST using function.*/

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

struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *del(struct Node *node, int key)
{
    if (node == NULL)
        return node;

    if (key < node->data)
        node->left = del(node->left, key);
    else if (key > node->data)
        node->right = del(node->right, key);
    else
    {
        if (node->left == NULL)
        {
            struct Node *temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL)
        {
            struct Node *temp = node->left;

            free(node);
            return temp;
        }
        struct Node *temp = minValueNode(node->right);
        node->data = temp->data;

        node->right = del(node->right, temp->data);
    }
    return node;
}

/*
int max1(struct Node *node) //Iterative way
{
    int max_val = node->data;
    while (node->right != NULL)
    {
        max_val = node->right->data;
        node = node->right;
    }
    return max_val;
}
*/

/*
int min1(struct Node *node) //Iterative way
{
    int min_val = node->data;
    while (node->left != NULL)
    {
        min_val = node->left->data;
        node = node->left;
    }
    return min_val;
}
*/

int main()
{
    struct Node *root = NULL;
    int choice, data;
    int key;
    while (1)
    {

         printf("\n1. Insert\n2. Largest\n3. Smallest\n4. Delete\n5. Exit\n");
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
            printf("Enter data to delete: ");
            scanf("%d", &key);
            root = del(root, key);
            break;
        case 5:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}

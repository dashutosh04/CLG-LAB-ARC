/*
8.1Write a program to create a binary search tree of n data elements using linked list and perform the
following menu driven operations:
i. preorder traversal
ii. postorder traversal
iii. inorder traversal
iv. search an element
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
    else if (data >= node->data)
        node->right = insert(node->right, data);
    return node;
}

void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(struct Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int search(struct Node *root, int key)
{
    if (root == NULL || root->data == key)
        return root != NULL;
    if (root->data > key)
        return search(root->left, key);
    return search(root->right, key);
}

int main()
{
    struct Node *root = NULL;
    int choice, data;
    int key;
    while (1)
    {

        printf("\n1. Insert\n2. Preorder\n3. Postorder\n4. Inorder\n5. Search\n6. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("\nPreorder traversal of binary tree is: ");
            preOrder(root);
            break;
        case 3:
            printf("\nPostorder traversal of binary tree is: ");
            postOrder(root);
            break;

        case 4:
            printf("\nInorder traversal of binary tree is: ");
            inOrder(root);
            break;

        case 5:

            printf("\nEnter the element to search: ");
            scanf("%d", &key);
            if (search(root, key))
            {
                printf("%d found in BST\n", key);
            }
            else
            {
                printf("%d not found in BST\n", key);
            }
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
}

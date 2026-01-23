/*
SET - B
Question 1

WAP to replace the first column of the 2D matrix to the last one, 2nd coloumn to the 2nd last one,
3rd coloumn to the third last one and so on.
*/

/*
Given matrix -
1 0
0 1
Result
0 1
1 0
*/

#include <stdio.h>
#include <stdlib.h>

/*Here I have used a swapper funciton to first reverse the first row then the second row
and so on.
*/

// Swapper funciton

void swapper(int **matrix, int rows, int cols)
{
    // Here I have iterated over half of the rows.
    for (int i = 0; i < rows; i++)
    {
        /*
            Here I am reversing each row one by one. using temp as a variable.
        */

        int temp = 0;
        for (int j = 0; j < cols / 2; j++)
        {
            temp = matrix[i][j];                    // To store the current value from the iterator in temp.
            matrix[i][j] = matrix[i][cols - j - 1]; // To replace the current value with the required value
            matrix[i][cols - j - 1] = temp;         // Put back the value from temp to its place.
        }
    }
}

// Main function
int main()
{
    int rows, cols;

    printf("Type the rows and cols for the 2D matrix.: ");
    scanf("%d %d", &rows, &cols);

    int **matrix = (int **)malloc(rows * sizeof(int *));
    /*Here we will be allocating memory for our 2D matrix using DMA*/

    if (matrix == NULL)
    {
        printf("Sorry but memory allocation was failed.\n");
        return 1;
    }

    // Here we are running a loop to allocate memory for rows withing the matrix.

    for (int i = 0; i < rows; i++)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]); // Freeing memory one by one if failed
            }
            free(matrix); // Freeing the entire matrix upon failure.
            return 1;
        }
    }

    // Taking user input
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Running the swapper function.
    swapper(matrix, rows, cols);

    // Resultant matrix
    printf("The resultant matrix is:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]); // Priting element by element.
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]); // Freeing the memory after use row by row
    }
    free(matrix); // Freeing the memory of the entire matrix.

    return 0;
}
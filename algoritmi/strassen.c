#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "utility.h"

IntMatrix *iterative_multiplication(IntMatrix *A, IntMatrix *B) 
{
    IntMatrix *result = (IntMatrix *)malloc(sizeof(IntMatrix));
    assert(result != NULL);

    result->rows = B->cols;
    result->cols = A->rows;

    int **result_vals = (int **)malloc(sizeof(int *) * B->cols);
    assert(result_vals != NULL);

    for (int row = 0; row < result->rows; row++) 
    {
        result_vals[row] = (int *)malloc(sizeof(int) * A->rows);
        assert(result_vals[row] != NULL);

        for (int col = 0; col < result->cols; col++) 
        {
            result_vals[row][col] = 0;
            for (int k = 0; k < A->cols; k++) 
            {
                result_vals[row][col] += A->values[row][k] * B->values[k][col];
            }
        }
    }

    result->values = result_vals;

    return result;
}

IntMatrix *recursive_multiplication(IntMatrix *A, IntMatrix *B) 
{
    /* to implement */
}

int main( void ) 
{
    srand(time(NULL));

    IntMatrix A = { 2, 2, NULL };
    init_matrix(&A, 0, 10);
    
    printf("A:\n");
    print_matrix(&A);

    IntMatrix B = { 2, 2, NULL };
    init_matrix(&B, 0, 10);
    
    printf("\nB:\n");
    print_matrix(&B);
    
    print_separator();
    printf("Iterative multiplication: \n");
    print_matrix(iterative_multiplication(&A, &B));

    return EXIT_SUCCESS;
}

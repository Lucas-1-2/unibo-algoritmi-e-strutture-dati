#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "utility.h"

void print_vector( int *vector, int size ) 
{
    printf("[");
    for (int i = 0; i < size - 1; i++) 
    {
        printf("%d,", vector[i]);
    }
    printf("%d]\n", vector[size - 1]);
}

void create_random_vector( int **out_vect, int size, int lower, int upper ) 
{
    srand(time(NULL));

    *out_vect = (int *)malloc(sizeof(int) * size);
    if (*out_vect == NULL) {
        fprintf(stderr, "Errore: allocazione di memoria non riuscita...");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++) {
        (*out_vect)[i] = rnd_number(lower, upper);
    }
}

void print_separator( void ) 
{
    puts("\n======================\n");
}

void swap( int *a, int *b ) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int rnd_number( int lower, int upper ) 
{
    return (rand() % (upper - lower + 1)) + lower;
}

void init_matrix(IntMatrix *matrix, int lower, int upper) 
{
    assert(matrix != NULL);

    matrix->values = (int **)malloc(sizeof(int *) * matrix->rows);
    assert(matrix->values != NULL);

    for (int row = 0; row < matrix->rows; row++) 
    {
        matrix->values[row] = (int *)malloc(sizeof(int) * matrix->cols);
        assert(matrix->values[row] != NULL);

        for (int col = 0; col < matrix->cols; col++) {
            matrix->values[row][col] = rnd_number(lower, upper);
        }
    }
}

void print_matrix(IntMatrix *matrix) 
{
    for (int row = 0; row < matrix->rows; row++) 
    {
        printf("[");
        for (int col = 0; col < matrix->cols - 1; col++) 
        {
            printf("%4d,", matrix->values[row][col]);
        }
        printf("%4d  ]\n", matrix->values[row][matrix->cols - 1]);
    }
}

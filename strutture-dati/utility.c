#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
        (*out_vect)[i] = (rand() % upper - lower + 1) + lower;
    }
}

void print_separator( void ) 
{
    puts("\n======================\n");
}

void swap(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

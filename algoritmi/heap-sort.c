#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utility.h"

static int size = -1;

/* 
 *   Utility per navigare e costruire un heap - implementate anche nel file 'stutture-dati/heap.c'
 */
int get_parent(int idx) 
{
    return floor(idx / 2);
}

int get_right(int idx) 
{
    return idx * 2 + 1;
}

int get_left(int idx) 
{
    return idx * 2;
}

void max_heapify(int *vector, int idx)
{
    int idx_right = get_right(idx);
    int idx_left = get_left(idx);
    int idx_largest = -1;

    if (idx_left < size && vector[idx] < vector[idx_left]) 
        idx_largest = idx_left;
    else
        idx_largest = idx;

    if (idx_right < size && vector[idx_largest] < vector[idx_right])
        idx_largest = idx_right;

    if (idx_largest != idx) 
    {
        swap(&vector[idx], &vector[idx_largest]);
        max_heapify(vector, idx_largest);
    }
}

void build_heap(int *vector) 
{
    for (int i = floor(size / 2); i >= 0; i--) {
        max_heapify(vector, i);
    }
}

void heap_sort(int *vector) 
{
    int original_size = size;
    build_heap(vector);

    while (size != 1) 
    {
        swap(&vector[0], &vector[size - 1]); /* Scambio il max con l'ultimo elemento del vettore */
        /* 
         * Ricostruisco l'heap considerando un elemento in meno, in modo da avere di nuovo il prossimo 
         * max degli elementi in cima all'heap 
         */
        size--; 
        build_heap(vector);
    }

    size = original_size;
}

int main( void ) 
{
    size = 10;

    int *vect = NULL;
    create_random_vector(&vect, size, 0, 100);
    
    printf("BEFORE Heap-Sort:\n");
    print_vector(vect, size);
    
    print_separator();
   
    printf("AFTER Heap-Sort:\n");
    heap_sort(vect);
    print_vector(vect, size);
    
    return EXIT_SUCCESS;
}

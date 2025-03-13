#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "utility.h"

/* Dimensione del vettore */
static int size = -1;

/* Metodi di navigazione */
int get_right(int i) {
    return 2 * i + 1;
} 

int get_left(int i) {
    return 2 * i;
}

int get_parent(int i) {
    return floor(i / 2);
}

/* 
 * Costruzione di un heap tramite vettore 
 */
void max_heapify(int *vector, int index) 
{
    int right = get_right(index);
    int left = get_left(index);
    int index_of_largest = -1;
    
    if (left <= size && vector[left] > vector[index]) {
        index_of_largest = left;
    }
    else {
        index_of_largest = index;
    }

    if (right <= size && vector[right] > vector[index_of_largest]) {
        index_of_largest = right;
    }

    if (index_of_largest != index) 
    {
        swap(&vector[index_of_largest], &vector[index]);
        max_heapify(vector, index_of_largest);
    }
}

/*
 * Costruzione dell'heap: per ogni elemento compreso nella prima metà del vettore
 * lo sistemo chiamando la funzione 'max_heapify()'
 */
void build_heap(int *vector) 
{
    for (int i = floor(size / 2); i >= 0; i--) {
        max_heapify(vector, i);
    }
}

int main(void) 
{
    int *vect = NULL;
    size = 10;
    
    create_random_vector(&vect, size, 0, 50);
    
    printf("Before MAX_HEAPIFY:\n");
    print_vector(vect, size);
    print_separator();
    printf("After MAX_HEAPIFY:\n");
    build_heap(vect);
    print_vector(vect, size);

    return EXIT_SUCCESS;
}

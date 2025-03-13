#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

static int size = -1;

int partition(int *vect, int left, int right) 
{
    int pivot = vect[right];
    int idx = left - 1;
    
    for (int j = left; j < right; j++) 
    {
        if (vect[j] <= pivot)
        {
            idx++;
            swap(&vect[idx], &vect[j]);
        }
    }

    swap(&vect[idx + 1], &vect[right]);
    
    return idx + 1;
}

void quick_sort(int *vect, int left, int right) 
{
    if (left < right) 
    {
        int pivot = partition(vect, left, right);
        quick_sort(vect, left, pivot - 1);
        quick_sort(vect, pivot + 1, right);
    }
}

int main( void ) 
{
    size = 10;
    int *vect = NULL;
    create_random_vector(&vect, size, 0, 100);
    
    printf("BEFORE Quick-Sort:\n");
    print_vector(vect, size);

    print_separator();

    printf("AFTER Quick-Sort:\n");
    quick_sort(vect, 0, size - 1);
    print_vector(vect, size);

    return EXIT_SUCCESS;
}

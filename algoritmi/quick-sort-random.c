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

int randomized_partition(int *vect, int left, int right) 
{
    int rnd_pivot_idx = rnd_number(left, right);
    swap(&vect[right], &vect[rnd_pivot_idx]);
    return partition(vect, left, right);
}

void randomized_quick_sort(int *vect, int left, int right) 
{
    if (left < right) 
    {
        int rnd_pivot = randomized_partition(vect, left, right);
        randomized_quick_sort(vect, left, rnd_pivot - 1);
        randomized_quick_sort(vect, rnd_pivot + 1, right);
    }
}

int main( void ) 
{
    size = 10;
    int *vect = NULL;
    create_random_vector(&vect, size, 0, 100);

    printf("Before RANDOMIZED QUICKSORT:\n");
    print_vector(vect, size);

    print_separator();

    printf("After RANDOMIZED QUICKSORT:\n");
    randomized_quick_sort(vect, 0, size - 1);
    print_vector(vect, size);

    return EXIT_SUCCESS;
}

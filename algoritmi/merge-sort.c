#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utility.h"

static int size = -1;

/* Da correggere l'implementazione */
void merge(int *vector, int left, int mid, int right)
{
    int left_length = mid - left + 1; 
    int right_length = right - mid;

    int left_vect[left_length];
    int right_vect[right_length];

    for (int i = 0; i < left_length; i++) 
    {
        left_vect[i] = vector[left + i];
    }

    for (int i = 0; i < right_length; i++) 
    {
        right_vect[i] = vector[mid + i];
    }

    int p_left = 0, p_right = 0;
    for (int i = left; i <= right; i++) 
    {
        if (left_vect[p_left] <= right_vect[p_right]) {
            vector[i] = left_vect[p_left];
            p_left++;
        }
        else {
            vector[i] = right_vect[p_right];
            p_right++;
        }
    }
}

void merge_sort(int *vector, int left, int right) 
{
    if (left < right) 
    {
        int middle = floor((left + right) / 2);
        merge_sort(vector, left, middle);
        merge_sort(vector, middle + 1, right);
        merge(vector, left, middle, right);
    }
}

int main( void ) 
{
    size = 10; 
    int *vector = NULL;
    create_random_vector(&vector, size, 0, 100);
    
    printf("Before MERGE-SORT:\n");
    print_vector(vector, size);
    print_separator();

    merge_sort(vector, 0, size - 1);
    printf("After MERGE-SORT:\n");
    print_vector(vector, size);
    
    return EXIT_SUCCESS;
}

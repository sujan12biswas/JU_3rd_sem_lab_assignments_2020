#include <stdio.h>
#include "p8_sortedness.h"
#define MAX_SIZE 1024

void main(void) {
    const char *messages[] = {
        "Array is in ascending order", 
        "Array is in descending order",
        "All elements of the array are equal",
        "Array is unsorted"
    };
    int A[MAX_SIZE], i, n;
    printf("Enter length of input array: "); scanf("%d", &n);
    printf("Enter %d integers: ", n);
    for(i = 0; i < n; i++) scanf("%d", A + i);
    printf("\n%s\n", messages[check_sorted(A, n)]);
}
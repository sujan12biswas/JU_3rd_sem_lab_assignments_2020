/*Given a large single dimensional array of integers, write functions for sliding window filter with maximum, minimum, 
median, and average to generate an output array. The window size should be an odd integer like 3, 5 or 7. Explain what you will 
do with the boundary values.

p6_swf.c Demostration program for given algorithms*/
#define MAX_ARRAY_SIZE 1024
#define MAX_WINDOW_SIZE 1023

/*Get a window from A, of size win_size (odd number), and put it into W. Assume position and win_size are valid.
lA = length of A.*/
void get_window(const float A[MAX_ARRAY_SIZE], int lA, int position, int win_size, float W[MAX_WINDOW_SIZE]) {
    int i, pos;
    for (i = 0; i < win_size; i++) {
        pos = position - (win_size >> 1) + i; /*Calculate position from where to get element from A*/
        /*floor(win_size / 2) == win_size >> 1 (binary right shift)*/
        if (pos < 0 || pos >= lA) W[i] = 0; /*Put 0 if out of bounds for A*/
        else W[i] = A[pos]; 
    }
}

/*An assortment of various reduction operations.*/

/*Parent prototype for reduction operations; W is the window to operate upon on size win_size (odd number)*/
typedef float (*reduction_operation)(const float W[MAX_WINDOW_SIZE], int win_size); 

/*Find minimum of W.*/
float minimum(const float W[MAX_WINDOW_SIZE], int win_size) {
    float min = W[0]; int i;
    for (i = 1; i < win_size; i++) if(min > W[i]) min = W[i];
    return min;
}
/*Find maximum of W.*/
float maximum(const float W[MAX_WINDOW_SIZE], int win_size) {
    float max = W[0]; int i;
    for (i = 1; i < win_size; i++) if(max < W[i]) max = W[i];
    return max;
}
/*Find average of W.*/
float average(const float W[MAX_WINDOW_SIZE], int win_size) {
    float sum = 0; int i;
    for (i = 1; i < win_size; i++) sum += W[i];
    return sum / win_size;
}

/*Compare two floats passed as void pointers. Required for the library qsort function.*/
int comp_float(const void *p1, const void *p2) {
    const float *f1 = (const float *)p1;
    const float *f2 = (const float *)p2;
    if(*f1 < *f2) return -1;
    else if (*f1 == *f2) return 0;
    else return 1;
}

#include <stdlib.h>
#include <string.h>
/*Find median of W.*/
float median(const float W[MAX_WINDOW_SIZE], int win_size) {
    static float WCopy[MAX_WINDOW_SIZE]; /*No need to create multiple times on stack each time median() is called*/
    memcpy(WCopy, W, sizeof(float) * win_size); /*Create a copy of W*/
    qsort(WCopy, win_size, sizeof(float), comp_float); /*Sort the copy of W.*/
    /*memcpy and qsort are included in C89*/
    return WCopy[win_size >> 1];
    /*Get the middle element of a sorted window to find median; floor(win_size / 2) = binary right shift*/
}

/*Generate output array of same length as A, using sliding window filters of window size win_size and a reduction operation.
lA = length of A; output array is B. Reduction operation is reduce.*/
void filter(const float A[MAX_ARRAY_SIZE], int lA, int win_size, float B[MAX_ARRAY_SIZE], reduction_operation reduce) {
    static float W[MAX_WINDOW_SIZE]; /*Window; no need to create multiple times as filter() is called*/
    int i;
    for (i = 0; i < lA; i++) {
        get_window(A, lA, i, win_size, W); /*Get a window over position i*/
        B[i] = reduce(W, win_size); /*Reduce window to get element*/
    }
}

#include <stdio.h>
void main(void) {
    float A[MAX_ARRAY_SIZE], B[MAX_ARRAY_SIZE]; /*Input array and output array*/
    int lA, win_size; /*Length of A and window size*/
    float limit; /*Limit of values in array*/
    int i;
    printf("Enter input array size: "); scanf("%d", &lA);
    printf("Enter %d numbers: ", lA);
    for(i = 0; i < lA; i++) scanf("%f", A + i);
    while(1) {
        printf("\nEnter window size (odd number greater than 1): "); scanf("%d", &win_size);
        if(!(win_size & 1) || win_size < 3) printf("Invalid window size! "); /*integer & 1 is 1 if integer is odd*/
        else break;
    }
    printf("\n\nFiltering with minimum of window...\n");
    filter(A, lA, win_size, B, minimum);
    printf("Output array:\n");
    for(i = 0; i < lA; i++) printf("%.2f ", B[i]);
    printf("\n\nFiltering with maximum of window...\n");
    filter(A, lA, win_size, B, maximum);
    printf("Output array:\n");
    for(i = 0; i < lA; i++) printf("%.2f ", B[i]);
    printf("\n\nFiltering with average of window...\n");
    filter(A, lA, win_size, B, average);
    printf("Output array:\n");
    for(i = 0; i < lA; i++) printf("%.2f ", B[i]);
    printf("\n\nFiltering with median of window...\n");
    filter(A, lA, win_size, B, median);
    printf("Output array:\n");
    for(i = 0; i < lA; i++) printf("%.2f ", B[i]);
    printf("\n");
}
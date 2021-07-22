/*Given two sorted arrays, write a function to merge the array in the sorting order.

p9_merge.c Demostration program and algorithm implementations*/

#include "p8_sortedness.h" /*We will use this file to determine sortedness of input.*/

/*Merge A and B, of length lenA and lenB, and put result into C. C must have at least lenA+lenB space.
A and B are sorted in direction, which is either ASCENDING or DESCENDING. C will also be sorted in that way.*/ 
void merge(const int A[], int lenA, const int B[], int lenB, enum sortedness direction, int C[]) {
    int i, j, k;
    i = 0; j = 0; k = 0; /*Tops of stacks A, B and C, 0-based indexes*/
    while (i < lenA && j < lenB) {/*While the input stacks have cards*/
        /*Compare according to direction.*/
        if ((direction == ASCENDING) ? A[i] <= B[j] : A[i] >= B[j]) { C[k] = A[i]; i++;} /*Put top of A on C*/
        else { C[k] = B[j]; j++; } /*Put top of B on C.*/
        k++; /*Advance top of C.*/
    }
    /*Elements might remain in either A or B (not both)*/
    while (i < lenA) { C[k] = A[i]; i++; k++; } /*Append A to C if A has elements.*/
    while (j < lenB) { C[k] = B[j]; j++; k++; } /*Append A to C if A has elements.*/
    /*C is in the correct order already.*/
    /*C was passed by reference.*/
}

/*Reverse the array of length n.*/
void reverse_array(int A[], int n) {
    int i, t;
    for(i = 0; i < (n/2); i++) {
        /*Swap an element of this lower half with corresponding element of upper half*/
        t = A[i]; 
        A[i] = A[n - i - 1]; 
        A[n - i - 1] = t;
    }
} 

#include <stdio.h>
/*Input an array of length n.*/
void input_array(int A[], int n) {
    int i;
    for(i = 0; i < n; i++) scanf("%d", A + i);
}
/*Output an array of length n.*/
void output_array(const int A[], int n) {
    int i;
    for(i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
}

#include <stdlib.h>

/*Compare two integers passed as void pointers. Required for the qsort function.*/
int comp_ints(const void *p1, const void *p2) {return (*(const int *)p1) - (*(const int *)p2); }
/*Compare two integers in reverse (passed as void pointers). Required for the qsort function.*/
int comp_ints_reversed(const void *p1, const void *p2) {return (*(const int *)p2) - (*(const int *)p1); }
/*Sort array A of length len in the direction given.*/
#define sort(A, len, direction) (qsort((A), (len), sizeof(int), ((direction) == ASCENDING) ? comp_ints : comp_ints_reversed))

#define MAX_SIZE 1024
void main(void) {
    char choice[2];
    int A[MAX_SIZE], B[MAX_SIZE], C[MAX_SIZE];
    int i, lenA, lenB;
    enum sortedness sA, sB, sC;
    printf("Enter length of first sorted array: "); scanf("%d", &lenA);
    printf("Enter a sorted array of %d integers: ", lenA); input_array(A, lenA);
    sA = check_sorted(A, lenA);
    if(sA == UNSORTED) {
        printf("First array is unsorted. Sort first array in which direction? [A=Ascending/D=Descending] "); scanf("%s", choice);
        sA = (choice[0] == 'a' || choice[0] == 'A') ? ASCENDING : DESCENDING;
        printf("Sorting first array...\n"); sort(A, lenA, sA); 
    }
    printf("\nEnter length of second sorted array: "); scanf("%d", &lenB);
    printf("Enter another sorted array of %d integers: ", lenB); input_array(B, lenB);
    sB = check_sorted(B, lenB);
    if(sB == UNSORTED) {
        printf("Second sorted array is unsorted. Sort second array in which direction? [A=Ascending/D=Descending] "); scanf("%s", choice);
        sB = (choice[0] == 'a' || choice[0] == 'A') ? ASCENDING : DESCENDING;
        printf("Sorting second array...\n"); sort(B, lenB, sB); 
    }
    printf("\nMerge in which direction? [A=Ascending/D=Descending] "); scanf("%s", choice);
    sC = (choice[0] == 'a' || choice[0] == 'A') ? ASCENDING : DESCENDING;
    if(sA != sC) { printf("Reversing first array...\n"); reverse_array(A, lenA); sA = sC; }
    if(sB != sC) { printf("Reversing second array...\n"); reverse_array(B, lenB); sB = sC; }
    printf("Merging array...\n"); merge(A, lenA, B, lenB, sC, C);
    printf("Merged array: "); output_array(C, lenA+lenB);
} 
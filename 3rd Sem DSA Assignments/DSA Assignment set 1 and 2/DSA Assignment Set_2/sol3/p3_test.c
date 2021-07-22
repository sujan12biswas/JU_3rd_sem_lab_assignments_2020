/*Define an ADT for List.
Write C data structure representation and functions for the operations on the List in a Header
file with array as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file. Two data structures with and without using sentinels in arrays
are to be implemented.

p3_test.c Testing program, this code defaults to the non-sentinel version. To conditionally compile to use sentinel version, 
define the macro USE_SENTINELS on the top. This can be done during compilation on the command line:
1. On GCC:
    gcc -DUSE_SENTINELS <...rest options...> p3_test.c
2. On Clang:
    clang -DUSE_SENTINELS <...rest options...> p3_test.c
3. On MSVC:
    CL /DUSE_SENTINELS <...rest options...> p3_test.c
*/

#include <stdio.h>

/*We will have integer vectors.*/
#define T int

#ifdef USE_SENTINELS
#define NIL -1
#include "p3_vector_sentinel.h"
#else
#include "p3_vector_nonsentinel.h"
#endif

int print_func(T *ptr) { /*Print the element at ptr.*/
    printf("%d ", *ptr);
    return 1; /*Print all elements.*/
}
int less_comp(const T a, const T b) { return a < b; } /*Check if a is less than b.*/
int greater_comp(const T a, const T b) { return a > b; } /*Check if a is greater than b.*/

void main(void) {
    int i, choice;
    T elem;
#ifdef USE_SENTINELS
    T V[1024];
#else
    vector V;
#endif
    vector_construct(V);
    printf("1. Print vector\n");
    printf("2. Print vector in reverse\n");
    printf("3. Insert into vector at a position\n");
    printf("4. Delete from vector from a position\n");
    printf("5. Find an element in vector\n");
    printf("6. Find an element in vector from the end\n");
    printf("7. Sort the vector\n");
    printf("8. Sort the vector in reverse\n");
    printf("0. Exit\n");
    while(1) {
        printf("\nEnter your choice: "); scanf("%d", &choice);
        switch(choice) {
        case 1:
        case 2:
            vector_traverse(V, (choice == 1) ? FIRST2LAST : LAST2FIRST, print_func);
            printf("\nLength: %d\n", vector_length(V));
            break;
        case 3:
            printf("Enter a location between 1 and %d and ", vector_length(V) + 1);
#ifdef USE_SENTINELS
            printf("a non-negative integer: ");
#else
            printf("an integer: ");
#endif
            scanf("%d %d", &i, &elem); i--;
            if(i < 0 || i > vector_length(V)) {
                printf("Invalid location. Please enter option %d and try again.\n", choice);
                break;
            }
#ifdef USE_SENTINELS
            if(elem == NIL) {
                printf("Invalid element. Please enter option %d and try again.\n", choice);
                break;
            }
#endif
            vector_insert(V, i, elem);
            break;
        case 4:
            if(vector_length(V) == 0) {
                printf("Vector empty, nothing to delete.\n");
                break;
            }
            printf("Enter a location between 1 and %d: ", vector_length(V));
            scanf("%d", &i); i--;
            if (i >= vector_length(V)) {
                printf("Invalid location. Please enter option %d and try again", choice);
                break;
            }
            vector_delete(V, i);
            break;
        case 5:
        case 6:
#ifdef USE_SENTINELS
            printf("Enter a non-negative integer: "); scanf("%d", &elem);
            if(elem == NIL) {
                printf("Invalid element. Please enter option %d and try again.\n", choice);
                break;
            }
#else
            printf("Enter an integer: "); scanf("%d", &elem);
#endif
            i = vector_search(V, elem, (choice == 5) ? FIRST2LAST : LAST2FIRST);
            if(i < 0) printf("%d not found", elem);
            else printf("%d found at position %d\n", elem, i+1);
            break;
        case 7:
        case 8:
            vector_sort_ascending(V, (choice == 7) ? less_comp : greater_comp);
            break;
        case 0: vector_destroy(V); return;
        default: printf("Invalid Option!\n"); break;
        }
    }
}
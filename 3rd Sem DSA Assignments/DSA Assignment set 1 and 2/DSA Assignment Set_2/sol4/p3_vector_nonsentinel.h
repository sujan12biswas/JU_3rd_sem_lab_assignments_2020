/*Define an ADT for List.
Write C data structure representation and functions for the operations on the List in a Header
file with array as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file. Two data structures with and without using sentinels in arrays
are to be implemented.

p3_vector_nonsentinel.h Vector implementation without sentinels
*/

#ifdef _P3_VECTOR_SENTINEL_
#error Cannot be used with sentinel version in the same compilation
#endif

#ifndef _P3_VECTOR_NONSENTINEL_
#define _P3_VECTOR_NONSENTINEL_

#ifdef __cplusplus
extern "C" {
#endif

/*Define your type to be stored as a vector before this header file is included... such as this
#define T custom_type
#include "p3_vector_sentinel.h"
*/
#ifndef T
#warning T not specified. Defining T as int
#define T int
#endif

typedef struct __vector_t {
    T *buffer; /*Actual array to store the elements*/
    int length; /*Number of elements actually stored in the vector*/
    int capacity; /*Total capacity of the vector; the value that length can reach before buffer is resized upward*/
} * vector;


#include <stdlib.h>

/*Construct an empty vector V.*/
#define vector_construct(V)                              \
    {                                                    \
        (V) = (vector)malloc(sizeof(struct __vector_t)); \
        (V)->buffer = (T *)malloc(sizeof(T) * 16);       \
        (V)->length = 0;                                 \
        (V)->capacity = 16;                              \
    }

/*Destroy a vector.*/
#define vector_destroy(V)  \
    {                      \
        free((V)->buffer); \
        free((V));         \
    }

/*Store a new value (overwrite) at ith position.*/
#define vector_set(V, i, element) (*((V)->buffer + (i)) = (element)) 

/*Retrieve the ith element*/
#define vector_get(V, i) (*((V)->buffer + (i)))

/*Get length of V.*/
#define vector_length(V) ((V)->length)

/*Vector traversal direction.*/
enum vector_traversal_direction {LAST2FIRST, FIRST2LAST};

/*Traverse V in the given direction. The visit function accepts a pointer of type T and can so make changes as it traverses
each element; it can return 0 at any point instead of a nonzero value to indicate to stop the iteration.*/ 
void vector_traverse(vector V, enum vector_traversal_direction direction, int (*visit)(T *)) {
    int i, len;
    if (direction == FIRST2LAST) {
        i = 0;
        while (i < V->length) { /*V[i] is not NIL*/
            if(!visit(V->buffer + i)) return; /*Visit the element, exit on signal*/
            i++;
        }
    }
    else {
        len = vector_length(V);
        for (i = len - 1; i >= 0; i--) if(!visit(V->buffer + i)) return; /*Exit on signal*/ 
    }
}

void vector_insert(vector V, int i, const T element) { /*Insert element at position i.*/
    int j;
    /*Ensure we have enough space.*/
    if(V->length == V->capacity) V->buffer = (T *)realloc(V->buffer, V->capacity <<= 1); /*Increase capacity by twice*/
    j = vector_length(V) - 1; /*Point to last element*/
    V->length++;              /*No need to assign proper terminator of vector, however update length*/
    while(j >= i) {
        vector_set(V, j + 1, vector_get(V, j)); /*Shift each towards the end*/
        j--;
    }
    vector_set(V, i, element);
}

void vector_delete(vector V, int i) {/*Delete element at position i.*/
    int j = i;
    while((j + 1) < V->length) {/*V[j+1] is not NIL*/
        vector_set(V, j, vector_get(V, j + 1)); /*Shift each towards the start*/
        j++;
    }
    V->length--; /*V[j] = NIL to assign proper terminator*/
}

/*Search V for element in the direction specified. Return index such that V[index] = element.*/
int vector_search(vector V, const T element, enum vector_traversal_direction direction) {
    int i;
    if(direction == FIRST2LAST) {
        for (i = 0; i < V->length; i++) if(vector_get(V, i) == element) return i;
        /*Perform a linear search from first to last and return first occurence*/
    }
    else {
        for (i = V->length - 1; i >= 0; i--) if(vector_get(V, i) == element) return i;
        /*Perform a reversed linear search from last to first*/
    }
    return -1; /*Not found, we do not have any NIL for indexes so we use -1 as -1 is not a valid index)*/
}

/*Sort the vector in ascending order, here we use selection sort. lessthan function will return nonzero value if a < b and 0
otherwise*/ 
void vector_sort_ascending(vector V, int (*lessthan)(const T a, const T b)) {
    int len = vector_length(V);
    T swap_temp;
    int k, j, i;
    for (i = 0; i < len; i++) {
        /*Search for the minimum element between i to len-1 inclusive, and store the index of such element in k*/
        k = i;
        for (j = i + 1; j < len; j++) if(lessthan(vector_get(V, j), vector_get(V, k))) k = j;
        /*Swap V[i] with V[k]*/
        swap_temp = vector_get(V, i); vector_set(V, i, vector_get(V, k)); vector_set(V, k, swap_temp);
    }
}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_P3_VECTOR_NONSENTINEL_*/
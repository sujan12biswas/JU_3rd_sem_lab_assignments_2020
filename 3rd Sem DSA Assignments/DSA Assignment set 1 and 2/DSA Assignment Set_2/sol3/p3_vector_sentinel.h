/*Define an ADT for List.
Write C data structure representation and functions for the operations on the List in a Header
file with array as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file. Two data structures with and without using sentinels in arrays
are to be implemented.

p3_vector_sentinel.h Vector implementation with sentinels to indicate termination
*/

#ifdef _P3_VECTOR_NONSENTINEL_
#error Cannot be used with non-sentinel version in the same compilation
#endif

#ifndef _P3_VECTOR_SENTINEL_
#define _P3_VECTOR_SENTINEL_

#ifdef __cplusplus
extern "C" {
#endif

/*Define your type to be stored as a vector before this header file is included... such as this
#define T custom_type
#define NIL custom_sentinel
#include "p3_vector_sentinel.h"
*/
#ifndef T
#warning T not specified. Defining T as int, taking 0 as sentinel
#define T int
#define NIL ((T)0)
#endif

/*Define NIL (the termination sentinel) before you include this header file... such as this
#define T custom_type
#define NIL custom_sentinel
#include "p3_vector_sentinel.h"
*/
#ifndef NIL
#error Please define NIL before you include this header file
#endif

typedef T *vector; /*Our custom vector type, we use 0-based indexes*/

/*Construct an empty vector V*/
#define vector_construct(V) vector_set(V, 0, NIL)

/*Destroy a vector.  This is an empty operation.*/
#define vector_destroy(V) {}

/*Store a new value (overwrite) at ith position*/
#define vector_set(V, i, element) (*((V) + (i)) = (element))

/*Retrieve the ith element*/
#define vector_get(V, i) (*((V) + (i)))

int vector_length(vector V) {/*get length of V*/
    int i = 0;
    while (vector_get(V, i) != NIL) i++;
    return i; /*The index at which NIL is stored is the length of the list as elements are from 0 to len-1 inclusive.*/
}

/*Vector traversal direction.*/
enum vector_traversal_direction {LAST2FIRST, FIRST2LAST};

/*Traverse V in the given direction. The visit function accepts a pointer of type T and can so make changes as it traverses
each element; it can return 0 at any point instead of a nonzero value to indicate to stop the iteration.*/ 
void vector_traverse(vector V, enum vector_traversal_direction direction, int (*visit)(T *)) {
    int i, len;
    if (direction == FIRST2LAST) {
        i = 0;
        while (vector_get(V, i) != NIL) {
            if(!visit(V + i)) return; /*Visit the element, exit on signal*/
            i++;
        }
    }
    else {
        len = vector_length(V);
        for (i = len - 1; i >= 0; i--) if(!visit(V + i)) return; /*Exit on signal*/ 
    }
}

/*Insert element at position i. Assume V has space to hold the extra element.*/
void vector_insert(vector V, int i, const T element) {
    int j = vector_length(V)-1; /*Point to last element*/
    vector_set(V, j + 2, NIL);  /*Assign proper terminator for vector*/
    while(j >= i) {
        vector_set(V, j + 1, vector_get(V, j)); /*Shift each towards the end*/
        j--;
    }
    vector_set(V, i, element);
}

void vector_delete(vector V, int i) {/*Delete element at position i.*/
    int j = i;
    while (vector_get(V, j+1) != NIL) {
        vector_set(V, j, vector_get(V, j + 1)); /*Shift each towards the start*/
        j++;
    }
    vector_set(V, j, NIL);
}

/*Search V for element in the direction specified. Return index such that V[index] = element.*/
int vector_search(vector V, const T element, enum vector_traversal_direction direction) {
    int i, idx;
    i = 0;
    idx = -1; /*Store final index, we do not have any NIL for indexes so we use -1 as -1 is not a valid index*/
    while (vector_get(V, i) != NIL) {
        if (vector_get(V, i) == element) {
            idx = i;
            if (direction == FIRST2LAST) return idx; /*Exit on first occurence in case of first-to-last search*/
        }
        i++;
    }
    return idx; /*Return last occurence in case of last-to-first search*/
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

#endif /*_P3_VECTOR_SENTINEL*/
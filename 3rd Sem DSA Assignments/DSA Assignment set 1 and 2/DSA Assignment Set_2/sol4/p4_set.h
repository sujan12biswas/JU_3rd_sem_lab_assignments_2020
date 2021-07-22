/*Define an ADT for Set.
Write C data representation and functions for the operations on the Set in a Header file, with
array as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file.

p4_set.h Set implementation.*/

#ifndef _P4_SET_
#define _P4_SET_

#ifdef __cplusplus
extern "C" {
#endif

/*Define your type to be the members of sets before this header file is included... such as this
#define T custom_type
#include "p4_set.h"
*/
#ifndef T
#warning T not specified. Defining T as int
#define T int
#endif

/*Sets are vectors in disguise. This header depends on the header below. We reuse code for array lists from problem 3.*/
#include "p3_vector_nonsentinel.h"

typedef vector set; /*Sets are vectors in disguise*/

/*Construct a new empty set.*/
#define set_construct(S) (vector_construct((S)))

/*Destroy a set.*/
#define set_destroy(S) (vector_destroy((S)))

/*Obtain cardinality of a set. list_length(list) = vector_length(list)*/
#define set_cardinality(S) (vector_length((S)))

/*Check if a set is null/empty. Null sets have cardinality 0.*/
#define set_is_null(S) ((set_cardinality((S))) == 0)

/*Check for membership of x in S. x is present in S if we find a valid index for x in S.*/
#define set_is_member(S, x) ((vector_search((S), (x), (FIRST2LAST))) >= 0)

int set_add_member(set S, T x) { /*Add a unique element x into the set.*/
    if (set_is_member(S, x)) return 0; /*false to indicate x was not added*/
    vector_insert(S, vector_length(S), x); /*insert to end of vector*/
    return 1; /*true to indicate x was added*/
}

void set_remove_member(set S, T x) {/*Remove x from S.*/
    /*First find the index of x in S.*/
    int idx = vector_search(S, x, FIRST2LAST);
    if(idx < 0) return; /*Do nothing if not present*/
    vector_delete(S, idx); /*Remove from (underlying) vector*/
}

/*Traverse over elements of S. visit is called over each element of S passed as a parameter (there is no guarantee on order
of elements). visit may return a zero at any point to indicate stopping of traversal.
We could not use vector_traverse for this as the visit function signatures are required to be different.*/
void set_traverse(set S, int (*visit)(const T)) {
    int len = vector_length(S), i;
    for (i = 0; i < len; i++) 
        if(!visit(vector_get(S, i))) return; /*Visit each element, exit on signal*/
}

void set_union(set A, set B, set C) { /*Put union of sets A and B into a (null) set C.*/
    T x; int i, lA = vector_length(A), lB = vector_length(B);
    for (i = 0; i < lA; i++) {
        x = vector_get(A, i);
        set_add_member(C, x);
    }
    for (i = 0; i < lB; i++) {
        x = vector_get(B, i);
        set_add_member(C, x); /*set_add_member takes care of common elements*/
    }
}

void set_intersection(set A, set B, set C) {/*Put intesection of sets A and B into a (null) set C.*/
    T x; int i, lA = vector_length(A);
    for (i = 0; i < lA; i++) {
        x = vector_get(A, i);
        if (set_is_member(B, x)) set_add_member(C, x); /*Add iff present in both A and B*/
    }
}

void set_subtraction(set A, set B, set C) {/*Subtract B from A and put result into a (null) set C.*/
    T x; int i, lA = vector_length(A);
    for (i = 0; i < lA; i++) {
        x = vector_get(A, i);
        if (!set_is_member(B, x)) set_add_member(C, x); /*Add iff present in A but not in B*/
    }
}

int set_is_subset(set A, set B) {/*Check if A is a subset of B.*/
    T x; int i, lA = vector_length(A);
    for (i = 0; i < lA; i++) {
        x = vector_get(A, i);
        if (!set_is_member(B, x)) return 0; /*false; not a subset if at least one element of A is not present in B.*/
    }
    return 1; /*true; all elements of A are in B*/
}

/*A is a proper subset of B if A is a subset of B and there is at least one element of B not in A; or in case of finite
sets, cardinality of B is more than that of A.*/
#define set_is_proper_subset(A, B) ((set_is_subset((A), (B))) && ((set_cardinality((A))) < (set_cardinality((B)))))

int set_is_disjoint(set A, set B) {/*Check if A and B have no elements common*/
    T x; int i, lA = vector_length(A);
    for (i = 0; i < lA; i++) {
        x = vector_get(A, i);
        if (set_is_member(B, x)) return 0; /*false; Not disjoint if at least one element of A is common to B*/
    }
    return 1; /*true; all elements of A are in B*/
}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_P4_SET_*/
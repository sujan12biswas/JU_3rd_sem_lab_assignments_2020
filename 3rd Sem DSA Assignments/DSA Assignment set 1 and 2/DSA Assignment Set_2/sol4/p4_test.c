/*Define an ADT for Set.
Write C data representation and functions for the operations on the Set in a Header file, with
array as the base data structure.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file.

p4_test.c Testing program.*/

#include <stdio.h>
#include <ctype.h>
/*Use sets having integers*/
#define T int
#include "p4_set.h"

void set_print(set S) {
    int print_func(const T);
    if(set_is_null(S)) printf("Null set.");
    else {
        set_traverse(S, print_func);
        printf("\nCardinality: %d", set_cardinality(S));
    }
    printf("\n");
}
int print_func(const T elem) {
    printf("%d ", elem); /*Print element*/
    return 1; /*Print all that comes to print_func*/
}

void main(void) {
    set A, B, C;
    T elem;
    char choice[2], ch;
    set_construct(A); set_construct(B); set_construct(C);
    printf("A. Print set A\n");
    printf("B. Print set B\n");
    printf("C. Add element to set A\n");
    printf("D. Add element to set B\n");
    printf("E. Remove element from set A\n");
    printf("F. Remove element from set B\n");
    printf("G. Check for membership of element in set A\n");
    printf("H. Check for membership of element in set B\n");
    printf("I. Print union of A and B\n");
    printf("J. Print intersection of A and B\n");
    printf("K. Print A - B\n");
    printf("L. Is A a subset of B?\n");
    printf("M. Is A a proper subset of B?\n");
    printf("N. Are A and B disjoint?\n");
    printf("0 (zero) to exit\n");
    while (1) {
        printf("\nEnter your choice: "); scanf("%s", choice);
        switch(ch = toupper(choice[0])) {
        case 'A':
        case 'B': set_print((ch == 'A') ? A : B); break;
        case 'C':
        case 'D':
            printf("Enter an integer: "); scanf("%d", &elem);
            if(!set_add_member((ch == 'C') ? A : B, elem))
                printf("%d was already present in %c\n", elem, (ch == 'C') ? 'A' : 'B');
            break;
        case 'E':
        case 'F':
            printf("Enter an integer: "); scanf("%d", &elem);
            if(!set_is_member((ch == 'E') ? A : B, elem))
                printf("%d was not present in %c\n", elem, (ch == 'E') ? 'A' : 'B');
            else
                set_remove_member((ch == 'E') ? A : B, elem);
            break;
        case 'G':
        case 'H':
            printf("Enter an integer: "); scanf("%d", &elem);
            if(set_is_member((ch == 'G') ? A : B, elem))
                printf("%d belongs to %c\n", elem, (ch == 'G') ? 'A' : 'B');
            else
                printf("%d does not belong to %c\n", elem, (ch == 'G') ? 'A' : 'B');
            break;
        case 'I':
            if(!set_is_null(C)) {set_destroy(C); set_construct(C);}
            set_union(A, B, C); set_print(C); break;
        case 'J':
            if(!set_is_null(C)) {set_destroy(C); set_construct(C);}
            set_intersection(A, B, C); set_print(C); break;
        case 'K':    
            if(!set_is_null(C)) {set_destroy(C); set_construct(C);}
            set_subtraction(A, B, C); set_print(C); break;
        case 'L':
            if(set_is_subset(A, B)) printf("A is a subset of B.\n");
            else printf("A is not a subset of B.\n");
            break;
        case 'M':
            if(set_is_proper_subset(A, B)) printf("A is a proper subset of B.\n");
            else printf("A is not a proper subset of B.\n");
            break;
        case 'N':
            if(set_is_disjoint(A, B)) printf("A and B are disjoint.\n");
            else printf("A and B have at least one element common.\n");
            break;
        case '0': set_destroy(A); set_destroy(B); set_destroy(C); return;
        default: printf("Invalid Option!\n"); break;
        }
    }
}
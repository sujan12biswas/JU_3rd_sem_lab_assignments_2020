/*Find whether an array is sorted or not, and the sorting order.

p8_sortedness.h Algorithm implementations.*/
#ifndef _P8_SORTEDNESS_
#define _P8_SORTEDNESS_

#ifdef __cplusplus
extern "C" {
#endif

/*State type to indicate possible outputs*/
enum sortedness {ASCENDING, DESCENDING, EQUAL, UNSORTED};

enum sortedness check_2state(int a, int b) {/*Return sortedness value for {a, b}*/
    if (a < b) return ASCENDING;
    else if(a == b) return EQUAL;
    else return DESCENDING;
}

/*Returns state of type enum sortedness for an input A of length len.*/
enum sortedness check_sorted(int A[], int len) {
    int i; enum sortedness overall_state, current_state;
    if(len == 0 || len == 1) return EQUAL; /*Because we have nothing to compare to*/
    overall_state = EQUAL; /*Initially we assume all elements are equal*/
    for(i = 0; i < (len - 1); i++) { /*Because we have 0-based indexes*/
        current_state = check_2state(A[i], A[i+1]); /*State of current pair*/
        if (overall_state == EQUAL) overall_state = current_state;
        /*We can change from EQUAL to EQUAL, ASCENDING or DESCENGING*/
        else if(overall_state != current_state && current_state != EQUAL) return UNSORTED;
        /*If we change from DESCENDING to ASCENDING or vice versa, input is unsorted*/
    }
    return overall_state;
}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_P8_SORTEDNESS_*/
/*
Define an ADT for String.
Write C data representation and functions for the operations on the String in a Header file, with
array as the base data structure, without using any inbuilt function in C.
Write a menu-driven main program in a separate file for testing the different operations and
include the above header file.

p5_strings.h String implementation. This header implements a parallel of functions found in string.h with similar semantics. We 
even use '\0' as null character (terminating sentinel)*/

#ifndef _P5_STRINGS_
#define _P5_STRINGS_

#ifdef __cplusplus
extern "C" {
#endif

#define NIL ((char)'\0')

/*Remember that our indexes start from 0.*/

int string_length(const char A[]) { /*Returns the length of string, paralleling strlen*/
    int i = 0;
    while (A[i] != NIL) i++;
    return i; /*Last index holding NIL will also be the length of the string; as we have a zero-based index.*/
}

void string_copy(char D[], const char S[]) {/*Copy S to D, paralleling strcpy.*/
    int i = 0;
    while (S[i] != NIL) {
        D[i] = S[i]; /*Copy valid character*/
        i++;
    }
    D[i] = NIL; /*Indicate valid end of string in destination*/
}

void string_concatenation(char D[], const char S[]) {/*Copy S to the end of D, paralleling strcat.*/
    int i, j;
    i = 0;
    while(D[i] != NIL) i++; /*First go to the end of D*/
    j = 0;
    while(S[j] != NIL) {
        D[i] = S[j]; /*Copy S to D starting from the end of D*/
        i++; j++;
    }
    D[i] = NIL;
}

/*Return values for the string_compare function.*/
enum string_compare_return {LESSTHAN = -1, EQUAL = 0, GREATERTHAN = 1};
/*Check whether A comes before B, is equal to B, or after B*/
enum string_compare_return string_compare(const char A[], const char B[]) {
    int i = 0;
    while (A[i] != NIL && B[i] != NIL) {
        if(A[i] < B[i]) return LESSTHAN;
        else if(A[i] > B[i]) return GREATERTHAN;
        i++;
    } /*The above loop will not execute if one of the strings or both of them are empty.*/
    if(A[i] != B[i]) {/*One of the strings is smaller, they did not reach NIL at the same position*/
        if(A[i] == NIL) return LESSTHAN; /*Because A finished before B*/
        else return GREATERTHAN; /*Because B finished before A*/
        /*An empty string is less than any other non-empty string. In case both are empty, we return EQUAL in the next 
        statement.*/
    }
    else return EQUAL; /*Same characters at same positions and same length; this correctly takes care of 2 empty strings.*/
}

int string_char_search(const char A[], char ch) { /*Search for ch inside A and return index*/
    int i = 0;
    while (A[i] != NIL) {
        if(A[i] == ch) return i;
        i++;
    }
    return -1;/*We did not find the character*/ 
    /*We return an invalid index less than 0 instead of NIL as the integral value of NIL is a valid index.*/
}

/*Return substring. Substring is stored in B. Required length of A > endindex >= startindex and B has at least 
endindex - startindex + 2 space. endindex and startindex are inclusive.*/
void sub_string(const char A[], int startindex, int endindex, char B[]) {
    int i;
    /*Check for valid indexes.*/
    if(endindex < startindex || endindex >= string_length(A)) return; /*Do nothing.*/
    for (i = startindex; i <= endindex; i++) B[i - startindex] = A[i]; /*As we have 0 based indexes.*/
    B[endindex - startindex + 1] = NIL; /*Properly terminate the string*/
    /*return B*/
}

/*This searches for B within A and returns starting index where B begins within A.*/
int string_sub_search(const char A[], const char B[]) {
    int i = 0, len = string_length(B);
    int flag, j;
    if(len == 0) return -1; /*Cannot find empty substrings within any kind of other string.*/
    while (A[i] != NIL) {
        if (A[i] == B[0]) { /*We found a possible beginning of substring.*/
            /*We could call sub_string but that would require auxiliary space. Instead we check within the given parameter 
            memory space.*/
            flag = 0; /*false*/
            for (j = 1; j < len; j++) { /*Check if this is a valid substring, compare all len characters*/
                if(B[j] != A[i + j]) {
                    flag = 1; /*true*/
                    break; /*out of the immediate above for*/
                }
            }
            if(flag == 0 /*not flag*/) return i; /*We found a valid substring as we never broke out of the for*/
        }
        i++;
    }
    return -1; /*As we did not find the string. In case A is also empty, we reach this statement directly, i.e. we cannot 
    search for strings within empty strings irrespective of what the other string is.*/
}

/*Reverses string S in-place.*/
void string_reverse(char S[]) {
    int i, len = string_length(S);
    char t;
    for(i = 0; i < (len >> 1); i++) {t = S[i]; S[i] = S[len-i-1]; S[len-i-1] = t;} 
    /*Swap corresponding element with its corresponding character from the other end*/
}

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*_P%_STRINGS_*/
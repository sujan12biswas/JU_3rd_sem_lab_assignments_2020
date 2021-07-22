#define MAX_ORDER 835 /*This can be a problem. Reduce if necessary.*/
/*Value was found by trial and error on a sample system.*/

/*Take an arbitrary Matrix of positive integers, say, 128 X 128. Also take integer matrices of size 3 X 3 and 5 X 5. Find out an 
output matrix of size 128 X 128 by multiplying the small matrix with the corresponding submatrix of the large matrix with the centre 
of the small matrix placed at the individual positions within the large matrix. Explain how you will handle the boundary values.

p7_matrix.c Demonstration program with requisite algorithm implementations.*/

typedef struct { /*Matrix data type.*/
    unsigned val[MAX_ORDER][MAX_ORDER]; /*values*/
    int numRows; /*Number of rows*/
    int numCols; /*Number of columns*/
} matrix_t, *matrix;

#define TRUE 1
#define FALSE 0

/*Compute A and B and put result into C. Returns TRUE on success and FALSE on failure.*/
int matrix_multiply(const matrix A, const matrix B, matrix C) {
    int i, j, k;
    /*Check validity of input.*/
    if(A->numCols != B->numRows) return FALSE; /*Error, invalid input*/
    C->numRows = A->numRows; C->numCols = B->numCols; /*Put proper dimensions of C*/
    for(i = 0; i < A->numRows; i++) {
        for(j = 0; j < B->numCols; j++) {
            C->val[i][j] = 0; /*Initialize C to zero matrix as we go*/
            for(k = 0; k < A->numCols; k++) C->val[i][j] += (A->val[i][k] * B->val[k][j]);
                                            /*C[i,j] = C[i,j] + (A[i,k] * B[k,j])*/
        }
    }
    /*C was passed by reference*/    
}

/*Get square submatrix of order n (odd number), centred at M[p, q], assume p and q are valid. Put result into W.*/
void sub_matrix(const matrix M, int p, int q, int n, matrix W) {
    int i, j, a, b;
    int r = p - (n / 2), s = q - (n / 2); /*Starting positions of submatrix in M, integer division implies floor()*/
    W->numRows = W->numCols = n; /*Put proper dimensions of W.*/
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            a = r + i; b = s + j; 
            /*Calculate positions in M for submatrix; no need to subtract 1 since we use 0-based indexes in C*/
            /*Does M[a, b] exist?*/
            if(a < 0 || a >= M->numRows || b < 0 || b >= M->numCols) W->val[i][j] = 0;
            /*If M[i,j] does not exist then W[i,j] = 0*/
            else W->val[i][j] = M->val[a][b]; /*W[i,j] = M[a,b]*/
        }
    }
    /*W was passed by reference.*/
}

/*Main algorithm for the problem. A is the input matrix, X is the other input small square matrix of odd order, reduce is the 
operation reducing a input square matrix of odd order into a single value. The output is placed in B.*/
void process_matrix(const matrix A, const matrix X, unsigned (*reduce)(const matrix W), matrix B) {
   static matrix_t W, product; /*Avoid recreation on stack repeatedly*/
   int i, j;
   B->numRows = A->numRows; B->numCols = A->numCols; /*Put proper dimensions in B.*/
   for(i = 0; i < A->numRows; i++) {
       for(j = 0; j < A->numCols; j++) {
           sub_matrix(A, i, j, X->numRows, &W); /*Obtain submatrix*/
           matrix_multiply(X, &W, &product); /*Obtain product*/
           B->val[i][j] = reduce(&product); /*Reduce product to a single value*/
           /*B[i, j] = reduce(matrix_multiply(X, sub_matrix(A, i, j, number of rows in X)))*/
       }
   }
}

/*Assortment of reduction operations. All operations assume matrix has at least 1 element.*/

/*Find minimum of the elements of the matrix.*/
unsigned minimum(const matrix W) {
    unsigned min = W->val[0][0];
    int i, j;
    for(i = 0; i < W->numRows; i++)
        for(j = 0; j < W->numCols; j++) 
            if(min > W->val[i][j]) min = W->val[i][j];
    return min;
}
/*Find maximum of the elements of the matrix.*/
unsigned maximum(const matrix W) {
    unsigned max = W->val[0][0];
    int i, j;
    for(i = 0; i < W->numRows; i++)
        for(j = 0; j < W->numCols; j++) 
            if(max < W->val[i][j]) max = W->val[i][j];
    return max;
}

/*Compare two unsigned integers passed as void pointers. Required for the qsort function.*/
int comp_uints(const void *p1, const void *p2) {
    const unsigned *a = (const unsigned *)p1;
    const unsigned *b = (const unsigned *)p2;
    if(*a < *b) return -1;
    else if (*a == *b) return 0;
    else return 1;
}

#include <stdlib.h>

/*Find median of all elements of W. Assuming order of W is odd.*/
unsigned median(const matrix W) {
    static unsigned buffer[MAX_ORDER * MAX_ORDER]; /*Temporary buffer to hold elements of W.*/
    int i, j, k;
    /*Copy elements of W into buffer.*/
    k = 0;
    for(i = 0; i < W->numRows; i++)
        for(j = 0; j < W->numCols; j++) {buffer[k] = W->val[i][j]; k++;}
    qsort(buffer, W->numRows * W->numCols, sizeof(unsigned), comp_uints); /*Sort the elements of W*/
    return buffer[(W->numRows * W->numCols) / 2]; /*Middle element of sorted buffer is median*/
}

#include <stdio.h>

/*Input M in row wise order.*/
void input_matrix(matrix M) {
    int i, j;
    for(i = 0; i < M->numRows; i++)
        for(j = 0; j < M->numCols; j++) scanf("%u", &(M->val[i][j]));
}
/*Output M.*/
void output_matrix(const matrix M) {
    int i, j;
    for(i = 0; i < M->numRows; i++) {
        for(j = 0; j < M->numCols; j++) printf("%u ", M->val[i][j]);
        printf("\n");
    }
}

void main(void) {
    matrix_t A, B, X;
    int i, j, n;
    printf("Enter order (number of rows and number of columns) of input matrix: "); scanf("%d %d", &A.numRows, &A.numCols);
    printf("Enter elements of input matrix (row wise):\n"); input_matrix(&A);
    while(1) {
        printf("Enter odd numbered order (number of rows and columns) of small square matrix: "); scanf("%d", &n);
        if(n < 0 || (n%2)==0) printf("Invalid order. ");
        else break;
    }
    X.numRows = X.numCols = n;
    printf("Enter elements of small square matrix (row wise):\n"); input_matrix(&X);
    printf("\n\nGenerating output matrix using minimum...\n");
    process_matrix(&A, &X, minimum, &B);
    printf("Output Matrix:\n"); output_matrix(&B);
    printf("\n\nGenerating output matrix using maximum...\n");
    process_matrix(&A, &X, maximum, &B);
    printf("Output Matrix:\n"); output_matrix(&B);
    printf("\n\nGenerating output matrix using median...\n");
    process_matrix(&A, &X, median, &B);
    printf("Output Matrix:\n"); output_matrix(&B);
}
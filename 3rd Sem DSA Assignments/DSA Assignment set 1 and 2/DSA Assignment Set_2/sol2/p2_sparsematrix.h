#ifndef _P2_SPARSEMATRIX_
#define _P2_SPARSEMATRIX_

#ifdef __cplusplus
extern "C" {
#endif

/*You need to include a #define directive defining your element type before inclusion, like this:
#define T float _Complex (for complex sparse matrices)*/
#ifndef T
#warning T not specified. Defining T as double
#define T double
/*double (real) matrices by default*/
#endif

#include <stdlib.h>
/*Node definition*/
struct sparse_matrix_node_tag {
    unsigned row; 
    unsigned column; 
    /*Either number of rows/columns or element positions, row == 0 if column header and column == 0 if row header*/
    T info; /*placeholder for actual value*/
    struct sparse_matrix_node_tag *down; /*Linking in the same column*/
    struct sparse_matrix_node_tag *right; /*Linking in the same row*/
} const EMPTY_HEADER = {0u, 0u, 0, NULL, NULL}; /*Use EMPTY_HEADER for initialization before use*/
typedef struct sparse_matrix_node_tag spnode;

/*Row dimension (number of rows) of matrix specified in header.*/
#define row_dimension(header) ((header)->row)
/*Column dimension (number of columns) of matrix specified in header.*/
#define col_dimension(header) ((header)->column)

/*Retrieve an element from the matrix at position r,c specified in matrix_header.*/
T get_element(const spnode *matrix_header, unsigned r, unsigned c) {
    const spnode *row_p, *col_p;
    if (matrix_header == NULL || r == 0 || r > row_dimension(matrix_header) || c == 0 || c > col_dimension(matrix_header))
        return 0; /*0 on invalid parameters*/
    row_p = matrix_header->down;
    while (row_p != NULL && row_p->row < r) row_p = row_p->down; /*Search for the row moving down*/
    if (row_p == NULL || row_p->row > r) return 0; /*We overshot the row or reached the end hence entire row is zero*/
    col_p = row_p->right;
    while (col_p != NULL && col_p->column < c) col_p = col_p->right; /*Search for the column moving right*/
    if (col_p == NULL || col_p->column > c) return 0; /*We overshot the column or reached the end hence zero*/
    else return col_p->info;
}

/*Set/change element at position r, c to value. Matrix specified as matrix_header.*/
void set_element(spnode *matrix_header, unsigned r, unsigned c, T value) {
    spnode *target = NULL, /*To hold the target node*/
        *row_hdr, *prev_row_hdr, *col_hdr, *prev_col_hdr, *row_elem, *prev_row_elem, *col_elem, *prev_col_elem, *new_col, *new_row;
    if(matrix_header == NULL || r == 0 || r > row_dimension(matrix_header) || c == 0 || c > col_dimension(matrix_header))
        return; /*Nothing for invalid parameters*/
    /*Search for column header*/
    prev_col_hdr = matrix_header; col_hdr = matrix_header->right;
    while (col_hdr != NULL && col_hdr->column < c) {
        prev_col_hdr = col_hdr;
        col_hdr = col_hdr->right;
    }
    if (col_hdr == NULL || col_hdr->column > c) {/*Column dows not exist(entire column was zero)*/
        if (value == 0) return; /*We do not need to do anything*/
        new_col = (spnode *)malloc(sizeof(spnode)); /*Construct a new column header node*/
        new_col->row = 0u; new_col->column = c;
        /*Insert new_col into the list using prev_col_hdr and col_hdr*/
        new_col->right = col_hdr; prev_col_hdr->right = new_col;
        col_hdr = new_col;
        col_hdr->down = NULL; /*To indicate this is a new column*/
        /*Column header inserted*/
    }
    prev_row_hdr = matrix_header; row_hdr = matrix_header->down;
    /*Now searching for row header*/
    while (row_hdr != NULL && row_hdr->row < r) {
        prev_row_hdr = row_hdr;
        row_hdr = row_hdr->down;
    }
    if (row_hdr == NULL || row_hdr->row > r) { /*Row does not exist (entire row was zero)*/
        if (value == 0) return; /*We do not need to do anything*/
        /*Insert a new row header and make row_hdr refer to the correct header as was done for the column header*/
        new_row = (spnode *)malloc(sizeof(spnode));
        new_row->row = r; new_row->column = 0;
        /*Insert new_row into the list using prev_row_hdr and row_hdr*/
        new_row->down = row_hdr; prev_row_hdr->down = new_row;
        row_hdr = new_row;
        row_hdr->right = NULL; /*To indicate this is a new row*/
        /*Row header inserted*/
    }
    /*Now search within the row as we did for column headers*/
    prev_row_elem = row_hdr; row_elem = row_hdr->right;
    while (row_elem != NULL && row_elem->column < c) {
        prev_row_elem = row_elem;
        row_elem = row_elem->right;
    }
    /*Similarly search within the column moving down*/
    prev_col_elem = col_hdr; col_elem = col_hdr->down;
    while (col_elem != NULL && col_elem->row < r) {
        prev_col_elem = col_elem;
        col_elem = col_elem->down;
    }
    if (row_elem != NULL && col_elem != NULL && row_elem == col_elem) {
        /*Check if row_elem and col_elem refer to the correct node*/
        /*No need to compare r or c since we started from the correct row/column*/
        if (value == 0) {
            /*We need to remove the element from both the column list and row list*/
            prev_row_elem->right = row_elem->right;
            prev_col_elem->down = col_elem->down;
            free(row_elem);
        }
        else {
            target = row_elem;
            target->info = value; /*Place correct value as required*/
        }
    }
    else if (value != 0) {/*Insert only if value was not zero*/
        target = (spnode *)malloc(sizeof(spnode));
        target->row = r; target->column = c; target->info = value;
        /*Insert target into row and column lists*/
        prev_row_elem->right = target; target->right = row_elem;
        prev_col_elem->down = target; target->down = col_elem;
    }
    /*It is possible that row_hdr->right == NULL or col->hdr->down == NULL due to removal of a node. 
    Need to remove empty headers.*/
    if(row_hdr->right == NULL) {
        prev_row_hdr->down = row_hdr->down;
        free(row_hdr); /*Delete row header*/
    }
    if(col_hdr->down == NULL) {
        prev_col_hdr->right = col_hdr->right;
        free(col_hdr); /*Delete column header*/
    }
}

/*Helper function to clear (set 0 and release memory) of all positions in matrix passed in matrix_header.*/
void clear(spnode *matrix_header) {
    spnode *row_p, *col_p, *p1, *p2;
    for (row_p = matrix_header; row_p != NULL;) {/*Iterate over all row headers, including matrix header which acts as a 
    row header for the column headers*/
        p1 = row_p->down; /*Storing for advance later*/
        for (col_p = row_p->right; col_p != NULL; ) {/*Iterate over all contents in the row*/
            p2 = col_p->right; /*Storing for advance later*/
            free(col_p); col_p = p2; /*Delete and advance*/
        }
        if(row_p != matrix_header) free(row_p); /*Do not delete the matrix header*/
        row_p = p1; /*Advance to next row*/
    }
}

#undef T /*Not required anymore*/
#ifdef __cplusplus
}
#endif

#endif
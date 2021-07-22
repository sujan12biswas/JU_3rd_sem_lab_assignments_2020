#include <stdio.h>
/*We take integer matrices*/
#define T int 
#include "p2_sparsematrix.h"

void printmenu(void) {
    printf("1. Get a value at a position\n");
    printf("2. Set a value at a position\n");
    printf("3. Show entire matrix\n");
    printf("4. Reset dimensions (this clears the entire matrix to 0)\n");
    printf("5. Exit\n");
}

void main(void) {
    spnode matrix = EMPTY_HEADER; /*Matrix header can be allocated on the stack, no problem*/
    int choice, value;
    unsigned i, j;
    printf("Enter initial row and column dimensions of the matrix: ");
    scanf("%u %u", &row_dimension(&matrix), &col_dimension(&matrix));
    printf("\n"); printmenu();
    do {
        printf("Enter your choice: "); scanf("%d", &choice);
        switch(choice) {
        case 1:
            printf("Enter row value between 1 and %u and column value between 1 and %u: ",
             row_dimension(&matrix), col_dimension(&matrix));
            scanf("%u %u", &i, &j);
            if(i == 0 || i > row_dimension(&matrix) || j == 0 || j > col_dimension(&matrix))
                printf("Invalid coordinates. Choose option 1 and try again.\n");
            else
                printf("Value at position (%u, %u) is %d\n", i, j, get_element(&matrix, i, j));
            break;
        case 2:
            printf("Enter row value between 1 and %u and column value between 1 and %u: ",
             row_dimension(&matrix), col_dimension(&matrix));
            scanf("%u %u", &i, &j);
            if(i == 0 || i > row_dimension(&matrix) || j == 0 || j > col_dimension(&matrix))
                printf("Invalid coordinates. Choose option 1 and try again.\n");
            else {
                printf("Enter value to store: "); scanf("%d", &value);
                set_element(&matrix, i, j, value);
            }
            break;
        case 3:
            for (i = 1; i <= row_dimension(&matrix); i++) {
                for (j = 1; j <= col_dimension(&matrix); j++) printf("%2d ", get_element(&matrix, i, j));
                printf("\n");
            }
            break;
        case 4:
            clear(&matrix);
            printf("Enter new row and column dimensions of the matrix: ");
            scanf("%u %u", &row_dimension(&matrix), &col_dimension(&matrix));
            break;
        case 5: clear(&matrix); return;
        default: printf("Invalid Option!\n"); break;
        }
    } while (choice != 5);
    clear(&matrix);
}
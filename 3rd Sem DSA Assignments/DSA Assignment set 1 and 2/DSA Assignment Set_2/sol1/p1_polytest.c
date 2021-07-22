#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "p1_polynomial.h"

/*Take input*/
Polynomial create(int *N) {
    int i;
    printf("Enter max degree of polynomial: "); scanf("%d", N);
    Polynomial p = (Polynomial)malloc((*N + 1) * sizeof(PolynomialBaseType));
    printf("Enter coefficients of polynomial from constant to highest degree term, in sequence, separated by spaces:\n");
    for (i = 0; i <= *N; i++) scanf("%d", p + i);
    *N = degree(p, *N); /*Ensure correct degree*/
    p = (Polynomial)realloc(p, sizeof(PolynomialBaseType) * (*N + 1));
    printf("\n");
    return p;
}
/*Initialize empty polynomial*/
Polynomial create_empty(int N) {
    Polynomial p = (Polynomial)malloc((N + 1) * sizeof(PolynomialBaseType));
    memset(p, 0, (N + 1) * sizeof(PolynomialBaseType));
    return p;
}
/*Print polynomial*/
void printpoly(const Polynomial P, int N) {
    int i; 
    PolynomialBaseType cf; /*Coefficient*/
    N = degree(P, N); /* Get degree*/
    if(is_zero(P, N)) {
        printf("0"); /*Zero function*/
        return;
    }
    printf("%d", *P); /*Print constant/degree 0 term*/
    for (i = 1; i <= N; i++) {
        cf = coeff(P, N, i);
        if(cf == 0) continue;
        else if(cf > 0) printf(" + ");
        else {printf(" - "); cf = -cf;}
        if(i != 1) printf("%dx^%d", cf, i); /* Coefficient * variate ^ exponent */
        else printf("%dx", cf); /*No exponent mentioned if exponent = 1*/
    }
}
/*Print menu*/
void printmenu(void) {
    printf("1.  Set polynomial A(x)\n");
    printf("2.  Set polynomial B(x)\n");
    printf("3.  Print polynomial A(x)\n");
    printf("4.  Print polynomial B(x)\n");
    printf("5.  Calculate C(x) = A(x) + B(x)\n");
    printf("6.  Calculate C(x) = A(x) - B(x)\n");
    printf("7.  Calculate C(x) = A(x) * scalar\n");
    printf("8.  Calculate C(x) = B(x) * scalar\n");
    printf("9.  Calculate C(x) = A(x) * B(x)\n");
    printf("10. Print last C(x) / result\n");
    printf("11. Evaluate A(x) for given x\n");
    printf("12. Evaluate B(x) for given x\n");
    printf("13. Print this menu\n");
    printf("0.  Exit\n");
}

void main(void) {
    Polynomial A, B, C;
    int Ad = 0, Bd = 0, Cd = 0; /*Respective degrees*/
    int choice, x;
    PolynomialBaseType scalar;
    A = create_empty(0); /*Initialize to zero polynomials*/
    B = create_empty(0);
    C = create_empty(0);
    printf("(For the purposes of demonstration, all coefficents and variates are integers.)\n\n");
    printmenu();
    do {
        printf("\nEnter your choice: "); scanf("%d", &choice);
        switch(choice) {
        case 1:
            free(A);
            printf("For A(x):\n");
            A = create(&Ad);
            break;
        case 2:
            free(B);
            printf("For B(x):\n");
            B = create(&Bd);
            break;
        case 3:
            printf("A(x) = "); printpoly(A, Ad); printf("\n");
            break;
        case 4:
            printf("B(x) = "); printpoly(B, Bd); printf("\n");
            break;
        case 5:
            free(C);
            C = create_empty((Ad > Bd) ? Ad : Bd);
            Cd = add(A, Ad, B, Bd, C);
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 6:
            free(C);
            C = create_empty((Ad > Bd) ? Ad : Bd);
            Cd = sub(A, Ad, B, Bd, C);
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 7:
            printf("Enter scalar: "); scanf("%d", &scalar);
            free(C);
            C = create_empty(Ad);
            scalar_mul(A, Ad, scalar, C); Cd = degree(C, Cd);
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 8:
            printf("Enter scalar: "); scanf("%d", &scalar);
            free(C);
            C = create_empty(Bd);
            scalar_mul(B, Bd, scalar, C); Cd = degree(C, Cd);
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 9:
            free(C);
            C = create_empty(Ad + Bd);
            Cd = mul(A, Ad, B, Bd, C);
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 10:
            printf("C(x) = "); printpoly(C, Cd); printf("\n");
            break;
        case 11:
            printf("Enter x: "); scanf("%d", &x);
            printf("A(%d) = %ld\n", x, evaluate(A, Ad, x));
            break;
        case 12:
            printf("Enter x: "); scanf("%d", &x);
            printf("B(%d) = %ld\n", x, evaluate(B, Bd, x));
            break;
        case 13:
            printmenu(); break;
        case 0:
            free(A); free(B); free(C); return;
        default:
            fprintf(stderr, "Invalid Option!\n");
            break;
        }
    } while (choice != 0);
}

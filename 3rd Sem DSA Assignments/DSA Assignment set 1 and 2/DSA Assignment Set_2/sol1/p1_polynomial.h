#ifndef _P1_POLYNOMIAL_
#define _P1_POLYNOMIAL_

#ifdef __cplusplus
extern "C" {
#endif

/*Single-variate polynomials header. For the purposes of demonstration, we consider integral coefficients only.*/
typedef int PolynomialBaseType;
typedef PolynomialBaseType *Polynomial;

/*Return "corrected" degree of the polynomial. Several high order terms may have 0 coefficent-
this method aims to reduce and find the correct degree of the polynomial. Return correct degree of
the polynomial.*/
int degree(const Polynomial A, int n) {
    int i;
    for (i = n; i >= 1; i--) 
        if(*(A + i) != 0) return i; /*Return the degree of first nonzero term from the right*/
    return 0; /*In any case whether or not degree 0 term is 0, the degree of polynomial is 0 if we reach here.*/
}

/*Check if polynomial is zero. Polynomial is zero if all terms are 0 <=> degree is 0 and constant term is 0.*/
int is_zero(const Polynomial A, int n) { return degree(A, n) == 0 && *A == 0; }

/*Get coefficient of A(x) at term with degree = exponent.*/
PolynomialBaseType coeff(const Polynomial A, int n, int exponent) { return (exponent <= n) ? *(A + exponent) : 0; }

/*Get C(x) = A(x) + B(x). Return final degree of C(x). C must have at least max(m, n) space.*/
int add(const Polynomial A, int m, const Polynomial B, int n, Polynomial C) {
    int K, i;
    m = degree(A, m); n = degree(A, n); /*Correct m and n so A[m] and B[n] are nonzero.*/
    K = (m > n) ? m : n; /*K = max(m, n)*/
    for (i = 0; i <= K; i++)
        *(C + i) = coeff(A, m, i) + coeff(B, n, i); /*Add coefficients of corresponding terms.*/
    K = degree(C, K); /*Ensure correct K*/
    return K; /*C was passed by reference.*/
}

/*Get B(x) = c * A(x). B must have at least n space.*/
void scalar_mul(const Polynomial A, int n, PolynomialBaseType c, Polynomial B) {
    int i;
    n = degree(A, n); /*Obtain actual degree to make A[n] nonzero*/
    for (i = 0; i <= n; i++) *(B + i) = *(A + i) * c; /*Multiply each term by scalar*/
    /*B was passed by reference*/
}

/*Get C(x) = A(x) - B(x). Return final degree of C(x). C must have at least max(m, n) space.*/
int sub(const Polynomial A, int m, const Polynomial B, int n, Polynomial C) {
    int K, i;
    m = degree(A, m); n = degree(A, n); /*Correct m and n so A[m] and B[n] are nonzero.*/
    K = (m > n) ? m : n; /*K = max(m, n)*/
    for (i = 0; i <= K; i++)
        *(C + i) = coeff(A, m, i) - coeff(B, n, i); /*Subtract coefficients of corresponding terms.*/
    K = degree(C, K); /*Ensure correct K*/
    return K; /*C was passed by reference.*/
}

/*Get C(x) = A(x) * B(x). Return final degree of C(x). C must have at least m + n space.*/
int mul(const Polynomial A, int m, const Polynomial B, int n, Polynomial C) {
    int K, i, j;
    m = degree(A, m); n = degree(B, n); /*Correct m and n so A[m] and B[n] are nonzero*/
    K = m + n;
    for (i = 0; i <= K; i++) {
        *(C + i) = 0; /*Initialize to zero*/
        for (j = 0; j <= i; j++)
            *(C + i) += (coeff(A, m, j) * coeff(B, n, i - j)); 
            /*Definition of polynomial multiplication: each term with degree i will compose sum of products of terms
            in A and B that make up the exponent i when multiplied.*/
    }
    K = degree(C, K); /*Ensure correct K*/
    return K; /*C was passed by reference*/
}

/*Evaluate a polynomial y = A(x) using Horner's rule;
Example 1*x + 2*x^2 + 3*x^3 + 4*x^4 = x*(1 + x*(2 + x*(3 + x*4))).
Return evaluated value for x*/
long /*Because polynomials can grow pretty quickly.*/
evaluate(const Polynomial A, int n, int x) {
    long y = 0L;
    int i;
    n = degree(A, n); /*Ensure correct degree to prevent unnecessary iterations.*/
    for (i = n; i >= 0; i--) y = (long) *(A + i) + y * (long)x; /* y = A[i] + y*x */
    return y;
}

#ifdef __cplusplus
}
#endif

#endif
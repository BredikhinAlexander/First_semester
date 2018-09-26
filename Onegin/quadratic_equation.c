#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>


const int INFINIT = 3;
const int NO_ROOTS = 0;
const int TRUE = 1;
const int FALSE = 0;

const double PRECISION = 0.00001;


//! Solves a square equation

//! @param [in] a   a - cofficient
//! @param [in] b   b - cofficient
//! @param [in] c   c - cofficient
//! @param [out] x1 pointer to the first root
//! @param [out] x2 pointer to the second root

//! @return Number of roots


int solv_square_equation(double a, double b, double c, double *x1, double *x2);

//! Solves a linear equation

//! @param [in] b   b - cofficient
//! @param [in] c   c - cofficient
//! @param [out] x1 pointer to the root

//! @return Number of roots


int linear_solution (double b, double c, double *x);

//! compares two double numbers

//! @param [in] a  a - first number
//! @param [in] b  b - second number

//! @return true if a == b, false if a != b

int compare_with_zero(double a, double b);


int main()
{
    printf("program for solving square equations\n");
    printf("please enter the coefficients of the square equation\n");

    double a = 0, b = 0, c = 0;
    scanf("%lg%lg%lg", &a, &b, &c);

    assert(!(isnan(a)));
    assert(!(isnan(b)));
    assert(!(isnan(c)));

    double x1 = 0, x2 = 0;
    int result = solv_square_equation (a, b, c, &x1, &x2);

    assert(!(isnan(x1)));
    assert(!(isnan(x2)));


    switch (result)
    {
        case 0 :
            printf("no solution");
            break;

        case 1:
            printf("one solution\n");
            printf("x = ");
            printf("%lg", x1);
            break;

        case 2:
            printf("two solutions\n");
            printf("x1 = %lg\n", x1);
            printf("x2 = %lg", x2);
            break;

        case 3 :
            printf("infinity solutions");
            break;

        default:
            printf("function square_solution does not work correctly, %d", result);
            break;
    }

    return 0;
}


int solv_square_equation (double a, double b, double c, double *x1, double *x2)
{
    assert(!(isnan(a)));
    assert(!(isnan(b)));
    assert(!(isnan(c)));
    assert(x1 != x2);
    assert(x1 != NULL);
    assert(x2 != NULL);


    if (compare_with_zero (a, 0))
        return linear_solution(b, c, x1);
    else
        {
        if (compare_with_zero(c, 0))
        {
            x1 = 0;
            return linear_solution(a, b, x2) + 1;
        }
        else {
            double discrim = b*b - 4*a*c;
            if (discrim - 0 <= -PRECISION)
                return NO_ROOTS;
            else if (compare_with_zero(discrim, 0) == TRUE)
            {
                *x1 = -b/(2*a);
                return 1;
            }
            else {
                double sq_discrim = sqrt(discrim);

                *x1 = (-b + sq_discrim)/(2*a);
                *x2 = (-b - sq_discrim)/(2*a);
                return 2;
            }

        }
        }

}



int linear_solution (double b, double c, double *x)
{
    assert(!(isnan(b)));
    assert(!(isnan(c)));

    if (compare_with_zero(b,0) && compare_with_zero(c,0))
        return INFINIT

    if (compare_with_zero(b, 0) && compare_with_zero(c, 0) == FALSE)
        return NO_ROOTS;

    *x = -c/b;
    return 1;
}

int compare_with_zero(double a, double b)
{
    assert(!(isnan(a)));
    assert(!(isnan(b)));

    return (abs(a - b) <= PRECISION);
}


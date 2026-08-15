 #include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    char name[30];
    long double value;
} Function;

int compare(const void *a, const void *b)
{
    Function *f1 = (Function *)a;
    Function *f2 = (Function *)b;

    if (f1->value < f2->value)
        return -1;
    else if (f1->value > f2->value)
        return 1;
    else
        return 0;
}

int main()
{

    long double n = 1000000.0L;

    Function f[] =
    {
        {"1/n",              1.0L / n},
        {"log2(n)",          log2l(n)},
        {"12sqrt(n)",        12.0L * sqrtl(n)},
        {"50n^0.5",          50.0L * sqrtl(n)},
        {"n^0.51",           powl(n, 0.51L)},
        {"nlog2(n)",         n * log2l(n)},
        {"n^2 - 324",        n * n - 324},
        {"100n^2 + 6n",      100 * n * n + 6 * n},
        {"2n^3",             2 * n * n * n},
        {"n^(log2(n))",      powl(n, log2l(n))},
        {"3^n",              INFINITY},
        {"2^(32n)",          INFINITY}
    };

    int size = sizeof(f) / sizeof(f[0]);

    qsort(f, size, sizeof(Function), compare);

    printf("Value of n = %.0Lf\n\n", n);
    printf("Functions in Increasing Order of Growth:\n\n");

    for (int i = 0; i < size; i++)
    {
        if (isinf(f[i].value))
            printf("%2d. %-15s = Infinity\n", i + 1, f[i].name);
        else
            printf("%2d. %-15s = %.5Le\n", i + 1, f[i].name, f[i].value);
    }

    printf("Note:\n");
    printf("The functions are evaluated for a sufficiently large value of n.\n");
    printf("3^n and 2^(32n) are treated as Infinity because they exceed the range of long double.\n");

    return 0;
}
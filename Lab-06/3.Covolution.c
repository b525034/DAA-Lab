#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct
{
    double real;
    double imag;
} Complex;

Complex add(Complex a, Complex b)
{
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}

Complex sub(Complex a, Complex b)
{
    Complex c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;
    return c;
}

Complex mul(Complex a, Complex b)
{
    Complex c;

    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;

    return c;
}

void fft(Complex a[], int n, int invert)
{
    if (n == 1)
        return;

    Complex even[n / 2];
    Complex odd[n / 2];

    for (int i = 0; i < n / 2; i++)
    {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    fft(even, n / 2, invert);
    fft(odd, n / 2, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);

    Complex w;
    w.real = 1;
    w.imag = 0;

    Complex wn;
    wn.real = cos(angle);
    wn.imag = sin(angle);

    for (int i = 0; i < n / 2; i++)
    {
        Complex t = mul(w, odd[i]);

        a[i] = add(even[i], t);
        a[i + n / 2] = sub(even[i], t);

        w = mul(w, wn);
    }

    if (invert)
    {
        for (int i = 0; i < n; i++)
        {
            a[i].real /= 2;
            a[i].imag /= 2;
        }
    }
}

int main()
{
    int m, n;

    printf("Enter size of A: ");
    scanf("%d", &m);

    printf("Enter size of B: ");
    scanf("%d", &n);

    int size = m + n - 1;
    int N = 1;

    while (N < size)
        N *= 2;

    Complex A[N], B[N];

    for (int i = 0; i < N; i++)
    {
        A[i].real = 0;
        A[i].imag = 0;

        B[i].real = 0;
        B[i].imag = 0;
    }

    printf("Enter A:\n");

    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i].real);

    printf("Enter B:\n");

    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i].real);

    fft(A, N, 0);
    fft(B, N, 0);

    for (int i = 0; i < N; i++)
        A[i] = mul(A[i], B[i]);

    fft(A, N, 1);

    printf("Convolution:\n");

    for (int i = 0; i < size; i++)
        printf("%.2lf ", A[i].real);

    printf("\n");

    return 0;
}
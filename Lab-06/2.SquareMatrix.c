#include <stdio.h>
#include <math.h>

#define MAX 20
#define EPS 0.000001

// --------------------------------------------------
// Function to input a matrix
// --------------------------------------------------
void inputMatrix(double A[MAX][MAX], int n)
{
    printf("Enter the elements of the matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &A[i][j]);
        }
    }
}

// --------------------------------------------------
// Function to display a matrix
// --------------------------------------------------
void displayMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%8.2lf ", A[i][j]);
        }
        printf("\n");
    }
}

// --------------------------------------------------
// 1. Matrix Addition
// --------------------------------------------------
void addMatrix(double A[MAX][MAX], double B[MAX][MAX],
               double C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// --------------------------------------------------
// 2. Matrix Multiplication
// --------------------------------------------------
void multiplyMatrix(double A[MAX][MAX], double B[MAX][MAX],
                    double C[MAX][MAX], int n)
{
    // Initialize result matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;
        }
    }

    // Matrix multiplication
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// --------------------------------------------------
// 3. Check Zero Matrix
// --------------------------------------------------
int isZeroMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(A[i][j]) > EPS)
            {
                return 0;
            }
        }
    }

    return 1;
}

// --------------------------------------------------
// 4. Check Symmetric Matrix
// --------------------------------------------------
int isSymmetric(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > EPS)
            {
                return 0;
            }
        }
    }

    return 1;
}

// --------------------------------------------------
// 5. Find Determinant using Gaussian Elimination
// --------------------------------------------------
double determinant(double A[MAX][MAX], int n)
{
    double temp[MAX][MAX];
    double det = 1.0;

    // Copy original matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        // Find pivot
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(temp[j][i]) > fabs(temp[pivot][i]))
            {
                pivot = j;
            }
        }

        // If pivot is zero, determinant is zero
        if (fabs(temp[pivot][i]) < EPS)
        {
            return 0.0;
        }

        // Swap rows if necessary
        if (pivot != i)
        {
            for (int j = 0; j < n; j++)
            {
                double t = temp[i][j];
                temp[i][j] = temp[pivot][j];
                temp[pivot][j] = t;
            }

            det = -det;
        }

        det *= temp[i][i];

        // Eliminate elements below pivot
        for (int j = i + 1; j < n; j++)
        {
            double factor = temp[j][i] / temp[i][i];

            for (int k = i; k < n; k++)
            {
                temp[j][k] -= factor * temp[i][k];
            }
        }
    }

    return det;
}

// --------------------------------------------------
// 6. In-place Transpose
// --------------------------------------------------
void transposeInPlace(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

// --------------------------------------------------
// 7. Power Iteration
// Finds dominant eigenvalue and eigenvector
// --------------------------------------------------
void eigenValueVector(double A[MAX][MAX], int n)
{
    double x[MAX];
    double y[MAX];

    // Initial vector
    for (int i = 0; i < n; i++)
    {
        x[i] = 1.0;
    }

    double eigenvalue = 0.0;

    // Maximum iterations
    int iterations = 1000;

    for (int iter = 0; iter < iterations; iter++)
    {
        // y = A * x
        for (int i = 0; i < n; i++)
        {
            y[i] = 0;

            for (int j = 0; j < n; j++)
            {
                y[i] += A[i][j] * x[j];
            }
        }

        // Find maximum absolute value
        double maxValue = fabs(y[0]);

        for (int i = 1; i < n; i++)
        {
            if (fabs(y[i]) > maxValue)
            {
                maxValue = fabs(y[i]);
            }
        }

        // Avoid division by zero
        if (maxValue < EPS)
        {
            printf("Could not find eigenvalue.\n");
            return;
        }

        // Normalize vector
        for (int i = 0; i < n; i++)
        {
            x[i] = y[i] / maxValue;
        }

        eigenvalue = maxValue;
    }

    printf("Dominant Eigenvalue = %.6lf\n", eigenvalue);

    printf("Corresponding Eigenvector:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%.6lf\n", x[i]);
    }
}

// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main()
{
    int n;
    int choice;

    double A[MAX][MAX];
    double B[MAX][MAX];
    double C[MAX][MAX];

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid matrix size.\n");
        return 0;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, n);

    do
    {
        printf("\n====================================\n");
        printf("       MATRIX OPERATIONS\n");
        printf("====================================\n");

        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Check Zero Matrix\n");
        printf("4. Check Symmetric Matrix\n");
        printf("5. Find Determinant\n");
        printf("6. In-place Transpose\n");
        printf("7. Eigenvalue and Eigenvector\n");
        printf("0. Exit\n");

        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // ------------------------------------------
            // Matrix Addition
            // ------------------------------------------
            case 1:

                printf("\nEnter Matrix B:\n");
                inputMatrix(B, n);

                addMatrix(A, B, C, n);

                printf("\nA + B =\n");
                displayMatrix(C, n);

                break;

            // ------------------------------------------
            // Matrix Multiplication
            // ------------------------------------------
            case 2:

                printf("\nEnter Matrix B:\n");
                inputMatrix(B, n);

                multiplyMatrix(A, B, C, n);

                printf("\nA x B =\n");
                displayMatrix(C, n);

                break;

            // ------------------------------------------
            // Zero Matrix
            // ------------------------------------------
            case 3:

                if (isZeroMatrix(A, n))
                    printf("\nMatrix A is a Zero Matrix.\n");
                else
                    printf("\nMatrix A is NOT a Zero Matrix.\n");

                break;

            // ------------------------------------------
            // Symmetric Matrix
            // ------------------------------------------
            case 4:

                if (isSymmetric(A, n))
                    printf("\nMatrix A is Symmetric.\n");
                else
                    printf("\nMatrix A is NOT Symmetric.\n");

                break;

            // ------------------------------------------
            // Determinant
            // ------------------------------------------
            case 5:

                printf("\nDeterminant = %.2lf\n",
                       determinant(A, n));

                break;

            // ------------------------------------------
            // In-place Transpose
            // ------------------------------------------
            case 6:

                transposeInPlace(A, n);

                printf("\nMatrix after In-place Transpose:\n");
                displayMatrix(A, n);

                break;

            // ------------------------------------------
            // Eigenvalue and Eigenvector
            // ------------------------------------------
            case 7:

                eigenValueVector(A, n);

                break;

            // ------------------------------------------
            // Exit
            // ------------------------------------------
            case 0:

                printf("\nProgram terminated.\n");
                break;

            default:

                printf("\nInvalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

int **createMatrix(int n)
{
    int **matrix = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)calloc(n, sizeof(int));
    }

    return matrix;
}

void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

void strassen(int **A, int **B, int **C, int n)
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    // Create submatrices
    int **A11 = createMatrix(k);
    int **A12 = createMatrix(k);
    int **A21 = createMatrix(k);
    int **A22 = createMatrix(k);

    int **B11 = createMatrix(k);
    int **B12 = createMatrix(k);
    int **B21 = createMatrix(k);
    int **B22 = createMatrix(k);

    // Divide A and B into four parts
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Create matrices for M1 to M7
    int **M1 = createMatrix(k);
    int **M2 = createMatrix(k);
    int **M3 = createMatrix(k);
    int **M4 = createMatrix(k);
    int **M5 = createMatrix(k);
    int **M6 = createMatrix(k);
    int **M7 = createMatrix(k);

    int **temp1 = createMatrix(k);
    int **temp2 = createMatrix(k);

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(A11, A22, temp1, k);
    addMatrix(B11, B22, temp2, k);
    strassen(temp1, temp2, M1, k);

    // M2 = (A21 + A22)B11
    addMatrix(A21, A22, temp1, k);
    strassen(temp1, B11, M2, k);

    // M3 = A11(B12 - B22)
    subtractMatrix(B12, B22, temp2, k);
    strassen(A11, temp2, M3, k);

    // M4 = A22(B21 - B11)
    subtractMatrix(B21, B11, temp2, k);
    strassen(A22, temp2, M4, k);

    // M5 = (A11 + A12)B22
    addMatrix(A11, A12, temp1, k);
    strassen(temp1, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    subtractMatrix(A21, A11, temp1, k);
    addMatrix(B11, B12, temp2, k);
    strassen(temp1, temp2, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    subtractMatrix(A12, A22, temp1, k);
    addMatrix(B21, B22, temp2, k);
    strassen(temp1, temp2, M7, k);

    // Combine M1-M7 into C

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            // C11 = M1 + M4 - M5 + M7
            C[i][j] =
                M1[i][j] +
                M4[i][j] -
                M5[i][j] +
                M7[i][j];

            // C12 = M3 + M5
            C[i][j + k] =
                M3[i][j] +
                M5[i][j];

            // C21 = M2 + M4
            C[i + k][j] =
                M2[i][j] +
                M4[i][j];

            // C22 = M1 - M2 + M3 + M6
            C[i + k][j + k] =
                M1[i][j] -
                M2[i][j] +
                M3[i][j] +
                M6[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(M1, k);
    freeMatrix(M2, k);
    freeMatrix(M3, k);
    freeMatrix(M4, k);
    freeMatrix(M5, k);
    freeMatrix(M6, k);
    freeMatrix(M7, k);

    freeMatrix(temp1, k);
    freeMatrix(temp2, k);
}


int nextPowerOfTwo(int n)
{
    int power = 1;

    while (power < n)
    {
        power *= 2;
    }

    return power;
}


int main()
{
    int n;

    printf("Enter the size of the matrices: ");
    scanf("%d", &n);

    // Original matrices
    int **A = createMatrix(n);
    int **B = createMatrix(n);

    printf("\nEnter matrix A:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

    printf("\nEnter matrix B:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &B[i][j]);
        }
    }

    // Find next power of 2
    int size = nextPowerOfTwo(n);

    // Padded matrices
    int **Ap = createMatrix(size);
    int **Bp = createMatrix(size);
    int **Cp = createMatrix(size);

    // Copy original matrices into padded matrices
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Ap[i][j] = A[i][j];
            Bp[i][j] = B[i][j];
        }
    }

    // Apply Strassen
    strassen(Ap, Bp, Cp, size);

    // Display result
    printf("\nResultant Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", Cp[i][j]);
        }

        printf("\n");
    }

    // Free memory
    freeMatrix(A, n);
    freeMatrix(B, n);

    freeMatrix(Ap, size);
    freeMatrix(Bp, size);
    freeMatrix(Cp, size);

    return 0;
}
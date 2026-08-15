#include <stdio.h>
#include <stdlib.h>

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


/*
   Multiplies two special-pattern matrices:

             A1 A2
        A =  A2 A1

             B1 B2
        B =  B2 B1

   Result:

             C1 C2
        C =  C2 C1
*/
void specialMultiply(int **A, int **B, int **C, int n)
{
    // Base case
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    /*
       Create the four blocks of A
    */

    int **A1 = createMatrix(k);
    int **A2 = createMatrix(k);

    int **B1 = createMatrix(k);
    int **B2 = createMatrix(k);

    /*
       Extract A1, A2, B1, B2

              A1 A2
          A = A2 A1

              B1 B2
          B = B2 B1
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A1[i][j] = A[i][j];
            A2[i][j] = A[i][j + k];

            B1[i][j] = B[i][j];
            B2[i][j] = B[i][j + k];
        }
    }


    /*
       P = (A1 + A2)(B1 + B2)
    */

    int **Aplus = createMatrix(k);
    int **Bplus = createMatrix(k);
    int **P = createMatrix(k);

    addMatrix(A1, A2, Aplus, k);
    addMatrix(B1, B2, Bplus, k);

    specialMultiply(Aplus, Bplus, P, k);


    /*
       Q = (A1 - A2)(B1 - B2)
    */

    int **Aminus = createMatrix(k);
    int **Bminus = createMatrix(k);
    int **Q = createMatrix(k);

    subtractMatrix(A1, A2, Aminus, k);
    subtractMatrix(B1, B2, Bminus, k);

    specialMultiply(Aminus, Bminus, Q, k);


    /*
       C1 = (P + Q) / 2

       C2 = (P - Q) / 2
    */

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] =
                (P[i][j] + Q[i][j]) / 2;

            C[i][j + k] =
                (P[i][j] - Q[i][j]) / 2;

            C[i + k][j] =
                (P[i][j] - Q[i][j]) / 2;

            C[i + k][j + k] =
                (P[i][j] + Q[i][j]) / 2;
        }
    }


    /*
       Free memory
    */

    freeMatrix(A1, k);
    freeMatrix(A2, k);

    freeMatrix(B1, k);
    freeMatrix(B2, k);

    freeMatrix(Aplus, k);
    freeMatrix(Bplus, k);

    freeMatrix(Aminus, k);
    freeMatrix(Bminus, k);

    freeMatrix(P, k);
    freeMatrix(Q, k);
}


int main()
{
    int n;

    printf("Enter the size of the matrices: ");
    scanf("%d", &n);

    int **A = createMatrix(n);
    int **B = createMatrix(n);
    int **C = createMatrix(n);


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


    specialMultiply(A, B, C, n);


    printf("\nResultant Matrix:\n");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", C[i][j]);
        }

        printf("\n");
    }


    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}
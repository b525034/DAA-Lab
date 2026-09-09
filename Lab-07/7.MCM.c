#include <stdio.h>
#include <limits.h>

#define MAX 100

int m[MAX][MAX];
int s[MAX][MAX];

/* Print the optimal parenthesization */
void printOptimalOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalOrder(i, s[i][j]);
    printOptimalOrder(s[i][j] + 1, j);

    printf(")");
}

int main()
{
    int n;
    int p[MAX];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of matrices.\n");
        return 1;
    }

    /*
        If there are n matrices, there are n+1 dimensions.
    */
    printf("\nEnter the dimensions:\n");

    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    /*
        m[i][j] = minimum cost of multiplying
                  matrices Ai ... Aj
    */

    /* Cost of multiplying one matrix = 0 */
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    /*
        chainLength = number of matrices
        in the current chain
    */
    for (int chainLength = 2;
         chainLength <= n;
         chainLength++)
    {
        for (int i = 1;
             i <= n - chainLength + 1;
             i++)
        {
            int j = i + chainLength - 1;

            m[i][j] = INT_MAX;

            /*
                Try every possible split
            */
            for (int k = i; k < j; k++)
            {
                long long cost =
                    (long long)m[i][k]
                    + m[k + 1][j]
                    + (long long)p[i - 1]
                    * p[k]
                    * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = (int)cost;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nMinimum number of scalar multiplications = %d\n",
           m[1][n]);

    printf("Optimal parenthesization = ");

    printOptimalOrder(1, n);

    printf("\n");

    return 0;
}
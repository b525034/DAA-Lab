#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

int eggDrop(int E, int F)
{
    int dp[E + 1][F + 1];

    /* Base cases */
    for (int e = 1; e <= E; e++)
    {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }

    /* With one egg, test floors one by one */
    for (int f = 0; f <= F; f++)
    {
        dp[1][f] = f;
    }

    /* Fill DP table */
    for (int e = 2; e <= E; e++)
    {
        for (int f = 2; f <= F; f++)
        {
            dp[e][f] = INT_MAX;

            /* Try dropping from every floor k */
            for (int k = 1; k <= f; k++)
            {
                int broken = dp[e - 1][k - 1];
                int notBroken = dp[e][f - k];

                int worstCase = max(broken, notBroken);

                dp[e][f] = min(dp[e][f],
                               1 + worstCase);
            }
        }
    }

    return dp[E][F];
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E <= 0 || F < 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int result = eggDrop(E, F);

    printf("\nMinimum number of droppings required = %d\n",
           result);

    return 0;
}
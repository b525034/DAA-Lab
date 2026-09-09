#include <stdio.h>
#include <limits.h>

#define MAX 100

long long dp[MAX + 1];
int bestSplit[MAX + 1];

/* Calculate 2^n - 1 */
long long hanoi3(int n)
{
    return (1LL << n) - 1;
}

/* Dynamic programming solution for Reve's puzzle */
void solveReve(int n)
{
    dp[0] = 0;

    if (n >= 1)
        dp[1] = 1;

    for (int disks = 2; disks <= n; disks++)
    {
        dp[disks] = LLONG_MAX;

        /*
         * k = number of smaller disks
         * moved using four pegs.
         */
        for (int k = 1; k < disks; k++)
        {
            long long moves =
                2 * dp[k] +
                hanoi3(disks - k);

            if (moves < dp[disks])
            {
                dp[disks] = moves;
                bestSplit[disks] = k;
            }
        }
    }
}

/* Print the selected split for each n */
void printSplits(int n)
{
    printf("\nOptimal splits:\n");

    for (int i = 2; i <= n; i++)
    {
        printf("n = %d : k = %d, moves = %lld\n",
               i, bestSplit[i], dp[i]);
    }
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n < 0 || n > MAX)
    {
        printf("Invalid number of disks.\n");
        return 0;
    }

    solveReve(n);

    printf("\nMinimum number of moves = %lld\n", dp[n]);

    printSplits(n);

    if (n == 8 && dp[n] == 33)
        printf("\nResult validated: 8 disks require 33 moves.\n");

    return 0;
}
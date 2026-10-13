#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of weights: ");
    scanf("%d", &n);

    int weight[n];

    printf("Enter the weights in order:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &weight[i]);
    }

    int totalCost = 0;

    while (n > 1)
    {
        int minIndex = 0;
        int minCost = weight[0] + weight[1];

        // Find minimum-cost adjacent pair
        for (int i = 1; i < n - 1; i++)
        {
            int cost = weight[i] + weight[i + 1];

            if (cost < minCost)
            {
                minCost = cost;
                minIndex = i;
            }
        }

        printf("Merging %d and %d -> %d\n",
               weight[minIndex],
               weight[minIndex + 1],
               minCost);

        // Add merge cost
        totalCost += minCost;

        // Replace two adjacent blocks by their merged block
        weight[minIndex] = minCost;

        // Shift remaining elements
        for (int i = minIndex + 1; i < n - 1; i++)
        {
            weight[i] = weight[i + 1];
        }

        n--;
    }

    printf("\nMinimum total merge cost = %d\n", totalCost);

    return 0;
}
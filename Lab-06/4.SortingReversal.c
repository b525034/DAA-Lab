#include <stdio.h>

void reverse(int a[], int i, int j, long long *cost)
{
    int length = j - i + 1;

    *cost += length;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    int p[n];

    printf("Enter permutation:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &p[i]);

    long long totalCost = 0;
    int reversals = 0;

    for (int i = 0; i < n; i++)
    {
        if (p[i] == i + 1)
            continue;

        int pos = i;

        while (p[pos] != i + 1)
            pos++;

        reverse(p, i, pos, &totalCost);

        reversals++;
    }

    printf("\nSorted permutation:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");

    printf("Number of reversals = %d\n", reversals);
    printf("Total reversal cost = %lld\n", totalCost);

    return 0;
}
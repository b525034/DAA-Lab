#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
        {
            return 1;
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return 0;
}

int main()
{
    int n, x;

    printf("Enter size of both sets: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S1[i]);
    }

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S2[i]);
    }

    printf("Enter value of x: ");
    scanf("%d", &x);

    // Sort S2
    qsort(S2, n, sizeof(int), compare);

    // Search for required element
    for (int i = 0; i < n; i++)
    {
        int required = x - S1[i];

        if (binarySearch(S2, n, required))
        {
            printf("\nPair found: %d + %d = %d\n",
                   S1[i], required, x);

            return 0;
        }
    }

    printf("\nNo pair exists whose sum is %d\n", x);

    return 0;
}
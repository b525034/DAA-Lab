#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int binarySearch(int arr[], int low, int high, int key)
{
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int findKSum(int arr[], int n, int k, int target,
             int start, int depth, int sum, int chosen[])
{
    // We have selected k-1 elements
    if (depth == k - 1)
    {
        int required = target - sum;

        int pos = binarySearch(arr, start, n - 1, required);

        if (pos != -1)
        {
            chosen[depth] = arr[pos];

            printf("\nPair of %d elements found: ", k);

            for (int i = 0; i < k; i++)
            {
                printf("%d ", chosen[i]);
            }

            printf("\n");

            return 1;
        }

        return 0;
    }

    // Choose elements for the first k-1 positions
    for (int i = start; i < n; i++)
    {
        chosen[depth] = arr[i];

        if (findKSum(arr, n, k, target,
                     i + 1, depth + 1,
                     sum + arr[i], chosen))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int S[n];
    int chosen[k];

    printf("Enter elements of S:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S[i]);
    }

    printf("Enter value of k: ");
    scanf("%d", &k);

    printf("Enter target T: ");
    scanf("%d", &T);

    // Sort the set
    qsort(S, n, sizeof(int), compare);

    int found = findKSum(S, n, k, T,
                         0, 0, 0, chosen);

    if (!found)
    {
        printf("\nNo %d elements add up to %d\n", k, T);
    }

    return 0;
}
#include <stdio.h>

long long comparisons = 0;

struct Result
{
    int min;
    int max;
};


struct Result MaxMin(int arr[], int low, int high)
{
    struct Result result;
    struct Result leftResult;
    struct Result rightResult;

    // Only one element
    if (low == high)
    {
        result.min = arr[low];
        result.max = arr[low];

        return result;
    }

    // Two elements
    if (high == low + 1)
    {
        comparisons++;

        if (arr[low] < arr[high])
        {
            result.min = arr[low];
            result.max = arr[high];
        }
        else
        {
            result.min = arr[high];
            result.max = arr[low];
        }

        return result;
    }

    // Divide
    int mid = low + (high - low) / 2;

    // Conquer
    leftResult = MaxMin(arr, low, mid);
    rightResult = MaxMin(arr, mid + 1, high);

    // Combine - find minimum
    comparisons++;

    if (leftResult.min < rightResult.min)
    {
        result.min = leftResult.min;
    }
    else
    {
        result.min = rightResult.min;
    }

    // Combine - find maximum
    comparisons++;

    if (leftResult.max > rightResult.max)
    {
        result.max = leftResult.max;
    }
    else
    {
        result.max = rightResult.max;
    }

    return result;
}


int main()
{
    int n;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[1000];

    printf("Enter the elements:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    comparisons = 0;

    struct Result result = MaxMin(arr, 0, n - 1);

    printf("\nMinimum element = %d\n", result.min);
    printf("Maximum element = %d\n", result.max);

    printf("Number of comparisons = %lld\n", comparisons);

    printf("Maximum allowed comparisons (3n/2) = %.1f\n",
           1.5 * n);

    return 0;
}
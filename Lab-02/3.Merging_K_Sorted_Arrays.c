#include <stdio.h>

void merge(int a[], int sizeA, int b[], int sizeB, int result[])
{
    int i = 0, j = 0, k = 0;
    while (i < sizeA && j < sizeB)
    {
        if (a[i] <= b[j])
        {
            result[k] = a[i];
            i++;
        }
        else
        {
            result[k] = b[j];
            j++;
        }
        k++;
    }

    while (i < sizeA)
    {
        result[k] = a[i];
        i++;
        k++;
    }

    while (j < sizeB)
    {
        result[k] = b[j];
        j++;
        k++;
    }
}

/* METHOD 1 */
void method1(int arr[][100], int k, int n)
{
    int result[10000];
    int temp[10000];

    for (int i = 0; i < n; i++)
    {
        result[i] = arr[0][i];
    }

    int currentSize = n;

    for (int i = 1; i < k; i++)
    {
        merge(result, currentSize, arr[i], n, temp);
        currentSize = currentSize + n;
        for (int j = 0; j < currentSize; j++)
        {
            result[j] = temp[j];
        }
    }

    printf("\nMethod 1 result:\n");

    for (int i = 0; i < currentSize; i++)
    {
        printf("%d ", result[i]);
    }

    printf("\n");
}


/* METHOD 2 */
void method2(int arr[][100], int k, int n)
{
    int current[10000];
    int next[10000];

    int currentSize = n;
    int numArrays = k;

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            current[i * n + j] = arr[i][j];
        }
    }

    while (numArrays > 1)
    {
        int newNumArrays = 0;
        for (int i = 0; i < numArrays; i += 2)
        {
            if (i + 1 < numArrays)
            {
                merge(
                    &current[i * currentSize],
                    currentSize,
                    &current[(i + 1) * currentSize],
                    currentSize,
                    &next[newNumArrays * currentSize * 2]
                );

                newNumArrays++;
            }
            else
            {
                for (int j = 0; j < currentSize; j++)
                {
                    next[newNumArrays * currentSize * 2 + j]
                        = current[i * currentSize + j];
                }

                newNumArrays++;
            }
        }

        currentSize = currentSize * 2;
        numArrays = newNumArrays;

        for (int i = 0; i < numArrays * currentSize; i++)
        {
            current[i] = next[i];
        }
    }

    printf("\nMethod 2 result:\n");

    for (int i = 0; i < k * n; i++)
    {
        printf("%d ", current[i]);
    }

    printf("\n");
}


int main()
{
    int k, n;

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    int arr[100][100];

    for (int i = 0; i < k; i++)
    {
        printf("Enter elements of array %d: ", i + 1);

        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    printf("\nChoose method:\n");
    printf("1. Method 1");
    printf("2. Method 2\n");

    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        method1(arr, k, n);
    }
    else if (choice == 2)
    {
        method2(arr, k, n);
    }
    else
    {
        printf("Invalid choice2");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}

void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n;

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    int a[n];

    // Generate random elements
    srand(time(NULL));

    FILE *input = fopen("input.txt", "w");

    if (input == NULL)
    {
        printf("Unable to create input file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(input, "%d ", a[i]);
    }

    fclose(input);

    printf("\nRandom elements stored in input.txt\n");

    // Read elements from file
    input = fopen("input.txt", "r");

    if (input == NULL)
    {
        printf("Unable to open input file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(input, "%d", &a[i]);
    }

    fclose(input);

    // Quick Sort
    quickSort(a, 0, n - 1);

    // Store sorted elements
    FILE *output = fopen("quicksort_output.txt", "w");

    if (output == NULL)
    {
        printf("Unable to create output file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(output, "%d ", a[i]);
    }

    fclose(output);

    printf("Sorted elements stored in quicksort_output.txt\n");

    printf("\nSorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Check left child
    if (left < n && a[left] > a[largest])
        largest = left;

    // Check right child
    if (right < n && a[right] > a[largest])
        largest = right;

    // If largest is not the root
    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    // Build Max Heap
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(a, n, i);
    }

    // Extract elements one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(&a[0], &a[i]);

        heapify(a, i, 0);
    }
}

int main()
{
    int n;

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    int a[n];

    srand(time(NULL));

    // Create input file
    FILE *input = fopen("input.txt", "w");

    if (input == NULL)
    {
        printf("Unable to create input file.\n");
        return 1;
    }

    // Generate random elements
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
        fprintf(input, "%d ", a[i]);
    }

    fclose(input);

    printf("\nRandom elements stored in input.txt\n");

    // Read from file
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

    // Heap Sort
    heapSort(a, n);

    // Create output file
    FILE *output = fopen("heapsort_output.txt", "w");

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

    printf("Sorted elements stored in heapsort_output.txt\n");

    printf("\nSorted elements:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
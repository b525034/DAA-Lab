#include <stdio.h>
#include <stdlib.h>

int Binary_Search(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    int comparisons = 0;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        comparisons++;

        if (arr[mid] == key)
        {
            printf("Element found at index %d (Binary Search)\n", mid);
            return comparisons;
        }

        comparisons++;

        if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    printf("Element not found (Binary Search)\n");
    return comparisons;
}


int Ternary_Search(int arr[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    int comparisons = 0;

    while (low <= high)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        comparisons++;

        if (arr[mid1] == key)
        {
            printf("Element found at index %d (Ternary Search)\n", mid1);
            return comparisons;
        }

        comparisons++;

        if (arr[mid2] == key)
        {
            printf("Element found at index %d (Ternary Search)\n", mid2);
            return comparisons;
        }

        comparisons++;

        if (key < arr[mid1])
        {
            high = mid1 - 1;
        }
        else
        {
            comparisons++;

            if (key > arr[mid2])
            {
                low = mid2 + 1;
            }
            else
            {
                low = mid1 + 1;
                high = mid2 - 1;
            }
        }
    }

    printf("Element not found (Ternary Search)\n");
    return comparisons;
}


int main()
{
    int n;

    printf("No. of elements in the array: ");
    scanf("%d", &n);

    int arr[1000];

    printf("Enter elements in sorted order:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("\nYou entered the following array: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n\nEnter the element to search: ");

    int key;
    scanf("%d", &key);

    printf("\n");

    int binary_comparisons = Binary_Search(arr, n, key);
    int ternary_comparisons = Ternary_Search(arr, n, key);

    printf("\nCOMPARISON\n");

    printf("Number of comparisons in Binary Search: %d\n",
           binary_comparisons);

    printf("Number of comparisons in Ternary Search: %d\n",
           ternary_comparisons);

    // EXPERIMENTAL DATA FOR GRAPH


    FILE *fp = fopen("search_data.dat", "w");

    if (fp == NULL)
    {
        printf("Error creating data file.\n");
        return 1;
    }

    int sizes[] = {10, 20, 50, 100, 200, 500, 1000};
    int numberOfSizes = 7;

    printf("\n========== EXPERIMENTAL DATA ==========\n");
    printf("n\tBinary\tTernary\n");

    for (int i = 0; i < numberOfSizes; i++)
    {
        int size = sizes[i];

        int testArray[1000];

        // Create sorted array
        for (int j = 0; j < size; j++)
        {
            testArray[j] = j + 1;
        }

        // Search for the last element
        int testKey = size;

        int binaryCount =
            Binary_Search(testArray, size, testKey);

        int ternaryCount =
            Ternary_Search(testArray, size, testKey);

        printf("%d\t%d\t%d\n",
               size, binaryCount, ternaryCount);

        // Save data to file
        fprintf(fp, "%d %d %d\n",
                size, binaryCount, ternaryCount);
    }

    fclose(fp);

    printf("\nExperimental data saved to search_data.dat\n");

    // GENERATE GRAPH USING GNUPLOT


    FILE *gp = fopen("search_graph.gnuplot", "w");

    if (gp == NULL)
    {
        printf("Error creating gnuplot file.\n");
        return 1;
    }

    fprintf(gp, "set terminal pngcairo size 1000,700\n");

    fprintf(gp, "set output 'binary_vs_ternary.png'\n");

    fprintf(gp,
            "set title 'Binary Search vs Ternary Search'\n");

    fprintf(gp,
            "set xlabel 'Input Size (n)'\n");

    fprintf(gp,
            "set ylabel 'Number of Comparisons'\n");

    fprintf(gp, "set grid\n");

    fprintf(gp, "set key top left\n");

    fprintf(gp,
            "plot 'search_data.dat' using 1:2 "
            "with linespoints title 'Binary Search', "
            "'search_data.dat' using 1:3 "
            "with linespoints title 'Ternary Search'\n");

    fclose(gp);
    system("gnuplot search_graph.gnuplot");


    printf("\nGraph generated successfully!\n");
    printf("Graph saved as: binary_vs_ternary.png\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Normal Merge Sort
long long normalComparisons = 0;

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    int i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        normalComparisons++;

        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

//Three-Way Merge Sort

long long threeWayComparisons = 0;

void threeWayMerge(int arr[], int left, int mid1, int mid2, int right)
{
    int n = right - left + 1;

    int *temp = (int *)malloc(n * sizeof(int));

    int i = left;
    int j = mid1 + 1;
    int k = mid2 + 1;

    int t = 0;

    while (i <= mid1 || j <= mid2 || k <= right)
    {
        if (i <= mid1 &&
            (j > mid2 || arr[i] <= arr[j]) &&
            (k > right || arr[i] <= arr[k]))
        {
            temp[t++] = arr[i++];
        }
        else if (j <= mid2 &&
                 (k > right || arr[j] <= arr[k]))
        {
            threeWayComparisons++;
            temp[t++] = arr[j++];
        }
        else
        {
            threeWayComparisons++;
            temp[t++] = arr[k++];
        }

        if (i <= mid1 && j <= mid2 && k <= right)
        {
            threeWayComparisons++;
        }
    }

    for (int x = 0; x < n; x++)
    {
        arr[left + x] = temp[x];
    }

    free(temp);
}

void threeWayMergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int n = right - left + 1;

        int mid1 = left + n / 3 - 1;
        int mid2 = left + (2 * n) / 3 - 1;

        if (mid1 < left)
            mid1 = left;

        if (mid2 <= mid1)
            mid2 = mid1 + 1;

        if (mid2 >= right)
            mid2 = right - 1;

        threeWayMergeSort(arr, left, mid1);

        threeWayMergeSort(arr, mid1 + 1, mid2);

        threeWayMergeSort(arr, mid2 + 1, right);

        threeWayMerge(arr, left, mid1, mid2, right);
    }
}

int main()
{
    FILE *fp;

    srand((unsigned int)time(NULL));

    fp = fopen("merge_data.dat", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    printf("n\tMergeSort\t3-WayMergeSort\n");

    for (int n = 100; n <= 10000; n += 100)
    {
        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));

        for (int i = 0; i < n; i++)
        {
            int value = rand() % 100000;

            arr1[i] = value;
            arr2[i] = value;
        }

        normalComparisons = 0;
        threeWayComparisons = 0;

        mergeSort(arr1, 0, n - 1);

        threeWayMergeSort(arr2, 0, n - 1);

        fprintf(fp, "%d %lld %lld\n",
                n,
                normalComparisons,
                threeWayComparisons);

        printf("%d\t%lld\t\t%lld\n",
               n,
               normalComparisons,
               threeWayComparisons);

        free(arr1);
        free(arr2);
    }

    fclose(fp);

    FILE *gnuplot = _popen("gnuplot", "w");

if (gnuplot == NULL)
{
    printf("\nGnuplot could not be opened.\n");
    printf("Make sure Gnuplot is installed and added to PATH.\n");
    return 1;
}

fprintf(gnuplot, "set terminal pngcairo size 1000,700\n");
fprintf(gnuplot, "set output 'merge_sort_comparison.png'\n");

fprintf(gnuplot, "set title 'Merge Sort vs 3-Way Merge Sort'\n");
fprintf(gnuplot, "set xlabel 'Input Size (n)'\n");
fprintf(gnuplot, "set ylabel 'Number of Comparisons'\n");
fprintf(gnuplot, "set grid\n");

fprintf(gnuplot,
        "plot 'merge_data.dat' using 1:2 "
        "with linespoints title 'Normal Merge Sort', "
        "'merge_data.dat' using 1:3 "
        "with linespoints title '3-Way Merge Sort'\n");

fflush(gnuplot);
_pclose(gnuplot);

printf("\nGraph saved as merge_sort_comparison.png\n");
}
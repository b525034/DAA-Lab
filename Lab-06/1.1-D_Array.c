#include <stdio.h>
#include <math.h>
#include <limits.h>

/* ---------- Utility Functions ---------- */

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* ---------- (i) Maximum ---------- */

void findMaximum(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > max)
            max = a[i];
    }

    printf("Maximum = %d\n", max);
}

/* ---------- (ii) First and Second Largest ---------- */

void findLargestTwo(int a[], int n)
{
    int largest = INT_MIN;
    int secondLargest = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > largest)
        {
            secondLargest = largest;
            largest = a[i];
        }
        else if (a[i] > secondLargest && a[i] != largest)
        {
            secondLargest = a[i];
        }
    }

    if (secondLargest == INT_MIN)
    {
        printf("Second largest distinct element does not exist.\n");
    }
    else
    {
        printf("Largest = %d\n", largest);
        printf("Second Largest = %d\n", secondLargest);
    }
}

/* ---------- (iii) Mean ---------- */

void findMean(int a[], int n)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }

    printf("Mean = %.2lf\n", sum / n);
}

/* ---------- Quickselect Partition ---------- */

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

/* ---------- Quickselect ---------- */

int quickSelect(int a[], int low, int high, int k)
{
    if (low == high)
        return a[low];

    int p = partition(a, low, high);

    if (p == k)
        return a[p];

    if (k < p)
        return quickSelect(a, low, p - 1, k);

    return quickSelect(a, p + 1, high, k);
}

/* ---------- (iv) Median ---------- */

void findMedian(int a[], int n)
{
    if (n % 2 == 1)
    {
        int median = quickSelect(a, 0, n - 1, n / 2);

        printf("Median = %.2lf\n", (double)median);
    }
    else
    {
        int x = quickSelect(a, 0, n - 1, n / 2 - 1);
        int y = quickSelect(a, 0, n - 1, n / 2);

        double median = (x + y) / 2.0;

        printf("Median = %.2lf\n", median);
    }
}

/* ---------- (v) Standard Deviation ---------- */

void findStandardDeviation(int a[], int n)
{
    double sum = 0;
    double mean;
    double variance = 0;

    /* Find mean */
    for (int i = 0; i < n; i++)
    {
        sum += a[i];
    }

    mean = sum / n;

    /* Find variance */
    for (int i = 0; i < n; i++)
    {
        variance += (a[i] - mean) * (a[i] - mean);
    }

    variance = variance / n;

    double sd = sqrt(variance);

    printf("Mean = %.2lf\n", mean);
    printf("Standard Deviation = %.2lf\n", sd);
}

/* ---------- (vi) Mode ---------- */

void findMode(int a[], int n)
{
    int mode = a[0];
    int maxCount = 0;

    for (int i = 0; i < n; i++)
    {
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[i] == a[j])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    printf("Mode = %d\n", mode);
    printf("Frequency = %d\n", maxCount);
}

/* ---------- (vii) Remove Duplicates ---------- */

void removeDuplicates(int a[], int n)
{
    int unique[n];
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        for (int j = 0; j < count; j++)
        {
            if (a[i] == unique[j])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            unique[count] = a[i];
            count++;
        }
    }

    printf("Array after removing duplicates:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d ", unique[i]);
    }

    printf("\n");
}

/* ---------- (viii) Reverse Array ---------- */

void reverseArray(int a[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        swap(&a[left], &a[right]);

        left++;
        right--;
    }

    printf("Reversed array:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");
}

/* ---------- (ix) Partition with Pivot ---------- */
/*
   Required arrangement:

   Elements >= pivot | Elements < pivot
*/

void partitionArray(int a[], int n, int pivot)
{
    int i = 0;

    for (int j = 0; j < n; j++)
    {
        if (a[j] >= pivot)
        {
            swap(&a[i], &a[j]);
            i++;
        }
    }

    printf("Array after partitioning:\n");

    for (int j = 0; j < n; j++)
    {
        printf("%d ", a[j]);
    }

    printf("\n");
}

/* ---------- MAIN ---------- */

int main()
{
    int n, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d unsorted integer elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    do
    {
        printf("\n========== ARRAY OPERATIONS ==========\n");
        printf("1. Find Maximum\n");
        printf("2. Find First and Second Largest\n");
        printf("3. Find Mean\n");
        printf("4. Find Median\n");
        printf("5. Find Standard Deviation\n");
        printf("6. Find Mode\n");
        printf("7. Remove Duplicates\n");
        printf("8. Reverse Array\n");
        printf("9. Partition with respect to Pivot\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                findMaximum(a, n);
                break;

            case 2:
                findLargestTwo(a, n);
                break;

            case 3:
                findMean(a, n);
                break;

            case 4:
                findMedian(a, n);
                break;

            case 5:
                findStandardDeviation(a, n);
                break;

            case 6:
                findMode(a, n);
                break;

            case 7:
                removeDuplicates(a, n);
                break;

            case 8:
                reverseArray(a, n);
                break;

            case 9:
            {
                int pivot;

                printf("Enter pivot: ");
                scanf("%d", &pivot);

                partitionArray(a, n, pivot);
                break;
            }

            case 0:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 0);

    return 0;
}
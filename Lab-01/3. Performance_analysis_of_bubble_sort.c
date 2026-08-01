#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int optimizedBubbleSort(int arr[], int n)
{
    int comparisons = 0;
    for(int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if(swapped == 0)
        {
            break;
        }
    }
    return comparisons;
}

int normalBubbleSort(int arr[], int n)
{
    int comparisons = 0;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            comparisons++;
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

int main()
{
    srand(time(NULL));
    FILE *fp = fopen("bubble.dat", "w");

    if(fp == NULL)
    {
        printf("Error creating file!\n");
        return 1;
    }

    for(int n = 10; n <= 100; n += 10)
    {
        int arr[n], arr1[n], arr2[n];

        for(int i = 0; i < n; i++)
        {
            arr[i] = rand() % 1000;
            arr1[i] = arr[i];
            arr2[i] = arr[i];
        }

        int opt = optimizedBubbleSort(arr1, n);
        int normal = normalBubbleSort(arr2, n);

        fprintf(fp, "%d %d %d\n", n, opt, normal);
    }

    fclose(fp);

    FILE *gp = _popen("gnuplot -persistent", "w");

    if(gp == NULL)
    {
        printf("GNUplot not found!\n");
        return 1;
    }

    fprintf(gp, "set title 'Bubble Sort Performance Analysis'\n");
    fprintf(gp, "set xlabel 'Number of Elements (n)'\n");
    fprintf(gp, "set ylabel 'Number of Comparisons'\n");
    fprintf(gp, "set grid\n");

    fprintf(gp,
        "plot 'bubble.dat' using 1:2 with linespoints lw 2 title 'Optimized Bubble Sort',"
        "'bubble.dat' using 1:3 with linespoints lw 2 title 'Normal Bubble Sort'\n");

    fflush(gp);

    printf("Graph displayed successfully!\n");

    getchar();
    getchar();

    _pclose(gp);

    return 0;
}
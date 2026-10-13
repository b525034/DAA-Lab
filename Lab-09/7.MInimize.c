#include <stdio.h>

#define MAX 1000

int heap[MAX];
int heapSize = 0;

/* Swap two elements */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert into max heap */
void insertMaxHeap(int value)
{
    int i = heapSize;

    heap[heapSize] = value;
    heapSize++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        swap(&heap[parent], &heap[i]);

        i = parent;
    }
}

/* Extract maximum */
int extractMax()
{
    int maximum = heap[0];

    heap[0] = heap[heapSize - 1];
    heapSize--;

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int largest = i;

        if (left < heapSize &&
            heap[left] > heap[largest])
        {
            largest = left;
        }

        if (right < heapSize &&
            heap[right] > heap[largest])
        {
            largest = right;
        }

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return maximum;
}

/* Get current minimum */
int getMin()
{
    int minimum = heap[0];

    for (int i = 1; i < heapSize; i++)
    {
        if (heap[i] < minimum)
            minimum = heap[i];
    }

    return minimum;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);

        /*
         * Convert odd number to even.
         */
        if (x % 2 != 0)
        {
            x = x * 2;
        }

        insertMaxHeap(x);
    }

    int minimum = getMin();
    int answer = 2147483647;

    while (heapSize > 0)
    {
        int maximum = extractMax();

        int deviation = maximum - minimum;

        if (deviation < answer)
            answer = deviation;

        /*
         * If maximum is odd, it cannot
         * be reduced any further.
         */
        if (maximum % 2 != 0)
            break;

        maximum = maximum / 2;

        /*
         * Update minimum if necessary.
         */
        if (maximum < minimum)
            minimum = maximum;

        insertMaxHeap(maximum);
    }

    printf("\nMinimum deviation = %d\n", answer);

    return 0;
}
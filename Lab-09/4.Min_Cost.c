#include <stdio.h>

#define MAX 1000

int heap[MAX];
int heapSize = 0;

/* Insert element into min-heap */
void insertMinHeap(int value)
{
    int i = heapSize;

    heap[heapSize] = value;
    heapSize++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent] <= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

/* Remove and return minimum element */
int extractMin()
{
    int minValue = heap[0];

    heap[0] = heap[heapSize - 1];
    heapSize--;

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int smallest = i;

        if (left < heapSize &&
            heap[left] < heap[smallest])
        {
            smallest = left;
        }

        if (right < heapSize &&
            heap[right] < heap[smallest])
        {
            smallest = right;
        }

        if (smallest == i)
            break;

        int temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;

        i = smallest;
    }

    return minValue;
}

int main()
{
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++)
    {
        int length;
        scanf("%d", &length);

        insertMinHeap(length);
    }

    int totalCost = 0;

    while (heapSize > 1)
    {
        /* Get two shortest sticks */
        int x = extractMin();
        int y = extractMin();

        /* Connect them */
        int newStick = x + y;

        /* Add connection cost */
        totalCost += newStick;

        printf("Connect %d and %d -> %d\n",
               x, y, newStick);

        /* Insert new stick back */
        insertMinHeap(newStick);
    }

    printf("\nMinimum total cost = %d\n",
           totalCost);

    return 0;
}
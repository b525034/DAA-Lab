#include <stdio.h>

#define MAX 1000

struct Station
{
    int distance;
    int fuel;
};

int heap[MAX];
int heapSize = 0;

/* Insert fuel into max heap */
void insertMaxHeap(int fuel)
{
    int i = heapSize;

    heap[heapSize] = fuel;
    heapSize++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent] >= heap[i])
            break;

        int temp = heap[parent];
        heap[parent] = heap[i];
        heap[i] = temp;

        i = parent;
    }
}

/* Remove and return maximum fuel */
int extractMax()
{
    int maxFuel = heap[0];

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

        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        i = largest;
    }

    return maxFuel;
}

int main()
{
    int D, F, n;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    struct Station stations[MAX];

    printf("\nEnter station distance and fuel:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d",
              &stations[i].distance,
              &stations[i].fuel);
    }

    int currentPosition = 0;
    int fuel = F;
    int stops = 0;

    for (int i = 0; i <= n; i++)
    {
        int nextPosition;

        if (i == n)
            nextPosition = D;
        else
            nextPosition = stations[i].distance;

        int distance =
            nextPosition - currentPosition;

        /*
         * If we don't have enough fuel,
         * use the largest fuel from a
         * previously passed station.
         */
        while (fuel < distance)
        {
            if (heapSize == 0)
            {
                printf("\nIt is impossible to reach the target.\n");
                return 0;
            }

            int addedFuel = extractMax();

            fuel += addedFuel;
            stops++;

            printf("Refuel with %d units of fuel.\n",
                   addedFuel);
        }

        /* Travel to next position */
        fuel -= distance;
        currentPosition = nextPosition;

        /*
         * Store this station's fuel
         * for possible future use.
         */
        if (i < n)
        {
            insertMaxHeap(stations[i].fuel);
        }
    }

    printf("\nMinimum number of refuelling stops = %d\n",
           stops);

    return 0;
}
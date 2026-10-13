#include <stdio.h>
#include <string.h>

#define MAX 1000
#define ASCII 256

struct Node
{
    char ch;
    int frequency;
};

struct WaitNode
{
    char ch;
    int frequency;
    int availableAt;
};

struct Node heap[MAX];
int heapSize = 0;

/* ---------------- MAX HEAP ---------------- */

void swap(struct Node *a, struct Node *b)
{
    struct Node temp = *a;
    *a = *b;
    *b = temp;
}

/* Insert into max heap */
void insertHeap(char ch, int frequency)
{
    int i = heapSize;

    heap[i].ch = ch;
    heap[i].frequency = frequency;

    heapSize++;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent].frequency >=
            heap[i].frequency)
        {
            break;
        }

        swap(&heap[parent], &heap[i]);

        i = parent;
    }
}

/* Extract maximum frequency character */
struct Node extractMax()
{
    struct Node maxNode = heap[0];

    heap[0] = heap[heapSize - 1];

    heapSize--;

    int i = 0;

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int largest = i;

        if (left < heapSize &&
            heap[left].frequency >
            heap[largest].frequency)
        {
            largest = left;
        }

        if (right < heapSize &&
            heap[right].frequency >
            heap[largest].frequency)
        {
            largest = right;
        }

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);

        i = largest;
    }

    return maxNode;
}

/* ---------------- MAIN ---------------- */

int main()
{
    char str[MAX];
    int K;

    printf("Enter string: ");
    scanf("%s", str);

    printf("Enter K: ");
    scanf("%d", &K);

    if (K <= 1)
    {
        printf("Rearranged string: %s\n", str);
        return 0;
    }

    int frequency[ASCII] = {0};

    int length = strlen(str);

    /* Count frequencies */
    for (int i = 0; i < length; i++)
    {
        frequency[(unsigned char)str[i]]++;
    }

    /* Insert all characters into max heap */
    for (int i = 0; i < ASCII; i++)
    {
        if (frequency[i] > 0)
        {
            insertHeap((char)i, frequency[i]);
        }
    }

    struct WaitNode waiting[MAX];

    int front = 0;
    int rear = 0;

    char result[MAX];

    int resultLength = 0;

    int position = 0;

    while (position < length)
    {
        /*
         * Release characters whose waiting
         * period is over.
         */
        while (front < rear &&
               waiting[front].availableAt <= position)
        {
            insertHeap(
                waiting[front].ch,
                waiting[front].frequency
            );

            front++;
        }

        /*
         * If no character is available,
         * rearrangement is impossible.
         */
        if (heapSize == 0)
        {
            printf("\nRearrangement is impossible.\n");
            return 0;
        }

        /* Choose most frequent character */
        struct Node current = extractMax();

        result[resultLength++] = current.ch;

        current.frequency--;

        /*
         * If more copies remain,
         * put character into waiting queue.
         */
        if (current.frequency > 0)
        {
            waiting[rear].ch = current.ch;

            waiting[rear].frequency =
                current.frequency;

            waiting[rear].availableAt =
                position + K;

            rear++;
        }

        position++;
    }

    result[resultLength] = '\0';

    printf("\nRearranged string: %s\n",
           result);

    return 0;
}
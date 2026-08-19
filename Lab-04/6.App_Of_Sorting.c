#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int point;
    int type;
};

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    // Sort according to point
    if (e1->point != e2->point)
    {
        return e1->point - e2->point;
    }

    // If points are same, start (+1) comes before end (-1)
    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    int k = 0;

    // Input intervals
    for (int i = 0; i < n; i++)
    {
        int l, r;

        printf("Enter left and right endpoint of interval %d: ",
               i + 1);

        scanf("%d %d", &l, &r);

        // Starting point
        events[k].point = l;
        events[k].type = 1;
        k++;

        // Ending point
        events[k].point = r;
        events[k].type = -1;
        k++;
    }

    // Sort events
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int maxPoint = 0;

    // Scan events
    for (int i = 0; i < 2 * n; i++)
    {
        current = current + events[i].type;

        if (current > maximum)
        {
            maximum = current;
            maxPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlap: %d", maxPoint);
    printf("\nMaximum number of intervals: %d\n", maximum);

    return 0;
}
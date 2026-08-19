#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int time;
    int type;
};

int compare(const void *a, const void *b)
{
    struct Event *e1 = (struct Event *)a;
    struct Event *e2 = (struct Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n;

    printf("Enter number of people: ");
    scanf("%d", &n);

    struct Event events[2 * n];

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Enter entry and exit time for person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        events[k].time = entry;
        events[k].type = 1;
        k++;

        events[k].time = exit;
        events[k].type = -1;
        k++;
    }

    // Sort all events by time
    qsort(events, 2 * n, sizeof(struct Event), compare);

    int current = 0;
    int maximum = 0;
    int maxTime = 0;

    // Process events
    for (int i = 0; i < 2 * n; i++)
    {
        current = current + events[i].type;

        if (current > maximum)
        {
            maximum = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum number of people present: %d", maximum);
    printf("\nTime when maximum people were present: %d\n", maxTime);

    return 0;
}
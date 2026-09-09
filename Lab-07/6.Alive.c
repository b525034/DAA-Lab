#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;   // -1 = death, +1 = birth
} Event;

/* Comparison function for qsort */
int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    /* Sort by year */
    if (e1->year != e2->year)
        return e1->year - e2->year;

    /*
       If years are equal:
       death (-1) comes before birth (+1)
    */
    return e1->type - e2->type;
}

int main()
{
    int n;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    Event *events =
        (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter birth and death years:\n");

    for (int i = 0; i < n; i++)
    {
        int birth, death;

        printf("Scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;       // Birth

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;  // Death
    }

    /* Sort all events */
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int alive = 0;
    int maxAlive = 0;
    int bestYear = 0;

    /*
       Process events in chronological order.
       Deaths at the same year are processed
       before births.
    */
    for (int i = 0; i < 2 * n; i++)
    {
        if (events[i].type == -1)
        {
            alive--;
        }
        else
        {
            alive++;

            if (alive > maxAlive)
            {
                maxAlive = alive;
                bestYear = events[i].year;
            }
        }
    }

    printf("\nMaximum number of scientists alive = %d\n",
           maxAlive);

    printf("Best time begins at year = %d\n",
           bestYear);

    free(events);

    return 0;
}
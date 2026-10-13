#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

int main()
{
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    int start[n], end[n];

    printf("Enter start and end time of each meeting:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Meeting %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);
    }

    // Sort start times
    qsort(start, n, sizeof(int), compare);

    // Sort end times
    qsort(end, n, sizeof(int), compare);

    int i = 0;
    int j = 0;
    int rooms = 0;
    int maxRooms = 0;

    while (i < n)
    {
        if (start[i] < end[j])
        {
            // New meeting starts before the earliest meeting ends
            rooms++;
            i++;

            if (rooms > maxRooms)
                maxRooms = rooms;
        }
        else
        {
            // A meeting has ended, so its room can be reused
            rooms--;
            j++;
        }
    }

    printf("\nMinimum number of meeting rooms required = %d\n", maxRooms);

    return 0;
}
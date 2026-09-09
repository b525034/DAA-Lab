#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

/*
    Check whether switch i can be toggled.

    Switches are numbered from left to right:
    0, 1, 2, ..., n-1

    The rightmost switch can always be toggled.
*/
int canToggle(unsigned int state, int i, int n)
{
    /* Rightmost switch */
    if (i == n - 1)
        return 1;

    /* Immediate right switch must be ON */
    if ((state & (1U << (n - i - 2))) == 0)
        return 0;

    /* All switches further right must be OFF */
    for (int j = i + 2; j < n; j++)
    {
        if (state & (1U << (n - j - 1)))
            return 0;
    }

    return 1;
}

/* BFS to find minimum number of moves */
int minimumMoves(int n)
{
    int totalStates = 1 << n;

    int *dist = (int *)malloc(totalStates * sizeof(int));
    unsigned int *queue =
        (unsigned int *)malloc(totalStates * sizeof(unsigned int));

    for (int i = 0; i < totalStates; i++)
        dist[i] = -1;

    /*
        All switches initially ON.
        Binary representation = 111...111
    */
    unsigned int start = (1U << n) - 1;
    unsigned int target = 0;

    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    dist[start] = 0;

    while (front < rear)
    {
        unsigned int state = queue[front++];

        if (state == target)
        {
            int answer = dist[state];

            free(dist);
            free(queue);

            return answer;
        }

        for (int i = 0; i < n; i++)
        {
            if (canToggle(state, i, n))
            {
                /*
                    Convert switch position i to
                    corresponding bit position.
                */
                int bit = n - i - 1;

                unsigned int newState =
                    state ^ (1U << bit);

                if (dist[newState] == -1)
                {
                    dist[newState] = dist[state] + 1;
                    queue[rear++] = newState;
                }
            }
        }
    }

    free(dist);
    free(queue);

    return -1;
}

/* Closed-form formula */
int formula(int n)
{
    return (1 << (n + 1)) / 3;
}

int main()
{
    int n;

    printf("Enter number of switches: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int bfsAnswer = minimumMoves(n);
    int formulaAnswer = formula(n);

    printf("\nMinimum moves using BFS = %d\n", bfsAnswer);
    printf("Formula result         = %d\n", formulaAnswer);

    if (bfsAnswer == formulaAnswer)
        printf("\nResult validated successfully.\n");
    else
        printf("\nValidation failed.\n");

    return 0;
}
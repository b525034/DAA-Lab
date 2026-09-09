#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

/*
    Checks whether switch i can be toggled.

    Switch i = 0 is the leftmost switch.
    Switch i = n-1 is the rightmost switch.
*/
int canToggle(unsigned int state, int i, int n)
{
    /* Rightmost switch can always be toggled */
    if (i == n - 1)
        return 1;

    /*
        Immediate right switch must be ON.
        Bit corresponding to switch i+1:
        n-i-2
    */
    if ((state & (1U << (n - i - 2))) == 0)
        return 0;

    /*
        All switches further to the right
        must be OFF.
    */
    for (int j = i + 2; j < n; j++)
    {
        if (state & (1U << (n - j - 1)))
            return 0;
    }

    return 1;
}

/* BFS to find the minimum number of moves */
int minimumMoves(int n)
{
    int totalStates = 1 << n;

    int *distance =
        (int *)malloc(totalStates * sizeof(int));

    unsigned int *queue =
        (unsigned int *)malloc(
            totalStates * sizeof(unsigned int));

    if (distance == NULL || queue == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    /* Mark all states as unvisited */
    for (int i = 0; i < totalStates; i++)
        distance[i] = -1;

    /* All switches initially ON */
    unsigned int start = (1U << n) - 1;

    /* All switches finally OFF */
    unsigned int target = 0;

    int front = 0;
    int rear = 0;

    queue[rear++] = start;
    distance[start] = 0;

    while (front < rear)
    {
        unsigned int state = queue[front++];

        /* Target reached */
        if (state == target)
        {
            int answer = distance[state];

            free(distance);
            free(queue);

            return answer;
        }

        /* Try every switch */
        for (int i = 0; i < n; i++)
        {
            if (canToggle(state, i, n))
            {
                int bit = n - i - 1;

                /*
                    Toggle the selected switch.
                    XOR with 1 changes:
                    1 -> 0
                    0 -> 1
                */
                unsigned int newState =
                    state ^ (1U << bit);

                if (distance[newState] == -1)
                {
                    distance[newState] =
                        distance[state] + 1;

                    queue[rear++] = newState;
                }
            }
        }
    }

    free(distance);
    free(queue);

    return -1;
}

/* Closed-form answer */
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

    printf("\nMinimum moves using BFS = %d\n",
           bfsAnswer);

    printf("Formula result         = %d\n",
           formulaAnswer);

    if (bfsAnswer == formulaAnswer)
    {
        printf("\nAlgorithm validated successfully.\n");
    }
    else
    {
        printf("\nValidation failed.\n");
    }

    return 0;
}
#include <stdio.h>

#define MAX 1000

int main()
{
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    int rating[MAX];
    int candy[MAX];

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &rating[i]);

        /* Initially give every child one candy */
        candy[i] = 1;
    }

    /*
     * Pass 1:
     * Left to Right
     */
    for (int i = 1; i < n; i++)
    {
        if (rating[i] > rating[i - 1])
        {
            candy[i] = candy[i - 1] + 1;
        }
    }

    /*
     * Pass 2:
     * Right to Left
     */
    for (int i = n - 2; i >= 0; i--)
    {
        if (rating[i] > rating[i + 1])
        {
            if (candy[i] < candy[i + 1] + 1)
            {
                candy[i] = candy[i + 1] + 1;
            }
        }
    }

    int total = 0;

    printf("\nCandies given:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Child %d: %d candies\n",
               i + 1,
               candy[i]);

        total += candy[i];
    }

    printf("\nMinimum total candies = %d\n",
           total);

    return 0;
}
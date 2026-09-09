#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} Point;

/* Check whether point p belongs to the original
   upright triangle of side n */
int inOriginal(Point p, int n)
{
    return (p.x >= 0 &&
            p.y >= 0 &&
            p.x + p.y <= n - 1);
}

/* Check whether point p belongs to a downward
   triangle described by a, b, c */
int inTarget(Point p, int a, int b, int c)
{
    return (p.x <= a &&
            p.y <= b &&
            p.x + p.y >= c);
}

/* Number of points in a downward triangle */
int targetSize(int a, int b, int c)
{
    int count = 0;

    for (int x = -50; x <= 50; x++)
    {
        for (int y = -50; y <= 50; y++)
        {
            if (inTarget((Point){x, y}, a, b, c))
                count++;
        }
    }

    return count;
}

/* Find maximum overlap */
int findMaximumOverlap(int n)
{
    int N = n * (n + 1) / 2;
    int maxOverlap = 0;

    /*
       For a downward triangle of side n:

       a + b - c = n - 1
    */

    for (int a = -n; a <= 2 * n; a++)
    {
        for (int b = -n; b <= 2 * n; b++)
        {
            int c = a + b - (n - 1);

            /* Ignore triangles outside useful region */
            if (targetSize(a, b, c) != N)
                continue;

            int overlap = 0;

            for (int x = 0; x < n; x++)
            {
                for (int y = 0; y < n; y++)
                {
                    Point p = {x, y};

                    if (inOriginal(p, n) &&
                        inTarget(p, a, b, c))
                    {
                        overlap++;
                    }
                }
            }

            if (overlap > maxOverlap)
                maxOverlap = overlap;
        }
    }

    return maxOverlap;
}

int main()
{
    int n;

    printf("Enter number of coins in the bottom row: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 0;
    }

    int totalCoins = n * (n + 1) / 2;

    int maxOverlap = findMaximumOverlap(n);

    int minimumMoves = totalCoins - maxOverlap;

    int formulaMoves = n * (n + 1) / 6;

    printf("\nTotal coins       = %d", totalCoins);
    printf("\nMaximum overlap   = %d", maxOverlap);
    printf("\nMinimum moves     = %d", minimumMoves);
    printf("\nFormula result    = %d", formulaMoves);

    if (minimumMoves == formulaMoves)
        printf("\n\nResult VALIDATED.\n");
    else
        printf("\n\nResult does NOT match formula.\n");

    return 0;
}
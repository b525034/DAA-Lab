#include <stdio.h>
#include <string.h>

#define MAX 100
#define LEN 1000

// Find overlap between suffix of a and prefix of b
int findOverlap(char a[], char b[])
{
    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxOverlap = 0;

    int maxLen = (lenA < lenB) ? lenA : lenB;

    for (int k = 1; k <= maxLen; k++)
    {
        int match = 1;

        for (int i = 0; i < k; i++)
        {
            if (a[lenA - k + i] != b[i])
            {
                match = 0;
                break;
            }
        }

        if (match)
            maxOverlap = k;
    }

    return maxOverlap;
}

// Merge a and b using their overlap
void mergeStrings(char a[], char b[], char result[])
{
    int overlap = findOverlap(a, b);

    strcpy(result, a);

    strcat(result, b + overlap);
}

int main()
{
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    char str[MAX][LEN];

    printf("Enter the strings:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%s", str[i]);
    }

    while (n > 1)
    {
        int maxOverlap = -1;
        int first = 0;
        int second = 1;

        // Find pair with maximum overlap
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                int overlap = findOverlap(str[i], str[j]);

                if (overlap > maxOverlap)
                {
                    maxOverlap = overlap;
                    first = i;
                    second = j;
                }
            }
        }

        char merged[LEN];

        mergeStrings(str[first], str[second], merged);

        printf("\nMerging \"%s\" + \"%s\"", 
               str[first], str[second]);

        printf(" -> \"%s\"", merged);

        // Put merged string in first position
        strcpy(str[first], merged);

        // Remove second string
        for (int i = second; i < n - 1; i++)
        {
            strcpy(str[i], str[i + 1]);
        }

        n--;
    }

    printf("\n\nGreedy superstring = %s\n", str[0]);

    return 0;
}
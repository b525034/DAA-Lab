#include <stdio.h>

struct Item
{
    int number;
    char colour;
};

int main()
{
    int n;

    printf("Enter number of items: ");
    scanf("%d", &n);

    struct Item items[n];
    struct Item red[n], blue[n], yellow[n];

    int r = 0, b = 0, y = 0;

    printf("\nEnter items in sorted order of number:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Enter number and colour (R/B/Y): ");
        scanf("%d %c", &items[i].number, &items[i].colour);
    }

    // Separate items according to colour
    for (int i = 0; i < n; i++)
    {
        if (items[i].colour == 'R')
        {
            red[r] = items[i];
            r++;
        }
        else if (items[i].colour == 'B')
        {
            blue[b] = items[i];
            b++;
        }
        else if (items[i].colour == 'Y')
        {
            yellow[y] = items[i];
            y++;
        }
    }

    // Combine: Red -> Blue -> Yellow
    int k = 0;

    for (int i = 0; i < r; i++)
    {
        items[k] = red[i];
        k++;
    }

    for (int i = 0; i < b; i++)
    {
        items[k] = blue[i];
        k++;
    }

    for (int i = 0; i < y; i++)
    {
        items[k] = yellow[i];
        k++;
    }

    printf("\nSorted by colour:\n");

    for (int i = 0; i < n; i++)
    {
        printf("(%d, %c) ", items[i].number, items[i].colour);
    }

    printf("\n");

    return 0;
}
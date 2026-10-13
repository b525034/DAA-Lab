#include <stdio.h>
#include <stdlib.h>

struct Item
{
    double value;
    double weight;
    double decay;
    double priority;
};

/* Sort in descending order of priority */
int compare(const void *a, const void *b)
{
    struct Item *x = (struct Item *)a;
    struct Item *y = (struct Item *)b;

    if (x->priority < y->priority)
        return 1;
    else if (x->priority > y->priority)
        return -1;
    else
        return 0;
}

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    struct Item items[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter value, weight and decay rate for item %d: ",
               i + 1);

        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);

        items[i].priority =
            items[i].value /
            (items[i].weight * items[i].decay);
    }

    /* Sort according to greedy priority */
    qsort(items, n, sizeof(struct Item), compare);

    printf("\nGreedy Order:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Item %d: priority = %.4lf\n",
               i + 1, items[i].priority);
    }

    double remaining = W;
    double totalValue = 0.0;
    double time = 0.0;

    printf("\nSelection:\n");

    for (int i = 0; i < n && remaining > 0; i++)
    {
        if (items[i].weight <= remaining)
        {
            /*
             * Take the complete item.
             */
            double effectiveDensity =
                (items[i].value / items[i].weight)
                - items[i].decay * time;

            double contribution =
                items[i].weight * effectiveDensity;

            totalValue += contribution;
            remaining -= items[i].weight;

            printf("Item %d: 100%% taken, contribution = %.4lf\n",
                   i + 1, contribution);

            time += items[i].weight;
        }
        else
        {
            /*
             * Take only the required fraction.
             */
            double fraction = remaining / items[i].weight;

            double effectiveDensity =
                (items[i].value / items[i].weight)
                - items[i].decay * time;

            double contribution =
                remaining * effectiveDensity;

            totalValue += contribution;

            printf("Item %d: %.2f%% taken, contribution = %.4lf\n",
                   i + 1, fraction * 100,
                   contribution);

            remaining = 0;
        }
    }

    printf("\nMaximum effective value = %.4lf\n", totalValue);

    return 0;
}
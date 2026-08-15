#include <stdio.h>

void balance_scale(int arr[], int left, int right, int normal_weight);

int main()
{
    int arr[1000];
    int n;
    int normal_weight;

    printf("Enter the number of coins: ");
    scanf("%d", &n);

    printf("Enter the required weight of a normal coin: ");
    scanf("%d", &normal_weight);

    printf("Enter the coins (weight): ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    balance_scale(arr, 0, n - 1, normal_weight);

    return 0;
}

void balance_scale(int arr[], int left, int right, int normal_weight)
{
    while (left < right)
    {
        int n = right - left + 1;

        int mid = left + n / 2;

        int left_sum = 0;
        int right_sum = 0;

        // Even number of coins
        if (n % 2 == 0)
        {
            for (int i = left; i < mid; i++)
            {
                left_sum += arr[i];
            }

            for (int i = mid; i <= right; i++)
            {
                right_sum += arr[i];
            }

            printf("\nWeighing:\n");

            if (left_sum < right_sum)
            {
                printf("Left side is lighter.\n");
                right = mid - 1;
            }
            else if (right_sum < left_sum)
            {
                printf("Right side is lighter.\n");
                left = mid;
            }
            else
            {
                printf("Both sides are equal.\n");
                printf("No defective coin found.\n");
                return;
            }
        }

        // Odd number of coins
        else
        {
            int mid1 = left + n / 2;

            for (int i = left; i < mid1; i++)
            {
                left_sum += arr[i];
            }

            for (int i = mid1; i < right; i++)
            {
                right_sum += arr[i];
            }

            printf("\nWeighing:\n");

            if (left_sum < right_sum)
            {
                printf("Left side is lighter.\n");
                right = mid1 - 1;
            }
            else if (right_sum < left_sum)
            {
                printf("Right side is lighter.\n");
                left = mid1;
                right = right - 1;
            }
            else
            {
                printf("Both sides are equal.\n");

                // Only the unweighed coin can be defective
                int extra_coin = right;

                if (arr[extra_coin] < normal_weight)
                {
                    printf("Defective coin found: Coin %d\n",
                           extra_coin + 1);
                    printf("Weight = %d\n",
                           arr[extra_coin]);
                }
                else
                {
                    printf("No defective coin found.\n");
                }

                return;
            }
        }
    }

    // One coin remains
    if (arr[left] < normal_weight)
    {
        printf("\nDefective coin found: Coin %d\n",
               left + 1);
        printf("Weight = %d\n",
               arr[left]);
    }
    else
    {
        printf("\nNo defective coin found.\n");
    }
}

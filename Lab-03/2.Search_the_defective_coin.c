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
    // Base case: only one coin remains
    if (left == right)
    {
        if (arr[left] < normal_weight)
        {
            printf("\nDefective coin found!\n");
            printf("Coin %d\n", left + 1);
            printf("Weight = %d\n", arr[left]);
        }
        else
        {
            printf("\nNo defective coin found.\n");
        }

        return;
    }

    int n = right - left + 1;

    // Even number of coins
    if (n % 2 == 0)
    {
        int mid = left + n / 2;

        int left_sum = 0;
        int right_sum = 0;

        for (int i = left; i < mid; i++)
        {
            left_sum += arr[i];
        }

        for (int i = mid; i <= right; i++)
        {
            right_sum += arr[i];
        }

        printf("\nWeighing:\n");
        printf("Left side weight  = %d\n", left_sum);
        printf("Right side weight = %d\n", right_sum);

        if (left_sum < right_sum)
        {
            printf("Left side is lighter.\n");

            balance_scale(arr, left, mid - 1, normal_weight);
        }
        else if (right_sum < left_sum)
        {
            printf("Right side is lighter.\n");

            balance_scale(arr, mid, right, normal_weight);
        }
        else
        {
            printf("Both sides are equal.\n");
            printf("No defective coin found.\n");
        }
    }

    // Odd number of coins
    else
    {
        int mid = left + n / 2;

        int left_sum = 0;
        int right_sum = 0;

        // Left half
        for (int i = left; i < mid; i++)
        {
            left_sum += arr[i];
        }

        // Right half
        for (int i = mid; i < right; i++)
        {
            right_sum += arr[i];
        }

        // arr[right] is left unweighed

        printf("\nWeighing:\n");
        printf("Left side weight  = %d\n", left_sum);
        printf("Right side weight = %d\n", right_sum);

        if (left_sum < right_sum)
        {
            printf("Left side is lighter.\n");

            balance_scale(arr, left, mid - 1, normal_weight);
        }
        else if (right_sum < left_sum)
        {
            printf("Right side is lighter.\n");

            balance_scale(arr, mid, right - 1, normal_weight);
        }
        else
        {
            printf("Both sides are equal.\n");

            // Only the unweighed coin can be defective
            if (arr[right] < normal_weight)
            {
                printf("Defective coin found!\n");
                printf("Coin %d\n", right + 1);
                printf("Weight = %d\n", arr[right]);
            }
            else
            {
                printf("No defective coin found.\n");
            }
        }
    }
}

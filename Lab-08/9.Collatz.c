#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef unsigned long long ull;

/* Check whether 3*n + 1 will overflow */
int will_overflow(ull n) {
    return n > (ULLONG_MAX - 1) / 3;
}

/* Generate and analyse trajectory */
void analyze_collatz(ull n) {

    ull original = n;
    ull steps = 0;
    ull max_value = n;

    ull capacity = 100;
    ull size = 0;

    ull *trajectory =
        (ull *)malloc(capacity * sizeof(ull));

    if (trajectory == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    while (n != 1) {

        /* Resize dynamically */
        if (size == capacity) {

            capacity *= 2;

            ull *temp =
                (ull *)realloc(
                    trajectory,
                    capacity * sizeof(ull)
                );

            if (temp == NULL) {
                printf("Memory reallocation failed.\n");
                free(trajectory);
                return;
            }

            trajectory = temp;
        }

        trajectory[size++] = n;

        if (n > max_value)
            max_value = n;

        if (n % 2 == 0) {
            n = n / 2;
        }
        else {

            if (will_overflow(n)) {
                printf("Overflow detected for %llu.\n", n);
                free(trajectory);
                return;
            }

            n = 3 * n + 1;
        }

        steps++;
    }

    /* Store 1 */
    if (size == capacity) {
        capacity *= 2;
        trajectory =
            (ull *)realloc(
                trajectory,
                capacity * sizeof(ull)
            );
    }

    trajectory[size++] = 1;

    printf("\nStarting value = %llu\n", original);
    printf("Number of steps = %llu\n", steps);
    printf("Maximum value reached = %llu\n", max_value);

    printf("Trajectory:\n");

    for (ull i = 0; i < size; i++) {
        printf("%llu", trajectory[i]);

        if (i < size - 1)
            printf(" -> ");
    }

    printf("\n");

    free(trajectory);
}

/* Analyse all values in [a,b] */
void analyze_interval(ull a, ull b) {

    printf("\n========== INTERVAL ANALYSIS ==========\n");

    for (ull n = a; n <= b; n++) {

        printf("\nFor n = %llu:\n", n);

        ull x = n;
        ull steps = 0;
        ull maximum = n;

        while (x != 1) {

            if (x % 2 == 0) {
                x = x / 2;
            }
            else {

                if (will_overflow(x)) {
                    printf("Overflow detected.\n");
                    break;
                }

                x = 3 * x + 1;
            }

            if (x > maximum)
                maximum = x;

            steps++;
        }

        if (x == 1) {
            printf("Steps = %llu, Maximum = %llu\n",
                   steps, maximum);
        }
    }
}

int main() {

    int choice;

    printf("COLLATZ CONJECTURE ANALYSER\n");
    printf("1. Analyse one starting value\n");
    printf("2. Analyse interval [a,b]\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {

        ull n;

        printf("Enter positive integer n: ");
        scanf("%llu", &n);

        if (n == 0) {
            printf("Invalid input. n must be positive.\n");
            return 0;
        }

        analyze_collatz(n);
    }

    else if (choice == 2) {

        ull a, b;

        printf("Enter interval [a,b]: ");
        scanf("%llu %llu", &a, &b);

        if (a == 0 || a > b) {
            printf("Invalid interval.\n");
            return 0;
        }

        analyze_interval(a, b);
    }

    else {
        printf("Invalid choice.\n");
    }

    return 0;
}
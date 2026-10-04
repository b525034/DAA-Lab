#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));
    int *dp = (int *)malloc(n * sizeof(int));

    printf("Enter array: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int answer = 1;

    for (int i = 0; i < n; i++) {
        dp[i] = 1;

        for (int j = 0; j < i; j++) {
            if (A[j] < A[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }

        answer = max(answer, dp[i]);
    }

    printf("Length of LIS = %d\n", answer);

    free(A);
    free(dp);

    return 0;
}
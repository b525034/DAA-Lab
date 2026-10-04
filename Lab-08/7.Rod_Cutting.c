#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    int *P = (int *)malloc((n + 1) * sizeof(int));
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    int *cut = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter prices P[1] to P[%d]:\n", n);

    for (int i = 1; i <= n; i++)
        scanf("%d", &P[i]);

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {

        dp[i] = -1;
        cut[i] = 0;

        for (int j = 1; j <= i; j++) {

            if (P[j] + dp[i - j] > dp[i]) {
                dp[i] = P[j] + dp[i - j];
                cut[i] = j;
            }
        }
    }

    printf("Maximum revenue = %d\n", dp[n]);

    printf("Optimal pieces: ");

    int length = n;

    while (length > 0) {
        printf("%d ", cut[length]);
        length -= cut[length];
    }

    printf("\n");

    free(P);
    free(dp);
    free(cut);

    return 0;
}
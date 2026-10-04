#include <stdio.h>
#include <stdlib.h>

#define INF 1000000

int main() {
    int n, V;

    printf("Enter number of coins: ");
    scanf("%d", &n);

    int *C = (int *)malloc(n * sizeof(int));

    printf("Enter coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &C[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    int *dp = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;

    for (int i = 1; i <= V; i++)
        dp[i] = INF;

    for (int i = 1; i <= V; i++) {
        for (int j = 0; j < n; j++) {
            if (C[j] <= i && dp[i - C[j]] != INF) {
                if (dp[i - C[j]] + 1 < dp[i])
                    dp[i] = dp[i - C[j]] + 1;
            }
        }
    }

    if (dp[V] == INF)
        printf("Minimum coins = -1\n");
    else
        printf("Minimum coins = %d\n", dp[V]);

    free(C);
    free(dp);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define INF 1e18

int main() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    double *p = (double *)malloc((n + 1) * sizeof(double));
    double *q = (double *)malloc((n + 1) * sizeof(double));

    double **cost = (double **)malloc((n + 2) * sizeof(double *));
    double **weight = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i <= n + 1; i++) {
        cost[i] = (double *)calloc(n + 2, sizeof(double));
        weight[i] = (double *)calloc(n + 2, sizeof(double));
        root[i] = (int *)calloc(n + 2, sizeof(int));
    }

    printf("Enter p[1] to p[%d]:\n", n);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &p[i]);

    printf("Enter q[0] to q[%d]:\n", n);
    for (int i = 0; i <= n; i++)
        scanf("%lf", &q[i]);

    /* Empty subtrees */
    for (int i = 1; i <= n + 1; i++) {
        cost[i][i - 1] = q[i - 1];
        weight[i][i - 1] = q[i - 1];
    }

    /* Calculate OBST */
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            cost[i][j] = INF;

            weight[i][j] =
                weight[i][j - 1] +
                p[j] +
                q[j];

            for (int r = i; r <= j; r++) {

                double current =
                    cost[i][r - 1] +
                    cost[r + 1][j] +
                    weight[i][j];

                if (current < cost[i][j]) {
                    cost[i][j] = current;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost = %.3lf\n",
           cost[1][n]);

    printf("Root key = k%d\n", root[1][n]);

    printf("\nRoot table:\n");

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            printf("root[%d][%d] = k%d\n",
                   i, j, root[i][j]);
        }
    }

    for (int i = 0; i <= n + 1; i++) {
        free(cost[i]);
        free(weight[i]);
        free(root[i]);
    }

    free(cost);
    free(weight);
    free(root);
    free(p);
    free(q);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    char X[100], Y[100];

    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    int m = strlen(X);
    int n = strlen(Y);

    int **L = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        L[i] = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int length = L[m][n];

    char *lcs = (char *)malloc((length + 1) * sizeof(char));

    int i = m, j = n;
    int index = length;

    lcs[index] = '\0';

    while (i > 0 && j > 0) {

        if (X[i - 1] == Y[j - 1]) {
            lcs[--index] = X[i - 1];
            i--;
            j--;
        }
        else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    printf("LCS length = %d\n", length);
    printf("LCS = %s\n", lcs);

    for (i = 0; i <= m; i++)
        free(L[i]);

    free(L);
    free(lcs);

    return 0;
}
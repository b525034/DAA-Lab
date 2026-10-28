
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];
}

int cmpInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void) {
    int n, m;
    scanf("%d%d", &n, &m);

    int *A = malloc(n * sizeof(int));
    int *indices = malloc(n * sizeof(int));
    int *values = malloc(n * sizeof(int));
    int *component = malloc(n * sizeof(int));
    parent = malloc(n * sizeof(int));
    sz = malloc(n * sizeof(int));

    if (!A || !indices || !values || !component ||
        !parent || !sz) {
        printf("Memory allocation failed.\n");
        free(A); free(indices); free(values);
        free(component); free(parent); free(sz);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u < 1 || u > n || v < 1 || v > n) {
            printf("Invalid edge\n");
            free(A); free(indices); free(values);
            free(component); free(parent); free(sz);
            return 1;
        }

        unite(u - 1, v - 1);
    }

    for (int i = 0; i < n; i++)
        component[i] = find(i);

    for (int root = 0; root < n; root++) {
        if (component[root] != root)
            continue;

        int count = 0;

        for (int i = 0; i < n; i++) {
            if (component[i] == root) {
                indices[count] = i;
                values[count] = A[i];
                count++;
            }
        }

        qsort(indices, count, sizeof(int), cmpInt);
        qsort(values, count, sizeof(int), cmpInt);

        for (int i = 0; i < count; i++)
            A[indices[i]] = values[i];
    }

    printf("Lexicographically smallest permutation:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);
    printf("\n");

    free(A); free(indices); free(values);
    free(component); free(parent); free(sz);
    return 0;
}

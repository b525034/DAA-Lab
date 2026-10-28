
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz;
long long *weight;

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
    weight[a] += weight[b];
}

int main(void) {
    int V, E, K;
    scanf("%d%d%d", &V, &E, &K);

    parent = malloc(V * sizeof(int));
    sz = malloc(V * sizeof(int));
    weight = malloc(V * sizeof(long long));

    if (!parent || !sz || !weight) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(sz);
        free(weight);
        return 1;
    }

    for (int i = 0; i < V; i++) {
        scanf("%lld", &weight[i]);
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge\n");
            continue;
        }

        unite(u - 1, v - 1);

        long long best = 0;
        int found = 0;

        for (int j = 0; j < V; j++) {
            if (find(j) == j && sz[j] <= K) {
                if (!found || weight[j] > best)
                    best = weight[j];
                found = 1;
            }
        }

        if (found)
            printf("%lld\n", best);
        else
            printf("No eligible component\n");
    }

    free(parent);
    free(sz);
    free(weight);
    return 0;
}

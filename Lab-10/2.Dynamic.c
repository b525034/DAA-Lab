
#include <stdio.h>
#include <stdlib.h>

int *parent, *sz, *active;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

int unite(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return 0;

    if (sz[a] < sz[b]) {
        int t = a;
        a = b;
        b = t;
    }

    parent[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main(void) {
    int R, C, k;
    scanf("%d%d%d", &R, &C, &k);

    int N = R * C;
    parent = malloc(N * sizeof(int));
    sz = malloc(N * sizeof(int));
    active = calloc(N, sizeof(int));

    if (!parent || !sz || !active) {
        printf("Memory allocation failed.\n");
        free(parent);
        free(sz);
        free(active);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    int islands = 0;

    for (int i = 0; i < k; i++) {
        int r, c;
        scanf("%d%d", &r, &c);  /* 0-based coordinates */

        if (r < 0 || r >= R || c < 0 || c >= C) {
            printf("Invalid cell\n");
            continue;
        }

        int id = r * C + c;

        if (!active[id]) {
            active[id] = 1;
            islands++;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (nr < 0 || nr >= R ||
                    nc < 0 || nc >= C)
                    continue;

                int nid = nr * C + nc;

                if (active[nid] && unite(id, nid))
                    islands--;
            }
        }

        printf("%d ", islands);
    }

    printf("\n");
    free(parent);
    free(sz);
    free(active);
    return 0;
}

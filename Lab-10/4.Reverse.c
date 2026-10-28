
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *parent, *sz, *active;
long long *weight, *value;
int *head, *to, *nextEdge;
int edgeCount = 0;

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

void addEdge(int u, int v) {
    to[edgeCount] = v;
    nextEdge[edgeCount] = head[u];
    head[u] = edgeCount++;
}

long long getMaximum(int V) {
    long long best = LLONG_MIN;
    int found = 0;

    for (int i = 1; i <= V; i++) {
        if (active[i] && find(i) == i) {
            if (!found || weight[i] > best)
                best = weight[i];
            found = 1;
        }
    }

    return found ? best : 0;
}

int main(void) {
    int V, E;
    scanf("%d%d", &V, &E);

    parent = malloc((V + 1) * sizeof(int));
    sz = malloc((V + 1) * sizeof(int));
    active = calloc(V + 1, sizeof(int));
    weight = malloc((V + 1) * sizeof(long long));
    value = malloc((V + 1) * sizeof(long long));
    head = malloc((V + 1) * sizeof(int));
    to = malloc(2 * E * sizeof(int));
    nextEdge = malloc(2 * E * sizeof(int));

    if (!parent || !sz || !active || !weight || !value ||
        !head || (E > 0 && (!to || !nextEdge))) {
        printf("Memory allocation failed.\n");
        free(parent); free(sz); free(active);
        free(weight); free(value); free(head);
        free(to); free(nextEdge);
        return 1;
    }

    for (int i = 1; i <= V; i++) {
        scanf("%lld", &value[i]);
        parent[i] = i;
        sz[i] = 1;
        weight[i] = 0;
        head[i] = -1;
    }

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (u < 1 || u > V || v < 1 || v > V) {
            printf("Invalid edge\n");
            free(parent); free(sz); free(active);
            free(weight); free(value); free(head);
            free(to); free(nextEdge);
            return 1;
        }

        addEdge(u, v);
        addEdge(v, u);
    }

    int *P = malloc(V * sizeof(int));
    long long *ans = malloc(V * sizeof(long long));

    if (!P || !ans) {
        printf("Memory allocation failed.\n");
        free(parent); free(sz); free(active);
        free(weight); free(value); free(head);
        free(to); free(nextEdge);
        free(P); free(ans);
        return 1;
    }

    for (int i = 0; i < V; i++)
        scanf("%d", &P[i]);

    for (int i = V - 1; i >= 0; i--) {
        /* State immediately after deleting P[i]. */
        ans[i] = getMaximum(V);

        int u = P[i];

        if (u < 1 || u > V || active[u]) {
            printf("Invalid deletion order.\n");
            free(parent); free(sz); free(active);
            free(weight); free(value); free(head);
            free(to); free(nextEdge);
            free(P); free(ans);
            return 1;
        }

        active[u] = 1;
        parent[u] = u;
        sz[u] = 1;
        weight[u] = value[u];

        for (int e = head[u]; e != -1; e = nextEdge[e]) {
            int v = to[e];
            if (active[v])
                unite(u, v);
        }
    }

    for (int i = 0; i < V; i++)
        printf("%lld\n", ans[i]);

    free(parent); free(sz); free(active);
    free(weight); free(value); free(head);
    free(to); free(nextEdge);
    free(P); free(ans);

    return 0;
}

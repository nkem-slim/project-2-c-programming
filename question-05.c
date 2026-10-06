#include <stdio.h>
#include <string.h>

#define N 10  // A,B,C,D,E,F,G,H,I,J
#define INF 999999 // used here to represent unreachable or infinite distance

typedef struct 
{
    char u, v;
    int weight;
} Edge;

int indexOf(char c) 
{
    if (c >= 'A' && c <= 'J') return c - 'A';
    return -1;
}

int main() {
    Edge edges[] = 
    {
        {'A','B',6}, {'A','D',16}, {'B','C',6}, {'B','D',6}, {'B','J',7},
        {'C','G',-9}, {'D','E',7}, {'D','J',8}, {'E','F',10}, {'E','I',-2},
        {'F','G',4}, {'F','I',2}, {'G','H',13}, {'I','F',2}, {'J','E',3}
    };
    int m = sizeof(edges) / sizeof(edges[0]);

    int dist[N];
    int parent[N];
    for (int i = 0; i < N; i++) 
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[indexOf('A')] = 0;

    // relax all edges (V-1) times
    for (int iter = 0; iter < N - 1; iter++) 
    {
        for (int e = 0; e < m; e++) 
        {
            int u = indexOf(edges[e].u);
            int v = indexOf(edges[e].v);
            if (dist[u] != INF && dist[u] + edges[e].weight < dist[v]) 
            {
                dist[v] = dist[u] + edges[e].weight;
                parent[v] = u;
            }
        }
    }

    // negative-cycle detection: one more relaxation pass
    int hasNegativeCycle = 0;
    for (int e = 0; e < m; e++) 
    {
        int u = indexOf(edges[e].u);
        int v = indexOf(edges[e].v);
        if (dist[u] != INF && dist[u] + edges[e].weight < dist[v]) 
        {
            hasNegativeCycle = 1;
            break;
        }
    }

    if (hasNegativeCycle) 
    {
        printf("Negative-weight cycle detected.\n");
        printf("Shortest-path results may be undefined.\n");
    } else {
        printf("No negative-weight cycle detected.\n");
    }

    printf("\nSource: A\n");
    printf("%-12s%-15s%-20s\n", "Destination", "Shortest Cost", "Path");

    for (int i = 0; i < N; i++) 
    {
        char dest = 'A' + i;
        if (dest == 'A') continue;

        if (dist[i] == INF) {
            printf("%-12c%-15s%-20s\n", dest, "unreachable", "-");
            continue;
        }

        // reconstruct path by walking parent[] backwards
        char path[N];
        int pathLen = 0;
        int cur = i;
        while (cur != -1) 
        {
            path[pathLen++] = 'A' + cur;
            cur = parent[cur];
        }

        printf("%-12c%-15d", dest, dist[i]);
        for (int j = pathLen - 1; j >= 0; j--) 
        {
            printf("%c", path[j]);
            if (j != 0) printf(" -> ");
        }
        printf("\n");
    }

    char query;
    printf("\nEnter a destination data center to check: ");
    scanf(" %c", &query);

    int qi = indexOf(query);
    if (qi == -1) {
        printf("Invalid data center name: %c\n", query);
    } else if (dist[qi] == INF) {
        printf("Data center %c is unreachable from A.\n", query);
    } else {
        printf("Shortest cost from A to %c: %d\n", query, dist[qi]);
    }


    return 0;
}

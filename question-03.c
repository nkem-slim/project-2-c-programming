#include <stdio.h>

typedef struct 
{
    char u, v;
    int cost;
} Edge;

int find(int parent[], int i) 
{
    while (parent[i] != i) i = parent[i];
    return i;
}

void unionSet(int parent[], int a, int b) 
{
    parent[find(parent, a)] = find(parent, b);
}

int main() {
    Edge edges[] = 
    {
        {'A','B',6}, {'A','D',12}, {'B','D',5}, {'B','C',11},
        {'C','D',17}, {'C','G',25}, {'D','E',22}, {'D','F',15},
        {'E','F',10}, {'F','G',22}
    };
    int n = sizeof(edges) / sizeof(edges[0]);

    // sort edges by cost (bubble sort, simple & fine for small n)
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - 1 - i; j++) 
        {
            if (edges[j].cost > edges[j+1].cost) 
            {
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }

    int parent[7];
    for (int i = 0; i < 7; i++) parent[i] = i;  // A=0, B=1, ..., G=6

    int totalCost = 0;
    int selectedCount = 0;

    printf("Selected Connections:\n");
    for (int i = 0; i < n && selectedCount < 6; i++) 
    {
        int u = edges[i].u - 'A';
        int v = edges[i].v - 'A';

        if (find(parent, u) != find(parent, v)) 
        {
            unionSet(parent, u, v);
            printf("Station %c - Stattion %c : %d\n", edges[i].u, edges[i].v, edges[i].cost);
            totalCost += edges[i].cost;
            selectedCount++;
        }
    }

    printf("\nTotal Installation Cost: %d thousand dollars\n", totalCost);


    return 0;
}

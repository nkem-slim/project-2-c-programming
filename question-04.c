#include <stdio.h>
#include <string.h>

#define N 7  // A..G

int graph[N][N];

int indexOf(char c) {
    return c - 'A';
}

void addEdge(char u, char v, int w) 
{
    graph[indexOf(u)][indexOf(v)] = w;
    graph[indexOf(v)][indexOf(u)] = w;  // undirected
}

// BFS traversal
int visited[N];
int queue[N];
int front = 0, rear = 0;

void bfs(int startIdx)
{
    visited[startIdx] = 1;
    queue[rear++] = startIdx;

    printf("BFS order: ");
    while(front < rear)
    {
        int current = queue[front++];
        printf("%c ", 'A' + current);

        for(int i = 0; i<N;i++)
        {
            if(graph[current][i] != 0 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void analyzeDirectNeighbors(int startIdx) 
{
    char maxGateway = 0;
    int maxTime = -1;

    printf("Directly connected gateways:\n");
    for (int i = 0; i < N; i++) {
        if (graph[startIdx][i] != 0) 
        {
            printf("%c - %c : %d ms\n", 'A' + startIdx, 'A' + i, graph[startIdx][i]);
            if (graph[startIdx][i] > maxTime) 
            {
                maxTime = graph[startIdx][i];
                maxGateway = 'A' + i;
            }
        }
    }

    printf("Highest transfer time: %c with %d ms\n", maxGateway, maxTime);
}


int main() 
{
    addEdge('A','B',6);
    addEdge('A','D',12);
    addEdge('B','D',5);
    addEdge('B','C',11);
    addEdge('C','D',17);
    addEdge('C','G',25);
    addEdge('D','E',22);
    addEdge('D','F',15);
    addEdge('E','F',10);
    addEdge('F','G',22);

    char start;
    printf("Enter starting gateway: ");
    scanf(" %c", &start);

    if(start < 'A' || start > 'G')
    {
        printf("Invalid gateway name.\n");
        return 1;
    }

    bfs(indexOf(start));
    analyzeDirectNeighbors(indexOf(start));
    return 0;
}


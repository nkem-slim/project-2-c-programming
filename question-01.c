#include <stdio.h>

#define MAX_SIZE 50

typedef struct 
{
    char id;
    int priority;
} Container;

Container heap[MAX_SIZE];
int heapSize = 0; // tracks how many elements are currently in it


void printHeap()
{
    printf("Heap: ");
    for(int i = 0; i < heapSize; i++)
    {
        printf("%c:%d ", heap[i].id, heap[i].priority);
    }
    printf("\n");
}

void heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].priority > heap[largest].priority) largest = left;
    if(right < n && heap[right].priority > heap[largest].priority) largest = right;

    if(largest != i)
    {
        Container temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        heapify(n, largest);
    }
}

// Assign an alphabet to each priority score and heapify from the bottom
void buildHeap(int arr[], int n)
{
    heapSize = n;
    for(int i = 0; i<n; i++)
    {
        heap[i].id = 'A'+i;
        heap[i].priority = arr[i];
    }

    // this loop starts at the last parent node (n/2-1) and walks backward to the root, calling heapify on each.
    for(int i =n/2 - 1;i>=0;i--) // last parent is ((n-1) - 1)/2 which is simplified to n/2 - 1
    {
        heapify(n, i);
    }
}

// Insertion function for task 2 urgent baggage contaainer
void insertHeap(char id, int priority)
{
    heap[heapSize].id = id;
    heap[heapSize].priority = priority;
    int i = heapSize;
    heapSize++;

    while(i != 0 && heap[(i - 1)/2].priority < heap[i].priority)
    {
        Container temp = heap[i];
        heap[i] = heap[(i-1)/2];
        heap[(i-1)/2] = temp;

        i = (i-1)/2;
    }
}

// Cancel container task 3 - find the container, swap it with the last element, shrink `heapSize` by one, then sift-down from that position to restore the max-heap priority
void deleteContainer(char id)
{
    int i;
    for(i=0; i <heapSize;i++)
    {
        if(heap[i].id == id) break; // replace the id value and stop once found
    }

    if(i == heapSize) // no change in the lenght 
    {
        printf("Container %c not found.\n", id);
        return;
    }

    heap[i] = heap[heapSize - 1];
    heapSize--;

    heapify(heapSize, i);
}

int main()
{
    int P[] =  {56, 23, 91, 34, 72, 48, 85, 17, 63, 79, 42};
    int n = sizeof(P)/sizeof(P[0]);

    buildHeap(P, n);
    printf("Max Heap after the heap construction:\n");
    printHeap();

    printf("\nInserting container X with priority 100...\n");
    insertHeap('X', 100);
    printf("Max Heap after insertion:\n");
    printHeap();

    printf("\nRemoving container X...\n");
    deleteContainer('X');
    printf("Max heap after removal:\n");
    printHeap();
    return 0;
}


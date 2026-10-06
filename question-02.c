#include <stdio.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct 
{
    char id[4];
    char name[20];
    int priority;
} Patient;

Patient heap[MAX_SIZE];
int heapSize = 0;

void printHeap()
{
    for(int i = 0; i < heapSize; i++)
    {
        printf("%s:%s - Priority %d\n", heap[i].id, heap[i].name, heap[i].priority);
    }
    printf("\n");
}

// Heapify - sift down
void heapify(int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && heap[left].priority > heap[largest].priority) largest = left;
    if(right < n && heap[right].priority > heap[largest].priority) largest = right;

    if(largest != i)
    {
        Patient temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;

        heapify(n, largest);
    }
}

// Build the initial heap
void buildHeap(char ids[][4], char names[][20], int priorities[], int n)
{
    heapSize = n;
    for(int i = 0; i<n; i++)
    {
        strcpy(heap[i].id, ids[i]);
        strcpy(heap[i].name, names[i]);
        heap[i].priority = priorities[i];
    }

    for(int i = n/2 - 1;i>=0;i--)
    {
        heapify(n, i);
    }
}

// generate the treatment order - 2
Patient extractMax()
{
    Patient top = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapify(heapSize, 0);
    return top;
}

void printTreatmentOrder()
{
    int savedSize = heapSize;
    Patient temp[MAX_SIZE];
    int tempCount = 0;

    while(heapSize > 0)
    {
        temp[tempCount++] = extractMax();
    }

    printf("Treatment Order:\n");
    for(int i = 0;i < tempCount;i++)
    {
        printf("Patient %s:%s - Priority %d\n", temp[i].id, temp[i].name, temp[i].priority);
    }

    // reestore heap for later use
    heapSize = savedSize;
    for(int i = 0;i<tempCount; i++) heap[i] = temp[i];
}

// Inerting Kofi :)
void insertHeap(char *id, char *name, int priority)
{
    strcpy(heap[heapSize].id, id);
    strcpy(heap[heapSize].name, name);
    heap[heapSize].priority = priority;
    int i = heapSize;
    heapSize++;

    while(i != 0 && heap[(i - 1)/2].priority < heap[i].priority)
    {
        Patient temp = heap[i];
        heap[i] = heap[(i-1)/2];
        heap[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

void deleteContainer(char *id) 
{
    int i;
    for (i = 0; i < heapSize; i++) 
    {
        if (strcmp(heap[i].id, id) == 0) break;
    }
    if (i == heapSize) 
    {
        printf("Patient %s not found.\n", id);
        return;
    }
    heap[i] = heap[heapSize - 1];
    heapSize--;
    heapify(heapSize, i);
}

int main()
{
    char ids[][4] = {"P01", "P02", "P03", "P04", "P05", "P06", "P07"};
    char names[][20] = {"Amina", "Daniel", "Eric", "Grace", "Hassan", "Irene", "Jean"};
    int priorities[] = {72, 45, 91, 63, 88, 54, 76};
    int n = sizeof(priorities)/sizeof(priorities[0]);

    buildHeap(ids, names, priorities, n);

    printf("Max heap after constructions:\n");
    printHeap();

    printf("\n");
    printTreatmentOrder();

    printf("\nInserting P08 Kofi, priority 98...\n");
    insertHeap("P08", "Kofi", 98);
    printHeap();

    printf("\nRemoving P08...\n");
    deleteContainer("P08");
    printHeap();

    return 0;
}

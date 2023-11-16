#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 1000  
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int arr[], int i, int size) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && arr[left] < arr[smallest])
        smallest = left;

    if (right < size && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, smallest, size);
    }
}

void insertMinHeap(int arr[], int* size, int val) {
    if (*size == MAX_SIZE) {
        printf("Overflow: Could not insertKey\n");
        return;
    }

    arr[*size] = val;
    int i = *size;
    *size = *size + 1;

    while (i != 0 && arr[(i-1)/2] > arr[i]) {
        swap(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

int extractMin(int arr[], int* size) {
    if (*size <= 0)
        return INT_MAX;
    if (*size == 1) {
        *size = *size - 1;
        return arr[0];
    }

    int root = arr[0];
    arr[0] = arr[*size-1];
    *size = *size - 1;
    minHeapify(arr, 0, *size);

    return root;
}
void maxHeapify(int arr[], int i, int size) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;

    if (right < size && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, largest, size);
    }
}

void insertMaxHeap(int arr[], int* size, int val) {
    if (*size == MAX_SIZE) {
        printf("Overflow: Could not insertKey\n");
        return;
    }

    arr[*size] = val;
    int i = *size;
    *size = *size + 1;

    while (i != 0 && arr[(i-1)/2] < arr[i]) {
        swap(&arr[i], &arr[(i-1)/2]);
        i = (i-1)/2;
    }
}

int extractMax(int arr[], int* size) {
    if (*size <= 0)
        return INT_MIN;
    if (*size == 1) {
        *size = *size - 1;
        return arr[0];
    }

        int root = arr[0];
    arr[0] = arr[*size-1];
    *size = *size - 1;
    maxHeapify(arr, 0, *size);

    return root;
}

int main() {
    int arr[MAX_SIZE];
    int size = 0;
    insertMinHeap(arr, &size, 37);
    insertMinHeap(arr, &size,82);
    insertMinHeap(arr, &size, 15);
    insertMinHeap(arr, &size, 69);
    insertMinHeap(arr, &size, 54);
    insertMinHeap(arr, &size, 8);
    insertMinHeap(arr, &size, 91);
    insertMinHeap(arr, &size, 20);
    insertMinHeap(arr, &size, 47);
    insertMinHeap(arr, &size, 63);
    insertMinHeap(arr, &size, 29);
    insertMinHeap(arr, &size, 75);
    insertMinHeap(arr, &size, 6);
    insertMinHeap(arr, &size, 42);
    insertMinHeap(arr, &size, 98);
    printf("minheap: \n");
    printf("original array: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\nmin heap deletion: \n");
    while(size > 0 ){
    printf("%d ", extractMin(arr, &size));}
    printf("\n");
    size = 0; 
    printf("maxheap: \n" );
    
    insertMaxHeap(arr, &size, 37);
    insertMaxHeap(arr, &size,82);
    insertMaxHeap(arr, &size, 15);
    insertMaxHeap(arr, &size, 69);
    insertMaxHeap(arr, &size, 54);
    insertMaxHeap(arr, &size, 8);
    insertMaxHeap(arr, &size, 91);
    insertMaxHeap(arr, &size, 20);
    insertMaxHeap(arr, &size, 47);
    insertMaxHeap(arr, &size, 63);
    insertMaxHeap(arr, &size, 29);
    insertMaxHeap(arr, &size, 75);
    insertMaxHeap(arr, &size, 6);
    insertMaxHeap(arr, &size, 42);
    insertMaxHeap(arr, &size, 98);
    printf("original array: \n");
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\nmax heap deletion: \n");
    while(size > 0 ){
    printf("%d ", extractMax(arr, &size));}  

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in a binomial heap
struct Node {
    int key;
    int degree;
    struct Node* parent;
    struct Node* child;
    struct Node* sibling;
};

// Function to create a new node with a given key
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

// Function to merge two binomial heaps into a single binomial heap
struct Node* mergeBinomialHeaps(struct Node* h1, struct Node* h2) {
    if (!h1)
        return h2;
    if (!h2)
        return h1;

    struct Node* res = NULL;
    struct Node* tail = NULL;
    struct Node* prev = NULL;
    struct Node* currH1 = h1;
    struct Node* currH2 = h2;

    while (currH1 != NULL || currH2 != NULL) {
        if (currH1 != NULL && (currH2 == NULL || currH1->degree <= currH2->degree)) {
            struct Node* next = currH1->sibling;
            currH1->sibling = NULL;

            if (tail == NULL)
                res = currH1;
            else
                tail->sibling = currH1;

            tail = currH1;
            prev = currH1;
            currH1 = next;
        } else {
            struct Node* next = currH2->sibling;
            currH2->sibling = NULL;

            if (tail == NULL)
                res = currH2;
            else
                tail->sibling = currH2;

            tail = currH2;
            prev = currH2;
            currH2 = next;
        }
    }

    return res;
}

// Function to link two binomial trees of the same degree
void link(struct Node* parent, struct Node* child) {
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree++;
}

// Function to perform union of two binomial heaps
struct Node* unionBinomialHeaps(struct Node* h1, struct Node* h2) {
    struct Node* mergedHeap = mergeBinomialHeaps(h1, h2);
    if (!mergedHeap)
        return NULL;

    struct Node* prev = NULL;
    struct Node* curr = mergedHeap;
    struct Node* next = curr->sibling;

    while (next != NULL) {
        if (curr->degree != next->degree || (next->sibling != NULL && next->sibling->degree == curr->degree)) {
            // Case 1: No need to consolidate
            prev = curr;
            curr = next;
        } else {
            // Case 2: Consolidate
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                link(curr, next);
            } else {
                if (prev == NULL)
                    mergedHeap = next;
                else
                    prev->sibling = next;
                link(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return mergedHeap;
}

// Function to insert a key into a binomial heap
struct Node* insert(struct Node* heap, int key) {
    struct Node* newNode = createNode(key);
    return unionBinomialHeaps(heap, newNode);
}

// Function to extract the minimum key from a binomial heap
struct Node* extractMin(struct Node* heap, int* minKey) {
    if (!heap)
        return NULL;

    struct Node* minNode = heap;
    struct Node* prev = NULL;
    struct Node* curr = heap;

    while (curr->sibling != NULL) {
        if (curr->sibling->key < minNode->key) {
            minNode = curr->sibling;
            prev = curr;
        }
        curr = curr->sibling;
    }

    if (prev == NULL)
        heap = minNode->sibling;
    else
        prev->sibling = minNode->sibling;

    *minKey = minNode->key;
    free(minNode);

    return heap;
}

// Function to print the keys of a binomial heap
void printBinomialHeap(struct Node* heap) {
    while (heap != NULL) {
        printf("Degree %d: ", heap->degree);
        struct Node* current = heap;
        while (current != NULL) {
            printf("%d ", current->key);
            current = current->child;
        }
        printf("\n");
        heap = heap->sibling;
    }
}

// Main function
int main() {
    struct Node* binomialHeap = NULL;

    // Insert keys into the binomial heap
    binomialHeap = insert(binomialHeap, 10);
    binomialHeap = insert(binomialHeap, 20);
    binomialHeap = insert(binomialHeap, 5);

    printf("Binomial Heap after insertion:\n");
    printBinomialHeap(binomialHeap);

    // Extract the minimum key from the binomial heap
    int minKey;
    binomialHeap = extractMin(binomialHeap, &minKey);

    printf("\nMinimum key extracted: %d\n", minKey);

    printf("\nBinomial Heap after extraction:\n");
    printBinomialHeap(binomialHeap);

    return 0;
}

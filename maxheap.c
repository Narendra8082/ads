#include<stdio.h>
#include<stdlib.h>

struct node {
    int key;
    struct node* left;
    struct node* right, *part;
};

void maxHeapify(struct node* root);
void maxHeapify1(struct node* root);

struct node* findRightMostInLastLevel(struct node* root);

struct node* newNode(int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->part = NULL;
    return temp;
}

struct node* maxHeapInsert(struct node* root, int data) {
    struct node* new = newNode(data);
    if (root == NULL) {
        return new;
    }
    else {
        struct node* queue[100];
        int rear = 0, front = 0;
        queue[rear++] = root;
        while (front != rear) {
            struct node* temp = queue[front++];
            if (temp->left == NULL) {
                temp->left = new;
                new->part = temp;
                break;
            }
            else if (temp->right == NULL) {
                temp->right = new;
                new->part = temp;
                break;
            }

            queue[rear++] = temp->left;
            queue[rear++] = temp->right;
        }
    }
    maxHeapify(new);
    return root;
}

void maxHeapify(struct node* root) {
    if (root->part == NULL) {
        return;
    }
    if (root->part->key > root->key) {
        return;
    }
    else {
        int temp = root->key;
        root->key = root->part->key;
        root->part->key = temp;
        maxHeapify(root->part);
    }
}

void maxHeapify1(struct node* root) {

    if (root == NULL) {
        return;
    }
    else if (root->left == NULL && root->right == NULL) {
        return;
    }
    else if (root->left == NULL && root->right != NULL) {
        if (root->key < root->right->key) {
            int temp = root->key;
            root->key = root->right->key;
            root->right->key = temp;
            maxHeapify1(root->right);
        }
        return;
    }
    else if (root->right == NULL && root->left != NULL) {
        if (root->key < root->left->key) {
            int temp = root->key;
            root->key = root->left->key;
            root->left->key = temp;
            maxHeapify1(root->left);
        }
        return;
    }
    else if (root->key > root->left->key && root->key > root->right->key) {
        return;
    }
    else {
        int t = root->key, t1 = root->left->key, t2 = root->right->key;
        if (t1 > t2) {
            root->key = t1;
            root->left->key = t;
            maxHeapify1(root->left);
        }
        else {
            root->key = t2;
            root->right->key = t;
            maxHeapify1(root->right);
        }
    }
}

int maxDelete(struct node* root) {
    if (root == NULL) {
        return 0;
    }
    else {
        int k = root->key;
        struct node* rightmost = findRightMostInLastLevel(root);
        if (rightmost == root) {
            root == NULL;
            free(root);
            return k;
        }
        if (rightmost->part->right == rightmost) {
            rightmost->part->right = NULL;
        }
        else {
            rightmost->part->left = NULL;
        }
        root->key = rightmost->key;
        maxHeapify1(root);
        return k;
    }
}

struct node* findRightMostInLastLevel(struct node* root) {
    struct node* rightmost = NULL;

    if (root == NULL) {
        return NULL;
    }

    struct node* queue[100];
    int rear = 0, front = 0;
    queue[rear++] = root;

    while (front != rear) {
        int levelSize = rear - front;
        for (int i = 0; i < levelSize; i++) {
            struct node* temp = queue[front++];

            // Update the rightmost element for the current level
            rightmost = temp;

            if (temp->left) {
                queue[rear++] = temp->left;
            }
            if (temp->right) {
                queue[rear++] = temp->right;
            }
        }
    }

    return rightmost;
}
int height(struct node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}
void printLevel(struct node* root, int level) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", root->key);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}
void levelOrderTraversal(struct node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printf(" level: %d   ",i);
        printLevel(root, i);
        printf("\n");
    }
}
int main() {
    int keys[] = { 4, 10, 3, 5, 1, 8, 58, 42, 36, 25, 14, 78, 54, 95, 200, 47 };
    int n = sizeof(keys) / sizeof(keys[0]);
    struct node* root = NULL;
    for (int i = 0; i < n; i++) {
        root = maxHeapInsert(root, keys[i]);
    }
    levelOrderTraversal(root);
    // printf("%d\n",root->key);
    int k = 0;
    while (k < n) {
        printf("%d ", maxDelete(root));
        // levelOrderTraversal(root);
        k++;
    }
    // printf("%d   ",mindelete(root));
    // printf("%d",mindelete(root));
    // // printf("%d\n",root->key);
    // levelOrderTraversal(root);
}

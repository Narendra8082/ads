#include<stdio.h>
#include<stdlib.h>
struct node{
    int data,color;
    struct node*left,*right;
};
struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct node* insertNode(struct node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    // Create a queue for level-order insertion
    struct node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct node* current = queue[front++];
        if (current->left == NULL) {
            current->left = createNode(data);
            break;
        } else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = createNode(data);
            break;
        } else {
            queue[rear++] = current->right;
        }
    }
    return root;
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
        printf("%d %d ", root->data,root->color);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}
void colorto(struct node* root, int level,int color) {
    if (root == NULL) {
        return;
    }
    if (level == 1) {
        root->color=color;
    } else if (level > 1) {
        colorto(root->left, level - 1,color);
        colorto(root->right, level - 1,color);
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
void color(struct node*root){
    int h=height(root);
    for(int i=1;i<=h;i++){
        if(i%2==1){
            colorto(root,i,0);
        }
        else{
            colorto(root,i,1);
        }
    }
}
struct node* findNearestAncestor(struct node* root, int node1, int node2) {
    if (root == NULL) {
        return NULL;
    }

    if (root->data == node1 || root->data == node2) {
        return root;
    }

    struct node* leftAncestor = findNearestAncestor(root->left, node1, node2);
    struct node* rightAncestor = findNearestAncestor(root->right, node1, node2);

    if (leftAncestor && rightAncestor) {
        return root;
    }

    return (leftAncestor != NULL) ? leftAncestor : rightAncestor;
}
struct node* search(struct node* root, int target) {
    if (root == NULL) {
        return NULL;  // Base case: node not found
    }
    
    if (root->data == target) {
        return root;  // Base case: node found
    }
    
    // Recurse on left and right subtrees
    struct node* leftResult = search(root->left, target);
    if (leftResult != NULL) {
        return leftResult;  // Node found in the left subtree
    }
    
    return search(root->right, target);  // Search the right subtree
}
int countred(struct node*root,int d,struct node*anc){
    struct node *temp=search(root,d);
    //printf("%d",temp->data);
    int c=0;
    while(temp!=anc){
        if(temp->color==1){
            c++;
        }
        temp=search(root,temp->data/2);
    }
    return c;
}
int countblack(struct node*root,int d,struct node*anc){
    struct node *temp=search(root,d);
    //printf("%d",temp->data);
    int c=0;
    while(temp!=anc){
        if(temp->color==0){
            c++;
        }
        temp=search(root,temp->data/2);
    }
    return c;
}
void recolor(struct node*root){
    if(root){
        recolor(root->left);
        if(root->color==0){
            root->color=1;
        }
        else{
            root->color=0;
        }
        recolor(root->right);
    }
}
int main(){
    int n,k;
    struct node *root=NULL;
    printf("enter no of nodes in the tree\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        root=insertNode(root,i+1);
        // levelOrderTraversal(root);
    }
    color(root);
    //recolor(root);
    levelOrderTraversal(root);
    printf("\n");
    struct node *na;
    //printf("%d ",na->data);
    int c=0,x,y,q,qi;
    //na=search(root,9);
    //printf("%d ",na->color);
    printf("enter no of queries\n");
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        printf("select query\n");
        scanf("%d",&qi);
    switch(qi){
        case 1:
        recolor(root);
        levelOrderTraversal(root);
        printf("\n");
        break;
        case 2:
        printf("enter x and y");
        scanf("%d%d",&x,&y);
        na=findNearestAncestor(root,x,y);
        c=0;
        c=countred(root,x,na);
        c+=countred(root,y,na);
        if(na->color==1){
            c+=1;
        }
        printf("no of red nodesin the path %d and %d are %d \n",x,y,c);
        break;
        case 3:
        printf("enter x and y");
        scanf("%d%d",&x,&y);
        na=findNearestAncestor(root,x,y);
        c=0;
        c=countblack(root,x,na);
        c+=countblack(root,y,na);
        if(na->color==0){
            c+=1;
        }
        printf("no of black nodes in the path %d and %d are %d \n",x,y,c);
        break;
    }
    }
}
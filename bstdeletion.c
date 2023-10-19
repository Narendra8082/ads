#include<stdio.h>
#include<stdlib.h>
struct node{
    int data,color;
    struct node *left,*right,*part;
};

struct node* insert(struct node *root,int k){
    struct node *newnode,*temp,*ptr;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=k;
    newnode->part=NULL;
    newnode->left=NULL;
    newnode->right=NULL;
    if(root==NULL){
        root=newnode;
    }
    else{
        ptr=NULL;
        temp=root;
        while(temp!=NULL){
            ptr=temp;
            if(k<temp->data){
                temp=temp->left;
            }
            else{
                temp=temp->right;
            }
        }
    if(k<ptr->data){
        ptr->left=newnode;
        newnode->part=ptr;
    }
    else{
        ptr->right=newnode;
        newnode->part=ptr;
    }
    }
    return root;
}
struct node* search(struct node *root, int x) {
    if (root == NULL) {
        printf("Element not found\n");
        return NULL;
    } else if (root->data == x) {
        return root;
    } else if (root->data > x) {
         return search(root->left, x);
    } else {
         return search(root->right, x);
    }
}
void leafdelete(struct node *ad){
    if(ad->data > ad->part->data){
            ad->part->right=NULL;
            free(ad);
        }
        else{
            ad->part->left=NULL;
            free(ad);
        }
}
void deletenode(struct node*root,int k){
    struct node* ad=search(root,k);
    if(ad->left==NULL && ad->right==NULL){
        leafdelete(ad);
    }
    else{
        if(ad->right==NULL){
            struct node*temp=ad->left;
            while(temp->right!=NULL){
                temp=temp->right;
            }
            ad->data=temp->data;
            deletenode(root,temp->data);
        }
        else
        {
            struct node*temp=ad->right;
            while(temp->left!=NULL){
                temp=temp->left;
            }
            ad->data=temp->data;
            leafdelete(temp);
        }
    }
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
        printf("%d ", root->data);
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
int main(){
    int n,k;
    struct node*root=NULL;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&k);
        root=insert(root,k);
    }
    deletenode(root,28);
    levelOrderTraversal(root);
}
/*
15
25
20
30
10
23
28
32
5
15
22
24
26
29
31
40
*/
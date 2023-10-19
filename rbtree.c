//rbtree insertion
#include<stdio.h>
#include<stdlib.h>
struct node* check_red_red_violation(struct node* root);
struct node* search(struct node* root, int x);
void recolor(struct node *root);
struct node{
    int data,color;
    struct node *left,*right,*part;
};
struct node * leftrotate(struct node *x)
	{
	struct node *y=x->right,*xp=x->part;
	struct node *t2=y->left;
	y->left=x;
	x->right=t2;
    y->part=x->part;
    x->part=y;
    if (t2) {
        t2->part = x;
    }
    if(xp){
        if(y->data > xp->data ){
            xp->right=y;
        }
        else{
            xp->left=y;
        }
    }
    return y;
	}
struct node * rightrotate(struct node *y)
	{
	struct node *x=y->left,*yp=y->part;
	struct node *t2=x->right,*p=y->part;
	x->right=y;
	y->left=t2;
    x->part=y->part;
    y->part=x;
    if (t2) {
        t2->part = y;
    }
    if(yp){
        if(x->data > yp->data ){
            yp->right=x;
        }
        else{
            yp->left=x;
        }
    }
	return x;
	}
struct node *rotaterecolor(struct node *root,struct node* newnode){
    struct node*temp=NULL,*p=newnode->part,*gp=newnode->part->part;
    if(newnode->data > p->data && newnode->data > gp->data){
        temp=leftrotate(gp);
        recolor(gp);
        recolor(p);
        if(temp->part==NULL){
            root=temp;
        }
    }
    else if(newnode->data < p->data && newnode->data < gp->data){
        temp=rightrotate(gp);
        if(temp->part==NULL){
            root=temp;
        }
        recolor(gp);
        recolor(p);
    }
    else if(newnode->data < p->data && newnode->data > gp->data){
        temp=rightrotate(p);
        if(temp->part==NULL){
            root=temp;
        }
        temp=leftrotate(gp);
        if(temp->part==NULL){
            root=temp;
        }
        recolor(gp);
        recolor(newnode);
    }
    else if(newnode->data > p->data && newnode->data < gp->data){
        temp=leftrotate(p);
        if(temp->part==NULL){
            root=temp;
        }
        temp=rightrotate(gp);
        if(temp->part==NULL){
            root=temp;
        }
        recolor(gp);
        recolor(newnode);
    }
    return root;
}
void recolor(struct node *root){
    if(root->color==1){
        root->color=0;
    }
    else{
        root->color=1;
    }
}
struct node * checkif(struct node *root){
    if(root!=NULL){
        if(root->color==1 && root->left->color ==1){
            return root->left;
        }
        else if(root->color==1 && root->right->color ==1){
            return root->right;
        }
        return checkif(root->left);
        return checkif(root->right);
    }
}
struct node * check(struct node *root){
    struct node *ad=NULL;
    ad=checkif(root);
    if(ad!=NULL){
        return rotaterecolor(root,ad);
    }
    return root;
}
struct node* insert(struct node *root,int k){
    struct node *newnode,*temp,*ptr;
    newnode=(struct node*)malloc(sizeof(struct node));
    newnode->data=k;
    newnode->part=NULL;
    newnode->left=NULL;
    newnode->right=NULL;
    if(root==NULL){
        root=newnode;
        newnode->color=0;
    }
    else{
        newnode->color=1;
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
    if(newnode->part->color==1){
        struct node* p=newnode->part,*gp=newnode->part->part;
        struct node *sbl=NULL;
        if(p->data > gp->data){
            sbl=gp->left;
        }
        else{
            sbl=gp->right;
        }
        if(sbl==NULL){
            root=rotaterecolor(root,newnode);
        }
        else if(sbl->color== 0){
            root=rotaterecolor(root,newnode);
        }
        else{
            sbl->color=0;
            p->color=0;
            if(gp!=root){
                recolor(gp);
            }
        }
    }
    }
    struct node* temp2=NULL;
    temp2=check_red_red_violation(root);
    if(temp2){
        root=rotaterecolor(root,temp2);
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
        printf("%d,%d ", root->data,root->color);
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
struct node * check_red_red_violation_helper(struct node* node, int prev_node_color) {
    if (node == NULL) {
        return node; // No violation
    }

    // In-order traversal - Go left
    if (check_red_red_violation_helper(node->left, node->color)) {
        return node; // Violation found
    }

    // Check if the current node and its parent are both red
    if (prev_node_color == 1 && node->color == 1) {
        return node ;// Violation found
    }

    // In-order traversal - Go right
    return check_red_red_violation_helper(node->right, node->color);
}

// Wrapper function to check red-red violation after an insertion
struct node* check_red_red_violation(struct node* root) {
    // Pass NULL as prev_node_color initially.
    return check_red_red_violation_helper(root, 0);
}
int main(){
    int n,k;
    struct node*root=NULL;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&k);
        root=insert(root,k);
        levelOrderTraversal(root);
    }
}
/*
11
12
20
9
17
18
32
27
42
80
4
2
*/
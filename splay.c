//finaldeletesplay

#include<stdio.h>
#include<stdlib.h>
struct node* search(struct node* root, int x);
struct node* searchelement(struct node *root, int x);
struct node{
    int data;
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
    //printf("%d        ",y->data);
    //levelOrderTraversal(y);
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
struct node* splay(struct node* root, int k) {
    if (!root) return NULL;
    
    struct node* ad = search(root, k);
    if (!ad) return root;

    while (ad->part) {
        struct node* p = ad->part;
        if (!p->part) {
            if (ad->data > p->data) {
                root = leftrotate(p);
            } else {
                root = rightrotate(p);
            }
        } else {
            struct node* gp = p->part;
            if (ad->data > p->data && ad->data > gp->data) {
                root = leftrotate(gp);
                root = leftrotate(p);
            } else if (ad->data < p->data && ad->data < gp->data) {
                root = rightrotate(gp);
                root = rightrotate(p);
            } else if (ad->data > p->data && ad->data < gp->data) {
                p = leftrotate(p);
                root = rightrotate(gp);
            } else {
                p = rightrotate(p);
                root = leftrotate(gp);
            }
        }
    }
    
    return root ? root : ad;
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
void inorder(struct node* root)
{
    if(root!=NULL)
    {
        inorder(root->left);
        printf("%d ",root->data);
        inorder(root->right);
    }
}
struct node* delete(struct node* root, int x) {
    root = splay(root, x);
    struct node*prev,*temp=root->left;
    while(temp->left!=NULL){
        prev=temp;
        temp=temp->left;
    }
    root->data=temp->data;
    prev->left=NULL;
    free(temp);
    return root;
}

struct node* searchelement(struct node *root, int x) {
    if (root == NULL) {
        printf("Element not found\n");
        return NULL;
    } else {
        root = splay(root, x); 
        if (root->data == x) {
            return root;
        } else {
            printf("Element not found\n");
            return NULL;
        }
    }
}

struct node* insert(struct node *root, int k) {
    struct node *newnode, *temp, *ptr;
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = k;
    newnode->part = NULL;
    newnode->left = NULL;
    newnode->right = NULL;

    if (root == NULL) {
        return newnode; 
    } else {
        ptr = NULL;
        temp = root;
        while (temp != NULL) {
            ptr = temp;
            if (k < temp->data) {
                temp = temp->left;
            } else if (k > temp->data) {
                temp = temp->right;
            } else {
                temp = temp->right;
            }
        }
        if (k < ptr->data) {
            ptr->left = newnode;
        } else {
            ptr->right = newnode;
        }
        newnode->part = ptr;
        root = splay(root, k); 
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
    int n,k,x;
    struct node*root=NULL;
    printf("enter the no of elements  ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        //printf("\n");
        scanf("%d",&k);
        root=insert(root,k);
        root=splay(root,k);
        levelOrderTraversal(root);
    }
    printf("enter element for searching    ");
    scanf("%d",&x);
    root=searchelement(root,x);
    printf("element after searching is %d \n",root->data);
    levelOrderTraversal(root);
    printf("enter element to be deleted");
    scanf("%d",&x);
    root=delete(root,x);
    //root=splay(root,x);
    levelOrderTraversal(root);
    // root=splay(root,24);
    // levelOrderTraversal(root);
    //printf("%d",search(root,23)->part->data);
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
5
21
32
65
98
54
*/
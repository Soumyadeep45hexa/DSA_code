#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *left,*right;
};
struct node *root=NULL;
struct node *newNode(struct node *root,int x){
  root=(struct node *)malloc(sizeof(struct node));
    root->data=x;
    root->left=root->right=NULL;
    return root;
}
struct node *insert(struct node *root,int x){
    if(root==NULL) return newNode(root,x);
    if(x>root->data) root->right=insert(root->right,x);
    else if (x<root->data) root->left=insert(root->left,x);
    else printf("The key is already present\n");
    return root;
}
struct node *create(){
   struct node *root=NULL;
    int key,n;
    printf("Enter the number of key need to be entered: ");
    scanf("%d",&n);
    printf("Enter %d elements: \n",n);
    for (int i=0;i<n;i++){
        scanf("%d",&key);
        root=insert(root,key);
    }
    return root;
}

struct node *search(struct node *root, int key) {

    if (root == NULL)
        return NULL;

    if (root->data > key)
        return search(root->left, key);

    else if (root->data < key)
        return search(root->right, key);

    else
        return root;
}

void preorder(struct node *root){if (root) {printf("%d ",root->data);preorder(root->left);preorder(root->right);}}
void postorder(struct node *root){if (root) {postorder(root->left);postorder(root->right);printf("%d ",root->data);}}
void inorder(struct node *root){if (root) {inorder(root->left);printf("%d ",root->data);inorder(root->right);}}

struct node *minnode(struct node *root){
    while(root->left!=NULL){
        root=root->left;
    }
    return root;
}
struct node *deletenode(struct node *root,int num){
    if (root==NULL){
        printf("The tree is empty\n");
        return NULL;
    }else if (root->data>num){ root->left=deletenode(root->left,num);}
    else if(root->data<num){ root->right=deletenode(root->right,num);}
        else{ if(root->left==NULL && root->right==NULL){
        free(root);
        return NULL;
        }else if(root->right==NULL){
            struct node *temp=root->left;
            free(root);
            return temp;
        }else if(root->left==NULL){
                struct node *temp=root->right;
            free(root);
            return temp;
        }else{
            struct node *suc=minnode(root->right);
            root->data = suc->data;
            root->right=deletenode(root->right,suc->data);
        }
    }
    return root;
}


int main(){
    int choice,key;
    struct node *root=NULL;
    while(1){
        printf("====BST_Menu====\n");
        printf("\n1.create,2.insert,3.Search,4.preorder,5.postorder,6.inorder,7.Exit,8.Deletenode\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: root=create();
            break;
            case 2:
            printf("Enter the key to be inserted : ");
                scanf("%d",&key);
            root=insert(root,key);
            break;
            case 3: 
                    printf("Enter the key to search: ");
                    scanf("%d",&key);
                    if (search(root,key)!=NULL) printf("The key %d is present\n",key);
                    else printf("The key %d is not present\n",key);
                    break;
            case 4: printf("Preorder\n"); preorder(root); break;
            case 5: printf("postorder\n"); postorder(root); break;
            case 6: printf("inorder\n"); inorder(root); break;
            case 7: printf("Exiting...\n"); exit(0);break;
            case 8: printf("Enter the key to be deleted:");
                    scanf("%d",&key);
                    deletenode(root,key);
                    printf("\n Deleted: %d",key);
                    break;
            default: printf("Invalid_Choice\n"); return 0;
        }
    }
    return  0;
}
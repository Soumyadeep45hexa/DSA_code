#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *left,*right;
};
struct node *newNode(struct node *root,int x){
  root=(struct node *)malloc(sizeof(struct node));
    root->data=x;
    root->left=root->right=NULL;
    return root;
}
struct node *insert(struct node *root,int x){
    if(root==NULL) return newNode(root,x);
    if(x>root->data) root->right=insert(root->right,x);
    else if  (x<root->data) root->left=insert(root->left,x);
    else printf("The key is already present\n");
    return root;
}
struct node *create(){
   struct node *root=NULL;
    int key,n;
    printf("Enter the numnber of key need to be entered: ");
    scanf("%d",&n);
    printf("Enter %d elements: \n",n);
    for (int i=0;i<n;i++){
        scanf("%d",&key);
        root=insert(root,key);
    }
    return root;
}
struct node *search(struct node *root,int key){
 
     if (root->data>key) return search(root->left,key);
    else if (root->data<key) return search(root->right,key);
    else if (root->data==key || root==NULL) return root;
}
void preorder(struct node *root){if (root) {printf("%d ",root->data);preorder(root->left);preorder(root->right);}}
void postorder(struct node *root){if (root) {postorder(root->left);postorder(root->right);printf("%d ",root->data);}}
void inorder(struct node *root){if (root) {inorder(root->left);printf("%d ",root->data);inorder(root->right);}}



int main(){
    int choice,key;
    struct node *root=NULL;
    while(1){
        printf("====BST_Menu====\n");
        printf("\n1.create,2.insert,3.Search,4.preorder,5.postorder,6.inorder,7.Exit\n");
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
            default: printf("Invalid_Choice\n"); return 0;
        }
    }
    return  0;
}
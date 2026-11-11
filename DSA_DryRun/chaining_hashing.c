#include <stdio.h>
#include <stdlib.h>
#define Size 10
struct node {
    int data;
    struct node *next;
};
struct node *table[Size];
void insert(int key){
    int index=key%10;
    struct node *p=(struct node *)malloc(sizeof(struct node));
    p->data=key;
    p->next=table[index];
    table[index]=p;
}
void display(){
    for (int i=0;i<Size;i++){
        printf("%d: ",i);
        for(struct node *p=table[i];p!=NULL;p=p->next){
            printf("%d->",p->data);
        }
        printf("NULL\n");
    }
}
void delete(){
    int key;
    printf("Enter the key need to be deleted : ");
    scanf("%d",&key);
    int index=key%Size;
    struct node *p=table[index];
    struct node *prev=NULL;
    while(p!=NULL){
       if(p->data==key){
        prev->next=p->next;
        free(p);
        return ;
       }
       prev=p;
       p=p->next;
    }
    printf("The key is not present\n");
      
}
int main() {
    int n, key;
    printf("How many keys? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        insert(key);
    }
    display();

    delete();
    display();
    return 0;
}
#include <stdio.h>
struct node{
    int data;
    struct node *next;
}
struct  node *top=NULL;
void push(int num){
    struct node *new=malloc(sizeof(struct node));
    new->data=num;
    new->next=NULL
    if (top==NULL){
        top=new;
    }else{
        new->next=top;
        top=new;
    }
}
void pop(){
    if(top==NULL){
        printf("Stack_Underflow\n");
        return;
    }else{
        struct node *tmp=top;
        printf("%d is popped\n",tmp->data);
        top=top->next;
        free(tmp);
    }
}
void peek(){
    if(top==NULL){
        printf("Stack_Underflow\n");
        return;
    }else{
        printf("The top element is %d",top->data);
    }
}
void sort(){
    struct node *i,*j;
    for (i=top;i!=NULL;i=i->next){
        for (j=i->next;j!=NULL;j=j->next){
            if (i->data > j->data){
                int temp=i->data;
                i->data =j->data;
                j->data=temp;
            }
        }
    }
}
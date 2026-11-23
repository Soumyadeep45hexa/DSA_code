#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *head=NULL;
struct node *newnode(struct node *head,int n){
    struct node *p=malloc(sizeof(struct node));
    p->data=n;
        p->next=NULL;
    if (head==NULL){
        head=p;
    }else{
        struct node *temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next=p;
    }
    return head;
}
// struct node *insert(struct node *head,int n){
//     if(head==NULL) newnode(head,n);
//     struct node *p=(struct node *)malloc(sizeof(struct node));

    
// }
struct node *display(struct node *head){
    struct node *temp=head;
    while(temp!=NULL){
        printf("%d->",temp->data);
        temp=temp->next;
    }
    return head;
}
struct  node *middlenode(struct node *head,int low,int high){
    int middle=low+(high-low)/2;
    int num=0;
    struct node *temp=head;
    while(temp!=NULL){
        num++;
        temp=temp->next;
        if (num==middle) break;
    }
    printf("The middle of the LL is : %d",temp->data);
    printf("\n");
    return head;
    
}
struct node *removeduplicate(struct node *head){
    struct node *temp=head;
    int arr[100]={0};
    while(temp!=NULL){
        arr[temp->data]++;
        temp=temp->next;
    }
    int ref=0;
    int flag=1;
    for (int i=0;i<100;i++){
        if (arr[i]>1){
            ref=i;
            flag=0;
            break;
        }
    }if(flag==1) {printf("NO duplicate\n"); return head;}
    struct  node *prev=NULL;
    struct node *temp1=head;
    while(temp1!=NULL){
        if (ref==temp1->data){
            printf("\nThe duplicate %d is removed\n",ref);
            if (prev==NULL){
                head=temp1->next;
            }else{
            prev->next=temp1->next;
            }
            free(temp1);
            break;
        }
        prev=temp1;
        temp1=temp1->next;
    }
    return head;
}
struct node *Nthnode(struct node *head,int n,int Size){
    int num=Size-n;
    int ref=0;
    struct node *temp=head;
    while(temp!=NULL){
        temp=temp->next;
        ref++;
        if (ref==num){
        printf("\nThe %d is the %d node from back of the LinkedList\n",temp->data,n);
        break;
        }
}
return head;
}
struct node *deletebeg(struct node *head){
    if (head==NULL) {printf("Empty Linked List\n"); return head;}
    else{
       struct node  *temp=head;
       head=head->next;
       temp->next=NULL;
       free(temp);
    }
    return head;
}
struct node *insertbeg(struct node *head,int n){
    if (head==NULL) return newnode(head,n);
    else{
        struct node *p=malloc(sizeof(struct node ));
        p->data=n;
        p->next=head;
        head=p;
    }
    return head;
}
struct node *sort(struct node *head){
    struct node *i,*j;
    for(i=head;i!=NULL;i=i->next){
        for (j=i->next;j!=NULL;j=j->next){
            if (i->data>j->data){
                int temp=i->data;
                i->data=j->data;
                j->data=temp;
            }
        }
    }
    return head;
}
int count(struct node *head){
    int count=0;
    struct node *temp=head;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count;
}
struct node *reverse(struct node *head){
     struct
}

int main(){
    int num;
    printf("Enter the number of elements : ");
    scanf("%d",&num);
    printf("Enter the elements: \n");
    for (int i=0;i<num;i++){
        int n=0;
        scanf("%d",&n);
        head=newnode(head,n);
    }
    display(head);
//     middlenode(head,0,num-1);
//    head= removeduplicate(head);
//    num=num-1;
//     display(head);
//     int n1;
//     printf("\nEnter the Nth node to find from back:\n");
//     scanf("%d",&n1);
//     Nthnode(head,n1,num);
    int p;
    printf("Enter the elements to be entered at the begin: ");
    scanf("%d",&p);
    head=insertbeg(head,p);
    
    display(head);
    printf("\n");
    head=deletebeg(head);
    display(head);
    printf("\n");
    head=sort(head);
    display(head);
return 0;
}
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *enterData(struct node *head) {
    struct node *new_node, *ptr;
    int num;
    printf("Enter -1 to stop\n");
    printf("Enter the value: ");
    scanf("%d", &num);

    while (num != -1) {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = num;
        new_node->link = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            ptr = head;
            while (ptr->link != NULL) {
                ptr = ptr->link;      
            }
            ptr->link = new_node;   
        }

        printf("Enter the value (-1 to stop): ");
        scanf("%d", &num);
    }
    return head;
}

struct node *display(struct node *head) {
    struct node *ptr = head;
    if (head == NULL) {
        printf("List is empty\n");
    }
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->link;
    }
    printf("\n");
    return head;
}
struct node *addfromback(struct node *head){
    
    struct node *ptr,*new_node;
    int n;
    printf("Enter the data: ");
    scanf("%d",&n);
    new_node =(struct node *)malloc(sizeof (struct node));
    new_node->data=n;
    new_node->link=NULL;
    ptr =head;
    if (head==NULL) return new_node;
    else{
    while (ptr->link!=NULL){
        ptr =ptr ->link;
    }
    ptr->link= new_node;
    
return head;
    }
}

struct node *addfromfront(struct node *head){
    struct node *new_node;
    int n;
    printf("Enter the data : ");
    scanf("%d",&n);
    new_node=(struct node *)malloc(sizeof(struct node));
    new_node->link=head;
    new_node->data=n;
    head=new_node;
return head;
}
struct node *insertafter(struct node *head){
    int n1;
    printf("Enter the value after which to add: ");
    scanf("%d",&n1);
    struct node *new_node,*ptr;
    ptr=head;
    int n;
    printf("Enter the value to add: ");
    scanf("%d",&n);
    new_node=(struct node *)malloc(sizeof(struct node));
    new_node->data=n;
    new_node->link=NULL;
    while (ptr->data != n1){
       ptr=ptr->link;
       if (ptr->link == NULL){
        printf("Such data dont Exist\n");
        return head;
       }
    }
    new_node->link =ptr->link;
    ptr->link=new_node;
    return head;
}
struct node *insertbefore (struct node *head){
     int n1,n;
    printf("Enter the value before which to add: ");
    scanf("%d",&n1);
       printf("Enter the data to be added: ");
    scanf("%d",&n);
    struct node *new_node,*ptr;
     new_node=(struct node *)malloc(sizeof(struct node));
    ptr=head;
     new_node->data=n;
   
    // ptrb=(struct node *)malloc(sizeof(struct node));
    if (head->data == n1 ){
        new_node->link=head ;
       
        return new_node;
    }
 
    new_node->link=NULL;
    new_node->data=n;
    //ptrb->data=n1;
    while (ptr->link !=NULL){
        if (ptr->link->data == n1){
            break;
        }
        ptr=ptr->link;
    }
    if (ptr->link == NULL) {
    printf("The Value Dont Exist\n");
    free(new_node);
    return head;
}
    new_node->link= ptr->link;
    ptr->link=new_node;
return head;
}
struct node *deletefront(struct node *head ){
    struct node *newnode ;
    if (head==NULL){
        printf("the LinkedList is empty\n");
        return 0;
    }
    newnode=(struct node *)malloc(sizeof (struct node));
    newnode =head;
    head=head->link;
    printf("The Data deleted is : %d\n",newnode->data);
    free(newnode);
return head;
} 
struct node *deleteback(struct node *head){
    struct node *ptr ,*preptr;
    if (head==NULL){
        printf("the LinkedList is empty\n");
        return 0;
    }
    ptr=head;   
    while(ptr ->link!=NULL){
        preptr = ptr;
        ptr =ptr->link;
    }
    preptr->link=NULL;
    printf("The deleted data is : %d\n",ptr->data);
    return head;
}
struct node *deleteafterdata(struct  node *head){
    int n1;
    printf("Enter the data after which ths node is to deletd: ");
    scanf("%d",&n1);
    struct node *ptr;
    if (head==NULL){
        ptr=head;
        head=head->link;
        free(ptr);
        return head;
    }
    else {
        ptr=head;
        while(ptr->data!=n1){
            ptr =ptr ->link;
            if (ptr->link==NULL){
                printf("Such data dont  present\n");
                return head;
            }
        }
        ptr->link=ptr->link->link;
        return head;
}
}
struct node *deleteafterpos(struct node *head){
    struct node *ptr ;
    int pos;
    printf ("Enter the pos: ");
        scanf("%d",&pos);
    int count=1;
    ptr=head;
    while(count!=pos){
        ptr =ptr ->link;
        count++;
        if (ptr ->link ==NULL){
            printf("Such position is not present\n");
            return head;
        }
    }
    printf("The Deleted data is: %d",ptr ->link->data);
    ptr->link=ptr->link->link;
   
    return head;

}
int main(){
    int ch;
    struct node *head = NULL;

    while (1) {
        printf("1. Enter data\n2. Display\n3.AddAtTheEnd\n4.addfromfront\n5.insertafter\n6.insertbefore\n7.Deletefromfront\n8.Deletefromback\n9.Deleteafterdata\n10.Deleteafterpos\n11. Exit\nEnter the Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                head = enterData(head);
                break;
            case 2:
                head = display(head);
                break;
            case 3:
                head = addfromback(head);
                break;
            case 4:
            head=addfromfront(head);
            break;
            case 5: 
            head=insertafter(head);
            break;
            case 6: 
            head=insertbefore(head);
            break;
            case 7: 
            head=deletefront(head);
            break;
            case 8: 
            head=deleteback(head);
            break;
            case 9:
            head=deleteafterdata(head);
            break;
            case 10: 
            head=deleteafterpos(head);
            break;
            case 11:
                printf("Exiting..!!");
                exit(0);
                
        }
    }
    return 0;
}
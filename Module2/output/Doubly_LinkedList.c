#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *prev;
    struct node *next;
};
struct node *insertatend(struct node *head) {
    struct node *newnode, *ptr;
    int num;

    // 1. Move ptr to the last node ONLY if list is not empty
    ptr = head;
    if (ptr != NULL) {
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
    }

    while (1) {
        printf("Enter the number(-1 to stop): ");
        scanf("%d", &num);
        if (num == -1)
            break;

        newnode = (struct node *)malloc(sizeof(struct node));
        if (newnode == NULL) {
            printf("Memory allocation failed\n");
            return head;
        }

        newnode->data = num;
        newnode->next = NULL;
        newnode->prev = NULL;

        if (head == NULL) {
            head = newnode;
            ptr = head;
        } else {
            ptr->next = newnode;
            newnode->prev = ptr;
            ptr = newnode;
        }
    }
    return head;
}

struct node *display(struct node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return head;
    }

    struct node *ptr = head;
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
    return head;
}
struct node *insertbegin(struct node *head) {
    struct node *newnode;
    int data;
    
    newnode = (struct node *)malloc(sizeof(struct node));
    
    // 1. Check for allocation error immediately
    if (newnode == NULL) {
        printf("Memory allocation failed\n");
        return head;
    }
    
    printf("Enter the data: ");
    scanf("%d", &data);
    
    // 2. Initialize the new node
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = head;
    
    // 3. Update the old head's prev pointer ONLY if the list is not empty
    if (head != NULL) {
        head->prev = newnode;
    }
    
    // 4. The new node is now the head of the list
    head = newnode;
    
    return head;
}
struct node *insertafterpos(struct node *head){
        struct node *newnode,*ptr;
        int val;
        printf("Enter the val to enter : ");
        scanf("%d",&val);
        int pos;
        printf("Enter the pos: ");
        scanf("%d",&pos);
        int count=0;
    while (count!=pos){
        ptr=ptr->next;
        count++;
        if (ptr==NULL){
            printf("Such index don't exists\n");
            return head;
        }
    }
    ptr->data=val;
f    return head;
}
    

int main()
{
    int ch;
    struct node *head=NULL;
    // head=(struct node *)malloc(sizeof(struct node ));
    // head->next=NULL;
    while (1){
    printf("\n-----MENU-----\n");
    printf("1.Enter DATA\n");
    printf("2.Display\n");
    printf("3.Insert at begining\n");
        printf("Enter the Choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
        case  1:
           head=insertatend(head);
            break;
        case  2:
           head=display(head);
            break;
        case  3:
           head=insertbegin(head);
            break;
        case 4 : 
        head=insertafterpos(head);
        break;
        default:
            break;
        }
    
        /* code */
    }
    return 0;
    
}
#include <stdio.h>
#define Size 100
int temp[Size],front =-1,rear=-1;
void enqueue(int val){
    if (((rear+1)%Size) == front ){
        printf("The Queue is \n");
        return ;
    }else {
        if (front==-1) front=0;
    rear = (rear+1) % Size ;
    temp[rear]=val;
    printf("The Value %d is insreted \n",val);
    }
}
void dequeue(){
    if (front ==-1 ){
        printf("The Queue is Empty\n");
        return ;
    }
    int val =temp[front];
    if (front == rear) {
        front = rear = -1;
    
    }else {
   front=(front+1)%Size;
    printf("The Value %d is deleted \n",val);
    }
}
int display(){
    
    // for (int i=front;i<=rear;i++){
    //     printf("%d ",temp[i]);
    // }
    // return 0;
    if (front == -1) 
     {
        printf("The Queue is empty\n");
        return 0;
     }
     int i=front;
     while(1){
        printf("%d ",temp[i]);
        if (i == rear) break;
        i=(i+1)%Size;

     }
     printf("\n");
     return 0;
}
int main(){
    int ch;
    while(1){
    printf("\n-------Menu Selection-------");
    printf("\n1.Enqueue\n");
    printf("2.Dequeue\n");
    printf("3.display\n");
    printf ("4.Exit\n");
    printf("Enter the Choice: ");
    scanf("%d",&ch );
   switch(ch){
    case 1: 
    int val;
    printf("Enter the Value to be Insterted : ");
    scanf("%d",&val);
    enqueue(val);
        break;
    case 2:
    dequeue();
        break;
    case 3:
        display();
        break;
    case 4:
        printf("Exiting....\n");
        return 0;
        break;
    default:
        printf("Inavlid_Input\n");
        return 0;
   }
    }
}
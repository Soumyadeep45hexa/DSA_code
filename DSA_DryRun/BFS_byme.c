#include <stdio.h>
// #define N 5
// int que[N];
// int front =0,rear =-1;
// void enqueue(int x){
//     if (front==-1 && rear==-1){
//             que[rear]=x;
//     }else if((rear+1)%N==front){
//         printf("The queue is full\n");
//         return;
//     }else {
//         rear=(rear+1)%N;
//         que[rear]=x;
//         }
// }
// void dequeue(){
//    if (front==-1 && rear==-1){
//            printf("The queue is empty\n");
//            return ;
//     } else if(front==rear){
//         front=rear=-1;
//     }else{
//         printf("the dequed element is: %d",que[front]);
//         front=(front+1)%N;
//     }
// }
#include <limits.h>
void merge(int arr[],int low,int high,int mid){
    int n1=mid-low+1;
    int n2=high-mid;
    int L[n1+1],R[n2+1];
     for (int i=0;i<n1;i++){
        L[i]=arr[low+i];
    }
     for (int i=0;i<n2;i++){
        R[i]=arr[mid+i+1];
    }
    L[n1]=INT_MAX;
    R[n2]=INT_MAX;
    int i=0,j=0;
    for (int k=low;k<=high;k++){
        if (L[i]<=R[j]){
            arr[k]=L[i++];
        }else{
            arr[k]=R[j++];
        }
    }

}
void mergesort(int arr[],int low,int high){
    if (low<high){
        int mid=low+(high-low)/2;
        mergesort(arr,low,mid);
        mergesort(arr,mid+1,high);
        merge(arr,low,high,mid);
    }
}
int main(){
    int n,arr[100];
    printf("Enter the number of elements need to be entered: ");
    scanf("%d",&n);
    printf("Enter the elements:\n");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int low=0;
    int high=n-1;
   // int mid=(low+high)/2;
    mergesort(arr,low,high);
    printf("The sorted array is :");
    for(int i=low;i<=high;i++)
    printf("%d ",arr[i]);
    return 0;
}
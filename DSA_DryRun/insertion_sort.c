#include <stdio.h>
void insertionsort(int arr[],int n){
    for (int i=1;i<n;i++){
        int temp=arr[i];
        int j=i-1;
           while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
           }
           arr[j+1]=temp;
        }    
}
int main(){
    int n,arr[10];
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    printf("Enter 10 elements: \n");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
insertionsort(arr,n);
for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
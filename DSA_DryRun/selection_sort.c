#include <stdio.h>
void selectionsort(int arr[],int n){
    for (int i=0;i<n;i++){
        int p=i;
        for (int j=i+1;j<n;j++){
            
            if(arr[j]<arr[p]){
                p=j;
            }
        }
        if (p!=i){
        int temp=arr[i];
        arr[i]=arr[p];
        arr[p]=temp;
    }   
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
selectionsort(arr,n);
for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
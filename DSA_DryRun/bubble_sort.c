#include <stdio.h>
void bubble(int arr[],int n){
     
    for (int i=0;i<n;i++){
        int flag=0;
        for (int j=0;j<n-i-1;j++){
            if (arr[j+1]>arr[j]){
            int temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
            flag=1;
        }
    }
    if (flag==0)
    return ;
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
bubble(arr,n);
for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
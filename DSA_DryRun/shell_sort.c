#include <stdio.h>
void shell(int arr[],int n){
    for (int gap=n/2;gap>0;gap=gap/2){
        for (int i=gap;i<n;i++){
            if(arr[i]<arr[i-gap]){
                int temp=arr[i-gap];
                arr[i-gap]=arr[i];
                arr[i]=temp;
            }
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
shell(arr,n);
for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
}
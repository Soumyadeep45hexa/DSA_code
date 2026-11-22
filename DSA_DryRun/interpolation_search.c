#include <stdio.h>
void interpolationsearch(int arr[],int low,int high,int n){
    if (low<high){
        int pos=low+((n-arr[low])/arr[high]-arr[low])*(high-low);
        if(arr[pos]!=n){
            interpolationsearch(arr,low,high-1,n);
        }else{
            printf("The key %d is present \n",n);
        }
    }else{
        printf("The key is not present\n");
    }
}
int main(){
    int arr[10],n,key;
    printf("Enter the number of elements : ");
    scanf("%d",&n);
    printf("Enter the elements\n ");
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int low=0;
    int high=n-1;
    printf("Enter  the key to searched: ");
    scanf("%d",&key);
   interpolationsearch(arr,low,high,key);
    return 0;
}
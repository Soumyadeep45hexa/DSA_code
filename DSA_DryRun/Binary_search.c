#include <stdio.h>
void Bsearch(int arr[],int low,int high,int key){
    if (low<=high){ 
int mid=(low+high)/2;
 if (arr[mid]==key){
    printf("The key %d is present at %d",key,mid);
 }else if (arr[mid]<key){
    
    Bsearch(arr,mid+1,high,key);
}else if(arr[mid]>key)
{
  
    Bsearch(arr,low,mid-1,key);
}
}else {printf("The key is not present\n"); return;}
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
    Bsearch(arr,low,high,key);
    return 0;
}



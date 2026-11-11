#include <stdio.h>
int rev(int arr[],int s){
int l=0,r=s-1;
while (l<r)
{
    int temp=arr[l];
    arr[l]=arr[r];
    arr[r]=temp;/* code */
    l++;
    r--;
}
for (int j=0;j<s;j++){
    printf("%d ",arr[j]);
}
return 0;
}

int main(){
    int a[10];
    int size;
    printf("The total size of the arr will :");
    scanf("%d",&size);
   printf("The enter the  elements: ");
   for (int i=0;i<size;i++){
    scanf("%d",&a[i]);
   }
   
   rev(a,size);
 return 0;
}
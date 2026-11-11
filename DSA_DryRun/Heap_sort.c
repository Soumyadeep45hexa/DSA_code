#include <stdio.h>

void swap(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
void heapify(int i,int arr[],int n){
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(largest, arr, n);
    }
} 
void heapsort(int arr[],int n){
    for (int i=n/2-1;i>=0;i--){
       heapify(i, arr, n);
    }
    for (int end=n-1;end>0;end--){
        swap(&arr[0],&arr[end]);
        heapify(0,arr,end);
        }
}
int main(){
    int n;
    printf("Enter the number of keys need to be entered: ");
    scanf("%d",&n);
    int arr[n];
    for (int i=0;i<n;i++)
        scanf("%d",&arr[i]);
    heapsort(arr,n);
for (int i=0;i<n;i++){
    printf("%d ",arr[i]);
}
return 0;
}

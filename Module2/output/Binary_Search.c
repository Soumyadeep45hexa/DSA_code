// ========================================Binary Sort================================================
//#include <stdio.h>
// void binarySearch(int num,int arr[],int size){

// int right=size-1;
// int left=0;
// int mid=(left+right)/2;
// while (left<=right){
//     if (num>arr[mid]) left =mid+1;
//     else if (num<arr[mid]) right =mid-1;
//     else{ printf("The required number: %d is in %dth index ",num,mid);
//     return; }
//     mid=(left + right)/2;

// }
// printf("Not found integer \n");
// }
// int main(){
//     int arr[100],ele;
//     printf("Enter the number the element to enter : ");
//     scanf("%d",&ele);
//     printf("Enter the elements: ");
//     for (int i=0;i<ele;i++){
//         scanf("%d",&arr[i]);
//     }
//     int num;
//     printf("Enter the number too search: ");
//     scanf("%d",&num);
//     binarySearch(num,arr,ele);
//     return 0;
// }
//===========================Insertion Sort==================================
// #include <stdio.h>
// void insertionSort(int arr[],int size){
//     for (int i=1;i<size;i++){
//         int temp=arr[i];
//         int j=i-1;
//         while(j>=0 && arr[j]>temp){
//             arr[j+1]=arr[j];
//             j--;
//         }
//         arr[j+1]=temp;
//     }
// }
// int main(){
//     int arr[100],ele;
//     printf("Enter the number the element to enter : ");
//     scanf("%d",&ele);
//     printf("Enter the elements: ");
//     for (int i=0;i<ele;i++){
//         scanf("%d",&arr[i]);
//     }
//     insertionSort(arr,ele);
//     for (int i=0;i<ele;i++){
//         printf("%d ",arr[i]);
//     }
//     return 0;
// }
//====================Selection Sort=====================
#include <stdio.h>
void selectionSort(int arr[],int size){
    int j=0;
    while(j<=size-1){
        int min=arr[j];
        int ind;
        for (int i=j;i<size;i++){
            if (min>arr[i]){ min =arr[i];
            ind=i;}
        }
        int temp=arr[j];
        arr[j]=arr[ind];
       arr[ind]=temp;
        j++;
    }
}
int main(){
    int arr[100],ele;
    printf("Enter the number the element to enter : ");
    scanf("%d",&ele);
    printf("Enter the elements: ");
    for (int i=0;i<ele;i++){
        scanf("%d",&arr[i]);
    }
    selectionSort(arr,ele);
    for (int i=0;i<ele;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}
// 
 #include <stdio.h>
// #include <math.h>
// int main(){
//     int num;
//     printf("Enter the number : ");
//     scanf("%d",&num);
//     int count=0;
//     int flag=1;
//     while (1)
//     {
//         int p=num+1;
//         for (int i=2;i< sqrt(p);i++){
//             if (p%i==0){
//                 flag=0;
//                 break;
//             }
//         }
//         if (flag){
//             count++;
//             printf("%d ",p);
//         }
//         flag=1;
//         num=p;
//     if (count==5){
//         break;
//     }
// }
//     return 0;
// }
// code 2
// int main(){
//     int arr[]={500,200,100,50,20,10,5,2,1};
//     int a=sizeof(arr)/sizeof(arr[0]);
//     int mon;
//     printf("Enter the value of the money: ");
//     scanf("%d",&mon);
//     for (int i=0;i<a;i++){
//         if (mon>=arr[i]){
//             int n=mon/arr[i];
//             printf(" %d no of %d notes/coins are needed\n",n,arr[i]);
//             mon=mon%arr[i];
//         }
//     }
//     return 0;
// }
//code 3
// int main(){
//     int row;
//     printf("Enter the number of rows :  ");
//     scanf("%d",&row);
//     int h= (row/2)+1;
//     for (int i=1;i<=h;i++){
//         for (int j=h;j>i;j--){
//             printf(" "); 
//         }
//         for (int k=1;k<=(2*i-1);k++){
//             printf("*");
//         }
//         printf("\n");
//     }
//     for(int i=h-1;i>0;i--){
//         for (int k=i;k<h;k++){
//             printf(" ");
//         }
//         for(int j=(2*i-1);j>0;j--){
//             printf("*");
//         }
//         printf("\n");
//     }
//     return 0;
// }
//code 4
// int max(int *arr,int size){
//     int max=arr[0];
//     for (int i=0;i<size;i++){
//         if(arr[i]>max){
//             max=arr[i];
//         }
//     }
//     return max;
// }
// int min(int *arr,int size){
//     int min=arr[0];
//     for (int i=0;i<size;i++){
//         if(arr[i]<min){
//             min=arr[i];
//         }
//     }
//     return min;
// }
// int main(){
//    int a[]={23,45,67,43,56};
//     int s=sizeof(a)/sizeof(a[0]);
//     printf("Maximum value of the array: %d\n",max(a,s));
//     printf("Minimum value of the array: %d\n",min(a,s));
//     return 0;
// }
// code 5

// int main(){
//     int no,arr[20];
//     printf("Enter the number of students :");
//     scanf("%d",&no);
//     for (int i=0;i<no;i++){
//         char name[20];
//         printf("Enter the name: ");
//         scanf("%s",name);
//         int m1,m2,m3;
//         printf("Enter the 3 subject marks: ");
//         scanf("%d %d %d",&m1,&m2,&m3);
//         int avg =(m1+m2+m3)/3;
//             arr[i]=avg;
           
//     }
//     for (int i=0;i<no-1;i++){
//          for (int j=0;j<(no-i-1);j++){
//                 if(arr[j]<arr[j+1]){
//                     int temp=arr[j];
//                     arr[j]=arr[j+1];
//                     arr[j+1]=temp;
//                 }
//             }
       
// }
// printf(" is the topper with a percentage of %dprec",arr[no-1]);
//    return 0;
// }

//code 6
# include <stdlib.h>
int *maxprofit(int *a){
    int mi=a[0],ma=a[0],p=0,pi=0;
    int f=0;
    for (int i=0;i<7;i++){
        if (a[i]<mi){
            mi=a[i];
            f=1;
        }
        if (f!=0){
            p=i+1;            //min amount closing day
        }
        f=0;
    }
    int f1=0;
    for (int i=0;i<7;i++){
        if (a[i]>ma){
            ma=a[i];
            f1=1;
        }
        if (f1!=0){
            pi=i+1;       //max amount closing day
        }
        f1=0;
    }
    if (p>pi){
        printf("No profit \n");
    }else{
        printf("Buy on: %d\n",p);
        printf("Sell on: %d\n",pi);
        printf("Total profit is : %d\n",ma-mi);
    }
    return 0;
}
int main(){
    int *arr;
    printf("Closing stocks: \n");
    arr=(int *)malloc(7*sizeof(int));
    for (int i=0;i<7;i++){
        scanf("%d",(arr+i));
    }
    maxprofit(arr);
free (arr);
 }
// code 7
// int cnt(int x){
//     static int count=0;
//     count+=x;
//     printf("%d\n",count);
// }
// int main(){
//     int x=9;
//     cnt(x);
//     cnt(x);
//     cnt(x);
//     return 0;
// }
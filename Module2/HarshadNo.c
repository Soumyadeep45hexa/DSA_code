#include <stdio.h>
int main(){
int num,k=0;
printf("Enter the Number : ");
scanf("%d",&num);
int dup=num;
while(num){
    int p=num%10;
     k += p;
    num/=10;
}
if (dup%k==0){
    printf("The Number %d is a Harshad Number",dup);
}else{
    printf("The Number %d is not a Harshad Number",dup);
}
}
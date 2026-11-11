#include <stdio.h>
int pal(){
    int num;
    printf("Enter the Number :");
    scanf("%d",&num);
    int dup=num;
    int res;
    while(num){
        int s=num%10;
        num=num/10;
         res=s*10+num;
    }
    if (dup==res){
    printf("The number is a pallindrome");
    }
    else{
    printf("The Number is not a pallindrome");
    }
 return 0;
}
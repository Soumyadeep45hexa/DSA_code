#include <stdio.h>
#include <math.h>
int main(){
    int num,digit=0,square,divisor;
    
    printf("Enter the Number :");
    scanf("%d",&num);
    int dup=num;
    square =num * num;
    while(num)
    {digit++;
        num=num/10;
    }
    divisor=pow(10,digit);
if (square % divisor==dup){
    printf("The Number %d is a Automorphic Number:",dup);
}else{
    printf("The Number %d is not a Automorphic Number",dup);
}
return 0;
}
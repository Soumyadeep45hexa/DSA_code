#include <stdio.h>
#include <math.h>
int fact( int p){
    int f=1;
    for (int i=1;i<=p;i++){
         f=i*f;
        
    }
    return f;
}
int main(){
int n, x;
float sum=0.0;

printf("Enter the value of x:");
scanf("%d",&x);
for (int i=0;i<5;i++){
    printf("Enter the value of n:");
scanf("%d",&n);
    if (n<=10){
        break;
    }else{
        printf("Invalid Value Of n!");
        return 0;
    }
}
if (n>10){
    printf("Too many attempts exiting\n");
    return 0;
}
for(int j=0;j<n;j++){
    sum+=(pow(-1,j)*(fact(x)/(float)fact((2*j)+1)));
   
    
}
 printf("The Summation is: %f",sum);
return 0;
    
} 


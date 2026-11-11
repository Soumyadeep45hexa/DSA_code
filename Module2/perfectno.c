#include <stdio.h>
int main(){
    int nu,sum=0;
    printf("Enter the Nmber:");
    scanf("%d",&nu);
    if(nu>0){
    for (int i=1;i<nu;i++){
        if(nu % i==0){
        sum+=i;
    }
    }
    if (sum==nu){
        printf("The number %d is a perfect number\n",nu);
    }else{
        printf("The number %d is not a perfect number\n",nu);
    }
}else{
    printf("Invalid_Input\n");
}
return 0;
}
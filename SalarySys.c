#include <stdio.h>
int main(){
    float Bas,TI;
    float TF;
    printf("The basic Salary :  ");
    scanf("%f",&Bas);
    float HRA=0.2*Bas, DA=Bas*0.5;
    TI=Bas+HRA+DA;
    printf("In-Hand excluding tax: %.3f \n",TI);
    if (TI<=250000){
        printf("NO Tax Applicable\n");
    }else if (TI<=500000){
        TF=(TI-250000)*0.05;
    }else if(TI>500000 && TI<=1000000){
        TF=(250000*0.05)+((TI-500000)*0.2);
    }else{
        TF=(250000*0.05)+(500000*0.2)+((TI-1000000)*0.3);   
    }
    printf("Total Payable Tax : %.2f \n",TF);
    float ref= TI-TF;
    printf("The IN-HAND After the tax is payed : %.3f",ref);
    return 0;
}

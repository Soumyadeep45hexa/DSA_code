#include <stdio.h>
int fact(){
    int result =1,num;
    printf("Enter the number : ");
    scanf("%d",&num);
    for (int i=1;i<=num;i++){
        result*=i;
    }
    printf("The Result is : %d\n",result);
return 0;
}
int prime(){
    int num,count=0;
    printf("Enter the number: ");
    scanf("%d",&num);
    for (int i=1;i<=num;i++){
        if (num%i==0)
            count++;
    }
    if (count>2){
        printf("The Number is not a Prime Number\n");
    }
    else{
        printf("The Number is  Prime Number\n");
    }
    return 0;
}
int pal(){
    int num;
    printf("Enter the Number :");
    scanf("%d",&num);
    int dup=num;
    int res=0;
    while(num){
        int s=num%10;
         res=res*10+s;
        num=num/10;
        
    }
    if (dup==res){
    printf("The number is a pallindrome\n");
    }
    else{
    printf("The Number is not a pallindrome\n");
    }
 return 0;
}
int main(){
 int choice;
 while(1){
    printf("1: Factorial Compute\n" );
    printf("2: Prime Check\n" );
    printf("1: Pallindrome Check \n" );
    printf("Enter the Choice (1-4) : ");
    scanf("%d",&choice);
     
    switch (choice)
    {
    case 1:
        fact();
        break;
    case 2:
        prime();
        break;
    case 3:
        pal();
        break;
    case 4:
    printf("ThankYou  For Coming \n");
    return 0;
    default:
    printf("Enter Valid choice 1-4\n");
        break;
    }
 }
 
  return 0;
}

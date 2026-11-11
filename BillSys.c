#include <stdio.h>
int main(){
    int Item, TC, price ,qty;
    float PA;
    TC=0;
    printf("Enter the number of Items:");
    scanf("%d",&Item);
    while (Item>0)
    {
      printf("Enter the Price: ") ;
      scanf("%d",&price);
      printf("Quantity:");
      scanf("%d",&qty);
      TC=TC+(price*qty);
      Item--;
    }
   printf("Total Cost: %d\n",TC);
   if (TC>2000){
    PA=TC-(TC*0.2);
    printf("Congratulation!! ***  You are eligible for  the exclusive discount *** \n");
    printf("Payable Amount: %f",PA);
   }else{
    printf("Payable Amount: %d",TC);
   }
   return 0;
}
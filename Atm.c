#include <stdio.h>
#include <string.h> 
int main(){
    int blnc, Amt;
    blnc=1200;
     char history[50][100]; 
    int Choice ;
    int count=0;
    long pin=94777885,pin_user;
for (int i=0;i<5;i++){                                 //Up to 5 Attempts are permitted 
    printf("Pls Enter the 8-Digit PIN:  ");
     scanf("%ld",&pin_user);
     
   if (pin==pin_user){
    
                                   printf("\n================================\n");
                                   printf("      ACCESS GRANTED! Welcome!       \n");
                                   printf("================================\n");
    while(1){
    printf("----------------------------Welcome To Your Virtual ATM-----------------------------\n");
    printf("1: Check Balance \n");
    printf("2: Deposit Money \n");
    printf("3: Withdraw Money \n");
    printf("4: Transfer Funds \n");
    printf("5: Check Transaction History \n");
    printf("6: Exit \n");
    
    printf("Enter Your Choice: ");
    scanf("%d",&Choice);
     
    switch (Choice)
    {
    case 1:
    printf("The Present Bank Balance: %d\n",blnc);                              //Checking Bank Balance
       break;

    case 2:
       
            printf("Enter Amount to be Deposited: ");                           // depostition process
            scanf("%d",&Amt);
             if (Amt>0){
            blnc+=Amt;
            printf("Successful Depossit!!...\n");
             sprintf(history[count++],
                            "Deposited: %d | Balance: %d", Amt, blnc);
             }else{
             printf("Invalid Amount\n");
            }
            break;


    case 3:
         printf("Enter Amount to be Withdraw:  ");                             // withdrawal process
              scanf("%d",&Amt);
               if (Amt>0 && blnc>=Amt){
              blnc-=Amt;
            printf("Successful Withdrawal!!...\n");
             sprintf(history[count++],
                            "Withdrawn: %d | Balance: %d", Amt, blnc);
               }else if(Amt>blnc){
                printf("Insufficient Fund Present\n");
               }else{
                    printf("Invalid_Input\n");
               }
               break;
     case 4:
      printf("Enter Amount to be Transferred :  ");
      long acc;                                                                 // Transfering Funds process
              scanf("%d",&Amt);
               if (Amt>0 && blnc>=Amt){
              blnc-=Amt;
              printf("Transfer Money to Account no: ");
                       scanf("%ld",&acc);
            printf("Successful Transfer!!...\n");
             sprintf(history[count++],
                            "Transferred: %d to Acc: %ld | Balance: %d", Amt,acc, blnc);
               }else if(Amt>blnc){
                printf("Insufficient Fund Present\n");
               }else{
                    printf("Invalid_Input\n");
               }
               break;
     case 5:
                        printf("\n--- Transaction History ---\n");
                        if (count == 0) {
                            printf("No transactions yet!\n");                   //Check Transaction History
                        } else {
                            for (int j = 0; j < count; j++)
                                printf("%d. %s\n", j + 1, history[j]);
                        }
                        break;

    case 6:
    printf("ThankYou  For Coming ");
    return 0;
     default :
       printf("Invalid_Input pls choose between (1-4)\n");
    }
    }
}else{
     printf("INVALID_PIN\n");
}
     }
     if (pin!=pin_user){
          printf("****The No Of Atempts exceeded the Limit the account is locked****\n ");
          return 0;
     }
    return 0;
}
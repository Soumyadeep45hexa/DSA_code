#include <stdio.h>
#include <string.h>

int main(){
   int mainChoice;

   float totalRevenue = 0;
   int totalCustomers = 0;
   int BkeCnt=0, BusCnt=0, CyCnt=0, CarCnt=0, NV;

   while (1)
   {
      printf("1.CustomerSide\n");
      printf("2.AdminSide\n");
      printf("3.Exit\n");

      printf("Enter the MainChoice: ");
      scanf("%d",&mainChoice);

      if (mainChoice==1){
         int Hr,fare, choise,D_N;

         while (1){
            printf("----------------------Welcome Parking Station----------------------\n");
            printf("1: Bike/Scooter Parking\n");
            printf("2: Car Parking\n");
            printf("3: Bus/Truck Parking\n");
            printf("4: Cycle Parking\n");
            printf("5: Exit\n");

            printf("Enter the Hour: ");
            scanf("%d",&Hr);

            int penalty = 0;
            if(Hr > 10){
                penalty = (Hr-10)*100;
            }

            printf("Enter The Choice(1-5): ");
            scanf("%d",&choise);

            printf("Enter number of vehicles: ");
            scanf("%d",&NV);

            printf("Day-1 or Night-2: ");
            scanf("%d",&D_N);

            switch (D_N)
            {
            case 1:
                switch (choise)
                {
                case 1:
                    fare = (Hr<=10) ? Hr*10 : Hr*10+penalty;
                    BkeCnt+=NV;
                    break;
                case 2:
                    fare = (Hr<=10) ? Hr*20 : Hr*20+penalty;
                    CarCnt+=NV;
                    break;
                case 3:
                    fare = (Hr<=10) ? Hr*50 : Hr*50+penalty;
                    BusCnt+=NV;
                    break;
                case 4:
                    fare = (Hr<=10) ? Hr*5 : Hr*5+penalty;
                    CyCnt+=NV;
                    break;
                case 5:
                    return 0;
                default:
                    printf("Invalid Choice\n");
                    continue;
                }
                break;

            case 2:
                switch (choise)
                {
                case 1:
                    fare = (Hr<=10) ? Hr*15 : Hr*15+penalty;
                    BkeCnt+=NV;
                    break;
                case 2:
                    fare = (Hr<=10) ? Hr*30 : Hr*30+penalty;
                    CarCnt+=NV;
                    break;
                case 3:
                    fare = (Hr<=10) ? Hr*70 : Hr*70+penalty;
                    BusCnt+=NV;
                    break;
                case 4:
                    fare = (Hr<=10) ? Hr*8 : Hr*8+penalty;
                    CyCnt+=NV;
                    break;
                case 5:
                    return 0;
                default:
                    printf("Invalid Choice\n");
                    continue;
                }
                break;

            default:
                printf("Invalid Day/Night Choice\n");
                continue;
            }

            int totalFare = NV * fare;

            if(totalFare >= 500){
                printf("Eligible for Discount\n");
                float dis = totalFare - (totalFare * 0.20);

                printf("Initial Fare: %d\n", totalFare);
                printf("Discounted Fare: %.2f\n", dis);

                totalRevenue += dis;  
            }else{
                printf("Fare to be paid: %d\n", totalFare);
                totalRevenue += totalFare;
            }

            printf("Penalty: %d\n", penalty);

            totalCustomers += 1;  // unchanged as you asked
            break;
         }

      }else if (mainChoice==2){

         char pass[10];
         printf("Enter Password: ");
         scanf("%9s", pass); 

         if (strcmp(pass, "admin123") == 0){
            printf("\n----- ADMIN DASHBOARD -----\n");
            printf("Total Revenue: %.2f\n", totalRevenue);
            printf("Total Customers: %d\n", totalCustomers);

            printf("Vehicle Count:\n");
            printf("Bike/Scooty: %d\n", BkeCnt);
            printf("Car: %d\n", CarCnt);
            printf("Bus/Truck: %d\n", BusCnt);
            printf("Cycle: %d\n", CyCnt);
         }else{
            printf("Invalid Password\n");
         }

      }else if(mainChoice==3){
         return 0;
      }else{
         printf("Wrong choice\n");
      }
   }
   return 0;
}
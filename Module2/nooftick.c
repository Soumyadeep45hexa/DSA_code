#include <stdio.h>
int main(){
//      int i=0;
//         int j=1;
//         int k=0;
//     do {
      
//         k+=i+j;
//         printf("%d ",k);
//           i++;
//         j-=2;
//         k=0;
//     }while(i<10 && j>-20);
        
//         return 0;
//     }

// // #include <stdio.h>
// //  int main(){
// //     for (int i=0,j=1,k=0;i<10 && i>-20;i++,j-=2,k=0){
// //         k+=i+j;
// //         printf("%d ",k);
// //     }
// //     return 0;
// // }

//     int arr[3][3]={{34,56,54},
//             {32,67,89},
//             {90,32,21}};
//             int sum1=0;
//             int sum2=0;
//     for (int i=0;i<3;i++){
//         for (int j=0;j<3;j++){
//             sum1+=arr[i][j];
//             sum2+=arr[j][i];
            
//         }
//         printf("Summation of row %d is %d\n",i+1,sum1);
//         printf("Summation of column %d is %d\n",i+1,sum2);
//         sum1=0;
//         sum2=0;
    
//     }return 0;
// }
int ra,ca,arra[10][10],rb,cb,arrb[10][10],sum=0;
printf("Enter rowa: ");
scanf("%d",&ra);
printf("Enter Columna: ");
scanf("%d",&ca);
printf("Enter row b: ");
scanf("%d",&rb);
printf("Enter Column b: ");
scanf("%d",&cb);
printf("pls enter the value of matrix 1");
    for (int j=0;j<ra;j++){
        for (int k=0;k<ca;k++){
            scanf("%d",&arra[j][k]);
        }
    }
printf("pls enter the value of matrix 2");
    for (int j=0;j<rb;j++){
        for (int k=0;k<cb;k++){
            scanf("%d",&arrb[j][k]);
        }
    }
    int rslt[10][10];
    for (int i=0;i<ra;i++){
        for (int k=0;k<cb;k++){
           for (int j=0;j<rb;j++){
             sum+=arra[i][j] * arrb[j][k];
           }
           rslt[i][k] = sum;
           sum=0;
        }
    }
    for (int i=0;i<ra;i++){
        for (int k=0;k<cb;k++){
            printf("%d ",rslt[i][k]);
        }
        printf("\n");
    }
return 0;
}

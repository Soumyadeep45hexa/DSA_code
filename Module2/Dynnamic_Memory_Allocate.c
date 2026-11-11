#include <stdio.h>
#include <stdlib.h>


int main(){
    int **arr1,r1,c1,**arr2,r2,c2,**res;
    printf("Enter the number of r1,c1: ");
    scanf("%d,%d",&r1,&c1);
    printf("Enter the number of r2,c2: ");
    scanf("%d,%d",&r2,&c2);
     arr1 = (int **)malloc(r1 * sizeof(int *));
    arr2 = (int **)malloc(r2 * sizeof(int *));
    res  = (int **)malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) arr1[i] = (int *)malloc(c1 * sizeof(int));
    for (int i = 0; i < r2; i++) arr2[i] = (int *)malloc(c2 * sizeof(int));
    for (int i = 0; i < r1; i++) res[i]  = (int *)calloc(c2, sizeof(int));
    for(int i=0;i<r1;i++){
        for (int j=0;j<c1;j++){
        scanf("%d",&arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
    for(int i=0;i<r2;i++){
        for (int j=0;j<c2;j++){
        scanf("%d",&arr2[i][j]);
        }
        printf("\n");
    }
    for (int i=0;i<r1;i++){
    for(int j=0;j<c2;j++){
        res[i][j]=0;
        for (int k=0;k<c1;k++){
           res[i][j]+=(arr1[i][k] * arr2[k][j]);
        }
    }
}
    printf("The array is : ");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
        printf("%d ",res[i][j]);
    }
   printf("\n");
}
for (int i = 0; i < r1; i++){
    free(arr1[i]);}
  for (int i = 0; i < r2; i++){
    free(arr2[i]);}
    for (int i = 0; i < r1; i++){
    free(res[i]);}
return  0;
}
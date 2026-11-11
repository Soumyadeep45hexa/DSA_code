#include <stdio.h>
#include <stdlib.h>
int main(){
    int row,col;
    printf("Enter the Number of row: ");
    scanf("%d",&row);
    printf("Enter the Number of column: ");
    scanf("%d",&col);
    int **mat=(int **)malloc(row*sizeof(int *));
    for (int i=0;i<row;i++){
        mat[i]=(int *)malloc(col*sizeof(int));
    }
    // for (int i=0;i<row;i++){
    //     for (int j=0;j<col;j++){
            
    //     }
    // }
    int flag=0;
    int flag1=0;
    int final=0;
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            scanf("%d",&mat[i][j]);
            if(i==j){
                if (mat[i][j]!=0){
                    flag=1;
                    if(mat[i][j]==1){
                        flag1=1;
                    }else{
                        flag1=0;
                    }
                }
            }else{
                if (mat[i][j]==0){
                    flag=1;
                }else{
                    flag=0;
                    printf("The matrix is not a diagonal matrix");
                   return 0;
                }
                
            }
        }
        if (flag1==0)
        final=1;
    }
    if (flag==1 && final==1){
        printf("The matrix is diagonal matrixt but not identity matrix\n");
    }else if(flag==1 && final==0){
        printf("The matrix is identity matrix\n");
    }
    //------free the matrix-----
    for (int i=0;i<row ;i++){ free(mat[i]);
    }free (mat);
    
    return 0;
}
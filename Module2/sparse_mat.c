#include <stdio.h>
#include <stdlib.h>
struct sparse{
    int row;
    int col;
    int value;

};
int main(){
    int row,col,nz=0,zero=0;
    printf("Enter the value of the row:");
    scanf("%d",&row);
    printf("Enter the value of the column:");
    scanf("%d",&col);
   
    //initializing
    int **a=(int **)malloc(row*sizeof(int *));
    for (int i=0;i<row;i++){
        a[i]=(int *)malloc(col*sizeof(int ));
    }
    //enter the data
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            scanf("%d",&a[i][j]);
            if(a[i][j]!=0){
            nz++;
           }else{
            zero++;
           }
        }
    }
     struct sparse s[nz+1];

    s[0].row=row;
    s[0].col=col;
    s[0].value=nz;
    int k=1;
    
    //checking for the number of nonzero
    // for (int i=0;i<row;i++){
    //     for (int j=0;j<col;j++){
    //        if(a[i][j]!=0){
    //         nz++;
    //        }else{
    //         zero++;
    //        }
    //     }
    // }
    if (zero<nz){
        printf("The entered matrix is not a sparse matrix\n");
    }else{
        for (int i=0;i<row;i++){
            for (int j=0;j<col;j++){
                if (a[i][j]!=0){
                    
                    s[k].row=i;
                    s[k].col=j;
                    s[k].value=a[i][j];
                    k++;
                    }
            }
        }
        for (int i=0;i<=nz;i++){
            
                    printf("%d\t%d\t%d\n",
                    s[i].row,
                    s[i].col,
                    s[i].value);
                    
                    }
            
        
    }
    return 0;
}
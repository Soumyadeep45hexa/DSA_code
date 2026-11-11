#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Create the random matrix 
void createRandomMatrix(const char *filename,int row,int col,int minVal,int maxVal){
    FILE *fp=fopen(filename,"w");
    fprintf(fp,"%d %d\n",row,col);
    for(int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            int value = minVal+rand()%(maxVal-minVal+1);
            fprintf(fp,"%d ",value);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    printf("The matrix is saved \n");
} 
// Perform the task
int matrixMultiply(const char *file1,const char *file2,const char *outfile){
    FILE *fp1=fopen(file1,"r");
    FILE *fp2=fopen(file2,"r");
    if ((fp1==NULL)||(fp2==NULL)){
        printf("The files are empty pls insert the data before performing the task\n");
        exit(1);
        }
        int r1,r2,c1,c2;
        fscanf(fp1,"%d %d\n",&r1,&c1);
        fscanf(fp2,"%d %d\n",&r2,&c2);

        // allocate matrix 1
        int **mat1=(int **)malloc(r1*sizeof(int *));
        for(int i=0;i<r1;i++){
            mat1[i]=(int *)malloc(c1*sizeof(int ));
        }
        // allocate matrix 2
        int **mat2=(int **)malloc(r2*sizeof(int *));
        for(int i=0;i<r2;i++){
            mat2[i]=(int *)malloc(c2*sizeof(int ));
        }
        //scanning data from files1
        for (int i=0;i<r1;i++){
            for (int j=0;j<c1;j++){
               fscanf(fp1,"%d",&mat1[i][j] );
            }
        }
         //scanning data from files2
        for (int i=0;i<r2;i++){
            for (int j=0;j<c2;j++){
                fscanf(fp2,"%d",&mat2[i][j] );
            }
        }
        //allocating  result matrix
        int ** res=(int **)malloc(r1*sizeof(int *));
            for (int i=0;i<r1;i++){
                res[i]=(int *)malloc(c2*sizeof(int ));
            }
        // Performing Multiplication
        for  (int i=0;i<r1;i++){
            for (int j=0;j<c2;j++){
                int sum=0;
                for (int k=0;k<c1;k++){
                    sum+=mat1[i][k]*mat2[k][j];
                }
                res[i][j]=sum;
            }
        }
        //putting the result in the file
        FILE *fpout=fopen(outfile,"w");
        if (fpout==NULL){
            printf("The files are empty pls insert the data before performing the task\n");
        exit(1);
        }
        for (int i=0;i<r1;i++){
            for(int j=0;j<c2;j++){
                fprintf(fpout,"%d ",res[i][j]);
            }
            fprintf(fpout,"\n");
        }
        fclose(fp1);
        fclose(fp2);
        fclose(fpout);
        //free the allocation
        for  (int i=0;i<r1;i++) free(mat1[i]);
        free(mat1);
         for  (int i=0;i<r2;i++) free(mat2[1]);
        free(mat2);
         for  (int i=0;i<r1;i++) free(res[i]);
        free(res);
 return 1;
}
int main(int argc,char *argv[]){
    if (argc!=4){
        printf("Usage: %s <file1> <file2> <file3> ",argv[0]);
    }
    const char *file1=argv[1];
    const char *file2=argv[2];
    const char *outfile=argv[3];

    srand((unsigned int )time(NULL));

    int row1,row2,col1,col2,minVal,maxVal;
    printf("Enter the value of number Rows  and Columns of Matrix1: ");
    scanf("%d %d",&row1,&col1);
    printf("Enter the value of number Rows  and Columns of Matrix2: ");
    scanf("%d %d",&row2,&col2);

    if (col1!=row2){
        printf("INVALID_Input enter the value of col1 and row2\n");
        return 0;
    }

    printf("Enter the value of number MIN and MAX: ");
    scanf("%d %d",&minVal,&maxVal);
    createRandomMatrix(file1,row1,col1,minVal,maxVal);
    createRandomMatrix(file2,row2,col2,minVal,maxVal);
    matrixMultiply(file1,file2,outfile);

}
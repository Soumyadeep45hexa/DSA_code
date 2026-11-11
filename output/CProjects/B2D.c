#include <stdio.h>
// struct data
// {
//    char name[20];
//    int run;
//    int nob;
//    float sr; /* data */
// };
// int main(){
//     struct data d[10];
//     int n;
//     FILE *fp;
//     fp=fopen("Directory.txt","w");
//     printf("Enter the Number of Batsman data to be enterred: ");
//     scanf("%d",&n);
//     for(int i=0;i<n;i++){
//         printf("Enter the name of Batsman: ");
//         scanf("%s",d[i].name);
//         printf("Enter the Score of the Batsman: ");
//         scanf("%d",&d[i].run);
//         printf("Enter the Number of ball bowled: ");
//         scanf("%d",&d[i].nob);
// d[i].sr=(d[i].run/d[i].nob)*100;
//         fprintf(fp,"%s\t%d\t%d\t%.2f\n\n",d[i].name,d[i].run,d[i].nob,d[i].sr);
//     }
// fclose(fp);
// return 0;
// }
//                        Program 2
// struct raindata
// {
//     char cname[30];
//     float amtrain;
// };
// int main(){
//     struct raindata rd,hrd,mrd;
    
//     FILE *in,*out;
//     in=fopen("myfile.txt","r");

//     if (fscanf(in, "%s %f", rd.cname, &rd.amtrain) != EOF)
//     {
//         hrd = rd;
//         mrd = rd;
//     }
    
//     while (fscanf(in,"%s %f",rd.cname,&rd.amtrain)!=EOF)
//     {   
        
//         if (rd.amtrain>hrd.amtrain){
//         hrd=rd;}
//         if (rd.amtrain<mrd.amtrain){
//         mrd=rd;
//         }
//     }
//     fclose(in);
//     out=fopen("Outfile.txt","w");
//     fprintf(out,"Name of the Higest rainfall city: %s\t Rainfall measured: %.2fcm\n\n",hrd.cname,hrd.amtrain);
//     fprintf(out,"Name of the Lowest rainfall city: %s\t Rainfall measured: %.2fcm\n\n",mrd.cname,mrd.amtrain);
//     fclose(out);
//     return 0;
// }
//                      Program 3
// int main(){
//     int m;
//     printf("Enter the amount: ");
//     scanf("%d",&m);
//     int arr[]={500,200,100,50,20,10,5,2,1};
//     int size=sizeof(arr)/sizeof(arr[0]);
//     for (int i=0;i<size;i++){
//         int n=m/arr[i];
//         if (n>0){
//             printf(" The %d notes are: %d",arr[i],n);
//         }
//         m%=arr[i];
//     }
// return 0;
// }
//                      Program 4
// int main(){
//     int row;
//     printf("Enter the row: ");
//     scanf("%d",&row);
//     for (int i=0;i<row;i++){
//         for (int k=row-1;k>i;k--){
//             printf(" ");
//         }
//         for (int j=0;j<(2*i+1);j++){
//             printf("*");
//         }
//         printf("\n");
//     }
//     return 0;
// // }    program 5
// int palindrome(int n){
//     int dup=n;
//     int rev=0;
//     while (n)
//     {
//     int p=n%10;
//     rev=rev*10+p;
//     n=n/10;
//     }
//     if (dup==rev){
//         printf("The Number %d is a pallindrome",dup);
//     }else{
//         printf("The Number %d is a not a pallindrome",dup);
//     }
// return 0;
// }
// int main(){
//     int Number;
//     printf("Enter the Number : ");
//     scanf("%d",&Number);
//     palindrome(Number);
// }
//                      Program 6
// #include <math.h>
// int min(int arr[],int s){
//     int min=arr[0];
//     for (int i=0;i<s;i++){
//         if (arr[i]<min){
//             min=arr[i];
//         }
//     }
//     printf("The mininmum element in the array is: %d",min);
//     return 0;
// }
// int max(int arr[],int s){
//     int max=arr[0];
//     for (int i=0;i<s;i++){
//         if (arr[i]>max){
//             max=arr[i];
//         }
//     }
//     printf("The maximum element in the array is: %d",max);
//     return 0;
// }
// int sd(int arr,int s){
//     int sum=0,diff,ass=0;
//     float res;
//     for (int i=0;i<s;i++){
//         sum+=arr[i];
//     }
//     int mean=sum/s;
//     for (int i=0;i<s;i++){
//         int sq=diff*diff;
//         diff=mean-arr[i];
//         ass+=sq;
// }
// res=pow((ass/s),2);
// printf("The result of Standard Deviation of %d is: %f",res);
// }
// int main(){
//     int arr[]={23,34,56,21,67,89,90};
//     int size=sizeof(arr)/sizeof(arr[0]);
//     min(arr,size);
//     max(arr,size);
//     sd(arr,size);

// return 0;
// }
//              program 7
// #include <string.h>
// int main(){
//     char target[30];
//     char line[20][30];
//     int n;
//     printf("Enter the Number of line be printed");
//     scanf("%d",&n);
//     getchar();
//     for (int i=0;i<n;i++){
//         printf("Enter the line %d",i);
//         fgets(line[i],sizeof(line[i]),stdin);
//         if(target[i]=='\n'){
//             target[i]='\0';
//         }
//     }
//     printf("Enter the target line: ");
//     fgets(target,sizeof(target),stdin);
//     for (int i=0;i<n;i++){
//         printf("The  line with the target string: ");
//         if(strstr(line[i],target)){
//             printf("Line %d : %s",i,line[i]);
//         }
//     }
//     return 0;
    
// }
//              program 8(pascal triangle)
// int main(){
//     int row;
//     printf("Enter the number of rows: ");
//     scanf("%d",&row);
//     //upper half
//     for (int i=0;i<row;i++){
//         for (int k=row-1;k>i;k--){
//             printf(" ");
//         }
//         int num=1;
//         for(int j=0;j<=i;j++){
//             printf("%d ",num);
//             num=num*(i-j)/(j+1);      
//           }
//           printf("\n");
//     }

//     return 0;
// }
//      program 9
// #include <stdlib.h>
// int **generate(int numRows, int* returnSize, int** returnColumnSizes){

//      *returnSize=numRows;
//     *returnColumnSizes=malloc(numRows*sizeof(int));
//     int **triangle=malloc(numRows*sizeof(int *));
//     for (int i=0;i<numRows;i++){
//         (*returnColumnSizes)[i]=i+1;
//         triangle[i]=malloc((i+1)*sizeof(int));
//     for(int j=0;j<=i;j++){
//         if (j==0 || j==i){
//             triangle[i][j]=1;
//         }else{
//             triangle[i][j]=triangle[i-1][j-1]+triangle[i-1][j];
//         }
//     }
// }
// return triangle;
// }
// int main(int argc, char const *argv[])
// {
//     int a=atoi(argv[1]);
//     int returnSize;
//     int *returnColumnSizes;
//     int **triangle=generate(a,&returnSize,&returnColumnSizes);
//     for (int i=0;i<returnSize;i++){
//         for(int k=returnSize-1;k>i;k--){
//             printf(" ");
//         }
//         for (int j=0;j < returnColumnSizes[i];j++){
//         printf("%d ",triangle[i][j]);
//     }
//     printf("\n");
// }
//     return 0;
// }
//              program 10
#include <ctype.h>  
int main(int argc, char *argv[])
{

    if (argc<2){
        printf("Usage %s .Your string here. ",argv[0]);
        return 1;
    }
    char *str=argv[1];
    int digit=0,alpha=0,space=0,others=0;
    for (int i=0;str[i]!='\0';i++){
        if (isdigit(str[i])){
            digit++;
        }else if(isalpha(str[i])){
            alpha++;
        }else if(str[i] == ' '){
            space++;
        }else{
            others++;
        }
    }
    printf("No of spaces:%d",space);
    printf("No of alphas:%d",alpha);
    printf("No of digits:%d",digit);
    printf("Others present: %d",others);

    return 0;
}

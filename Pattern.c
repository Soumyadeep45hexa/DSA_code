#include <stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    int total=2*n-1;
    for(int i=1;i<=total;i++){
        int row=(i<=n)? i:(total-i+1);
        for (int j=1;j<=(n-row);j++){
            printf(" ");


        }
        for (int j=0;j<(row);j++){
            printf("%c",'A'+j);
            
        }
        for (int j=row-2;j>=0;j--){
            printf("%c",'A'+j);
            
        }
        printf("\n");
    }
    return 0;
}
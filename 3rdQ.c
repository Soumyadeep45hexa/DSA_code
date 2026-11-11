#include <stdio.h>
int main(){
    int n;
    scanf("%d",&n);
    for (int i=0;i<n-1;i++){
        for (int j=1;j<=(2*i+1);j++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
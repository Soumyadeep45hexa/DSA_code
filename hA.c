#include <stdio.h>
#include <stdlib.h>   // for rand() and srand()
#include <time.h>     // for the time funnction

int ran(){
    srand(time(NULL));
    int t = 0;
    for (int i = 0; i < 10; i++){
        t = rand() % 10 + 1;            //gives the random output between 1-10
         
    }
    return t;   
}
int main(){
    int num;
    int attempt=5;
    int ml=ran();
    int count=0;
    while (attempt)
    {
        printf("Enter any Number between 1-10: ");
    scanf("%d",&num);
    if (num>10){
    printf("Invalid Input");
    return 0;
    }
    if (num==ml){
        printf("You WON\n");
        count++;
    break;
    }else if(num>(ml)){
        printf("Almost There :Little bit less\n");
        
    }else{
        printf("Almost There :Little bit more\n");
       
        }
        count++;
        attempt--;
    }
        if (num!=ml){
            printf("Number Of Attempts Exceeded\n");
            printf("You lost\n");
            return 0;
        }
    
    printf("No OF Attempts Took: %d",count);
    return 0;
}
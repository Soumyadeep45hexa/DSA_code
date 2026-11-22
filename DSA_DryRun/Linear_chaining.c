#include <stdio.h>
#define m 10
int arr[m];
void insert(){
    int key;
    printf("Enter the key need to be entered: ");
    scanf("%d",&key);
    int index=key%m;
    while(arr[index]!=0){
        index=(index+1)%m;
    }
    arr[index]=key;
}
void display(){
    for (int i=0;i<m;i++){
        if(arr[i]!=0)
        printf("%d->%d\n",i,arr[i]);
        else  printf("%d->NULL\n",i);
    }
}
void search(){
    int key;
    printf("Enter the key need to be searched: ");
    scanf("%d",&key);
    int index=key%m;
   if (arr[index]!=key){
    int def=index;
        index=(index+1)%m;
        while(index!=def){
            if (arr[index]!=key){
                index=(index+1)%m;
            }
            if (arr[index]==key){
                printf("The key %d is at index %d",key,index);
                return ;
            }
        }
        printf("The key %d is not present",key);
   }else{printf("The key %d is at index %d",key,index);}



}
int main(){
    insert();
    insert();
    insert();
    insert();
    insert();
    insert();
    insert();
    insert();
    insert();
    insert();
    
    display();
    search();
    search();
return 0;
}

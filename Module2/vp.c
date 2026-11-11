#include <stdio.h>
#define MAX 100
char st[MAX];
int top=-1;
void push (char ch){
    st[++top]=ch ;
}
char pop(){
    char vec=st[top];
    top--;
    return vec;
}
int main(){
    char filename[100];
    printf("Enter the filename: ");
    scanf("%s",filename);
    FILE *fp=fopen(filename,"r");
    if (fp==NULL) {
        printf("Invalid_File Corrupted\n");
        return -1;
    }
    int ch ;
    int balanced=1;
    while((ch=fgetc(fp))!=EOF){
        if  ( ch =='(' || ch=='{' || ch=='['){
                 push(ch);
        }
        else if ( ch =='}' || ch==')' || ch==']'){
            if(top==-1){
                balanced=0;
                break;
            }
        
        
            char data=pop();
            if (( data =='(' && ch != ')' )||
                ( data =='[' && ch != ']' ) ||
                ( data =='{' && ch != '}' )){
                    balanced=0;
                    break;
                }
        }
    }
    
    fclose(fp);
    if(balanced==1 && top==-1){
        printf("Tru Valid Parenthesis\n");
    }else{
        printf("Invalid parenthesis\n");
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
struct details{
    char name[40];
   long long int phno;
};
int main(){
    FILE *a;
    a=fopen("Directory.txt","a+");
    if (a==NULL){
        printf("Error in openning the file");
        return 0;
    }
    struct details det[40];
    char name[40];
    long long int phno;
    int choice;
    
    
    while (1)
    {
    printf  ("1:    Add new friends\n");
    printf  ("2:    Display Contact  info\n");
    printf  ("3:    Exit\n");
    printf("Enter the Choice : ");
    scanf("%d",&choice);
       switch (choice)
       {
       case 1:
       int n;
       printf("Enter  the Number of details to be added:");
       scanf("%d",&n);
       for (int i=0;i<n;i++)
    {
            printf("Enter the name :");
            scanf("%s",det[i].name);
            printf("Enter the Phone No :");
            scanf("%lld",&det[i].phno);
            
            fprintf(a, "%s %lld\n", det[i].name, det[i].phno);
       }
      fflush(a);
        break;
       case 2:
      rewind(a);
            printf("----All the records present till now----\n");
            if(a!=NULL){
            while (fscanf(a,"%s %lld",name,&phno)!=EOF)
            {
               printf("Name: %s\t",name);
               printf("Phone No: %lld\n\n",phno);
            }
        }else{

        }printf("No Data till now!!\n");
            break;
        case 3:
        printf("Thank You--- Exiting...!\n");
        fclose(a);
        return 0;
        break;
       default:printf("Invalid Choice \n");
       return 0;
        break;
       } 
    }
    

   
    
   
    return 0;
}


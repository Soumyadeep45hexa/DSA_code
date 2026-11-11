#include <stdio.h>
#include <string.h>
struct Library
{
    char name[40];
    char author[30];
    char publisher[40];
    double price;
    char branch[50];
};
int main(){
    FILE *infile;
   struct Library lib[20];
    char name[40],aut[30],pub[40],bran[50];
    double mrp;
    
    
    while (1)
    {
    int choice;
        printf("1: Enter the Admin Portal: \n");
        printf("2:  Print the list of books supplied by the publication: \n");
        printf("3: Print the list of books if particular branch : \n");
        printf("4: Exit\n");
    printf("Enter the Choice :");
    scanf("%d",&choice);
    infile=fopen("infile.txt","a+");
        switch (choice)
        {
    case 1:
        int psu;
        printf("Password: ");
        scanf("%d",&psu);
        int psw=4567;
        if (psu==psw){
            printf("Entry Granted \n");
            int no;
            printf("Enter the Number  of books to be added:");
            scanf("%d",&no);
            for (int i=0;i<no;i++){
                printf("The name of the Book: ");
                    scanf("%s",name);
                printf("The name of the Author: ");
                    scanf("%s",aut);
                printf("The name of the Publisher : ");
                    scanf("%s",pub);
                printf("The Price : ");
                    scanf("%lf",&mrp);
                printf("The name of the Branch : ");
                    scanf("%s",bran);
                strcpy(lib[i].name,name);
                strcpy(lib[i].publisher,pub);
                strcpy(lib[i].author,aut);
                strcpy(lib[i].branch,bran);
                lib[i].price=mrp;
                fprintf(infile,"%s %s %s %s %lf\n",name,pub,aut,bran,mrp);
            }
        }else{
            printf("Invalid_Password Admin Access Denied....");
            return 0;
        }
        fflush(infile);
            break;
    case 2:
        rewind(infile);
        char publish[40];
            printf("Enter the Name of  the publisher: ");
            scanf("%s",publish);
            int flag=0;
        while (fscanf(infile,"%s %s %s %s %lf\n",name,pub,aut,bran,&mrp)!=EOF)
        
        {
            
            if (stricmp(pub,publish)==0){
                flag=1;
            printf("The books of the Publisher Name :%s \n",pub);
           printf("Name:%s\t Author:%s\t Branch:%s\t MRP:$%lf\n\n",name,aut,bran,mrp);
            }
        }if (!flag){
            printf("Publisher could  Not Be Found\n");
            return 0;
        }
        fflush(infile);
        fclose(infile);
        break;
        
    case 3:
        rewind(infile);
         char bra[40];
            printf("Enter the Name of  the Branch: ");
            scanf("%s",bra);
            int flag1=0;
        while (fscanf(infile,"%s %s %s %s %lf\n",name,pub,aut,bran,&mrp)!=EOF)
        {
           
            if (stricmp(bra,bran)==0){
                flag1=1;
            printf("The books belong to the Branch Name %s\n is:",bra);
            printf("Name:%s\t Author:%s\t Publication:%s\t MRP:$%lf\n\n",name,aut,pub,mrp);
            }
        }
        if (!flag1){
            printf("Branch could  Not Be Found\n");
            return 0;
        }
        fclose(infile);
        break;
    case 4:
     printf("Thank you...Exiting");
     return 0;
        default:
            break;
        }
        /* code */
    }
    
    
    return 0;
}


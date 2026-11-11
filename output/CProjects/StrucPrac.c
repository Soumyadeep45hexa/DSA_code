//#include <stdio.h>
// #include <string.h>
// struct Std{
//  char name[40];
//  int rn;
//  int age;
// int marks;
// };
// int main(){
//     int n;
//     int rollno,age,marks;
//     char name[40];
//     printf("Enter the Number of Students Entry needed to do: ");
//     scanf("%d",&n);
//     struct Std student[n];
//     for (int i=0;i<n;i++){
//         printf("Enter the Name of the Student: ");
//             scanf("%s",name);
//         printf("Enter the RollNo of the Student: ");
//             scanf("%d",&rollno);
//         printf("Enter the Age of the Student: ");
//             scanf("%d",&age);
//         printf("Enter the Marks: ");
//             scanf("%d",&marks);
//         student[i].age=age;
//         student[i].rn=rollno;
//         student[i].marks=marks;
//         strcpy(student[i].name,name);
//         }
//         printf("------The Students details------\n");
//     for (int i=0;i<n;i++){
//         printf("The name of student %d is: %s\n",i,student[i].name);
//         printf("The age of student %d is: %d\n",i,student[i].age);
//         printf("The rollno of student %d is: %d\n",i,student[i].rn);
//         printf("The marks of student %d is: %d\n",i,student[i].marks);
//         printf("\n");
//     }
//     return 0;
// }

#include <stdio.h>
#include <string.h>
int compare(char *str1,char *str2){
    while (*str1 && *str2)
    {if(*str1!=*str2){
        return 0;}
    
        str1++;
        str2++;
    }
    if (*str1=='\0' && *str2=='\0'){
        return 1;
    }else{
        return 0;
    }
    
}
int concatinate(char *str1,char *str2){
    char *strt= str1;
    while (*str1){
        str1++;
    }while (*str2){
        *str1=*str2;
        str1++;
        str2++;
    }
    *str2='\0';
   printf("%s\n",strt);
return 0;

}


int main(){
    char str1[10],str2[10];
    printf("Enter the first string: ");
    scanf("%s",str1);
    printf("Enter the second string: ");
    scanf("%s",str2);
    int ch;
    while(1){
        printf("1: Compare\n");
        printf("2: Concatinate\n");
        printf("3: Check for Palindrome\n");
        printf("Enter the choice: ");
        scanf("%d",&ch);
    switch (ch)
    {
    case 1:
        if ( compare(str1,str2)==0){
            printf("The strings are not same\n");
        }else{
            printf("Strings are  same\n");
        }
        break;
    case 2:
         concatinate(str1,str2);
        break;
  
    default:
        break;
    } 
    }
    
return 0;
}
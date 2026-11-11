// #include <stdio.h>

// struct Books
// {
//     char title[90];
//     char author[100];
//     float price;
//     int pages;
// };

// int main()
// {
//     struct Books book1={"The programming Basics ","Charles Bishop",567.99,400};
//     struct Books book2={"Mahabharat ","Valmiki",567.99,12045};
//     for (int i=0;i<2;i++){
//     printf("%s\n",book1.title);
//     printf("%s\n",booki.author);
//     printf("%f\n",booki.price );
//     printf("%d\n",book i.pages);
//     }
//     return 0;
// }
#include <stdio.h>
#include <string.h>

struct students {
    int Rollno;
    char Name[200];
    int Marks;
};

int main() {
    struct students student[4];  // array of 4 students
    int rollno, marksP,marksC,marksM,marks;
    char name[200];

    for (int i = 0; i <3; i++) {
        printf("Enter the RollNo: ");
        scanf("%d", &rollno);

        printf("Enter the Name: ");
        scanf("%s", name);

        printf("Enter the Marks of Physics : ");
        scanf("%d", &marksP);
        printf("Enter the Marks of Chemistry: ");
        scanf("%d", &marksC);
        printf("Enter the Marks of Maths : ");
        scanf("%d", &marksM);
marks =marksC+marksP+marksM;
        student[i].Rollno = rollno;
        strcpy(student[i].Name, name);
        student[i].Marks = marks;
    }

    printf("\n--- Student Details ---\n");
    for (int i = 0; i < 3; i++) {
        for (int j=0;j<3-i-1;j++){
            if (student[j+1].Marks>student[j].Marks){
                
               struct students temp=student[j+1];
                student[j+1]=student[j];
                student[j]=temp;
            }
        }
    }
    int sum=0;
        for (int i=0;i<3;i++){

            printf("RollNo: %d\n", student[i].Rollno);
            printf("Name: %s\n", student[i].Name);
            printf("Marks: %d\n\n", student[i].Marks);
            sum+=student[i].Marks;
        }
        
    printf("The sum of the marks of the students :%d\n",sum);


    return 0;
}
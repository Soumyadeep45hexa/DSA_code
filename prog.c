#include <stdio.h>
#include <stdlib.h>   // for rand() and srand()
struct employee
{
  int empno;
  char name[40];
  char dept[20];
  float BP,DA,HRA,GS;
};
int main(){
  FILE *infile,*outfile;
  struct employee emp,highestemp;
  highestemp.GS=0;
infile = fopen("C:\\Edtech\\SoumyaCodes\\myfile.txt", "r");
  if (infile==NULL){
    printf("Error openning the input file");
    fclose(infile);
    return 1;
  }
  outfile=fopen("Outfile.txt","w");
  if (outfile==NULL){
    printf("Error openning the output file");
    fclose(outfile);
    return 1;
  }
  while (fscanf(infile,"%d %s %s %f",&emp.empno,&emp.name,&emp.dept,&emp.BP)==4)
  {
    emp.DA = 0.60 * emp.BP;
emp.HRA = 0.27 * emp.BP;
emp.GS = emp.BP + emp.DA + emp.HRA;

if (emp.GS > highestemp.GS) {
    highestemp = emp;
}
  }
 fprintf(outfile, "Highest GS Employee:\nEmployee No: %d\nName: %s\nDept: %s\nGS: %.2f\n",
            highestemp.empno, highestemp.name, highestemp.dept, highestemp.GS);
            printf("The data is entered successfully in the outfile");
fclose(infile);
fclose(outfile);
return 0;
}

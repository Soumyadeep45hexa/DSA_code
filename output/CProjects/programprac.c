// #include <stdio.h>
// #include <math.h>
// int main(){
//     int a,b,c,D;
//     printf("Enter the values of a,b,c: ");
//     scanf("%d%d%d",&a,&b,&c);
  
//    if (b*b<4*a*c){
//      D=sqrt(4*a*c-(b*b));
//      printf("The complex solution is: (-%d+%di)/2*%d \n",b,D,a);
//       printf("The complex solution is: (-%d-%di)/2*%d ",b,D,a);
//    }else{
//       D=sqrt((b*b)-4*a*c);
//     float res1 =(-b+D)/2*a;
//      float res2 =(-b-D)/2*a;
//      printf("The real solution 1 is : %.2f",res1);
//      printf("The real solution 2 is : %.2f",res2);

//    }

// return 0;
// }
#include <stdio.h>
//#include&lt;stdlib.h&gt;
int strtoint(char *s){ //string to integer conversion
int val=0;
for(int i=0;*(s+i)!='\0';i++)
val=val*10+(*(s+i)-'0');
//subtracting ASCII of 0 from digit character&#39;s ASCII to extract the digit&#39;s value
return val;
}
int main(int cnt,char *arg[]){
if(cnt!=3){
printf("Improper number of argument!");
return -1;
}
int a,b;
//a=atoi(arg[1]);
//b=atoi(arg[2]);
a=strtoint(arg[1]);
b=strtoint(arg[2]);
printf("%d+%d=%d\n",a,b,(a+b));
return 0;
}
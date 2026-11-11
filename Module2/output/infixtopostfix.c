#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100
int st[MAX];
int top = -1;

void push(int ch)
{
    st[++top] = ch;
}
int pop()
{
    int val = st[top];
    top--;
    return val;
}
int prio(char ch)
{
    if (ch == '(')
        return 0;

    if (ch == '+' || ch == '-')
        return 1;

    if (ch == '*' || ch == '/')
        return 2;

    return 0;
}

int main()
{
    char chr[100];
    char pf[200];
    int p = 0;
    char *ch, x;

    printf("Enter the string: ");
    scanf("%s", chr);

    ch = chr;

    /* INFIX TO POSTFIX */

    while (*ch != '\0')
    {
        if (isdigit(*ch)){
            while(isdigit(*ch)){
                printf("%c",*ch);
                pf[p++]=*ch;
                
            ch++;
            }
            pf[p++]=' ';
            ch--;
        }
        else if (*ch == '(')
        {
            push(*ch);
        }
        else if (*ch==')'){
            while(top!=-1 && (x=pop())!='('){
                printf("%c",x);
                pf[p++]=x;
                pf[p++]=' ';
            }
        }
        else
        {
          while(top!=-1 && (prio(st[top]) >= prio(*ch))){
            x=pop();
            printf("%c",x);
            pf[p++]=x;
            pf[p++]=' ';
          }
          push(*ch);
        }

        ch++;
    }

    while (top != -1)
    {
        x = pop();

        printf("%c", x);

        pf[p++] = x;
        pf[p++] = ' ';
    }

    pf[p] = '\0';

    printf("\nThe required postfix: %s\n", pf);


    /* POSTFIX EVALUATION */

    top = -1;

    ch = pf;

    while (*ch != '\0')
    {
        if (isdigit(*ch))
        {
            int num = 0;

            while (isdigit(*ch))
            {
                num = num * 10 + (*ch - '0');
                ch++;
            }

            push(num);
        }

        else if (*ch == '+' ||
                 *ch == '-' ||
                 *ch == '*' ||
                 *ch == '/')
        {
            int b = pop();
            int a = pop();

            int result;

            switch (*ch)
            {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    result = a / b;
                    break;
            }

            push(result);
        }

        ch++;
    }

    printf("Result = %d\n", pop());

    return 0;
}
 
//Second Approach 
// #include <stdio.h>
// #include <ctype.h>
// #include<math.h>
// #define MAX 100
// char stack[MAX];
// int top = -1;
// void push(char x)
// {
//     stack[++top] = x;
// }
// char pop()
// {
//     return stack[top--];
// }

// int priority(char x)
// {
//     if (x == '+' || x == '-')
//     {
//         return 1;
//     }
//     if (x == '*' || x == '/')
//     {
//         return 2;
//     }
//     if (x == '^')
//     {
//         return 3;
//     }
//     return 0;
// }

// void infixtopostfix(char infix[], char postfix[])
// {
//     int i = 0, j = 0;
//     while (infix[i] != '\0')
//     {
//         if (infix[i] == ' ')
//         {
//             i++;
//         }
//         else if (isdigit(infix[i]))
//         {
//             while (isdigit(infix[i]))
//             {
//                 postfix[j++] = infix[i++];
//             }
//             postfix[j++] = ' ';
//         }
//         else if (infix[i] == '(')
//         {
//             push(infix[i++]);
//         }
//         else if (infix[i] == ')')
//         {
//             while (stack[top] != '(')
//             {
//                 postfix[j++] = pop();
//                 postfix[j++] = ' ';
//             }
//             pop();
//             i++;
//         }
//         else
//         {
//             while (top != -1 && priority(stack[top]) >= priority(infix[i]))
//             {
//                 postfix[j++] = pop();
//                 postfix[j++] = ' ';
//             }
//             push(infix[i++]);
//         }
//     }
//     while (top != -1)
//     {
//         postfix[j++] = pop();
//         postfix[j++] = ' ';
//     }
//     postfix[j] = '\0';
// }
// double evaluatepostfix(char postfix[])
// {
//     double s[MAX];
//     int t = -1;
//     int i = 0;
//     while (postfix[i] != '\0')
//     {
//         if (postfix[i] == ' ')
//         {
//             i++;
//         }
//         else if (isdigit(postfix[i]))
//         {
//             double num = 0;
//             while (isdigit(postfix[i]))
//             {
//                 num = num * 10 + postfix[i] - '0';
//                 i++;
//             }
//             s[++t] = num;
//         }
//         else
//         {
//             double b = s[t--];
//             double a = s[t--];
//             switch (postfix[i])
//             {
//             case '+':
//                 s[++t] = a + b;
//                 break;
//             case '-':
//                 s[++t] = a - b;
//                 break;
//             case '*':
//                 s[++t] = a * b;
//                 break;
//             case '/':
//                 s[++t] = a / b;
//                 break;
//             case '^':
//                 s[++t] = (int)pow(a,b);
//                 break;
//             }
//             i++;
//         }
//     }
//     return s[t];
// }
// int main()
// {
//     char infix[MAX], postfix[MAX];
//     printf("Enter the infix expression:- ");
//     scanf("%s",infix);
//     infixtopostfix(infix, postfix);
//     printf("The postfix is:- %s\n", postfix);
//     printf("The result:- %lf\n", evaluatepostfix(postfix));

//     return 0;
// }
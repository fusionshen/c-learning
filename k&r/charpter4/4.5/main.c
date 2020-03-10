#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include "calc.h"
#define MAXOP 100 /* max size of operand or operator */

double var[26]; /* A-Z's value, must upper */
double prev = 0.0; /* v: pre print val */

/*
** run code in terminnal cd "d:\self-learning\c-learning\k&r\charpter4\4.5\" ; if ($?) { gcc 'main.c' 'stack.c' 'getop.c' 'getch.c' 'calc.h'  -o 'main.exe' -Wall -g -O2 -static-libgcc -std=c11 -fexec-charset=GBK } ; if ($?) { &'.\main' }
** debugger 需要在.vscode/tasks.json中args中添加
** "${fileDirname}/getop.c",
** "${fileDirname}/getch.c",
** "${fileDirname}/stack.c",
** "${fileDirname}/calc.h",
*/
/* reverse polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    int pret = EOF; /* pre type */

    for (int i = 0; i < 26; i++)
        var[i] = 0.0;

    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            if (op2 != 0.0)
                push((int)pop() % (int)op2);
            else
                printf("error: zero mod\n");
            break;
        case 's': /* sin */
            push(sin(pop()));
            break;
        case 'e': /* exp */
            push(exp(pop()));
            break;
        case 'p': /* pow */
            op2 = pop();
            push(pow(pop(), op2));
            break;
        case '\n':
            if (!isempty())
            {
                prev = pop();
                printf("\t%.8g\n", prev);
            }
            break;
        case '=':
            if(isupper(pret)) {
                pop();
                var[pret - 'A'] = pop();
                printf("\t%c = %g\n", pret, var[pret - 'A']);
            }
            else
                printf("error: wrong variable\n");
            break;
        default:
            if (isalpha(type)) /* A-Z & v */
            {
                if (type == 'v')
                    push(prev);
                else if (isupper(type))
                    push(var[type - 'A']);
                else
                    printf("error: wrong variable\n");
            }
            else
                printf("error: unknown command %s\n", s);
            break;
        }
        pret = type;
    }
    return 0;
}

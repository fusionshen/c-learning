#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXLINE 1000
void push(double);
double pop(void);
/*
* 编写程序expr，以计算从命令行输入的逆波兰表达式的值，其中每个运算符或操作数
* 用一个单独的参数表示。例如，命令
* expr 2 3 4 + *
* 将表达式2 x (3 + 4)的值
*/
int main(int argc, char *argv[])
{
    int c;
    double op2;

    while(--argc > 0 && (c = **++argv))
    {
        //printf("%s\n", *argv);
        // 判断每个参数第一个字符，如果是数字就有可能是数值，反之，可能是操作符
        if (isdigit(c))
            push(atof(*argv));
        else
            switch (c)
            {
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
            default:
                printf("error: unknown command %c\n", c);
                break;
            }
    }
    printf("\t%.8g\n", pop());
    return 0;

}

#define MAXVAL 100 /* maximun depth of val stack */

int sp = 0; /* next free stack positon */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

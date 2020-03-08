#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int isempty(void);

int getch(void);
void ungetch(int);

char buf;
double var[26]; /* A-Z's value, must upper */
double prev = 0.0; /* v: pre print val */

/* 假定最多只能压回一个字符。请相应得修改getch与ungetcha这两个函数 */
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

/* isempty: stack is empty */
int isempty(void)
{
    return sp == 0;
}

/* getop: get next character or numberic operand */
/* 增加负数情况 */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c; /* not a number */
    i = 0;
    if (c == '-') /* maybe a number */
        s[++i] = c = getch();
    if (isdigit(c))  /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part*/
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    if (s[i-1] == '-')
        return '-'; /* just - */
    return NUMBER;
}

int getch(void) /* get a (prossibly pushed-back) charactor */
{
    if (buf != 0) {
        int c = buf;
        printf("取回%c\n", c);
        buf = 0;
        return c;
    }
    else
        return getchar();

}

void ungetch(int c) /* push character back on input */
{
    if (buf != 0)
        printf("error: too many\n");
    else {
        printf("存入%c\n", c);
        buf = c;
    }
}


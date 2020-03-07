#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <string.h>

#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define COMMAND '1'
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
void printstack(void);
void printtop(void);
void copytop(void);
void switchtop(void);
void clear(void);

int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/*
** 在栈操作中添加几个命令，分别用于不在弹出元素的情况下打印栈顶元素；
** 复制栈顶元素：交换栈顶两个元素的值。另外增加一个命令用于清空栈。
** &10 2
** stack:10        2
** &print
** top value from stack is 2
** stack:10        2
** &copy
** stack:10        2       2
** &3
** stack:10        2       2       3
** &switch
** stack:10        2       3       2
** &clear
** cleaned done
** error: stack empty
*/
int main()
{
    int type;
    char s[MAXOP];
    printf("Type number push into stack, spaced by spaces or tables, end by key enter, like 10.1 -3 18.\n");
    printf("Command-print: print the top value from stack.\n");
    printf("Command-copy: copy the top value from stack.\n");
    printf("Command-switch: switch the top 2 values from stack.\n");
    printf("Command-clear: clear stack.\n");
    printf("NOW! ENJOY!\n");
    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case COMMAND:
            if (!strcmp(s,"print"))
                printtop();
            else if (!strcmp(s,"copy"))
                copytop();
            else if (!strcmp(s,"switch"))
                switchtop();
            else if (!strcmp(s,"clear"))
                clear();
            else
                printf("error: unknown command %s\n", s);
            break;
        case '\n':
            printstack();
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
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

/* printstack: print stach */
void printstack(void)
{
    if (sp > 0) {
        printf("stack:");
        for (int i = 0; i < sp; i++)
            printf("%g  ", val[i]);
        printf("\n");
    }
    else
        printf("error: stack empty\n");
}

/* printtop: print top value from stach */
void printtop(void)
{
    if (sp > 0)
        printf("top value from stack is %g\n", val[sp-1]);
    else
        printf("error: stack empty\n");
}

/* copytop: copy top value from stach */
void copytop(void)
{
    if (sp > 0) {
        double d = val[sp-1];
        val[sp++] = d;
        //printstack();
    }
    else
        printf("error: stack empty\n");
}

/* switchtop: switch the top 2 value from stach */
void switchtop(void)
{
    if(sp > 1) {
        double d = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = d;
        //printstack();
    }

}

/* clear: clear stack */
void clear(void)
{
    sp = 0;
    printf("cleaned done\n");
}


/* getop: get next character or numberic operand */
/* 增加command */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (c == '\n' || c == EOF)
        return c; /* breakpoints */
    i = 0;
    if (c == '-') /* maybe a number */
        s[++i] = c = getch();
    if (isalpha(c)) /* collect command */
        while (isalpha(s[++i] = c = getch()))
            ;
    if (isdigit(c))  /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') /* collect fraction part*/
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);

    if (isalpha(s[i-1]))
        return COMMAND;

    if (s[i-1] == '-')
        return '-'; /* just - */

    return NUMBER;
}

int getch(void) /* get a (prossibly pushed-back) charactor */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZ)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

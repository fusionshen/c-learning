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
void sort(void);

int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/*
** 快速排序
7 3 2 8 9 10 11
stack:7  3  2  8  9  10  11
sort
stack:2  3  7  8  9  10  11
clear
cleaned done
error: stack empty
sort
error: stack empty
sort
error: stack empty
7
stack:7
sort
stack:7
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
    printf("Command-sort: sort stack.\n");
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
            else if (!strcmp(s,"sort"))
                sort();
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

/* sort: sort stack */
void sort(void)
{
    void qqsort(double v[], int left, int right);
    qqsort(val, 0, sp - 1);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qqsort(double v[], int left, int right)
{
    int i, last;
    void swap(double v[], int i, int j);
    if (left >= right) /* do nothing if array contains */
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (v[i] < v[left])
            swap(v, ++last, i);
    swap(v, left, last);
    qqsort(v, left, last - 1);
    qqsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(double v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
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

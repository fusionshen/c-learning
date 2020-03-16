#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100
#define SIZE 100

int getch(void);
void ungetch(int);

/*
** 在上面的例子中，如果符号+或-的后面紧跟的不是数字，getint函数将把符号视为数字0的有效表达方式。
** 修改该函数，将这种形式的+或-符号重新写回到输入流中。
*/
int main()
{
    int n, array[SIZE], getint(int *);
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    printf("array:");
    for (int i = 0; i < n; i++)
        printf("%d ", array[i]);
}

/* getint: get next integer from input int *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c!= '+' && c !='-') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    int temp;
    if ((temp = c) == '+' || (temp = c) == '-') {
        c = getch();
        if(!isdigit(c))
            ungetch(temp);
        while (!isdigit(c = getch())) /* skip no numberic */
            ;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if ( c != EOF)
        ungetch(c);
    return c;
}

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

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
